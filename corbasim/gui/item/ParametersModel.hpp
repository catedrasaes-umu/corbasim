#ifndef CORBASIM_GUI_PARAMETERSMODEL_HPP
#define CORBASIM_GUI_PARAMETERSMODEL_HPP

#include <list>
#include <QStandardItemModel>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC ParametersModel : public QStandardItemModel
{
    Q_OBJECT

public:
    ParametersModel(QObject *parent = 0);
    virtual ~ParametersModel();

    virtual bool setData(const QModelIndex & index, 
            const QVariant& value, 
            int role = Qt::EditRole);

    InterfaceDescriptor_ptr 
    getReflective(const QString& id) const;

public slots:

    void registerInstance(const QString& name,
            InterfaceDescriptor_ptr reflective);

    void unregisterInstance(const QString& name);

    void check(const QString& id, const QList< int >& path);
    void uncheck(const QString& id, const QList< int >& path);

signals:

    void checked(const QString& id, 
            InterfaceDescriptor_ptr reflective,
            const QList< int >& path);

    void unchecked(const QString& id, 
            InterfaceDescriptor_ptr reflective,
            const QList< int >& path);

protected:

    void insertRecursive(QStandardItem * parent, 
        TypeDescriptor_ptr reflective);

    virtual bool isCheckable(TypeDescriptor_ptr reflective);

    struct FirstLevelItem
    {
        QString name;
        InterfaceDescriptor_ptr reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_PARAMETERSMODEL_HPP

