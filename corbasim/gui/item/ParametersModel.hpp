#ifndef CORBASIM_GUI_PARAMETERSMODEL_HPP
#define CORBASIM_GUI_PARAMETERSMODEL_HPP

#include <list>
#include <QStandardItemModel>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/item/InstanceModel.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC ParametersModel : 
    public InstanceModel
{
    Q_OBJECT

public:
    ParametersModel(QObject *parent = 0);
    virtual ~ParametersModel();

    InterfaceDescriptor_ptr getReflective(const QString& id) const;

protected:

    virtual bool isCheckable(TypeDescriptor_ptr reflective) const;
};

} // gui
} // corbasim

#endif // CORBASIM_GUI_PARAMETERSMODEL_HPP

