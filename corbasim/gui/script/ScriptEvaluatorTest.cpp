#include <corbasim/gui/Application.hpp>
#include <corbasim/gui/script/ScriptEvaluator.hpp>
#include <corbasim/gui/utils.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "You must specify an interface full qualified name"
            << std::endl;
        return -1;
    }

    QApplication app(argc, argv);

    // Required by evaluator
    corbasim::gui::Application application;

    corbasim::core::interface_reflective_base const * reflective =
        corbasim::gui::getReflectiveByFQN(argv[1]);

    if (!reflective)
    {
        std::cerr << "Library not found: " << argv[1] << std::endl;
        return -1;
    }

    corbasim::gui::ScriptEvaluatorWidget ev;
    ev.initialize(reflective);

    ev.show();

    int res = app.exec();

    return res;
}

