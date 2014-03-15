#include "ParametersModel.hpp"

using namespace corbasim::gui;

ParametersModel::ParametersModel(QObject *parent)
    : InstanceModel(parent)
{
}

ParametersModel::~ParametersModel()
{
}

InterfaceDescriptor_ptr
ParametersModel::getReflective(const QString& id) const
{
    Objref_ptr obj = getInstance(id);

    if (obj) return obj->interface();

    return NULL;
}

bool ParametersModel::isCheckable(TypeDescriptor_ptr reflective) const
{
    return true;
}


