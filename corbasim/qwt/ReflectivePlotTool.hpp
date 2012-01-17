// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectivePlotTool.hpp
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

#include <QWidget>
#include <corbasim/qt/PlotModel.hpp>

namespace corbasim 
{
namespace qt 
{
class SortableGroup;
} // namespace qt

namespace qwt 
{

class ReflectivePlotTool : public QWidget
{
    Q_OBJECT
public:
    ReflectivePlotTool(QWidget * parent = 0);
    virtual ~ReflectivePlotTool();

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

    void createPlot(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

    void deletePlot(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

protected:
    qt::PlotModel m_model;
    qt::SortableGroup * m_group;
};

} // namespace qwt
} // namespace corbasim

#endif /* CORBASIM_QWT_REFLECTIVEPLOTTOOL_HPP */
