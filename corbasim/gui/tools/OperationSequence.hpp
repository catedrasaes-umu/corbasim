// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * OperationSequence.hpp
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

#ifndef CORBASIM_GUI_OPERATIONSEQUENCE_HPP
#define CORBASIM_GUI_OPERATIONSEQUENCE_HPP

#include <corbasim/gui/export.hpp>
#include <corbasim/gui/tools/AbstractSequenceTool.hpp>

#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QDialogButtonBox>

namespace corbasim
{
namespace gui
{

class OperationInputForm;

class CORBASIM_GUI_DECLSPEC OperationSequenceItem :
    public AbstractSequenceItem
{
    Q_OBJECT
public:
    OperationSequenceItem(Objref_ptr object,
            OperationDescriptor_ptr operaation,
            QWidget * parent = 0);
    virtual ~OperationSequenceItem();

public slots:

    void showDetails(bool show);

signals:

    /**
     * @brief Used for sending a request.
     *
     * Will be connected to an object reference.
     *
     * @param Request_ptr The request pointer
     */
    void sendRequest(Request_ptr);


private slots:

    void sendClicked();

    void sendStored();
    void startStopChecked(bool = true);
    void storeRequest();
    void stopTimer();

protected:

    void doSave(QVariantMap& map);
    void doLoad(const QVariantMap& map);

    OperationInputForm * m_dlg;

    // Periodic
    QSpinBox * m_sbPeriod;
    QSpinBox * m_sbTimes;
    QCheckBox * m_cbUseStored;
    QDialogButtonBox * m_buttonBox;
    QPushButton * m_pbStartStop;
    QPushButton * m_pbUpdate;

    QTimer m_timer;
    int m_currentPeriodicRequest;
    event::request_ptr m_storedRequest;
    // End periodic
};

class CORBASIM_GUI_DECLSPEC OperationSequenceTool :
    public AbstractSequenceTool
{
    Q_OBJECT
public:
    OperationSequenceTool(QWidget * parent = 0);
    virtual ~OperationSequenceTool();

protected:

    AbstractSequenceItem * createAbstractItem(
            Objref_ptr object,
            OperationDescriptor_ptr op);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_OPERATIONSEQUENCE_HPP */

