#ifndef CORBASIM_GUI_OPERATIONMODEL_HPP
#define CORBASIM_GUI_OPERATIONMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC OperationParametersModel : 
    public QStandardItemModel
{
    Q_OBJECT

public:
    OperationParametersModel(QObject *parent = 0);
    virtual ~OperationParametersModel();

    virtual bool setData(const QModelIndex & index, 
            const QVariant& value, 
            int role = Qt::EditRole);

    OperationDescriptor_ptr 
    getReflective() const;

public slots:

    void initialize(
            OperationDescriptor_ptr reflective);

    void check(const QList< int >& path);
    void uncheck(const QList< int >& path);

signals:

    void checked(
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

    void unchecked(
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

protected:

    void insertRecursive(QStandardItem * parent, 
        TypeDescriptor_ptr reflective);

    virtual bool isCheckable(TypeDescriptor_ptr reflective);
            
    OperationDescriptor_ptr m_reflective;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_OPERATIONMODEL_HPP

