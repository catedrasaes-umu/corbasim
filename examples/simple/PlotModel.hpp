#ifndef CORBASIM_QT_PLOTMODEL_HPP
#define CORBASIM_QT_PLOTMODEL_HPP

#include <QAbstractItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <list>

namespace corbasim
{
namespace qt
{

class PlotModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    PlotModel(QObject *parent = 0);
    virtual ~PlotModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void registerInstance(const std::string& name,
            core::interface_reflective_base const * reflective);

protected:

    struct FirstLevelItem
    {
        std::string name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

} // qt
} // corbasim

#endif // CORBASIM_QT_PLOTMODEL_HPP

