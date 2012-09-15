#include "PlotModel.hpp"
#include <iostream>

using namespace corbasim::qwt;

PlotModel::PlotModel(QObject *parent)
    : ::corbasim::gui::ParametersModel(parent)
{
}

PlotModel::~PlotModel()
{
}

bool PlotModel::isCheckable(gui::TypeDescriptor_ptr reflective) const
{
    while (reflective->is_repeated())
        reflective = reflective->get_slice();

   return (reflective->is_primitive());
}

