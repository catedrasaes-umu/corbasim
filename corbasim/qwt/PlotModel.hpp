#ifndef CORBASIM_QWT_PLOTMODEL_HPP
#define CORBASIM_QWT_PLOTMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <list>
#include <corbasim/qwt/export.hpp>
#include <corbasim/gui/ParametersModel.hpp>

namespace corbasim
{
namespace qwt
{

class CORBASIM_QWT_DECLSPEC PlotModel : 
    public ::corbasim::gui::ParametersModel
{
    Q_OBJECT

public:
    PlotModel(QObject *parent = 0);
    virtual ~PlotModel();

protected:
    virtual bool isCheckable(core::reflective_base const * reflective);
};

} // qwt
} // corbasim

#endif // CORBASIM_QWT_PLOTMODEL_HPP

