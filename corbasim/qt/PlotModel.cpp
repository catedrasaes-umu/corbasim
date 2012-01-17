#include "PlotModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

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

bool PlotModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    // TODO get the current value
    
    bool res = QStandardItemModel::setData(index, value, role);

    if (res && index.column() == 1 && value.type() == QVariant::Bool)
    {
        std::cout << "begin" << std::endl;

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

            if (value.toBool())
                emit createPlot(item.name, item.reflective, path);
            else
                emit deletePlot(item.name, item.reflective, path);
        }

        std::cout << "end" << std::endl;
    }

    return res;
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

        if (child->is_primitive() || 
                (child->is_repeated() && child->get_slice()->is_primitive()))
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

