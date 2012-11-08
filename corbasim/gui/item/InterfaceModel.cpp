#include "InterfaceModel.hpp"
#include <iostream>
#include <limits>

using namespace corbasim::gui;

InterfaceModel::InterfaceModel(QObject *parent)
    : QAbstractItemModel(parent) 
{
}

InterfaceModel::~InterfaceModel()
{
}

int InterfaceModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant InterfaceModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const int row = index.row();

        if (row < m_nodes.size())
        {
            return QString(m_nodes.at(row)->get_fqn());
        }
    }

    return QVariant();
}

bool InterfaceModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    return false;
}

Qt::ItemFlags InterfaceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant InterfaceModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal 
            && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Interfaces");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex InterfaceModel::index(int row, int column, 
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column, 
                (void *) m_nodes.at(row));
    }

    return QModelIndex();
}

QModelIndex InterfaceModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int InterfaceModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (!parent.isValid())
    {
        return m_nodes.size(); 
    }

    return 0;
}

void InterfaceModel::addInterface(InterfaceDescriptor_ptr interface)
{
    beginInsertRows(QModelIndex(), m_nodes.size(), m_nodes.size());

    m_nodes.push_back(interface);
        
    endInsertRows();
}

