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

    void registerInstance(const std::string& name,
            core::interface_reflective_base const * reflective);

protected:

    struct FirstLevelItem
    {
        std::string name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

} // qt
} // corbasim

#endif // CORBASIM_QT_PLOTMODEL_HPP

