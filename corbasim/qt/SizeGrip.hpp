// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SizeGrip.hpp
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

#ifndef CORBASIM_QT_SIZEGRIP_HPP
#define CORBASIM_QT_SIZEGRIP_HPP

#include <QtGui>

namespace corbasim 
{
namespace qt 
{

class SizeGrip : public QWidget
{
    Q_OBJECT
public:
    SizeGrip(QWidget * parent = 0);
    virtual ~SizeGrip();

    void setAffectedWidget(QWidget * widget);

protected:

    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * mouseEvent);
    
    void paintEvent(QPaintEvent * paintEvent);

    bool m_resizing;
    QPoint m_oldPos;

    QWidget * m_affectedWidget;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_SIZEGRIP_HPP */

