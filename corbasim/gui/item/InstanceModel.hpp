#ifndef CORBASIM_GUI_INSTANCEMODEL_HPP
#define CORBASIM_GUI_INSTANCEMODEL_HPP

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

class CORBASIM_GUI_DECLSPEC InstanceModel : 
    public QAbstractItemModel
{
    Q_OBJECT
/*
    Q_PROPERTY(bool checkable 
            READ isCheckable
            WRITE setCheckable)
 */
    Q_PROPERTY(bool displayOperations 
            READ displayOperations
            WRITE setDisplayOperations)
    Q_PROPERTY(bool displayParameters 
            READ displayParameters
            WRITE setDisplayParameters)
    Q_PROPERTY(bool maxLevel 
            READ maxLevel
            WRITE setMaxLevel)
public:
    InstanceModel(QObject *parent = 0);
    virtual ~InstanceModel();

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

    // void save(QVariant& settings);
    // void load(const QVariant& settings);

    bool displayOperations() const;
    bool displayParameters() const;
    int maxLevel() const;

    bool isOperationNode(const QModelIndex& index) const;
    bool isInstanceNode(const QModelIndex& index) const;

    OperationDescriptor_ptr getOperation(const QString& instance,
            const QString& operation) const;

    Objref_ptr getInstance(const QModelIndex&) const;
    Objref_ptr getInstance(const QString&) const;

public slots:

    void registerInstance(Objref_ptr objref);
    void unregisterInstance(ObjectId id);

    void setDisplayOperations(bool value);
    void setDisplayParameters(bool value);
    void setMaxLevel(int value);

signals:

protected:

    typedef QList< InstanceNode_ptr > Nodes_t;
    Nodes_t m_nodes;

    ObjrefRepository m_instances;

    int m_maxLevel;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_INSTANCEMODEL_HPP

