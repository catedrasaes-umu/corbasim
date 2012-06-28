#include "FilterModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

using namespace corbasim::qt;

FilterModel::FilterModel(QObject *parent)
    : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Plotable parameters";

    setHorizontalHeaderLabels(headers);
}

FilterModel::~FilterModel()
{
}

bool FilterModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    // TODO get the current value
    
    bool res = QStandardItemModel::setData(index, value, role);

    if (role == Qt::CheckStateRole)
    {
        /*
        QList< int > path;

        QModelIndex parent = index;

        // Calculate path
        do {
            path.push_front(parent.row());
            parent = parent.parent();
        } while(parent.isValid());
        
        if (path.size() > 2)
        {
            const FirstLevelItem& item = 
                *boost::next(m_items.begin(), path.front());

            // Remove instance index
            path.pop_front();

            QStandardItem * mitem = itemFromIndex(index);

            if (mitem->checkState() == Qt::Checked)
                emit createdPlot(item.name, item.reflective, path);
            else
                emit deletedPlot(item.name, item.reflective, path);
        }
        */

        emit filterChanged();
    }

    return res;
}

void FilterModel::registerInstance(const QString& name,
		corbasim::core::interface_reflective_base const * reflective)
{
    FirstLevelItem item;
    item.name = name;
    item.reflective = reflective;
    m_items.push_back(item);

    m_itemsByName.insert(std::make_pair(name, &m_items.back()));

    QStandardItem * ifItem = new QStandardItem(name);
    ifItem->setEditable(false);

    const unsigned int count = reflective->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_reflective_base const * op =
            reflective->get_reflective_by_index(i);

        QStandardItem * opItem = new QStandardItem(op->get_name());
        opItem->setEditable(false);
        opItem->setCheckable(true);
        opItem->setCheckState(Qt::Checked);

        ifItem->appendRow(opItem);
    }

    appendRow(ifItem);
}

void FilterModel::unregisterInstance(const QString& name)
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
    
    m_itemsByName.erase(name);
}

bool FilterModel::visibleOperation(const QString& name, tag_t tag) const
{
    // TODO optimize
    
    int i = 0;
    for (FirstLevelItems_t::const_iterator it = m_items.begin(); 
            it != m_items.end(); ++it, ++i) 
    {
        if (name == it->name)
        {
            for (unsigned int j = 0; j < it->reflective->operation_count(); j++) 
            {
                if (it->reflective->get_reflective_by_index(j)->get_tag() == tag)
                {
                    return (item(i)->child(j)->checkState() == Qt::Checked);
                }
            }
        }
    }

    return false;
}

