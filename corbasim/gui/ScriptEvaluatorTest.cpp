#include <corbasim/gui/ScriptEvaluator.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/Sender.hpp>
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

    ::corbasim::core::interface_reflective_base const * reflective = 
        ::corbasim::gui::getReflectiveByFQN(argv[1]);

    if (!reflective)
    {
        std::cerr << "Library not found: " << argv[1] << std::endl;
        return -1;
    }

    corbasim::gui::SenderController * senderController =
        corbasim::gui::SenderController::getInstance();

    QThread senderThread;
    senderController->moveToThread(&senderThread);

    senderController->start();
    senderThread.start();

    corbasim::gui::ScriptEvaluator ev;
    ev.initialize(reflective);

    ev.show();

    int res = app.exec();

    senderController->stop();
    senderThread.quit();
    senderController->join();
    senderThread.wait();

    return res;
}

