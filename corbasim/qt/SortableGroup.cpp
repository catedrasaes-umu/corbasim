// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SortableGroup.cpp
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

#include "SortableGroup.hpp"

using namespace corbasim::qt;

AbstractItemFrame::AbstractItemFrame(QWidget * parent) :
    QFrame(parent), m_timer(this), m_currentAlpha(100)
{
    connect(&m_timer, SIGNAL(timeout()),
        this, SLOT(update()));

    m_timer.start(25);
}

AbstractItemFrame::~AbstractItemFrame()
{
}

void AbstractItemFrame::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (m_currentAlpha > 0)
    {
        QColor semiTransparentColor = Qt::black;
        semiTransparentColor.setAlpha(m_currentAlpha);
        painter.fillRect(rect(), semiTransparentColor);

        m_currentAlpha -= 5;
    }
    else if (m_timer.isActive())
    {
        m_timer.stop();

        disconnect(&m_timer, SIGNAL(timeout()),
            this, SLOT(update()));
    }

    QRect r = rect();
    r.setWidth(r.width() - 1);
    r.setHeight(r.height() - 1);
    painter.drawRect(r);
}

SortableGroupItem::SortableGroupItem(QWidget * widget,
        QWidget * parent) :
    AbstractItemFrame(parent), m_widget(widget)
{
    QVBoxLayout * layout = new QVBoxLayout();

    // Title bar
    QHBoxLayout * tLayout = new QHBoxLayout();
    m_title = new QLabel();
    tLayout->addWidget(m_title);

    QSpacerItem * spacer = new QSpacerItem(40, 20,
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    tLayout->addItem(spacer);

    layout->addLayout(tLayout);

    // Editor
    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_widget);
    m_widget->hide();
    layout->addLayout(m_layout);

    // Buttons
    m_btShowInput = new QToolButton();
    m_btShowInput->setIcon(style()->standardIcon(
                QStyle::SP_FileDialogDetailedView));
    m_btShowInput->setCheckable(true);
    QToolButton * btUp = new QToolButton();
    btUp->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    QToolButton * btDown = new QToolButton();
    btDown->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
    QToolButton * btDelete = new QToolButton();
    btDelete->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    tLayout->addWidget(m_btShowInput);
    tLayout->addWidget(btUp);
    tLayout->addWidget(btDown);
    tLayout->addWidget(btDelete);

    m_btShowInput->setMaximumSize(20, 20);
    btUp->setMaximumSize(20, 20);
    btDown->setMaximumSize(20, 20);
    btDelete->setMaximumSize(20, 20);

    connect(m_btShowInput, SIGNAL(toggled(bool)),
            m_widget, SLOT(setVisible(bool)));

    connect(btDelete, SIGNAL(clicked()),
            this, SLOT(deleteClicked()));
    connect(btUp, SIGNAL(clicked()),
            this, SLOT(upClicked()));
    connect(btDown, SIGNAL(clicked()),
            this, SLOT(downClicked()));
    // End buttons

    setLayout(layout);

    // Tooltips
    m_btShowInput->setToolTip("Show/hide detailed input form");
    btDelete->setToolTip("Delete item");
    btUp->setToolTip("Move up");
    btDown->setToolTip("Move down");
}

SortableGroupItem::~SortableGroupItem()
{
}

void SortableGroupItem::showDetails()
{
    m_btShowInput->setChecked(true);
}

QWidget * SortableGroupItem::getWidget()
{
    return m_widget;
}

QString SortableGroupItem::title() const
{
    return m_title->text();
}

void SortableGroupItem::setTitle(const QString& title)
{
    m_title->setText(QString("<b>%1</b>").arg(title));
}

void SortableGroupItem::deleteClicked()
{
    emit doDelete();
}

void SortableGroupItem::upClicked()
{
    emit up();
}

void SortableGroupItem::downClicked()
{
    emit down();
}

SortableGroup::SortableGroup(QWidget * parent) :
    QWidget(parent), m_delete(true)
{
    QVBoxLayout * layout = new QVBoxLayout();
    layout->setMargin(0);

    QWidget * scrollWidget = new QWidget();
    QVBoxLayout * scrollLayout = new QVBoxLayout();
    m_layout = new CustomVLayout();
    scrollWidget->setLayout(scrollLayout);
    scrollLayout->addLayout(m_layout);
    scrollLayout->setMargin(0);

    QSpacerItem * spacer = new QSpacerItem(40, 20,
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollLayout->addItem(spacer);

    // Scroll
    m_scroll = new QScrollArea();
    m_scroll->setObjectName("scroll");
    m_scroll->setWidgetResizable(true);
    m_scroll->setWidget(scrollWidget);

    m_scroll->setLineWidth(0);
    m_scroll->setFrameStyle(QFrame::NoFrame);

    layout->addWidget(m_scroll);
    setLayout(layout);
}

SortableGroup::~SortableGroup()
{
}

const QList< SortableGroupItem * >&
SortableGroup::getItems()
{
    return m_items;
}

void SortableGroup::appendWidget(QWidget * item)
{
    appendItem(new SortableGroupItem(item, this));
}

void SortableGroup::appendItem(SortableGroupItem * item)
{
    // Before spacer
    m_layout->addWidget(item);

    // Scroll to item
    m_scroll->widget()->resize(m_scroll->widget()->sizeHint());
    qApp->processEvents();
    m_scroll->ensureWidgetVisible(item);

    connect(item, SIGNAL(doDelete()),
            this, SLOT(deleteItem()));
    connect(item, SIGNAL(up()),
            this, SLOT(moveUpItem()));
    connect(item, SIGNAL(down()),
            this, SLOT(moveDownItem()));

    m_items.push_back(item);
}

void SortableGroup::deleteItem(SortableGroupItem * item)
{
    m_items.removeAll(item);
    item->deleteLater();
}

void SortableGroup::moveUpItem(SortableGroupItem * item)
{
     int idx = m_items.indexOf(item);

     if (idx > 0)
     {
         // List
         m_items.takeAt(idx);
         m_items.insert(idx - 1, item);

         // Layout
         QLayoutItem * lItem = m_layout->takeAt(idx);
         m_layout->insertItem(idx - 1, lItem);
     }
}

void SortableGroup::moveDownItem(SortableGroupItem * item)
{
     int idx = m_items.indexOf(item);

     if (idx > -1 && idx < m_items.size() - 1)
     {
         // List
         m_items.takeAt(idx);
         m_items.insert(idx + 1, item);

         // Layout
         QLayoutItem * lItem = m_layout->takeAt(idx);
         m_layout->insertItem(idx + 1, lItem);
     }
}

void SortableGroup::deleteItem()
{
    SortableGroupItem * sndObj =
        qobject_cast< SortableGroupItem * >(sender());

    if (sndObj)
    {
        if (m_delete) deleteItem(sndObj);
        else
        {
            emit deleteRequested(sndObj);
        }
    }
}

void SortableGroup::moveUpItem()
{
    SortableGroupItem * sndObj =
        qobject_cast< SortableGroupItem * >(sender());

    if (sndObj)
        moveUpItem(sndObj);
}

void SortableGroup::moveDownItem()
{
    SortableGroupItem * sndObj =
        qobject_cast< SortableGroupItem * >(sender());

    if (sndObj)
        moveDownItem(sndObj);
}

void SortableGroup::setDelete(bool del)
{
    m_delete = del;
}
