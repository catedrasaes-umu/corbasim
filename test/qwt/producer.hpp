#ifndef PRODUCER_
#define PRODUCER_

#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <qwt_symbol.h>

class DataProducer : public QWidget
{
    Q_OBJECT
public:
    DataProducer(QWidget * parent = 0) :
        QWidget(parent)
    {
        QVBoxLayout * layout = new QVBoxLayout();

        sb = new QSpinBox();
        layout->addWidget(sb);

        QPushButton * bt = new QPushButton("Append");

        QObject::connect(bt, SIGNAL(clicked()),
                this, SLOT(btClicked()));
        layout->addWidget(bt);

        setLayout(layout);
    }

private slots:
    void btClicked()
    {
        emit produced(sb->value());
    }

signals:

    void produced(double);

protected:
    QSpinBox * sb;

};

class HistoricData: public QwtPointSeriesData
{
public:
    HistoricData()
    {
    }

    void append(double v)
    {
        d_samples.push_back(QPointF(d_samples.size(), v));
    }

    void append(const QVector< double >& v)
    {
        // TODO
    }
};

class Plot : public QwtPlot
{
    Q_OBJECT
public:
    Plot( QWidget *parent = NULL );

public slots:

    void update()
    {
        size_t size = m_data->size();

        if (size - 1 > m_interval.maxValue())
        {
            double w = m_interval.width();

            m_interval.setMinValue(size - 1 - w);
            m_interval.setMaxValue(size - 1);

            setAxisScale(xBottom,
                m_interval.minValue(), m_interval.maxValue() );
        }

        replot();
    }

    void append(const QVector< double >& v)
    {
        m_data->append(v);

        // TODO insert a marker
        m_idx++;

        update();
    }

    void append(double v)
    {
        m_data->append(v);
        update();
    }

protected:
    void populate();

    unsigned long long m_idx;
    QwtInterval m_interval;
    HistoricData * m_data;
};

#endif /* PRODUCER_ */
