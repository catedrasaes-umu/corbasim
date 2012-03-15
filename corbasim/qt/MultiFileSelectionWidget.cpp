// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MultiFileSelectionWidget.cpp
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

#include "MultiFileSelectionWidget.hpp"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>

using namespace corbasim::qt;

MultiFileSelectionWidget::MultiFileSelectionWidget(QWidget * parent) :
    QWidget(parent)
{
    QGridLayout * mainLayout = new QGridLayout;
    QHBoxLayout * layout = new QHBoxLayout;

    // File Selection
    mainLayout->addWidget(new QLabel("Input files"), 0, 0);

    m_leSelectedFiles = new QLineEdit;
    m_leSelectedFiles->setReadOnly(true);
    layout->addWidget(m_leSelectedFiles);

    QPushButton * btn = new QPushButton("Browse");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(showSelectionDialog()));
    layout->addWidget(btn);
    mainLayout->addLayout(layout, 0, 1);
    
    // Next file
    mainLayout->addWidget(new QLabel("Next file to send"), 1, 0);
    m_leNextFile = new QLineEdit;
    m_leNextFile->setReadOnly(true);
    mainLayout->addWidget(m_leNextFile, 1, 1);

    // Current index
    m_sbCurrentIndex = new QSpinBox;
    mainLayout->addWidget(new QLabel("Current index"), 2, 0);
    mainLayout->addWidget(m_sbCurrentIndex, 2, 1);
    QObject::connect(m_sbCurrentIndex, SIGNAL(valueChanged(int)), 
            this, SLOT(currentIndexChanged(int)));

    // Repeat
    m_ckRepeat = new QCheckBox;
    m_ckRepeat->setChecked(true);
    mainLayout->addWidget(new QLabel("Repeat"), 3, 0);
    mainLayout->addWidget(m_ckRepeat, 3, 1);

    // Restart
    QHBoxLayout * restartLayout = new QHBoxLayout();
    // Spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    restartLayout->addItem(spacer);

    QPushButton * btnRestart = new QPushButton("&Restart");
    QObject::connect(btnRestart, SIGNAL(clicked()), 
            this, SLOT(restart()));
    restartLayout->addWidget(btnRestart);
    mainLayout->addLayout(restartLayout, 4, 1);

    setLayout(mainLayout);
}

MultiFileSelectionWidget::~MultiFileSelectionWidget()
{
}

const QStringList& MultiFileSelectionWidget::selectedFiles() const
{
    return m_selectedFiles;
}

void MultiFileSelectionWidget::setSelectedFiles(const QStringList& list)
{
    m_selectedFiles = list;

    m_leSelectedFiles->setText(m_selectedFiles.join(", "));

    m_sbCurrentIndex->setRange(0, m_selectedFiles.length());
}

bool MultiFileSelectionWidget::repeat() const 
{ 
    return m_ckRepeat->isChecked(); 
}

void MultiFileSelectionWidget::setRepeat(bool r)
{
    m_ckRepeat->setChecked(r);
}

int MultiFileSelectionWidget::currentIndex() const
{
    return m_sbCurrentIndex->value();
}

void MultiFileSelectionWidget::setCurrentIndex(int i)
{
    m_sbCurrentIndex->setValue(i);
}

const QString* MultiFileSelectionWidget::getNext()
{
    const QString * res = 0;

    int currentIndex = m_sbCurrentIndex->value();

    // Curreent file
    if (currentIndex < m_selectedFiles.length())
        res = &m_selectedFiles.at(currentIndex++);

    // Repeat
    if (currentIndex >= m_selectedFiles.length() &&
            m_ckRepeat->isChecked())
        currentIndex = 0;

    // Next file
    else if (currentIndex >= m_selectedFiles.length())
        m_leNextFile->setText("No more files!");

    if (currentIndex < m_selectedFiles.length())
        m_sbCurrentIndex->setValue(currentIndex);

    return res;
}

void MultiFileSelectionWidget::showSelectionDialog()
{
    m_selectedFiles = QFileDialog::getOpenFileNames(this, 
            "Select input files...");

    m_leSelectedFiles->setText(m_selectedFiles.join(", "));

    restart();
}

void MultiFileSelectionWidget::restart()
{
    m_sbCurrentIndex->setValue(0);

    m_sbCurrentIndex->setRange(0, m_selectedFiles.length());
    
    if (!m_selectedFiles.length())
        m_leNextFile->clear();
    else
        m_leNextFile->setText(m_selectedFiles.at(0));
}

void MultiFileSelectionWidget::currentIndexChanged(int val)
{
    // Next file
    if (val < m_selectedFiles.length())
        m_leNextFile->setText(m_selectedFiles.at(val));
}

