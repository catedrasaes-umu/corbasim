// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ValueViewerTool.hpp
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

#ifndef CORBASIM_GUI_VALUEVIEWERTOOL_HPP
#define CORBASIM_GUI_VALUEVIEWERTOOL_HPP

#include <QtGui>
#include <QDateTimeEdit>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/tools/AbstractInputTool.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC ValueViewer : public AbstractInputItem
{
    Q_OBJECT
public:

    ValueViewer(Objref_ptr objref,
            OperationDescriptor_ptr reflective,
            const QList< int >& path,
            QWidget * parent = 0);
    virtual ~ValueViewer();

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void start();

public slots:

    void appendValue(Request_ptr,
            TypeDescriptor_ptr,
            Holder);

protected:

    QDateTimeEdit * m_date;
    QWidget * m_widget;
};

class CORBASIM_GUI_DECLSPEC ValueViewerTool : public AbstractInputTool
{
    Q_OBJECT
public:

    ValueViewerTool(QWidget * parent = 0);
    virtual ~ValueViewerTool();

protected:

    AbstractInputItem * createItem(
            Objref_ptr objref,
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_VALUEVIEWERTOOL_HPP */
