#include <corbasim/qwt/SimplePlot.hpp>
#include <corbasim/qwt/ReflectivePlotTool.hpp>
#include <QtGui>

#include "producer.hpp"

using namespace corbasim::qwt;

int main( int argc, char **argv )
{
    QApplication a(argc, argv);

    SimplePlot plot("Example");
    plot.show();

    DataProducer producer;
    producer.show();

    QObject::connect(&producer, SIGNAL(produced(double)), 
            &plot, SLOT(append(double)));

    ReflectivePlotTool tool;
    tool.show();

    return a.exec();
}
