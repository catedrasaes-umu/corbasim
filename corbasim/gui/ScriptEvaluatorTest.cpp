#include <corbasim/gui/ScriptEvaluator.hpp>
#include <QLibrary>

namespace  
{
    ::corbasim::core::interface_reflective_base const * 
    getReflectiveByFQN(const char * fqn)
    {
        QString symbol (fqn);
        symbol.replace("::","_");
        symbol.prepend("corbasim_reflective_");

        typedef const corbasim::core::interface_reflective_base *
            (*get_reflective_t)();
        get_reflective_t get_reflective = NULL;

        QLibrary lib(symbol);

        if (lib.load() && 
                (get_reflective = (get_reflective_t) 
                     lib.resolve(symbol.toStdString().c_str())) != NULL)
        {
            return get_reflective();
        }

        return NULL;
    }
} // namespace 

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    corbasim::gui::ScriptEvaluator ev;
    ev.initialize(getReflectiveByFQN(argv[1]));

    ev.show();

    return app.exec();
}

