#include "simpleC.h"
#include "simple_adapted.hpp"
#include "simple_servant.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/gui/gui_factory.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include <QtGui>
#include <corbasim/qwt/ReflectivePlotTool.hpp>
#include <corbasim/qt/OperationSequence.hpp>

void print(corbasim::core::reflective_base const * current, 
        unsigned int level = 0)
{
    if (current->is_primitive()) return;

    // TODO implement slice type
    if (current->is_repeated()) return;
    
    unsigned int count;
    if ((count = current->get_children_count()) > 0)
    {
        for (unsigned int i = 0; i < count; i++) 
        {
            corbasim::core::reflective_base const * child = 
                current->get_child(i);

            std::cout << std::string(level * 4, ' ') 
                << current->get_child_name(i) << std::endl;

            print(child, level + 1);
        }
    }
}

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    const corbasim::core::reflective< SimpleExample::Padre > ref;

    print(&ref);

    corbasim::core::interface_reflective_base const * iface = 
        corbasim::core::interface_reflective< SimpleExample::Test >::get_instance();

    corbasim::gui::gui_factory_base const * fac = 
        corbasim::gui::gui_factory< SimpleExample::Test >::get_instance();

    corbasim::qt::OperationSequenceTool seq;
    seq.objrefCreated("prueba", fac);
    seq.show();

    corbasim::qwt::ReflectivePlotTool tool;
    tool.registerInstance("prueba", iface);
    tool.show();

    QObject::connect(&seq, 
            SIGNAL(sendRequest(QString, corbasim::event::request_ptr)),
            &tool,
            SLOT(processRequest(const QString&, corbasim::event::request_ptr)));

    return app.exec();
}

