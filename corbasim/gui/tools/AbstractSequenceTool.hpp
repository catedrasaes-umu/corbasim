// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AbstractSequence.hpp
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

#ifndef CORBASIM_GUI_ABSTACTSEQUENCETOOL_HPP
#define CORBASIM_GUI_ABSTACTSEQUENCETOOL_HPP

#include <QtGui>
#include <QLineEdit>
#include <QPushButton>
#include <corbasim/qt/CustomLayouts.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/item/InstanceModel.hpp>
#include <corbasim/gui/tools/AbstractTool.hpp>
#include <corbasim/qt/SortableGroup.hpp>

namespace corbasim
{
namespace gui
{

class OperationsView;

class CORBASIM_GUI_DECLSPEC AbstractSequenceItem :
    public qt::AbstractItemFrame
{
    Q_OBJECT
protected:

    AbstractSequenceItem(Objref_ptr object,
            OperationDescriptor_ptr operation,
            QWidget * parent = 0);

public:

    virtual ~AbstractSequenceItem();

    ObjectId objectId() const;
    Objref_ptr object() const;
    OperationDescriptor_ptr operation() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    virtual void showDetails(bool show) = 0;

signals:

    void doDelete();
    void up();
    void down();

protected:

    virtual void doSave(QVariantMap& settings) = 0;
    virtual void doLoad(const QVariantMap& settings) = 0;

    Objref_ptr m_object;
    OperationDescriptor_ptr m_operation;
    QLineEdit * m_title;
};

class CORBASIM_GUI_DECLSPEC AbstractSequence : public QWidget
{
    Q_OBJECT
public:
    AbstractSequence(const QString& name, QWidget * parent = 0);
    virtual ~AbstractSequence();

    const QString& getName() const;
    void setName(const QString& name);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    /**
     * @brief Remove all the items related to an instance.
     *
     * @param id The identifier of the instance.
     */
    void removeInstance(ObjectId id);

public slots:

    void appendItem(AbstractSequenceItem * item);
    void forgetItem(AbstractSequenceItem * item);

    void deleteItem(AbstractSequenceItem * item);
    void moveUpItem(AbstractSequenceItem * item);
    void moveDownItem(AbstractSequenceItem * item);

    void stop();

private slots:

    void startOrStopAll(bool checked);

    void deleteItem();
    void moveUpItem();
    void moveDownItem();

signals:

    void modified();

protected:

    /**
     * @brief The sequence name.
     */
    QString m_name;

    qt::CustomVLayout * m_layout;

    typedef QList< AbstractSequenceItem * > items_t;
    items_t m_items;

    QScrollArea * m_scroll;

    QPushButton * m_stBtn;
};

/**
 * @brief Abstraction for operation sequences tool.
 *
 * It is composed of a QTabWidget with a tab per sequence.
 * Every sequence consists in an ordered set of AbstratSequenceItem
 * instances.
 */
class CORBASIM_GUI_DECLSPEC AbstractSequenceTool :
    public AbstractTool
{
    Q_OBJECT
public:
    AbstractSequenceTool(QWidget * parent = 0);
    virtual ~AbstractSequenceTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void registerInstance(Objref_ptr object);
    void unregisterInstance(ObjectId id);

    /**
     * @brief Append a new item to the current sequence. It uses
     * createAbstractItem to create the item.
     *
     * If no current creates a new sequence.
     *
     * @param object
     * @param op
     *
     * @return The new item or NULL if invalid object or operation.
     */
    AbstractSequenceItem * appendAbstractItem(
            Objref_ptr object,
            OperationDescriptor_ptr op);

    AbstractSequence* createSequence();

    void closeSequence(int idx);

    void showContextMenu(const QPoint& pos);

    void saveCurrentSequence();
    void loadSequence();

    // Current item slots
    void saveCurrentItem();
    void loadCurrentItem();

    void duplicateCurrentItem();
    void deleteCurrentItem();

    void moveCurrentItemTo(int idx);
    // End current item slots

    void setTreeVisible(bool visible);

    /**
     * @brief Displays a dialog for setting the current sequence name.
     */
    void showSetName();

    /**
     * @brief Stop all the sequences.
     */
    void stop();

private slots:

    void sequenceModified();

protected:

    /**
     * @brief Must create an instance of a subclass of AbstractSequenceItem.
     *
     * @param object The associated instance.
     * @param op The associated operation.
     *
     * @return The created instance or NULL if invalid object or operation.
     */
    virtual AbstractSequenceItem * createAbstractItem(
            Objref_ptr object,
            OperationDescriptor_ptr op) = 0;

    void regenerateMoveTo(int idx);

    InstanceModel m_model;

    OperationsView * m_view;
    QTabWidget * m_tabs;

    typedef QList< AbstractSequence * > sequences_t;
    sequences_t m_sequences;

    QMenu * m_menu;
    QMenu * m_menuCurrentItem;
    QMenu * m_menuCurrentItemMoveTo;
    QSignalMapper * m_moveToSignalMapper;

    QString m_filter;
    QString m_extension;

    /**
     * @brief Current item.
     */
    AbstractSequenceItem * m_currentItem;

    /**
     * @brief Only enabled when a current item.
     */
    QList< QAction * > m_currentItemActions;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_ABSTACTSEQUENCETOOL_HPP */

