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
#include <corbasim/qwt/PlotModel.hpp>
#include <corbasim/qwt/SimplePlot.hpp>
#include <corbasim/gui/InputRequestProcessor.hpp>
#include <map>

#include <corbasim/qwt/export.hpp>

namespace corbasim 
{
namespace qt 
{
class SortableGroup;
class SortableGroupItem;
} // namespace qt

namespace qwt 
{

class CORBASIM_QWT_DECLSPEC PlotProcessor : public QObject,
    public gui::RequestProcessor
{
    Q_OBJECT
public:

    PlotProcessor(const QString& id,
            const gui::ReflectivePath_t path);
    ~PlotProcessor();

    void process(event::request_ptr req, 
            core::reflective_base const * ref,
            core::holder hold);

signals:

    void append(corbasim::event::request_ptr, 
            const corbasim::core::reflective_base *,
            corbasim::core::holder);
};

class CORBASIM_QWT_DECLSPEC ReflectivePlot : public SimplePlot
{
    Q_OBJECT
public:

    ReflectivePlot(const QString& id,
            core::operation_reflective_base const * reflective,
            const QList< int >& path, 
            QWidget * parent = 0);
    virtual ~ReflectivePlot();

    core::operation_reflective_base const * getReflective() const;

    inline const QList< int >& getPath() const
    {
        return m_path;
    }

    inline gui::RequestProcessor_ptr getProcessor() const
    {
        return m_processor;
    }

public slots:

    void appendValue(corbasim::event::request_ptr, 
            const corbasim::core::reflective_base *,
            corbasim::core::holder);

protected:

    gui::RequestProcessor_ptr m_processor;

    const QString m_id;
    core::operation_reflective_base const * m_reflective;
    const QList< int > m_path;

    SimplePlot * m_plot;
};

class CORBASIM_QWT_DECLSPEC ReflectivePlotTool : public QWidget
{
    Q_OBJECT
public:

    ReflectivePlotTool(QWidget * parent = 0);
    virtual ~ReflectivePlotTool();

public slots:

    void registerInstance(const QString& name,
            const corbasim::core::interface_reflective_base * reflective);

    void unregisterInstance(const QString& name);

    void createPlot(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

    void deletePlot(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

signals:

    void addProcessor(corbasim::gui::RequestProcessor_ptr);
    void removeProcessor(corbasim::gui::RequestProcessor_ptr);

protected slots:

    void deleteRequested(corbasim::qt::SortableGroupItem *);

protected:
    PlotModel m_model;
    qt::SortableGroup * m_group;

    typedef std::pair< QString, tag_t > key_t;
    typedef std::map< key_t, QList< ReflectivePlot * > > map_t;
    typedef std::map< ReflectivePlot *, key_t > inverse_map_t;

    map_t m_map;
    inverse_map_t m_inverse_map;
};

} // namespace qwt
} // namespace corbasim

#endif /* CORBASIM_QWT_REFLECTIVEPLOTTOOL_HPP */
