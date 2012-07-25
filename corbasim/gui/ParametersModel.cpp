#include "ParametersModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

using namespace corbasim::gui;

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

bool ParametersModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    // TODO get the current value
    
    bool res = QStandardItemModel::setData(index, value, role);

    if (role == Qt::CheckStateRole)
    {
        QList< int > path;

        QModelIndex parent = index;

        // Calculate path
        do {
            path.push_front(parent.row());
            parent = parent.parent();
        } while(parent.isValid());
        
        if (path.size() > 1)
        {
            const FirstLevelItem& item = 
                *boost::next(m_items.begin(), path.front());

            // Remove instance index
            path.pop_front();

            QStandardItem * mitem = itemFromIndex(index);

            if (mitem->checkState() == Qt::Checked)
                emit checked(item.name, item.reflective, path);
            else
                emit unchecked(item.name, item.reflective, path);
        }
    }

    return res;
}

corbasim::core::interface_reflective_base const * 
ParametersModel::getReflective(const QString& id) const
{
    for (FirstLevelItems_t::const_iterator it = m_items.begin(); 
            it != m_items.end(); ++it) 
    {
        if (id == it->name)
        {
            return it->reflective;
        }
    }

    return NULL;
}

void ParametersModel::insertRecursive(QStandardItem * parent, 
        corbasim::core::reflective_base const * reflective)
{
    const unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        corbasim::core::reflective_base const * child =
            reflective->get_child(i);

        const corbasim::core::reflective_type type = child->get_type();

        bool bIsCheckable = isCheckable(child);

        QStandardItem * childItem = 
            new QStandardItem(reflective->get_child_name(i));
        childItem->setEditable(false);
        childItem->setCheckable(bIsCheckable);

        // Recursive
        if (type == corbasim::core::TYPE_STRUCT ||
                type == corbasim::core::TYPE_UNION)
        {
            insertRecursive(childItem, child);
        }
        else if (child->is_repeated())
        {
            unsigned int length = 1;
            
            if (!child->is_variable_length())
            {
                length = child->get_length(core::holder());
            }

            bool bIsCheckable = isCheckable(child->get_slice());

            for (int j = 0; j < length; j++) 
            {
                QStandardItem * item = new QStandardItem(QString("%1").arg(j));

                item->setEditable(false);
                item->setCheckable(bIsCheckable);

                insertRecursive(item, child->get_slice());
                childItem->appendRow(item);
            }
        }

        // TODO union

        parent->appendRow(childItem);
    }
}

bool ParametersModel::isCheckable(core::reflective_base const * reflective)
{
    return true;
}

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
        opItem->setCheckable(isCheckable(op));

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

void ParametersModel::uncheck(const QString& id, const QList< int >& path)
{
    // TODO optimize

    unsigned int i = 0;
    for (FirstLevelItems_t::const_iterator it = m_items.begin(); 
            it != m_items.end(); ++it, ++i) 
    {
        if (id == it->name)
        {
            // navigate until last element

            // Instance element
            QModelIndex idx = index(i, 0);
            
            for (int i = 0; i < path.size(); i++) 
            {
                idx = index(path[i], 0, idx);
            }

            QStandardItem * item = itemFromIndex(idx);

            item->setCheckState(Qt::Unchecked);

            break;
        }
    }
}

void ParametersModel::check(const QString& id, const QList< int >& path)
{
    // TODO optimize

    unsigned int i = 0;
    for (FirstLevelItems_t::const_iterator it = m_items.begin(); 
            it != m_items.end(); ++it, ++i) 
    {
        if (id == it->name)
        {
            // navigate until last element

            // Instance element
            QModelIndex idx = index(i, 0);
            
            for (int i = 0; i < path.size(); i++) 
            {
                idx = index(path[i], 0, idx);
            }

            QStandardItem * item = itemFromIndex(idx);

            item->setCheckState(Qt::Checked);

            break;
        }
    }
}

