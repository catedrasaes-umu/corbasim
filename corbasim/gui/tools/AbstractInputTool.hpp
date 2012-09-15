// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AbstractInputTool.hpp
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

#ifndef CORBASIM_GUI_ABSTRACTINPUTTOOL_HPP
#define CORBASIM_GUI_ABSTRACTINPUTTOOL_HPP

#include <QtGui>
#include <corbasim/gui/item/ParametersModel.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>
#include <map>

#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace qt 
{
class SortableGroup;
class SortableGroupItem;
} // namespace qt

namespace gui
{

class CORBASIM_GUI_DECLSPEC AbstractInputItem : public QWidget
{
    Q_OBJECT
protected:

    AbstractInputItem(Objref_ptr objref,
            OperationDescriptor_ptr reflective,
            const QList< int >& path, 
            QWidget * parent = 0);

public:

    virtual ~AbstractInputItem();

    OperationDescriptor_ptr getReflective() const;

    inline const QList< int >& getPath() const
    {
        return m_path;
    }

    inline RequestProcessor_ptr getProcessor() const
    {
        return m_processor;
    }

    void save(QVariant& settings);
    void load(const QVariant& settings);

    virtual void start();
    virtual void reset();

signals:

    void addProcessor(RequestProcessor_ptr);
    void removeProcessor(RequestProcessor_ptr);

protected:

    RequestProcessor_ptr m_processor;

    Objref_ptr m_objref;
    OperationDescriptor_ptr m_reflective;
    const QList< int > m_path;
};

class CORBASIM_GUI_DECLSPEC AbstractInputTool : public QWidget
{
    Q_OBJECT
public:

    AbstractInputTool(QWidget * parent = 0);
    virtual ~AbstractInputTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void setModel(ParametersModel * model);

protected:
    
    virtual AbstractInputItem * createItem(
            Objref_ptr objref, 
            OperationDescriptor_ptr reflective,
            const QList< int >& path) = 0;

    virtual ParametersModel * createModel();

public slots:

    void clear();

    void registerInstance(Objref_ptr objref);

    void unregisterInstance(ObjectId id);

    AbstractInputItem * createAbstractInputItem(const QString& id, 
            InterfaceDescriptor_ptr reflective,
            const QList< int >& path);

    void deleteAbstractInputItem(const QString& id, 
            InterfaceDescriptor_ptr reflective,
            const QList< int >& path);

protected slots:

    void deleteRequested(corbasim::qt::SortableGroupItem *);

protected:

    ObjrefRepository m_instances;

    ParametersModel * m_model;
    qt::SortableGroup * m_group;

    typedef std::pair< QString, tag_t > key_t;
    typedef std::map< key_t, QList< AbstractInputItem * > > map_t;
    typedef std::map< AbstractInputItem *, key_t > inverse_map_t;

    map_t m_map;
    inverse_map_t m_inverse_map;

    QTreeView * m_view;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_ABSTRACTINPUTTOOL_HPP */
