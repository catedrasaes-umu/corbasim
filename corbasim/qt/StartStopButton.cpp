// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * StartStopButton.cpp
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

#include "StartStopButton.hpp"
#include <QStyle>

using namespace corbasim::qt;

StartStopButton::StartStopButton(QWidget * parent) :
    QPushButton(parent),
    m_startText("Start"),
    m_stopText("Stop")
{
    m_startIcon = style()->standardIcon(QStyle::SP_MediaPlay);
    m_stopIcon = style()->standardIcon(QStyle::SP_MediaStop);

    setCheckable(true);

    setStarted(false);

    connect(this, SIGNAL(toggled(bool)), this, SLOT(setStarted(bool)));
}

StartStopButton::~StartStopButton()
{
}

void StartStopButton::setStarted(bool started)
{
    if (!started)
    {
        setText(m_startText);
        setIcon(m_startIcon);
    }
    else
    {
        setText(m_stopText);
        setIcon(m_stopIcon);
    }
}
