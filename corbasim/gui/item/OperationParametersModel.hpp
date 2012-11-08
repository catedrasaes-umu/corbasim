#ifndef CORBASIM_GUI_PARAMETERSMODEL_HPP
#define CORBASIM_GUI_PARAMETERSMODEL_HPP

#include <list>
#include <QAbstractItemModel>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/item/ModelNode.hpp>

namespace corbasim
{
namespace gui
{

class OperationParametersModel : 
    public QAbstractItemModel
{
    Q_OBJECT

public:
    OperationParametersModel(QObject *parent = 0);
    virtual ~OperationParametersModel();

    // QAbstractItemModel
    QVariant data(const QModelIndex& index, 
            int role = Qt::DisplayRole) const; 
    virtual bool setData(const QModelIndex & index, 
            const QVariant& value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    // End QAbstractItemModel

    // Single instance
    void initialize(
            int idx,
            OperationDescriptor_ptr reflective);

    OperationDescriptor_ptr 
    getReflective() const;

public slots:

    // Single instance
    void check(
            const QList< int >& path);

    void uncheck(
            const QList< int >& path);

signals:

    // Single instance
    void checked(
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

    void unchecked(
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

protected:

    virtual bool isCheckable(TypeDescriptor_ptr reflective) const;

    int m_idx;
    QString m_name;
    OperationDescriptor_ptr m_reflective;
    DescriptorNode_ptr m_node;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_PARAMETERSMODEL_HPP

