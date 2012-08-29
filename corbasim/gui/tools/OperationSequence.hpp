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

#include <QtGui>
#include <corbasim/qt/CustomLayouts.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/item/InstanceModel.hpp>
#include <corbasim/gui/item/OperationsView.hpp>

#include <ostream>

namespace corbasim 
{
namespace gui 
{

class OperationInputForm;

class CORBASIM_GUI_DECLSPEC OperationSequenceItem : 
    public QFrame
{
    Q_OBJECT
public:
    OperationSequenceItem(const QString& id,
            OperationInputForm * dlg,
            QWidget * parent = 0);
    virtual ~OperationSequenceItem();

    const QString& getObjrefId() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

signals:

    void sendRequest(Request_ptr);

    void doDelete();
    void up();
    void down();

private slots:

    void deleteClicked();
    void upClicked();
    void downClicked();

    void sendClicked();

    void sendStored(); 
	void startStopChecked(bool = true); 
    void storeRequest();
    void stopTimer();

protected:

    const QString m_id;
    OperationInputForm * m_dlg;
    QLayout * m_layout;
    QLineEdit * m_title;

    // Periodic
    QSpinBox * m_sbPeriod;
    QSpinBox * m_sbTimes;
    QCheckBox * m_cbUseStored;
    QPushButton * m_pbStartStop;
    QPushButton * m_pbUpdate;

    QTimer m_timer;
    int m_currentPeriodicRequest;
    event::request_ptr m_storedRequest;
    // End periodic
};

class CORBASIM_GUI_DECLSPEC OperationSequence : public QWidget
{
    Q_OBJECT
public:
    OperationSequence(const QString& name, QWidget * parent = 0);
    virtual ~OperationSequence();

    const QString& getName() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void removeInstance(const QString& name);

public slots:

    void appendItem(OperationSequenceItem * item);

    void deleteItem(OperationSequenceItem * item);
    void moveUpItem(OperationSequenceItem * item);
    void moveDownItem(OperationSequenceItem * item);

private slots:

    void startOrStopAll(bool checked);

    void deleteItem();
    void moveUpItem();
    void moveDownItem();

signals:

    void modified();

protected:

    QString m_name;

    qt::CustomVLayout * m_layout;
    typedef QList< OperationSequenceItem * > items_t;
    items_t m_items;
    QScrollArea * m_scroll;

};

class CORBASIM_GUI_DECLSPEC OperationSequenceTool : 
    public QWidget
{
    Q_OBJECT
public:
    OperationSequenceTool(QWidget * parent = 0);
    virtual ~OperationSequenceTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void objrefCreated(Objref_ptr object);
    void objrefDeleted(ObjectId id);

    OperationSequenceItem * appendOperation(
            const QString& id, 
            OperationDescriptor_ptr op);

    OperationSequence* createSequence();

    void closeSequence(int idx);

    void showContextMenu(const QPoint& pos);

    void saveCurrentSequence();
    void loadSequence();

private slots:

    void sequenceModified();

protected:

    ObjrefRepository m_instances;

    InstanceModel m_model;

    OperationsView * m_view;
    QTabWidget * m_tabs;

    typedef QList< OperationSequence * > sequences_t;
    sequences_t m_sequences;

    QMenu * m_menu;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_OPERATIONSEQUENCE_HPP */

