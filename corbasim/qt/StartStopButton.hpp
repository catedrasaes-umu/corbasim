// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * StartStopButton.hpp
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

#ifndef CORBASIM_QT_STARTSTOPBUTTON_HPP
#define CORBASIM_QT_STARTSTOPBUTTON_HPP

#include <QPushButton>
#include <corbasim/qt/export.hpp>

namespace corbasim 
{
namespace qt 
{

class CORBASIM_QT_DECLSPEC StartStopButton : public QPushButton
{
    Q_OBJECT
public:
    StartStopButton(QWidget * parent = 0);
    ~StartStopButton();

protected slots:

    void setStarted(bool started);

protected:
    const QString m_startText;
    const QString m_stopText;

    QIcon m_startIcon;
    QIcon m_stopIcon;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_STARTSTOPBUTTON_HPP */

