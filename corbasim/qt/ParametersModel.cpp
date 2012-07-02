#include "ParametersModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

using namespace corbasim::qt;

ParametersModel::ParametersModel(QObject *parent)
    : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Parameters";

    setHorizontalHeaderLabels(headers);
}

ParametersModel::~ParametersModel()
{
}

namespace 
{

void insertRecursive(QStandardItem * parent, 
        corbasim::core::reflective_base const * reflective)
{
    const unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        corbasim::core::reflective_base const * child =
            reflective->get_child(i);

        const corbasim::core::reflective_type type = child->get_type();

        QStandardItem * childItem = 
            new QStandardItem(reflective->get_child_name(i));
        childItem->setEditable(false);

        // Recursive
        if (type == corbasim::core::TYPE_STRUCT || 
                child->is_repeated())
        {
            insertRecursive(childItem, child);
        }
        else if (child->is_repeated() && 
                !child->get_slice()->is_primitive())
        {
            insertRecursive(childItem, child->get_slice());
        }

        parent->appendRow(childItem);
    }
}

} // namespace 

void ParametersModel::registerInstance(const QString& name,
		corbasim::core::interface_reflective_base const * reflective)
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

void ParametersModel::unregisterInstance(const QString& name)
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

