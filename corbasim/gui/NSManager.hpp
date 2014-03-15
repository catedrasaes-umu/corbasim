// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NSManager.hpp
 * Copyright (C) Andrés Senac 2012 <andres@senac.es>
 *
 * CORBASM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORBASIM_APP_MANAGER_HPP
#define CORBASIM_APP_MANAGER_HPP

#include <QtCore>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>

#include <corbasim/cosnaming/CosnamingC.h>
#include <corbasim/core/ns_register.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC NSManager : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Creates a new Name Service Manager.
     *
     * @param orb We use this ORB to obtain the initial Name Service
     *        with resolve_initial_references.
     * @param parent
     */
    NSManager(const CORBA::ORB_var& orb, QObject * parent = 0);
    ~NSManager();

    /**
     * @brief Start to refresh the objects form the Name Service each
     *        5 seconds.
     */
    void start();

protected slots:

    void refreshNS();
    void doStart();

public slots:

    void setNSReference(const CORBA::Object_var& ref);

    /**
     * @brief Asynchronous name resolution using signals and slots.
     *
     * @param objref Resolve this object if it has set the nsEntry
     *        property.
     */
    void resolve(Objref_ptr objref);

    void objrefCreated(Objref_ptr objref);
    void objrefDeleted(ObjectId);

    void servantCreated(Objref_ptr servant);
    void servantDeleted(ObjectId);

signals:

    void started();

    void error(const QString& msg);
    void message(const QString& msg);

protected:

    void resetRegisters();
    void registerServant(Objref_ptr servant);

    CORBA::ORB_var m_orb;

    QTimer m_timer;

    CosNaming::NamingContextExt_var m_nameService;

    ObjrefRepository m_objrefs;
    ObjrefRepository m_servants;

    typedef core::ns_register_ptr register_ptr;
    typedef QMap< ObjectId, register_ptr > registers_t;
    registers_t m_registers;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_APP_MANAGER_HPP */

