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
#include <QWidget>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/Model.hpp>

namespace corbasim
{
namespace gui
{

/**
 * @brief Abstraction for collections.
 */
class CORBASIM_GUI_DECLSPEC AbstractTool : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief Functor for interation.
     *
     * Register instances in the tool.
     */
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

    /**
     * @brief Use this method to save the tool's configuration.
     *
     * @param settings Recipient for the configuration.
     */
    virtual void save(QVariant& settings) = 0;

    /**
     * @brief Use this method to load the tool's configuration.
     *
     * @param settings Recipient for the configuration.
     */
    virtual void load(const QVariant& settings) = 0;


public slots:

    /**
     * @brief Register an instance in this tool.
     *
     * @param object The instance.
     */
    virtual void registerInstance(Objref_ptr object) = 0;

    /**
     * @brief Unregister an instance from this tool.
     *
     * @param id The instance identifier.
     */
    virtual void unregisterInstance(ObjectId id) = 0;

    /**
     * @brief Stop the tool. Reimplement if required.
     */
    virtual void stop();
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_ABSTRACTTOOL_HPP */

