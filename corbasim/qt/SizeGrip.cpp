// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SizeGrip.cpp
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

#include "SizeGrip.hpp"

using namespace corbasim::qt;

SizeGrip::SizeGrip(QWidget * parent) :
    QWidget(parent), m_resizing(false), m_affectedWidget(NULL)
{
    setFixedHeight(15);
    setMinimumWidth(150);
    setCursor(Qt::SizeVerCursor);
}

SizeGrip::~SizeGrip()
{
}

void SizeGrip::setAffectedWidget(QWidget * widget)
{
    m_affectedWidget = widget;
}

void SizeGrip::mouseMoveEvent(QMouseEvent * event)
{
    if (m_resizing)
    {
        QPoint delta = event->pos() - m_oldPos;
        m_oldPos = event->pos();

        if (m_affectedWidget)
        {
            int height = m_affectedWidget->height();
            m_affectedWidget->setMinimumHeight(height + delta.y());
            m_affectedWidget->updateGeometry();
        }
    }
}

void SizeGrip::mousePressEvent(QMouseEvent * event)
{
    m_resizing = true;
    m_oldPos = event->pos();
}

void SizeGrip::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
    m_resizing = false;
}

void SizeGrip::paintEvent(QPaintEvent * paintEvent)
{
    QPainter painter(this);
    /*
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.drawRect(0, 0, width(), height());
    */
   
    QStyleOption opt;
    opt.rect = QRect(0, 0, width(), height());
    style()->drawControl(QStyle::CE_Splitter, &opt, &painter);
}

