// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SortableGroup.hpp
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

#ifndef CORBASIM_QT_SORTABLEGROUP_HPP
#define CORBASIM_QT_SORTABLEGROUP_HPP

#include <QtGui>
#include <corbasim/qt/types.hpp>
#include <corbasim/qt/CustomLayouts.hpp>
#include <corbasim/qt/export.hpp>

namespace corbasim 
{
namespace qt 
{

class CORBASIM_QT_DECLSPEC SortableGroupItem : public QFrame
{
    Q_PROPERTY(QString title READ title WRITE setTitle)
    // Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded)
    Q_OBJECT
public:
    SortableGroupItem(QWidget * widget,
            QWidget * parent = 0);
    virtual ~SortableGroupItem();

    QWidget * getWidget();

public slots:

    QString title() const;
    void setTitle(const QString& title);

signals:

    void doDelete();
    void up();
    void down();

private slots:

    void deleteClicked();
    void upClicked();
    void downClicked();

protected:

    QWidget * m_widget;
    QLayout * m_layout;
    QLabel * m_title;
};

class CORBASIM_QT_DECLSPEC SortableGroup : public QWidget
{
    Q_OBJECT
public:
    SortableGroup(QWidget * parent = 0);
    virtual ~SortableGroup();

public slots:

    void setDelete(bool del);

    void appendWidget(QWidget * item);

    void appendItem(SortableGroupItem * item);
    void deleteItem(SortableGroupItem * item);
    void moveUpItem(SortableGroupItem * item);
    void moveDownItem(SortableGroupItem * item);

private slots:

    void deleteItem();
    void moveUpItem();
    void moveDownItem();

signals:

    void deleteRequested(corbasim::qt::SortableGroupItem *); 

protected:

    bool m_delete;

    CustomVLayout * m_layout;
    QList< SortableGroupItem * > m_items;
    QScrollArea * m_scroll;

};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_SORTABLEGROUP_HPP */

