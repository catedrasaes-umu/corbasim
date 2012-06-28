#ifndef CORBASIM_QT_FILTERMODEL_HPP
#define CORBASIM_QT_FILTERMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <list>
#include <map>
#include <corbasim/qt/export.hpp>

namespace corbasim
{
namespace qt
{

class CORBASIM_QT_DECLSPEC FilterModel : public QStandardItemModel
{
    Q_OBJECT

public:
    FilterModel(QObject *parent = 0);
    virtual ~FilterModel();

    virtual bool setData(const QModelIndex & index, 
            const QVariant& value, 
            int role = Qt::EditRole);

    bool visibleOperation(const QString& name, tag_t tag) const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

signals:

    void filterChanged();

protected:

    struct FirstLevelItem
    {
        QString name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;
    typedef std::map< QString, FirstLevelItem* > FirstLevelItemsByName_t;

    FirstLevelItems_t m_items;
    FirstLevelItemsByName_t m_itemsByName;
};

} // qt
} // corbasim

#endif // CORBASIM_QT_FILTERMODEL_HPP

