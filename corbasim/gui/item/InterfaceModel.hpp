#ifndef CORBASIM_GUI_INTERFACEMODEL_HPP
#define CORBASIM_GUI_INTERFACEMODEL_HPP

#include <QList>
#include <QAbstractItemModel>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/item/ModelNode.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC InterfaceModel : 
    public QAbstractItemModel
{
    Q_OBJECT
public:
    InterfaceModel(QObject *parent = 0);
    virtual ~InterfaceModel();

    QVariant data(const QModelIndex& index, 
            int role) const; 
    bool setData(const QModelIndex & index, 
            const QVariant& value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;


public slots:

    void addInterface(InterfaceDescriptor_ptr interface);

signals:

protected:

    typedef QList< InterfaceDescriptor_ptr > Nodes_t;
    Nodes_t m_nodes;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_INTERFACEMODEL_HPP

