// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * InputRequestProcessor.hpp
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

#ifndef CORBASIM_GUI_INPUTREQUESTPROCESSOR_HPP
#define CORBASIM_GUI_INPUTREQUESTPROCESSOR_HPP

#include <QString>
#include <QObject>
#include <map>
#include <corbasim/event_fwd.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC RequestProcessor
{
public:

    virtual ~RequestProcessor();

    virtual void process(event::request_ptr req, 
            core::reflective_base const * ref,
            core::holder hold) = 0;

    virtual const QString& getId() const;

    virtual const ReflectivePath_t& getPath() const;

protected:

    RequestProcessor(const QString& id, 
            const ReflectivePath_t& path);

    const QString m_id;
    const ReflectivePath_t m_path;
};

typedef boost::shared_ptr< RequestProcessor > RequestProcessor_ptr;


/**
 * @brief Process input requests in a non-GUI thread.
 *
 * Use moveToThread to process its events in other thread.
 */
class CORBASIM_GUI_DECLSPEC InputRequestController : 
    public QObject
{
    Q_OBJECT
public:

    InputRequestController(QObject * parent = 0);
    virtual ~InputRequestController();

public slots:

    // Instances
    void registerInstance(const QString& id, 
            const corbasim::core::interface_reflective_base * factory);
    void unregisterInstance(const QString& id);

    void processRequest(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr res);

    // Processors
    void addProcessor(corbasim::gui::RequestProcessor_ptr);
    void removeProcessor(corbasim::gui::RequestProcessor_ptr);

protected:

    typedef std::pair< QString, tag_t > key_t;
    typedef std::map< key_t, QList< RequestProcessor_ptr > > map_t;
    typedef std::map< QString, core::interface_reflective_base const * >
        instances_t;

    /**
     * @brief Registred instances.
     */
    instances_t m_instances;

    /**
     * @brief Registred processors.
     *
     * Must be optimized using a tree-based collection.
     */
    map_t m_processors;

};

CORBASIM_GUI_DECLSPEC 
InputRequestController * getDefaultInputRequestController();

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_INPUTREQUESTPROCESSOR_HPP */

