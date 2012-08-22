// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NSWatcher.hpp
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

#ifndef CORBASIM_APP_WATCHER_HPP
#define CORBASIM_APP_WATCHER_HPP

#include <corbasim/impl.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include "app_adapted.hpp"
#include <QtCore>

namespace corbasim 
{
namespace app 
{

class NSWatcher : public QObject
{
    Q_OBJECT
public:
    NSWatcher(QObject * parent = 0);
    ~NSWatcher();

    void start();

public slots:

    void refreshNS();
    
    void objrefCreated(const QString& id,
            const corbasim::core::interface_reflective_base * factory,
            const corbasim::app::ObjrefConfig& cfg);
    void objrefDeleted(const QString& id);

signals:

    void updateReference(const QString&,
            const CORBA::Object_var&);

protected:

    QTimer m_timer;

    struct entry_t
    {
        std::string entry;
        CORBA::Object_var ref;
    };

    typedef QMap< QString, entry_t > entries_t;
    entries_t m_entries;

};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_WATCHER_HPP */

