#include <corbasim/gui/server/ServerApp.hpp>

int main(int argc, char **argv)
{
    corbasim::gui::ServerApp app(argc, argv);

    return app.exec();
}
