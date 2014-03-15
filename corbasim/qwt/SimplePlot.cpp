// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SimplePlot.cpp
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

#include "SimplePlot.hpp"
#include "private/Plot.hpp"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QPushButton>

#include <limits>

using namespace corbasim::qwt;

struct SimplePlot::Data
{
    priv::Plot * plot;
    QDoubleSpinBox * spYMin;
    QDoubleSpinBox * spYMax;
};

SimplePlot::SimplePlot(QWidget * parent) :
    QWidget(parent), m_data(new Data())
{
    QHBoxLayout * mainLayout = new QHBoxLayout();

    // Plot
    QWidget * plotW = new QWidget(this);
    QHBoxLayout * plotL = new QHBoxLayout(plotW);
    m_data->plot = new priv::Plot(plotW);
    // m_data->plot->setTitle(title);

    // plotL->setContentsMargins(0, 0, 0, 0);
    plotL->addWidget(m_data->plot);
    plotW->setLayout(plotL);
    mainLayout->addWidget(m_data->plot);

    setMinimumSize(600, 350);

    QPushButton * bt = new QPushButton();
    bt->setCheckable(true);
    bt->setMaximumWidth(15);
    bt->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addWidget(bt);

    // Options
    QWidget * gw = new QWidget();
    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("Displayed samples"), 0, 0);
    QSpinBox * spSamples = new QSpinBox();
    gridLayout->addWidget(spSamples, 0, 1);
#if 0
    // X
    QGroupBox * gbX = new QGroupBox("Display X");
    QGridLayout * lX = new QGridLayout();
    lX->addWidget(new QLabel("min"), 0, 0);
    lX->addWidget(new QLabel("max"), 1, 0);
    QSpinBox * spXMin = new QSpinBox();
    lX->addWidget(spXMin, 0, 1);
    QSpinBox * spXMax = new QSpinBox();
    lX->addWidget(spXMax, 1, 1);
    gbX->setLayout(lX);
    gridLayout->addWidget(gbX, 1, 0, 1, 2);
#endif
    // Y
    QGroupBox * gbY = new QGroupBox("Display Y");
    QGridLayout * lY = new QGridLayout();
    lY->addWidget(new QLabel("min"), 0, 0);
    lY->addWidget(new QLabel("max"), 1, 0);
    QDoubleSpinBox * spYMin = new QDoubleSpinBox();
    lY->addWidget(spYMin, 0, 1);
    QDoubleSpinBox * spYMax = new QDoubleSpinBox();
    lY->addWidget(spYMax, 1, 1);
    gbY->setLayout(lY);
    gridLayout->addWidget(gbY, 2, 0, 1, 2);
    m_data->spYMin = spYMin;
    m_data->spYMax = spYMax;

    spYMin->setValue(-10.0);
    spYMax->setValue(10.0);

    connect(spYMin, SIGNAL(valueChanged(double)),
            this, SLOT(updateY()));
    connect(spYMax, SIGNAL(valueChanged(double)),
            this, SLOT(updateY()));

    // Spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20,
            QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(spacer, 3, 0, 1);

    gw->setLayout(gridLayout);
    mainLayout->addWidget(gw);

    // Ranges
    spSamples->setRange(10, std::numeric_limits< int >::max());
#if 0
    spXMin->setRange(0, std::numeric_limits< int >::max());
    spXMax->setRange(10, std::numeric_limits< int >::max());
#endif
    spYMin->setRange(std::numeric_limits< int >::min(),
            std::numeric_limits< int >::max());
    spYMax->setRange(std::numeric_limits< int >::min(),
            std::numeric_limits< int >::max());

    // Signals
    connect(spSamples, SIGNAL(valueChanged(int)),
            m_data->plot, SLOT(displayedSamples(int)));

    connect(bt, SIGNAL(toggled(bool)),
            gw, SLOT(setVisible(bool)));

    gw->hide();

    setLayout(mainLayout);

    updateY();
}

SimplePlot::~SimplePlot()
{
    delete m_data;
}

void SimplePlot::append(const QVector< double >& v)
{
    m_data->plot->append(v);
}

void SimplePlot::append(double v)
{
    m_data->plot->append(v);
}

void SimplePlot::updateY()
{
    m_data->spYMin->setMaximum(m_data->spYMax->value());
    m_data->spYMax->setMinimum(m_data->spYMin->value());

    m_data->plot->setAxisScale(QwtPlot::yLeft,
        m_data->spYMin->value(),
        m_data->spYMax->value());

    m_data->plot->replot();
}

