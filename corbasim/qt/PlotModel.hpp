#ifndef CORBASIM_QT_PLOTMODEL_HPP
#define CORBASIM_QT_PLOTMODEL_HPP

#include <QStandardItemModel>
#if 0
#include <QIdentityProxyModel>
#else
#include <QProxyModel>
#endif
#include <corbasim/core/reflective_fwd.hpp>
#include <list>

namespace corbasim
{
namespace qt
{

class PlotModel : public QStandardItemModel
{
    Q_OBJECT

public:
    PlotModel(QObject *parent = 0);
    virtual ~PlotModel();

    virtual bool setData(const QModelIndex & index, const QVariant& value, 
            int role = Qt::EditRole);

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

    void deletePlot(const QString& id, const QList< int >& path);

signals:

    void createdPlot(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

    void deletedPlot(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

protected:

    struct FirstLevelItem
    {
        QString name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

class ReflectiveModel : public QStandardItemModel
{
    Q_OBJECT

public:
    ReflectiveModel(QObject *parent = 0);
    virtual ~ReflectiveModel();

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

protected:

    struct FirstLevelItem
    {
        const QString name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

// QIdentityProxyModel Only in Qt 4.8
class CheckedReflectiveModel : public 
#if 0
                               QIdentityProxyModel
#else
                               QProxyModel
#endif
{
    Q_OBJECT
public:
    CheckedReflectiveModel(QObject * parent = 0);
    virtual ~CheckedReflectiveModel();

    void setReflectiveModel(ReflectiveModel * model);

    Qt::ItemFlags flags(const QModelIndex& index) const;

protected:
    ReflectiveModel * m_model;

};

} // qt
} // corbasim

#endif // CORBASIM_QT_PLOTMODEL_HPP

