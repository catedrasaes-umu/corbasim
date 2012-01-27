#include "simpleC.h"
#include "simple_adapted.hpp"
#include "simple_servant.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/gui/gui_factory.hpp>
#include <corbasim/core/reflective.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include <QtGui>
#include <corbasim/qwt/ReflectivePlotTool.hpp>
#include <corbasim/qt/OperationSequence.hpp>

#include <corbasim/reflective_gui/ReflectiveGUI.hpp>
#include <corbasim/reflective_gui/OperationSequence.hpp>

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

//    corbasim::reflective_gui::StructWidget w(
//            iface->get_reflective_by_index(0));
//    w.show();

    corbasim::reflective_gui::OperationSequenceTool seq2;
    seq2.objrefCreated("prueba", iface);
    seq2.show();

    QObject::connect(&seq2, 
            SIGNAL(sendRequest(QString, corbasim::event::request_ptr)),
            &tool,
            SLOT(processRequest(const QString&, corbasim::event::request_ptr)));

    {
        corbasim::core::reflective_base const * ref = 
            corbasim::core::reflective< SimpleExample::Hijo >::get_instance();

        SimpleExample::Hijo hijo;

        corbasim::core::holder h(corbasim::core::create_holder(hijo));

        corbasim::core::reflective_base const * bref = ref->get_child(0);

        corbasim::core::holder bh(ref->get_child_value(h, 0));

        bh.to_value< int32_t >() = 10;

        std::cout << hijo.b << std::endl;
    }

    return app.exec();
}

