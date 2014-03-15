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

#include <map>
#include <QObject>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>

namespace corbasim
{
namespace gui
{

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
    void registerInstance(Objref_ptr objref);
    void unregisterInstance(ObjectId id);

    void processRequest(ObjectId id,
            Request_ptr req,
            Event_ptr res);

    // Processors
    void addProcessor(RequestProcessor_ptr);
    void removeProcessor(RequestProcessor_ptr);

signals:

    void addedProcessor(RequestProcessor_ptr);
    void removedProcessor(RequestProcessor_ptr);

protected:

    typedef std::pair< ObjectId, tag_t > key_t;
    typedef QList< RequestProcessor_ptr > processors_t;
    typedef std::map< key_t, processors_t > map_t;

    typedef ObjrefRepository instances_t;

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

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_INPUTREQUESTPROCESSOR_HPP */

