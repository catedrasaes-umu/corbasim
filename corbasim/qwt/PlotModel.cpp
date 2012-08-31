#include "PlotModel.hpp"
#include <iostream>
#include <boost/next_prior.hpp>

using namespace corbasim::qwt;

PlotModel::PlotModel(QObject *parent)
    : ::corbasim::gui::ParametersModel(parent)
{
    QStringList headers;
    headers << "Plotable parameters";

    setHorizontalHeaderLabels(headers);
}

PlotModel::~PlotModel()
{
}

bool PlotModel::isCheckable(gui::TypeDescriptor_ptr reflective)
{
    while (reflective->is_repeated())
        reflective = reflective->get_slice();

   return (reflective->is_primitive());
}

