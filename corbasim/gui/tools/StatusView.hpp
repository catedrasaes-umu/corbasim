// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * StatusView.hpp
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

#ifndef CORBASIM_GUI_TOOLS_STATUSVIEW_HPP
#define CORBASIM_GUI_TOOLS_STATUSVIEW_HPP

#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <QtGui>

namespace corbasim 
{
namespace qt 
{
class Status;
} // namespace qt

namespace gui 
{

class StatusViewItem : public QWidget
{
    Q_OBJECT
public:
    StatusViewItem(Objref_ptr objref, QWidget * parent = 0);
    ~StatusViewItem();

public slots:

    void update();

protected:
    Objref_ptr m_objref;
    qt::Status * m_status;
};

class StatusView : public QWidget
{
    Q_OBJECT
public:
    StatusView(QWidget * parent = 0);
    ~StatusView();

public slots:

    void registerInstance(Objref_ptr objref);

    void unregisterInstance(ObjectId id);

protected:

    void reallocate(int width);
    
    void resizeEvent(QResizeEvent * event);

    typedef QMap< ObjectId, StatusViewItem * > items_t;
    items_t m_items;

    QGridLayout * m_layout;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_TOOLS_STATUSVIEW_HPP */

