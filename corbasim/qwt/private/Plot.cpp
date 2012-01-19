// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Plot.cpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * CORBASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Plot.hpp"
#include "HistoricData.hpp"

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

#include <limits>

using namespace corbasim::qwt::priv;

Plot::Plot(QWidget *parent):
    QwtPlot(parent), m_idx(0), m_interval(0.0, 10.0)
{
    // panning with the left mouse button
    (void) new QwtPlotPanner(canvas());

    // zoom in/out with the wheel
    QwtPlotMagnifier * mag = new QwtPlotMagnifier(canvas());
    mag->setAxisEnabled(xBottom, false);

    // axes
    setAxisTitle(xBottom, "Sample");
    setAxisTitle(yLeft, "Value");

    setAxisScale(yLeft, std::numeric_limits< short >::min(), 
            std::numeric_limits< short >::max());

    // canvas
    canvas()->setLineWidth(1);
    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas()->setBorderRadius(15);

    QPalette canvasPalette(Qt::white);
    canvasPalette.setColor( 
            QPalette::Foreground, QColor(133, 190, 232));
    canvas()->setPalette(canvasPalette);

    populate();
}

void Plot::populate()
{
    // Insert new curve
    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush,
                QPen(Qt::black), QSize(5, 5)));
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
    curve->setPen(QPen(Qt::red));
    curve->attach(this);
    
    setAxisScale(xBottom,
        m_interval.minValue(), m_interval.maxValue());

    m_data = new HistoricData();
    curve->setData(m_data);
}

void Plot::update()
{
    size_t size = m_data->size();

    if (size - 1 > m_interval.maxValue())
    {
        double w = m_interval.width();

        m_interval.setMinValue(size - 1 - w);
        m_interval.setMaxValue(size - 1);

        setAxisScale(xBottom,
            m_interval.minValue(), m_interval.maxValue());
    }

    replot();
}

void Plot::append(const QVector< double >& v)
{
    // TODO
    QwtPlotMarker *mY = new QwtPlotMarker();
    mY->setLabel(QTime::currentTime().toString("hh:mm:ss.zzz"));
    mY->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::VLine);
    mY->setXValue(m_data->size());
    mY->attach(this);

    m_data->append(v);

    // TODO insert a marker
    m_idx++;

    update();
}

void Plot::append(double v)
{
    m_data->append(v);
    update();
}

void Plot::displayedSamples(int samples)
{
    m_interval.setMaxValue(m_interval.minValue() + (double) samples);

    setAxisScale(xBottom,
        m_interval.minValue(), m_interval.maxValue() );

    replot();
}

void Plot::clear()
{
    // TODO
}

