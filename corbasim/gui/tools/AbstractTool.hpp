// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AbstractTool.hpp
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

#ifndef CORBASIM_GUI_ABSTRACTTOOL_HPP
#define CORBASIM_GUI_ABSTRACTTOOL_HPP

#include <QtGui>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/Model.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC AbstractTool : public QWidget
{
    Q_OBJECT
public:

    struct Register
    {
        AbstractTool * _this;
        Register(AbstractTool * __this) : _this(__this) {}

        void operator()(Objref_ptr o)
        {
            _this->registerInstance(o);
        }
    };

    AbstractTool(QWidget * parent = 0);
    virtual ~AbstractTool();

    virtual void save(QVariant& settings) = 0;
    virtual void load(const QVariant& settings) = 0;


public slots:

    virtual void registerInstance(Objref_ptr object) = 0;
    virtual void unregisterInstance(ObjectId id) = 0;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_ABSTRACTTOOL_HPP */

