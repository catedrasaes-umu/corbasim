// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MultiFileSelectionWidget.hpp
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

#ifndef CORBASIM_QT_MULTIFILESELECTIONWIDGET_HPP
#define CORBASIM_QT_MULTIFILESELECTIONWIDGET_HPP

#include <QtGui>

namespace corbasim 
{
namespace qt 
{

class MultiFileSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    MultiFileSelectionWidget(QWidget * parent = 0);
    virtual ~MultiFileSelectionWidget();

    const QString * getNext();

public slots:
    void showSelectionDialog();
    void restart();
    void currentIndexChanged(int);

protected:
    QLineEdit * m_leSelectedFiles;
    QStringList m_selectedFiles;

    QLineEdit * m_leNextFile;
    QCheckBox * m_ckRepeat;
    QSpinBox * m_sbCurrentIndex;
};
} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_MULTIFILESELECTIONWIDGET_HPP */

