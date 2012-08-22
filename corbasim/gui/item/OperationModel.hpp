#ifndef CORBASIM_GUI_OPERATIONMODEL_HPP
#define CORBASIM_GUI_OPERATIONMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC OperationModel : 
    public QStandardItemModel
{
    Q_OBJECT

public:
    OperationModel(QObject *parent = 0);
    virtual ~OperationModel();

    OperationDescriptor_ptr 
    getOperation(const QString& obj, const QString& op) const;

public slots:

    void registerInstance(const QString& name,
            InterfaceDescriptor_ptr factory);

    void unregisterInstance(const QString& name);

private slots:

    void doubleClicked(const QModelIndex& index);

signals:
    
    void selectedOperation(QString id, 
            OperationDescriptor_ptr op);

protected:

    struct FirstLevelItem
    {
        QString name;
        InterfaceDescriptor_ptr factory;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_OPERATIONMODEL_HPP

