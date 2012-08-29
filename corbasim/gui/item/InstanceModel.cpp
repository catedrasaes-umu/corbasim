#include "InstanceModel.hpp"
#include <iostream>
#include <limits>

using namespace corbasim::gui;

InstanceModel::InstanceModel(QObject *parent)
    : QAbstractItemModel(parent), 
    m_instances(this),
    m_maxLevel(std::numeric_limits< int >::max())
{
}

InstanceModel::~InstanceModel()
{
}

void InstanceModel::registerInstance(Objref_ptr objref)
{
    m_instances.add(objref);

    InstanceNode_ptr node(new InstanceNode(objref));

    // beginInsertRows(QModelIndex(), m_nodes.size(), m_nodes.size());

    m_nodes.push_back(node);
        
    // endInsertRows();

    reset();
}

void InstanceModel::unregisterInstance(ObjectId id)
{
    int i = 0;
    for (Nodes_t::iterator it = m_nodes.begin();
            it != m_nodes.end(); ++it, i++) 
    {
        if ((*it)->instance->id() == id)
        {
            // beginRemoveRows(QModelIndex(), i, i);

            m_instances.del(id);

            m_nodes.erase(it);
            
            // endRemoveRows();

            reset();
            break;
        }
    }
}

bool InstanceModel::displayOperations() const
{
    return (m_maxLevel > 0);
}

bool InstanceModel::displayParameters() const
{
    return (m_maxLevel > 1);
}

int InstanceModel::maxLevel() const
{
    return m_maxLevel;
}

void InstanceModel::setDisplayOperations(bool value)
{
    m_maxLevel = (value)? 1: 0;

    reset();
}

void InstanceModel::setDisplayParameters(bool value)
{
    m_maxLevel = (value)? std::numeric_limits< int >::max(): 1;

    reset();
}

void InstanceModel::setMaxLevel(int value)
{
    m_maxLevel = value;
}

int InstanceModel::columnCount(const QModelIndex&) const
{
    return 1;
}

namespace 
{

QString getNodeName(DescriptorNode const * node)
{
    if (node->parent && node->parent->reflective->is_repeated())
    {
        return QString("[%1]").arg(node->index);
    }
    else if (node->parent && node->parent->reflective->get_type() ==
            corbasim::core::TYPE_STRUCT)
    {
        return node->parent->reflective->get_child_name(node->index);
    }
    else if (node->parent && node->parent->reflective->get_type() ==
            corbasim::core::TYPE_UNION)
    {
        return node->parent->reflective->get_child_name(
                node->reflective->get_child_index());
    }

    return "Error!";
}

} // namespace 

QVariant InstanceModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    AbstractNode * node = static_cast< AbstractNode * >(
            index.internalPointer());

    InstanceNode * iNode = 
        dynamic_cast< InstanceNode *>(node);

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (iNode)
        {
            iNode->check_for_initialized();

            return iNode->instance->name() + 
                " (" + iNode->reflective->get_fqn() +
                ")";
        }
        else
        {
            DescriptorNode * dNode = 
                static_cast< DescriptorNode *>(node);
            
            dNode->check_for_initialized();

            // Operation node
            if (!dNode->parent)
            {
                // Operation name
                return dNode->instance->reflective->get_reflective_by_index(dNode->index)->get_name();
            }
            else
            {
                return getNodeName(dNode);
            }
        }
    }
    else if (role == Qt::UserRole)
    {
        if (iNode)
        {
            return QVariant::fromValue(
                    iNode->instance->reference());
        }
    }

    return QVariant();
}

bool InstanceModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    return false;
}

Qt::ItemFlags InstanceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
/*
    // Value is editable by default
    if (index.column())
        return Qt::ItemIsEnabled 
            | Qt::ItemIsSelectable 
            | Qt::ItemIsEditable;
 */
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant InstanceModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal 
            && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Instances");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex InstanceModel::index(int row, int column, 
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column, 
                (void *) m_nodes.at(row).get());
    }

    AbstractNode * node = static_cast< AbstractNode * >(
            parent.internalPointer());

    InstanceNode * iNode = 
        dynamic_cast< InstanceNode *>(node);

    if (iNode)
    {
        iNode->check_for_initialized();

        if (row < (int) iNode->children.size())
        {
            return createIndex(row, column, 
                    (void *) iNode->children[row].get());
        }
    }
    else
    {
        DescriptorNode * dNode = 
            static_cast< DescriptorNode *>(node);
        
        dNode->check_for_initialized();

        if (row < (int) dNode->children.size())
        {
            return createIndex(row, column, 
                    (void *) dNode->children[row].get());
        }
    }

    return QModelIndex();
}

QModelIndex InstanceModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    AbstractNode * node = static_cast< AbstractNode * >(
            index.internalPointer());

    if (!node)
        return QModelIndex();

    DescriptorNode * dNode = 
        dynamic_cast< DescriptorNode *>(node);

    if (dNode)
    {
        dNode->check_for_initialized();

        // Operation node
        if (!dNode->parent)
            return createIndex(dNode->index, 0, (void *) dNode->instance);
            
        return createIndex(dNode->index, 0, (void *) dNode->parent);
    }

    return QModelIndex();
}

int InstanceModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_nodes.size(); 

    if (!parent.parent().isValid())
    {
        InstanceNode * node = 
            static_cast< InstanceNode * >(parent.internalPointer());

        if (node && displayOperations())
        {
            node->check_for_initialized();

            return node->children.size();
        }
    }
    else 
    {
        DescriptorNode * node = 
            static_cast< DescriptorNode * >(parent.internalPointer());

        if (node && displayParameters())
        {
            node->check_for_initialized();

            return node->children.size();
        }
    }

    return 0;
}

// Accessors
bool InstanceModel::isOperationNode(const QModelIndex& index) const
{
    if (!index.isValid())
        return false;

    AbstractNode * node = 
        static_cast< AbstractNode * >(index.internalPointer());

    DescriptorNode * dNode = 
        dynamic_cast< DescriptorNode * >(node);

    return dNode && !dNode->parent;
}

bool InstanceModel::isInstanceNode(const QModelIndex& index) const
{
    if (!index.isValid())
        return false;

    return !index.parent().isValid();
}

OperationDescriptor_ptr InstanceModel::getOperation(
        const QString& instance,
        const QString& operation) const
{
    Objref_ptr obj = m_instances.find(instance);

    if (obj)
    {
        const std::string str (operation.toStdString());
        return obj->interface()->get_reflective_by_name(str.c_str());
    }

    return NULL;
}

Objref_ptr InstanceModel::getInstance(const QModelIndex& index) const
{
    if (!index.isValid())
        return Objref_ptr();

    if (!index.parent().isValid())
    {
        InstanceNode * node = 
            static_cast< InstanceNode * >(index.internalPointer());

        return node->instance;
    }
    else 
    {
        DescriptorNode * node = 
            static_cast< DescriptorNode * >(index.internalPointer());

        return node->instance->instance;
    }

    return Objref_ptr();
}

Objref_ptr InstanceModel::getInstance(const QString& name) const
{
    return m_instances.find(name);
}

