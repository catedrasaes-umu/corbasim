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
#include <boost/shared_ptr.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/qt/RequestDialog.hpp>
#include <corbasim/qt/SimpleScriptEditor.hpp>

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
    Objref(QMdiArea * area,
            const QString& id,
            gui::gui_factory_base * factory,
            QObject * parent = 0);
    virtual ~Objref();

    QMenu * getMenu() const;

    qt::RequestDialog * getRequestDialog(int idx);
    QMdiSubWindow * getWindow(int idx);

public slots:

    void sendRequest(corbasim::event::request_ptr req);
    
    void deleteObjref();

    void showRequestDialog(int idx);
    void showRequestDialog(QAction * act);
    void showScriptEditor();

    void showSetReference();

signals:

    void sendRequest(QString,
        corbasim::event::request_ptr);

    void deleteObjref(QString);

protected:

    QMdiArea * m_mdi_area;

    QString m_id;
    gui::gui_factory_base * m_factory;

    // Operation dialogs
    typedef std::vector< qt::RequestDialog * > dialogs_t;
    dialogs_t m_dialogs;
    
    typedef std::vector< QMdiSubWindow * > subwindows_t;
    subwindows_t m_subwindows;

    QMdiSubWindow * m_sub_script;
    qt::SimpleScriptEditor * m_script;

    QMenu * m_menu;
};

typedef boost::shared_ptr< Objref > Objref_ptr;

} // namespace view
} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_VIEW_OBJREF_HPP */

