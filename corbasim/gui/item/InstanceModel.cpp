#include "InstanceModel.hpp"
#include <QtGui>
#include <QStyle>
#include <iostream>
#include <limits>

using namespace corbasim::gui;

InstanceModel::InstanceModel(QObject *parent)
    : QAbstractItemModel(parent), 
    m_instances(this),
    m_maxLevel(std::numeric_limits< int >::max())
{
    m_servantIcon = qApp->style()->standardIcon(QStyle::SP_ArrowRight);
    m_objrefIcon = qApp->style()->standardIcon(QStyle::SP_ArrowLeft);
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

QString getNodeName(DescriptorNode const * node)
{
    using namespace corbasim::core;
    DescriptorNode const * parent = node->parent;

    if (parent)
    {
        TypeDescriptor_ptr reflective = parent->reflective;

        if (reflective->is_repeated())
        {
            return QString("[%1]").arg(node->index);
        }
        else if (reflective->get_type() == TYPE_STRUCT)
        {
            return reflective->get_child_name(node->index);
        }
        else if (reflective->get_type() == TYPE_UNION)
        {
            return reflective->get_child_name(
                    node->reflective->get_child_index());
        }
    }

    return "Error!";
}

QVariant InstanceModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    AbstractNode * node = static_cast< AbstractNode * >(
            index.internalPointer());

    InstanceNode * iNode = 
        dynamic_cast< InstanceNode *>(node);

    if (role == Qt::ToolTipRole)
    {
        if (iNode)
        {
            return QString("%1: %2 Interface: %3")
                .arg(((iNode->instance->isServant())? "Servant": "Object reference"))
                .arg(iNode->instance->name())
                .arg(iNode->reflective->get_fqn());
        }
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
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
                return dNode->instance->reflective->get_reflective_by_index(
                        dNode->index)->get_name();
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
    else if (!iNode && role == Qt::CheckStateRole)
    {
        DescriptorNode * dNode = 
            static_cast< DescriptorNode *>(node);
        
        dNode->check_for_initialized();

        if (isCheckable(dNode->reflective))
            return (node->checked)? Qt::Checked: Qt::Unchecked;
    }
    else if (!index.parent().isValid() && index.column() == 0
            && role == Qt::DecorationRole)
    {
        const InstanceNode_ptr entry = m_nodes.at(index.row());

        if (entry->instance->isServant())
            return m_servantIcon;

        return m_objrefIcon;
    }
    else if (role == Qt::BackgroundRole)
    {
        // backward to first level item
        AbstractNode * node = static_cast< AbstractNode * >(
                index.internalPointer());

        InstanceNode * iNode = 
            dynamic_cast< InstanceNode *>(node);
        DescriptorNode * dNode = 
            static_cast< DescriptorNode *>(node);

        InstanceNode * entry = (iNode)? iNode: dNode->instance;

        if (entry->instance->isServant())
            return QColor(Qt::green);

        return QColor(Qt::yellow);
    }

    return QVariant();
}

bool InstanceModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    AbstractNode * aNode = 
        static_cast< AbstractNode * >(index.internalPointer());
    DescriptorNode * node = 
        dynamic_cast< DescriptorNode * >(aNode);

    if (role == Qt::CheckStateRole && node && isCheckable(node->reflective))
    {
        QList< int > path;
        node->check_for_initialized();

        const DescriptorNode * cnode = node;

        // Calculate path
        while(cnode)
        {
            path.push_front(cnode->index);
            cnode = cnode->parent;
        }
        
        if (path.size() > 0)
        {
            Qt::CheckState state = 
                static_cast<Qt::CheckState>(value.toUInt());

            bool check = (state == Qt::Checked)? true: false;
            bool old = node->checked;

            if (check != old)
            {
                InterfaceDescriptor_ptr iface = node->instance->reflective;
                const QString name (node->instance->instance->name());
                node->checked = check;

                emit dataChanged(index, index);

                if (check)
                {
                    emit checked(name, iface, path);
#if 0
                    if (m_items.size() == 1)
                        emit checked(item.reflective, path);
#endif
                }
                else
                {
                    emit unchecked(name, iface, path);
#if 0
                    if (m_items.size() == 1)
                        emit unchecked(item.reflective, path);
#endif
                }
            }

            return true;
        }
    }

    return false;
}

Qt::ItemFlags InstanceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    
    Qt::ItemFlags f =  Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (!isInstanceNode(index))
    {
        DescriptorNode * node = static_cast< DescriptorNode * >(
                index.internalPointer());

        node->check_for_initialized();

        if (isCheckable(node->reflective))
            f = f | Qt::ItemIsUserCheckable;
    }

    return f;
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

// Checkable
bool InstanceModel::isCheckable(TypeDescriptor_ptr reflective) const
{
    return false;
}

void InstanceModel::check(const QString& id, const QList< int >& path) 
{
    int i = 0;
    for (Nodes_t::iterator it = m_nodes.begin();
            it != m_nodes.end(); ++it, i++) 
    {
        if ((*it)->instance->name() == id)
        {
            // Instance element
            QModelIndex idx = index(i, 0, QModelIndex());
            
            for (int ii = 0; ii < path.size(); ii++) 
            {
                idx = index(path[ii], 0, idx);
            }

            setData(idx, Qt::Checked, Qt::CheckStateRole);

            break;
        }
    }
}

void InstanceModel::uncheck(const QString& id, const QList< int >& path) 
{
    int i = 0;
    for (Nodes_t::iterator it = m_nodes.begin();
            it != m_nodes.end(); ++it, i++) 
    {
        if ((*it)->instance->name() == id)
        {
            // Instance element
            QModelIndex idx = index(i, 0, QModelIndex());
            
            for (int ii = 0; ii < path.size(); ii++) 
            {
                idx = index(path[ii], 0, idx);
            }

            setData(idx, Qt::Unchecked, Qt::CheckStateRole);

            break;
        }
    }
}

