// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SenderSequence.hpp
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

#ifndef CORBASIM_GUI_SENDERSEQUENCE_HPP
#define CORBASIM_GUI_SENDERSEQUENCE_HPP

#include <QtGui>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/qt/CustomLayouts.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/item/InstanceModel.hpp>
#include <corbasim/gui/item/OperationsView.hpp>

#include <ostream>

namespace corbasim 
{
namespace gui 
{

class OperationSender;

class CORBASIM_GUI_DECLSPEC SenderSequenceItem : 
    public QFrame
{
    Q_OBJECT
public:
    SenderSequenceItem(OperationSender * dlg,
            QWidget * parent = 0);
    virtual ~SenderSequenceItem();

    ObjectId objectId() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

signals:

    void doDelete();
    void up();
    void down();

protected:

    OperationSender * m_dlg;
    QLineEdit * m_title;
};

class CORBASIM_GUI_DECLSPEC SenderSequence : public QWidget
{
    Q_OBJECT
public:
    SenderSequence(const QString& name, QWidget * parent = 0);
    virtual ~SenderSequence();

    const QString& getName() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void removeItems(ObjectId id);

    void appendItem(SenderSequenceItem * item);

    void deleteItem(SenderSequenceItem * item);
    void moveUpItem(SenderSequenceItem * item);
    void moveDownItem(SenderSequenceItem * item);

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

    typedef QList< SenderSequenceItem * > items_t;
    items_t m_items;

    QScrollArea * m_scroll;

};

class CORBASIM_GUI_DECLSPEC SenderSequenceTool : 
    public QWidget
{
    Q_OBJECT
public:
    SenderSequenceTool(QWidget * parent = 0);
    virtual ~SenderSequenceTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void objrefCreated(Objref_ptr object);
    void objrefDeleted(ObjectId id);

    SenderSequenceItem * appendOperation(Objref_ptr instance, 
            OperationDescriptor_ptr op);

    SenderSequence* createSequence();

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

    typedef QList< SenderSequence * > sequences_t;
    sequences_t m_sequences;

    QMenu * m_menu;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SENDERSEQUENCE_HPP */

