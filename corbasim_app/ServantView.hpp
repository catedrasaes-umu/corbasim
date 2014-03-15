// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ServantView.hpp
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

#ifndef CORBASIM_APP_VIEW_SERVANT_HPP
#define CORBASIM_APP_VIEW_SERVANT_HPP

#include <QtGui>
#include <boost/shared_ptr.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/tools/SimpleScriptEditor.hpp>

namespace corbasim
{
namespace app
{

using namespace corbasim::gui;

class ServantView : public QObject
{
    Q_OBJECT
public:
    ServantView(QMdiArea * area,
            Objref_ptr servant,
            QObject * parent = 0);
    virtual ~ServantView();

    Objref_ptr servant() const;

    QMenu * getMenu() const;

    InterfaceDescriptor_ptr getFactory() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void deleteServant();

    void showSelfStimulator();

signals:

    void deleteServant(ObjectId);

protected:
    QMdiArea * m_mdi_area;

    Objref_ptr m_servant;

    QMdiSubWindow * m_sub_script;
    SimpleScriptEditor * m_script;

    QMenu * m_menu;
};

typedef boost::shared_ptr< ServantView > ServantView_ptr;

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_VIEW_SERVANT_HPP */

