// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * PlotTool.hpp
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

#ifndef CORBASIM_QWT_REFLECTIVEPLOTTOOL_HPP
#define CORBASIM_QWT_REFLECTIVEPLOTTOOL_HPP

#include <corbasim/qwt/export.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/tools/AbstractInputTool.hpp>

namespace corbasim 
{
namespace qwt 
{

using namespace ::corbasim::gui;

class SimplePlot;
class PlotModel;

class CORBASIM_QWT_DECLSPEC PlotProcessor : public QObject,
    public RequestProcessor
{
    Q_OBJECT
public:

    PlotProcessor(Objref_ptr objref,
            const QList< int >& path);
    ~PlotProcessor();

    void process(Request_ptr req, 
            TypeDescriptor_ptr ref,
            Holder hold);
    
signals:

    void append(Request_ptr, 
            TypeDescriptor_ptr,
            Holder);
};

class CORBASIM_QWT_DECLSPEC ReflectivePlot : public AbstractInputItem
{
    Q_OBJECT
public:

    ReflectivePlot(Objref_ptr objref,
            OperationDescriptor_ptr reflective,
            const QList< int >& path, 
            QWidget * parent = 0);
    virtual ~ReflectivePlot();

    virtual void start();

public slots:

    void appendValue(Request_ptr, 
            TypeDescriptor_ptr,
            Holder);

protected:

    SimplePlot * m_plot;
};

class CORBASIM_QWT_DECLSPEC PlotTool : public AbstractInputTool
{
    Q_OBJECT
public:

    PlotTool(QWidget * parent = 0);
    virtual ~PlotTool();

protected:

    AbstractInputItem * createItem(
            Objref_ptr objref, 
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

    ParametersModel * createModel();
};

} // namespace qwt
} // namespace corbasim

#endif /* CORBASIM_QWT_REFLECTIVEPLOTTOOL_HPP */
