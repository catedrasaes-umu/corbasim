#include "PlotModel.hpp"
#include <iostream>

using namespace corbasim::qt;

PlotModel::PlotModel(QObject *parent)
    : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Object" << "Plot";

    setHorizontalHeaderLabels(headers);
}

PlotModel::~PlotModel()
{
}

void insertRecursive(QStandardItem * parent, 
        corbasim::core::reflective_base const * reflective)
{
    const unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        corbasim::core::reflective_base const * child =
            reflective->get_child(i);

        QStandardItem * childItem = 
            new QStandardItem(reflective->get_child_name(i));
        childItem->setEditable(false);

        insertRecursive(childItem, child);

        if (child->is_primitive())
        {
            QList< QStandardItem * > list;
            list << childItem;

            // Do plot?
            QStandardItem * value = new QStandardItem();
            value->setData(false, Qt::DisplayRole);
            value->setEditable(true);
            list << value;

            parent->appendRow(list);
        }
        else
            parent->appendRow(childItem);
    }
}

void PlotModel::registerInstance(const QString& name,
        core::interface_reflective_base const * reflective)
{
    FirstLevelItem item;
    item.name = name;
    item.reflective = reflective;
    m_items.push_back(item);

    QStandardItem * ifItem = new QStandardItem(name);
    ifItem->setEditable(false);

    const unsigned int count = reflective->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_reflective_base const * op =
            reflective->get_reflective_by_index(i);

        QStandardItem * opItem = new QStandardItem(op->get_name());
        opItem->setEditable(false);

        insertRecursive(opItem, op);

        ifItem->appendRow(opItem);
    }

    appendRow(ifItem);
}

void PlotModel::unregisterInstance(const QString& name)
{
    int i = 0;
    for (FirstLevelItems_t::iterator it = m_items.begin(); 
            it != m_items.end(); ++it, ++i) 
    {
        if (name == it->name)
        {
            removeRows(i, 1);

            m_items.erase(it);
            break;
        }
    }
}

