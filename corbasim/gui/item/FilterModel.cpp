#include "FilterModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

using namespace corbasim::gui;

FilterModel::FilterModel(QObject *parent)
    : QStandardItemModel(parent), m_instances(this)
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

void FilterModel::registerInstance(Objref_ptr objref)
{
    m_instances.add(objref);

    FirstLevelItem item;
    item.objref = objref;
    FirstLevelItems_t::iterator it = 
        m_items.insert(objref->id(), item);
    
    OperationsMap_t& operations = it.value().operations;

    QStandardItem * ifItem = new QStandardItem(objref->name());
    ifItem->setEditable(false);
    ifItem->setCheckable(true);
    ifItem->setTristate(true);
    ifItem->setCheckState(Qt::Checked);

    const unsigned int count = objref->interface()->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        OperationDescriptor_ptr op =
            objref->interface()->get_reflective_by_index(i);

        QStandardItem * opItem = new QStandardItem(op->get_name());
        opItem->setEditable(false);
        opItem->setCheckable(true);
        opItem->setCheckState(Qt::Checked);

        ifItem->appendRow(opItem);

        operations.insert(op->get_tag(), opItem);
    }

    appendRow(ifItem);
    
    emit filterChanged();
}

void FilterModel::unregisterInstance(ObjectId id)
{
    m_instances.del(id);
    m_items.remove(id);

    emit filterChanged();
}

bool FilterModel::visibleOperation(ObjectId id, tag_t tag) const
{
    FirstLevelItems_t::const_iterator it = m_items.find(id); 

    if (it != m_items.end())
    {
        OperationsMap_t::const_iterator op = 
            it.value().operations.find(tag);

        if (op != it.value().operations.end())
        {
            return (op.value()->checkState() == Qt::Checked);
        }
    }

    return false;
}

void FilterModel::save(QVariant& settings)
{
    QVariantList list;

    for (FirstLevelItems_t::iterator it = m_items.begin(); 
            it != m_items.end(); ++it) 
    {
        Objref_ptr objref = it.value().objref;

        QVariantMap map;

        map["instance"] = objref->name();

        QVariantMap ops;

        for (unsigned int j = 0; 
                j < objref->interface()->operation_count(); j++) 
        {
            OperationDescriptor_ptr op = 
                objref->interface()->get_reflective_by_index(j);
            tag_t tag = op->get_tag();

            OperationsMap_t::const_iterator opit = 
                it.value().operations.find(tag);

            if (opit != it.value().operations.end())
            {
                ops[op->get_name()] = 
                    (opit.value()->checkState() == Qt::Checked);
            }
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

        // Name to ID conversion
        const QString instance = map["instance"].toString();

        if (instance.isEmpty()) continue;

        Objref_ptr objref = m_instances.find(instance);

        if (!objref) continue;

        FirstLevelItems_t::iterator fit =  m_items.find(objref->id());

        if (fit == m_items.end()) continue;

        // End Name to ID conversion
        
        const QVariantMap operations = map["operations"].toMap();

        for (unsigned int j = 0; 
                j < objref->interface()->operation_count(); j++) 
        {
            OperationDescriptor_ptr op = 
                objref->interface()->get_reflective_by_index(j);
            tag_t tag = op->get_tag();

            OperationsMap_t::iterator opit = 
                fit.value().operations.find(tag);

            if(operations.contains(op->get_name()) && 
                    opit != fit.value().operations.end())
            {
                bool state = operations[op->get_name()].toBool();

                opit.value()->setCheckState((state)?
                        Qt::Checked: Qt::Unchecked);
            }
        }
    }
}
