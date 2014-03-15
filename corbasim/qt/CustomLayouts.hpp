// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * CustomLayouts.hpp
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

#ifndef CORBASIM_QT_CUSTOMLAYOUTS_HPP
#define CORBASIM_QT_CUSTOMLAYOUTS_HPP

#include <QVBoxLayout>
#include <corbasim/qt/export.hpp>

namespace corbasim
{
namespace qt
{

class CORBASIM_QT_DECLSPEC CustomVLayout : public QVBoxLayout
{
    Q_OBJECT
public:

    CustomVLayout(QWidget * parent = 0);

    virtual ~CustomVLayout();

public slots:

    void insertItem(int idx, QLayoutItem * item);

};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_CUSTOMLAYOUTS_HPP */

