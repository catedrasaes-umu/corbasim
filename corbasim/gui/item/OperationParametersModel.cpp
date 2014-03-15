#include "OperationParametersModel.hpp"
#include <iostream>

using namespace corbasim::gui;

OperationParametersModel::OperationParametersModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

OperationParametersModel::~OperationParametersModel()
{
}

bool OperationParametersModel::setData(const QModelIndex & index,
        const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::CheckStateRole)
    {
        QList< int > path;

        DescriptorNode * node =
            static_cast< DescriptorNode * >(index.internalPointer());
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
                node->checked = check;

                emit dataChanged(index, index);

                if (check)
                {
                    emit checked(m_reflective, path);
                }
                else
                {
                    emit unchecked(m_reflective, path);
                }
            }

            return true;
        }
    }

    return false;
}

OperationDescriptor_ptr
OperationParametersModel::getReflective() const
{
    return m_reflective;
}

bool OperationParametersModel::isCheckable(TypeDescriptor_ptr reflective) const
{
    return true;
}

void OperationParametersModel::initialize(
        int idx,
        OperationDescriptor_ptr reflective)
{
    m_idx = idx;
    m_name = reflective->get_name();
    m_reflective = reflective;
    m_node.reset(new DescriptorNode(reflective, NULL, NULL, idx));

    reset();
}

void OperationParametersModel::uncheck(const QList< int >& path)
{
    QModelIndex idx = index(0, 0);

    for (int ii = 1; ii < path.size(); ii++)
    {
        idx = index(path[ii], 0, idx);
    }

    setData(idx, Qt::Unchecked, Qt::CheckStateRole);
}

void OperationParametersModel::check(const QList< int >& path)
{
    QModelIndex idx = index(0, 0);

    for (int ii = 1; ii < path.size(); ii++)
    {
        idx = index(path[ii], 0, idx);
    }

    setData(idx, Qt::Checked, Qt::CheckStateRole);
}


//
//
// AbstractItemModel
//
//

// fwd
QString getNodeName(DescriptorNode const * node);

QVariant OperationParametersModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        DescriptorNode * node =
            static_cast< DescriptorNode * >(index.internalPointer());
        node->check_for_initialized();

        // First level item
        if (!index.parent().isValid())
        {
            return m_name;
        }
        else
        {
            // Name
            return getNodeName(node);
        }
    }
    else if (role == Qt::CheckStateRole)
    {
        DescriptorNode * node =
            static_cast< DescriptorNode * >(index.internalPointer());
        node->check_for_initialized();

        return (node->checked)? Qt::Checked: Qt::Unchecked;
    }

    return QVariant();
}

Qt::ItemFlags OperationParametersModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    DescriptorNode * node =
        static_cast< DescriptorNode * >(index.internalPointer());
    node->check_for_initialized();

    Qt::ItemFlags flags = Qt::ItemIsEnabled |
        Qt::ItemIsSelectable;

    if (isCheckable(node->reflective))
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

QVariant OperationParametersModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Parameters");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex OperationParametersModel::index(int row, int column,
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {

        return createIndex(row, column, (void *) m_node.get());
    }

    DescriptorNode * node =
        static_cast< DescriptorNode * >(parent.internalPointer());
    node->check_for_initialized();

    if (row < (int) node->children.size())
    {
        return createIndex(row, column,
                (void *) node->children[row].get());
    }

    return QModelIndex();
}

QModelIndex OperationParametersModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DescriptorNode * node =
        static_cast< DescriptorNode * >(index.internalPointer());
    node->check_for_initialized();

    if (!node || !node->parent)
        return QModelIndex();

    // parent is first level item
    if (!node->parent->parent)
    {
        return createIndex(0, 0, (void *) node->parent);
    }

    return createIndex(node->index, 0, (void *) node->parent);
}

int OperationParametersModel::rowCount(const QModelIndex &parent) const
{
    // Modelo no inicializado
    if (!m_node)
        return 0;

    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return 1;

    DescriptorNode * node =
        static_cast< DescriptorNode * >(parent.internalPointer());
    node->check_for_initialized();

    return node->children.size();
}

int OperationParametersModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

bool OperationParametersModel::removeRows(int row, int count,
        const QModelIndex& parent)
{
    // Solo se pueden borrar elementos de primer nivel
    if (parent.isValid())
        return false;

#if 0
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++)
    {
    }

    endRemoveRows();
#endif

    return false;
}

