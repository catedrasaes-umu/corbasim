// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FormWidget.hpp
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

#ifndef CORBASIM_QT_FORMWIDGET_HPP
#define CORBASIM_QT_FORMWIDGET_HPP

#include <QtGui>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <corbasim/qt/export.hpp>

namespace corbasim
{
namespace qt
{

class CORBASIM_QT_DECLSPEC FormWidget :
    public QWidget
{
    Q_OBJECT
public:
    FormWidget(QWidget * parent = 0);
    virtual ~FormWidget();

    void addField(const QString& text, QWidget * widget);
    void addMediumField(const QString& text, QWidget * widget);
    void addBigField(const QString& text, QWidget * widget);

    void addField(const QString& text, QLayout * layout);
    void addMediumField(const QString& text, QLayout * layout);
    void addBigField(const QString& text, QLayout * layout);

protected:

    void resizeEvent(QResizeEvent * event);
    void reallocate(int width);

    struct Item
    {
        QGroupBox * group;
        QLabel * label;
        QWidget * widget;
        bool medium;

        Item() : group(NULL), label(NULL), widget(NULL), medium(false)
        {}
    };

    int m_minWidth;
    QGridLayout * m_layout;
    std::vector< Item > m_items;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_FORMWIDGET_HPP */

