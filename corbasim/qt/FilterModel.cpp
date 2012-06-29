#include "FilterModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

using namespace corbasim::qt;

FilterModel::FilterModel(QObject *parent)
    : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Log filter";

    setHorizontalHeaderLabels(headers);
}

FilterModel::~FilterModel()
{
}

bool FilterModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    bool res = QStandardItemModel::setData(index, value, role);

    if (role == Qt::CheckStateRole)
    {
        if (!index.parent().isValid())
        {
            QStandardItem * item = itemFromIndex(index);
            Qt::CheckState st = item->checkState(); 

            if (st != Qt::PartiallyChecked)
            {
                for (int i = 0; i < item->rowCount(); i++) 
                {
                    item->child(i)->setCheckState(st);
                }
            }
        }

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
    ifItem->setCheckable(true);
    ifItem->setTristate(true);
    ifItem->setCheckState(Qt::Checked);

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

        m_items.back().operations.insert(std::make_pair(
                    op->get_name(), opItem));
    }

    appendRow(ifItem);
    
    emit filterChanged();
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

    emit filterChanged();
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

            return false;
        }
    }

    return false;
}

void FilterModel::save(QVariant& settings)
{
    QVariantList list;

    int i = 0;
    for (FirstLevelItems_t::iterator it = m_items.begin(); 
            it != m_items.end(); ++it, ++i) 
    {
        QVariantMap map;

        map["instance"] = it->name;

        QVariantMap ops;

        for (unsigned int j = 0; 
                j < it->reflective->operation_count(); j++) 
        {
            ops[it->reflective->get_reflective_by_index(j)->get_name()] = 
                (item(i)->child(j)->checkState() == Qt::Checked);
        }

        map["operations"] = ops;

        list << map;
    }

    settings = list;
}

void FilterModel::load(const QVariant& settings)
{
    const QVariantList list = settings.toList();

    for (QVariantList::const_iterator it = list.begin(); 
            it != list.end(); ++it) 
    {
        const QVariantMap map = it->toMap();

        if (!map.contains("instance") || !map.contains("operations"))
            continue;

        const QString instance = map["instance"].toString();

        if (instance.isEmpty()) continue;

        FirstLevelItemsByName_t::iterator it = 
            m_itemsByName.find(instance);

        if (it == m_itemsByName.end()) continue;

        const QVariantMap operations = map["operations"].toMap();

        QVariantMap::const_iterator mit = operations.begin();

        for (; mit != operations.end(); mit++)
        {
            if (mit.value().canConvert< bool >())
            {
                const QString name = mit.key();

                OperationsMap_t::iterator opt = 
                    it->second->operations.find(name);

                if (opt != it->second->operations.end())
                {
                    bool state = mit.value().toBool();

                    opt->second->setCheckState((state)?
                            Qt::Checked: Qt::Unchecked);
                }
            }
        }
    }
}

