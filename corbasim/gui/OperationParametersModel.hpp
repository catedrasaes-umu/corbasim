#ifndef CORBASIM_GUI_OPERATIONMODEL_HPP
#define CORBASIM_GUI_OPERATIONMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/export.hpp>

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

    core::operation_reflective_base const * 
    getReflective(const QString& id) const;

public slots:

    void initialize(
            core::operation_reflective_base const * reflective);

    void check(const QList< int >& path);
    void uncheck(const QList< int >& path);

signals:

    void checked(
            core::operation_reflective_base const * reflective,
            const QList< int >& path);

    void unchecked(
            core::operation_reflective_base const * reflective,
            const QList< int >& path);

protected:

    void insertRecursive(QStandardItem * parent, 
        corbasim::core::reflective_base const * reflective);

    virtual bool isCheckable(core::reflective_base const * reflective);
            
    ::corbasim::core::operation_reflective_base const * m_reflective;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_OPERATIONMODEL_HPP

