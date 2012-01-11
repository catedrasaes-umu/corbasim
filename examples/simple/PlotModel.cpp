#include "PlotModel.hpp"

using namespace corbasim::qt;

PlotModel::PlotModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

PlotModel::~PlotModel()
{
}

int PlotModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

QVariant PlotModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return QVariant();
}

Qt::ItemFlags PlotModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant PlotModel::headerData(int section, Qt::Orientation orientation,
                           int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Object");
        case 1:
            return QString("Value");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex PlotModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return QModelIndex();
}

QModelIndex PlotModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    int row = 0;
    return createIndex(row, 0, NULL);
}

int PlotModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    void * ptr = parent.internalPointer();

    if (ptr)
    {
        // TODO
        return 0;
    }

    return m_items.size();
}

void PlotModel::registerInstance(const std::string& name,
        core::interface_reflective_base const * reflective)
{
    FirstLevelItem item;
    item.name = name;
    item.reflective = reflective;
    m_items.push_back(item);

    // TODO emit data changed
}

