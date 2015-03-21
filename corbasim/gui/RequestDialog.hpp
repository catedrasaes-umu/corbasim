// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestDialog.hpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * CORBASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORBASIM_GUI_REQUESTDIALOG_HPP
#define CORBASIM_GUI_REQUESTDIALOG_HPP

#include <QDialog>
#include <QTimer>
#include <QScrollArea>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>

// fwd
class QSpinBox;
class QCheckBox;
class QPushButton;
class QTabWidget;
class QPlainTextEdit;

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC RequestDialog :
    public QDialog
{
    Q_OBJECT
public:

    RequestDialog(
            OperationDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~RequestDialog();

    OperationDescriptor_ptr getReflective() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void sendClicked();
    void sendStored();
    void startStopChecked(bool = true);
    void storeRequest();
    void stopTimer();

signals:

    void sendRequest(Request_ptr);

protected:

    OperationInputForm * m_dlg;

    QScrollArea * m_scroll;

    QSpinBox * m_sbPeriod;
    QSpinBox * m_sbTimes;
    QCheckBox * m_cbUseStored;
    QPushButton * m_pbStartStop;
    QPushButton * m_pbUpdate;

    QTimer m_timer;

    int m_currentPeriodicRequest;

    Request_ptr m_storedRequest;

    void hideEvent(QHideEvent * event);

    void resizeEvent(QResizeEvent * event);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_REQUESTDIALOG_HPP */

