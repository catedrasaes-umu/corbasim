// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TreeView.hpp
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

#ifndef CORASIM_GUI_TREEVIEW_HPP
#define CORASIM_GUI_TREEVIEW_HPP

#include <QTreeView>

namespace corbasim 
{
namespace gui 
{

class TreeView : public QTreeView
{
    Q_OBJECT
    Q_PROPERTY(bool autoScrollToItem 
            READ autoScrollToItem
            WRITE setAutoScrollToItem)
public:
    TreeView(QWidget * parent = 0);
    virtual ~TreeView();

    bool autoScrollToItem() const;

    virtual void setModel(QAbstractItemModel * model);

public slots:
    
    void setAutoScrollToItem(bool value);

protected slots:

    void scrollToItem(const QModelIndex& parent, int start, int end);

protected:

    bool m_autoScrollToItem;
};

} // namespace gui
} // namespace corbasim

#endif /* CORASIM_GUI_TREEVIEW_HPP */

