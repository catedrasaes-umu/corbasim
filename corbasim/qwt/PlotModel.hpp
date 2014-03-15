#ifndef CORBASIM_QWT_PLOTMODEL_HPP
#define CORBASIM_QWT_PLOTMODEL_HPP

#include <corbasim/qwt/export.hpp>
#include <corbasim/gui/item/ParametersModel.hpp>

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
    virtual bool isCheckable(gui::TypeDescriptor_ptr reflective) const;
};

} // qwt
} // corbasim

#endif // CORBASIM_QWT_PLOTMODEL_HPP

