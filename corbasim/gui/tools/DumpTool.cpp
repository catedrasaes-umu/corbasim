// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DumpTool.cpp
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

#include "DumpTool.hpp"
#include <corbasim/gui/utils.hpp>
#include <corbasim/core/file_format_helper.hpp>
#include <QHBoxLayout>
#include <QTreeView>

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace corbasim::gui;

DumpProcessor::DumpProcessor(Objref_ptr object,
        const ReflectivePath_t path, 
        const Config& config) :
    RequestProcessor(object, path), m_config(config),
    m_currentIndex(0)
{
    switch(m_config.format)
    {
    case FORMAT_JSON:
        m_extension = ".json";
        break;

    case FORMAT_TEXT:
        m_extension = ".txt";
        break;

    case FORMAT_BINARY:
        m_extension = ".bin";
        break;

    default:
        break;
    }
    
    nextFile();
}

DumpProcessor::~DumpProcessor()
{
}

void DumpProcessor::nextFile()
{
    std::ostringstream oss;

    oss << m_config.filePrefix 
        << std::setfill('0')
        << std::setw(m_config.suffixLength)
        << m_currentIndex
        << m_extension;

    m_nextFile = oss.str();
}

void DumpProcessor::process(Request_ptr req, 
        TypeDescriptor_ptr ref,
        Holder hold)
{
    using namespace ::corbasim::core;

    std::ios_base::openmode flags = std::ios_base::out;

    const file_format_factory * factory = 
        file_format_factory::get_instance();

    if (!m_config.multipleFiles)
    {
        flags = flags | std::ios_base::app;
    }

    try 
    {
        switch(m_config.format)
        {
        case FORMAT_JSON:
            {
                std::ofstream out(m_nextFile.c_str(), flags);

                factory->get_helper(FILE_FORMAT_JSON)->save(out, ref, hold);
                
                out.close();
            }
            break;

        case FORMAT_TEXT:
            {
                std::ofstream out(m_nextFile.c_str(), flags);

                factory->get_helper(FILE_FORMAT_TEXT)->save(out, ref, hold);

                out.close();
            }
            break;

        case FORMAT_BINARY:
            {
                flags = flags | std::ios::binary;

                std::ofstream out(m_nextFile.c_str(), flags);

                factory->get_helper(FILE_FORMAT_BINARY)->save(out, ref, hold);

                out.close();
            }
            break;

        default:
            break;
        }
    } 
    catch(...) 
    {
    }

    if (m_config.multipleFiles)
    {
        m_currentIndex++;
        nextFile();
    }
}

// Reflective plot

Dumper::Dumper(Objref_ptr objref,
        OperationDescriptor_ptr reflective,
        const QList< int >& path, 
        QWidget * parent) :
    AbstractInputItem(objref, reflective, path, parent)
{
    const QString& id = objref->name();

    QGridLayout * layout = new QGridLayout();
    layout->setMargin(0);

    int row = 0;

    m_filePrefix = new QLineEdit();
    QHBoxLayout * prefixLayout = new QHBoxLayout();
    QPushButton * browse = new QPushButton("&Browse");
    prefixLayout->addWidget(m_filePrefix);
    prefixLayout->addWidget(browse);
    layout->addWidget(new QLabel("File prefix"), row, 0);
    layout->addLayout(prefixLayout, row++, 1);

    m_multipleFiles = new QCheckBox();
    m_multipleFiles->setChecked(true);
    layout->addWidget(new QLabel("Multiple files"), row, 0);
    layout->addWidget(m_multipleFiles, row++, 1);
    
    m_suffixLength = new QSpinBox();
    m_suffixLength->setRange(1, 10); 
    m_suffixLength->setValue(4);
    layout->addWidget(new QLabel("Suffix length"), row, 0);
    layout->addWidget(m_suffixLength, row++, 1);

    m_format = new QComboBox();
    m_format->addItem("Binary (*.bin)");
    m_format->addItem("Text (*.txt)");
    m_format->addItem("JSON (*.json)");
    layout->addWidget(new QLabel("Format"), row, 0);
    layout->addWidget(m_format, row++, 1);

    // start and stop button
    m_startStopButton = new QPushButton("&Start/stop");
    m_startStopButton->setCheckable(true);
    QHBoxLayout * startStopLayout = new QHBoxLayout();
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    startStopLayout->addItem(spacer);
    startStopLayout->addWidget(m_startStopButton);
    layout->addLayout(startStopLayout, row++, 1);

    setLayout(layout);

    connect(m_startStopButton,
            SIGNAL(clicked(bool)),
            this, SLOT(doStart(bool)));

    connect(m_startStopButton,
            SIGNAL(toggled(bool)),
            this, SLOT(setEnabled(bool)));

    connect(browse, SIGNAL(clicked()),
            this, SLOT(browse()));

    QString defaultFile(id);
    defaultFile += ".";
    defaultFile += getFieldName(reflective, path);
    defaultFile += "-";
    m_filePrefix->setText(defaultFile);
}

Dumper::~Dumper()
{
}

void Dumper::browse()
{
    const QString file = QFileDialog::getSaveFileName(this, 
            "Select a file...", ".");

    m_filePrefix->setText(file);
}

void Dumper::setEnabled(bool enabled)
{
    m_filePrefix->setEnabled(!enabled);
    m_format->setEnabled(!enabled);
    m_suffixLength->setEnabled(!enabled);
    m_multipleFiles->setEnabled(!enabled);
}

void Dumper::doStart(bool start)
{
    reset();

    if (start)
    {
        const QString& file (m_filePrefix->text());

        if (file.isEmpty())
        {
            m_startStopButton->setChecked(false);
        }
        else
        {
            const DumpProcessor::Config config = {
                m_multipleFiles->isChecked(),
                file.toStdString(),
                static_cast< DumpProcessor::Format >(m_format->currentIndex()),
                m_suffixLength->value()
            };
            
            DumpProcessor * processor =
                new DumpProcessor(m_objref, m_path, config);

            m_processor.reset(processor);

            emit addProcessor(m_processor);
        }
    }
}

void Dumper::reset()
{
    if (m_processor)
    {
        emit removeProcessor(m_processor);
        m_processor.reset();
    }
}

DumpTool::DumpTool(QWidget * parent) :
    AbstractInputTool(parent)
{
}

DumpTool::~DumpTool()
{
}

AbstractInputItem * DumpTool::createItem(
        Objref_ptr objref, 
        OperationDescriptor_ptr reflective,
        const QList< int >& path)
{
    return new Dumper(objref, reflective, path);
}

// Save and load

void Dumper::save(QVariant& settings)
{
    QVariantMap map;

    const QString& file (m_filePrefix->text());

    map["file_prefix"] = file;
    map["multiple_files"] = m_multipleFiles->isChecked();
    map["format"] = m_format->currentText();
    map["suffix_length"] = m_suffixLength->value();
    map["running"] = m_startStopButton->isChecked();

    settings = map;
}

void Dumper::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    m_filePrefix->setText(map["file_prefix"].toString());
    m_multipleFiles->setChecked(map["multiple_files"].toBool());

    m_suffixLength->setValue(map["suffix_length"].toInt());

    int format = m_format->findText(map["format"].toString());

    if (format != -1)
    {
        m_format->setCurrentIndex(format);
    }

    m_startStopButton->setChecked(map["running"].toBool());
}

