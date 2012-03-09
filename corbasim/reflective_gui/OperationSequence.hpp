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

#ifndef CORBASIM_REFLECTIVE_GUI_OPERATIONSEQUENCE_HPP
#define CORBASIM_REFLECTIVE_GUI_OPERATIONSEQUENCE_HPP

#include <QtGui>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/qt/types.hpp>
#include <corbasim/qt/CustomLayouts.hpp>
#include <corbasim/reflective_gui/export.hpp>

#include <ostream>

namespace corbasim 
{
namespace reflective_gui 
{

class OperationInputForm;

class CORBASIM_REFLECTIVE_GUI_DECLSPEC OperationSequenceItem : 
    public QFrame
{
    Q_OBJECT
public:
    OperationSequenceItem(const QString& id,
            OperationInputForm * dlg,
            QWidget * parent = 0);
    virtual ~OperationSequenceItem();

    const QString& getObjrefId() const;
    const char * getOperationName() const;

    void save(QSettings& settings);
    void load(QSettings& settings);

signals:

    void sendRequest(QString id, corbasim::event::request_ptr);

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

class CORBASIM_REFLECTIVE_GUI_DECLSPEC OperationSequence : public QWidget
{
    Q_OBJECT
public:
    OperationSequence(const QString& name, QWidget * parent = 0);
    virtual ~OperationSequence();

    const QString& getName() const;

    void save(QSettings& settings);
    void load(QSettings& settings);

public slots:

    void appendItem(OperationSequenceItem * item);

    void deleteItem(OperationSequenceItem * item);
    void moveUpItem(OperationSequenceItem * item);
    void moveDownItem(OperationSequenceItem * item);

private slots:

    void deleteItem();
    void moveUpItem();
    void moveDownItem();

signals:

    void modified();

protected:

    QString m_name;

    qt::CustomVLayout * m_layout;
    QList< OperationSequenceItem * > m_items;
    QScrollArea * m_scroll;

};

class CORBASIM_REFLECTIVE_GUI_DECLSPEC OperationsView : public QTreeView
{
    Q_OBJECT
public:
    OperationsView(QWidget * parent = 0);
    virtual ~OperationsView();
};

class CORBASIM_REFLECTIVE_GUI_DECLSPEC OperationModel : 
    public QStandardItemModel
{
    Q_OBJECT

public:
    OperationModel(QObject *parent = 0);
    virtual ~OperationModel();

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * factory);

    void unregisterInstance(const QString& name);

private slots:

    void doubleClicked(const QModelIndex& index);

signals:
    
    void selectedOperation(QString id, 
            const corbasim::core::operation_reflective_base * op);

protected:

    struct FirstLevelItem
    {
        QString name;
        core::interface_reflective_base const * factory;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

class CORBASIM_REFLECTIVE_GUI_DECLSPEC OperationSequenceTool : 
    public QWidget
{
    Q_OBJECT
public:
    OperationSequenceTool(QWidget * parent = 0);
    virtual ~OperationSequenceTool();

    void save(QSettings& settings);
    void load(QSettings& settings);

public slots:

    void objrefCreated(const QString& id,
        const corbasim::core::interface_reflective_base * factory);
    void objrefDeleted(const QString& id);

    void appendOperation(const QString& id, 
            const corbasim::core::operation_reflective_base * op);

    OperationSequence* createSequence();

    void closeSequence(int idx);

    void showContextMenu(const QPoint& pos);

    void saveCurrentSequence();
    void loadSequence();

signals:

    void sendRequest(QString id, corbasim::event::request_ptr);

private slots:
    
    void slotSendRequest(const QString& id, 
            corbasim::event::request_ptr);

    void sequenceModified();

protected:

    OperationModel m_model;

    OperationsView * m_view;
    QTabWidget * m_tabs;
    QList< OperationSequence * > m_sequences;

    QMenu * m_menu;
};

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_OPERATIONSEQUENCE_HPP */

