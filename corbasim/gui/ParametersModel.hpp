#ifndef CORBASIM_GUI_PARAMETERSMODEL_HPP
#define CORBASIM_GUI_PARAMETERSMODEL_HPP

#include <list>
#include <QStandardItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/export.hpp>

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

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

    void uncheck(const QString& id, const QList< int >& path);

signals:

    void checked(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

    void unchecked(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

protected:

    void insertRecursive(QStandardItem * parent, 
        corbasim::core::reflective_base const * reflective);

    virtual bool isCheckable(core::reflective_base const * reflective);

    struct FirstLevelItem
    {
        QString name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_PARAMETERSMODEL_HPP

