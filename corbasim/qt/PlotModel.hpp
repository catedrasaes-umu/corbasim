#ifndef CORBASIM_QT_PLOTMODEL_HPP
#define CORBASIM_QT_PLOTMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <list>
#include <corbasim/qt/export.hpp>

namespace corbasim
{
namespace qt
{

class CORBASIM_QT_DECLSPEC PlotModel : public QStandardItemModel
{
    Q_OBJECT

public:
    PlotModel(QObject *parent = 0);
    virtual ~PlotModel();

    virtual bool setData(const QModelIndex & index, 
            const QVariant& value, 
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

} // qt
} // corbasim

#endif // CORBASIM_QT_PLOTMODEL_HPP

