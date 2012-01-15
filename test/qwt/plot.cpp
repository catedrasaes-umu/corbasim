#include "producer.hpp"

Plot::Plot( QWidget *parent ):
    QwtPlot( parent ), m_idx(0), m_interval(0.0, 10.0)
{
    // panning with the left mouse button
    ( void ) new QwtPlotPanner( canvas() );

    // zoom in/out with the wheel
    ( void ) new QwtPlotMagnifier( canvas() );

    setAutoFillBackground( true );
    setPalette( QPalette( QColor( 165, 193, 228 ) ) );

    setTitle( "A Simple QwtPlot Demonstration" );

    // axes
    setAxisTitle( xBottom, "Sample" );
    setAxisTitle( yLeft, "Value" );

    // canvas
    canvas()->setLineWidth( 1 );
    canvas()->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas()->setBorderRadius( 15 );

    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
    canvas()->setPalette( canvasPalette );

    populate();
}

void Plot::populate()
{
    // Insert new curve
    QwtPlotCurve *curve = new QwtPlotCurve("");
    curve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::NoBrush,
                QPen( Qt::black ), QSize( 5, 5 ) ) );
    curve->setRenderHint( QwtPlotItem::RenderAntialiased );
    curve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
    curve->setPen( QPen( Qt::red ) );
    curve->attach( this );
    
    setAxisScale(xBottom,
        m_interval.minValue(), m_interval.maxValue() );

    m_data = new HistoricData();
    curve->setData(m_data);
}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    Plot *plot = new Plot();

    // We put a dummy widget around to have
    // so that Qt paints a widget background
    // when resizing

    QWidget window;
    QHBoxLayout *layout = new QHBoxLayout( &window );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( plot );

    window.resize( 600, 400 );
    window.show();



    DataProducer producer;
    producer.show();

    QObject::connect(&producer, SIGNAL(produced(double)), plot, SLOT(append(double)));

    return a.exec();
}
