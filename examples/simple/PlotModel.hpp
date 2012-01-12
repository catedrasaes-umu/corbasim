#ifndef CORBASIM_QT_PLOTMODEL_HPP
#define CORBASIM_QT_PLOTMODEL_HPP

#include <QStandardItemModel>
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

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

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

