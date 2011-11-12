// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Objref.hpp
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

#ifndef CORBASIM_APP_VIEW_OBJREF_HPP
#define CORBASIM_APP_VIEW_OBJREF_HPP

#include <QtGui>
#include <corbasim/gui/gui_factory_fwd.hpp>

namespace corbasim 
{
namespace app 
{
namespace view 
{

class Objref : public QObject
{
    Q_OBJECT
public:
    Objref(const QString& id,
            gui::gui_factory_base * factory,
            QObject * parent = 0);
    virtual ~Objref();

    QMenu * getMenu() const;

public slots:

    void sendRequest(corbasim::event::request_ptr req);

signals:

    void sendRequest(QString id,
        corbasim::event::request_ptr req);

protected:
    QString m_id;
    gui::gui_factory_base * m_factory;

    QMenu * m_menu;
};

} // namespace view
} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_VIEW_OBJREF_HPP */

