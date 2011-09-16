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

#ifndef CORBASIM_QT_REQUESTDIALOG_HPP
#define CORBASIM_QT_REQUESTDIALOG_HPP

#include <QtGui>
#include <corbasim/event.hpp>

Q_DECLARE_METATYPE(corbasim::event::request_ptr)

// fwd
namespace corbasim 
{
namespace dialogs 
{
struct input_base;
} // namespace dialogs
} // namespace corbasim

namespace corbasim 
{
namespace qt 
{

class RequestDialog : public QDialog
{
    Q_OBJECT
public:
        
    /**
     * @brief 
     *
     * @param dlg Asume su propiedad.
     * @param parent
     */
    RequestDialog(dialogs::input_base* dlg, QWidget * parent = 0);
    virtual ~RequestDialog();

public slots:
	void sendClicked(); 
	void sendStored(); 
	void startStopChecked(bool = true); 
    void storeRequest();
    void stopTimer();

signals:
    void sendRequest(corbasim::event::request_ptr);

protected:
    dialogs::input_base * m_dlg;

    QSpinBox * m_sbPeriod;
    QSpinBox * m_sbTimes;
    QCheckBox * m_cbUseStored;
    QPushButton * m_pbStartStop;
    QPushButton * m_pbUpdate;

    QTimer m_timer;

    int m_currentPeriodicRequest;

    event::request_ptr m_storedRequest;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_REQUESTDIALOG_HPP */

