#include "OperationModel.hpp"
#include <boost/next_prior.hpp>
#include <iostream>

using namespace corbasim::gui;

// Model
OperationModel::OperationModel(QObject *parent)
    : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Operations";

    setHorizontalHeaderLabels(headers);
}

OperationModel::~OperationModel()
{
}

void OperationModel::registerInstance(const QString& name,
        InterfaceDescriptor_ptr factory)
{
    FirstLevelItem item;
    item.name = name;
    item.factory = factory;
    m_items.push_back(item);

    QStandardItem * ifItem = new QStandardItem(name);
    ifItem->setEditable(false);

    const unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        OperationDescriptor_ptr op =
            factory->get_reflective_by_index(i);

        QStandardItem * opItem = new QStandardItem(op->get_name());
        opItem->setEditable(false);

        // opItem->setData(op);

        ifItem->appendRow(opItem);
    }

    appendRow(ifItem);
}

void OperationModel::unregisterInstance(const QString& name)
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

void OperationModel::doubleClicked(const QModelIndex& index)
{
    const QModelIndex parent = index.parent();

    if (parent.isValid())
    {
        FirstLevelItem& item = *boost::next(m_items.begin(), 
                parent.row());

        OperationDescriptor_ptr op =
            item.factory->get_reflective_by_name(
                    index.data().toString().toStdString());

        emit selectedOperation(item.name, op);
    }
}

OperationDescriptor_ptr 
OperationModel::getOperation(
        const QString& obj, const QString& operation) const
{
    for (FirstLevelItems_t::const_iterator it = m_items.begin(); 
            it != m_items.end(); ++it) 
    {
        if (it->name == obj)
        {
            const std::string op (operation.toStdString());

            return it->factory->get_reflective_by_name(op.c_str());
        }
    }

    return NULL;
}    

