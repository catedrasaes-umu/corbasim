#ifndef CORBASIM_GUI_FILTERMODEL_HPP
#define CORBASIM_GUI_FILTERMODEL_HPP

#include <QMap>
#include <QStandardItemModel>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC FilterModel : public QStandardItemModel
{
    Q_OBJECT

public:
    FilterModel(QObject *parent = 0);
    virtual ~FilterModel();

    virtual bool setData(const QModelIndex & index,
            const QVariant& value,
            int role = Qt::EditRole);

    bool visibleOperation(ObjectId id, tag_t tag) const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void registerInstance(Objref_ptr objref);

    void unregisterInstance(ObjectId id);

signals:

    void filterChanged();

protected:

    typedef QMap< tag_t, QStandardItem * > OperationsMap_t;

    struct FirstLevelItem
    {
        Objref_ptr objref;
        OperationsMap_t operations;
        QStandardItem * item;
    };

    typedef QMap< ObjectId, FirstLevelItem > FirstLevelItems_t;

    ObjrefRepository m_instances;

    FirstLevelItems_t m_items;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_FILTERMODEL_HPP

