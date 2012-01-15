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

#ifndef CORBASIM_QT_OPERATIONSEQUENCE_HPP
#define CORBASIM_QT_OPERATIONSEQUENCE_HPP

#include <QtGui>
#include <corbasim/qt/types.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>

#include <ostream>

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

class OperationSequenceItem : public QFrame
{
    Q_OBJECT
public:
    OperationSequenceItem(const QString& id,
            dialogs::input_base* dlg,
            QWidget * parent = 0);
    virtual ~OperationSequenceItem();

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

protected:

    const QString m_id;
    dialogs::input_base* m_dlg;
    QLayout * m_layout;
};

class CustomLayout : public QVBoxLayout
{
    Q_OBJECT
public:

    CustomLayout(QWidget * parent = 0) :
        QVBoxLayout(parent)
    {
    }

    virtual ~CustomLayout()
    {
    }

public slots:

    void insertItem(int idx, QLayoutItem * item)
    {
        QBoxLayout::insertItem(idx, item);
    }
};

class OperationSequence : public QWidget
{
    Q_OBJECT
public:
    OperationSequence(QWidget * parent = 0);
    virtual ~OperationSequence();

public slots:

    void appendItem(OperationSequenceItem * item);

    void deleteItem(OperationSequenceItem * item);
    void moveUpItem(OperationSequenceItem * item);
    void moveDownItem(OperationSequenceItem * item);

private slots:

    void deleteItem();
    void moveUpItem();
    void moveDownItem();

protected:

    CustomLayout * m_layout;
    QList< OperationSequenceItem * > m_items;
};

class OperationsView : public QTreeView
{
    Q_OBJECT
public:
    OperationsView(QWidget * parent = 0);
    virtual ~OperationsView();
};

class OperationModel : public QStandardItemModel
{
    Q_OBJECT

public:
    OperationModel(QObject *parent = 0);
    virtual ~OperationModel();

public slots:

    void registerInstance(const QString& name,
            gui::gui_factory_base const * factory);

    void unregisterInstance(const QString& name);

private slots:

    void doubleClicked(const QModelIndex& index);

signals:
    
    void selectedOperation(QString id, 
            const corbasim::gui::operation_factory_base * op);

protected:

    struct FirstLevelItem
    {
        QString name;
        gui::gui_factory_base const * factory;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

class OperationSequenceTool : public QWidget
{
    Q_OBJECT
public:
    OperationSequenceTool(QWidget * parent = 0);
    virtual ~OperationSequenceTool();

public slots:

    void objrefCreated(const QString& id,
        const corbasim::gui::gui_factory_base * factory);
    void objrefDeleted(const QString& id);

    void appendOperation(const QString& id, 
            const corbasim::gui::operation_factory_base * op);

    OperationSequence* createSequence();

    void closeSequence(int idx);

signals:

    void sendRequest(QString id, corbasim::event::request_ptr);

private slots:
    
    void slotSendRequest(const QString& id, 
            corbasim::event::request_ptr);

protected:

    OperationModel m_model;

    OperationsView * m_view;
    QTabWidget * m_tabs;
    QList< OperationSequence * > m_sequences;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_OPERATIONSEQUENCE_HPP */

