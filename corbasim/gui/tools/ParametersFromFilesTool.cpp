// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ParametersFromFilesTool.cpp
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

#include "ParametersFromFilesTool.hpp"
#include <corbasim/qt/SortableGroup.hpp>
#include <corbasim/core/file_format_helper.hpp>
#include <corbasim/gui/utils.hpp>
#include <iostream>

using namespace corbasim::gui;

ParametersFromFilesTool::ParametersFromFilesTool(QWidget * parent) :
    QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout(this);

    // Model view
    QTreeView * view = new QTreeView(this);
    view->setModel(&m_model);
    layout->addWidget(view);
    view->setMaximumWidth(300);
    view->setColumnWidth(0, 210);

    // Files
    m_group = new qt::SortableGroup(this);
    m_group->setDelete(false);
    layout->addWidget(m_group);

    setLayout(layout);

    // widget signals
    connect(m_group, 
            SIGNAL(deleteRequested(corbasim::qt::SortableGroupItem *)),
            this, 
            SLOT(deleteRequested(corbasim::qt::SortableGroupItem *)));

    // connect model signals 
    connect(&m_model, 
            SIGNAL(checked(
                    OperationDescriptor_ptr,
                    const QList< int >&)),
            this,
            SLOT(createFilesItem(
                    OperationDescriptor_ptr,
                    const QList< int >&)));
    connect(&m_model, 
            SIGNAL(unchecked(
                    OperationDescriptor_ptr,
                    const QList< int >&)),
            this,
            SLOT(deleteFilesItem(
                    OperationDescriptor_ptr,
                    const QList< int >&)));
    
    setMinimumSize(650, 400);
}

ParametersFromFilesTool::~ParametersFromFilesTool()
{
}

void ParametersFromFilesTool::initialize(
        OperationDescriptor_ptr reflective)
{
    m_model.initialize(reflective);
}

void ParametersFromFilesTool::createProcessors(
        QList< SenderItemProcessor_ptr >& processors)
{
    const QList< qt::SortableGroupItem * >& items = 
        m_group->getItems();

    for (int i = 0; i < items.size(); i++) 
    {
        FilesItem * item = 
            qobject_cast< FilesItem * >(items.at(i)->getWidget());

        processors.push_back(item->createProcessor());
    }
}

FilesItem * ParametersFromFilesTool::createFilesItem( 
        OperationDescriptor_ptr op,
        const QList< int >& path)
{
    FilesItem * plot = NULL;

    if (op)
    {
        plot = new FilesItem(op, path);

        const key_t key(op->get_tag());
        m_map[key].push_back(plot);
        m_inverse_map[plot] = key;

        qt::SortableGroupItem * item = 
            new qt::SortableGroupItem(plot, m_group);

        item->showDetails();

        const QString title(gui::getFieldName(op, path));
        item->setTitle(title);

        m_group->appendItem(item);
    }

    return plot;
}

void ParametersFromFilesTool::deleteFilesItem(
        OperationDescriptor_ptr op,
        const QList< int >& path)
{
    const key_t key(op->get_tag());
    QList< FilesItem * >& list = m_map[key];

    for (int i = 0; i < list.size(); i++) 
    {
        FilesItem * plot = list[i];
        if (plot->getPath() == path)
        {
            list.removeAt(i);
            m_inverse_map.erase(plot);
            m_group->deleteItem(
                    qobject_cast< qt::SortableGroupItem * >
                        (plot->parent()));
            break;
        }
    }
}

void ParametersFromFilesTool::deleteRequested(qt::SortableGroupItem* item)
{
    FilesItem * plot = 
        qobject_cast< FilesItem * >(item->getWidget());

    if (plot)
    {
        inverse_map_t::iterator it = m_inverse_map.find(plot);

        if (it != m_inverse_map.end())
        {
            const key_t key(it->second);
            m_map[key].removeAll(plot);

            // notify to model
            m_model.uncheck(plot->getPath());

            m_inverse_map.erase(it);
        }
    }
    m_group->deleteItem(item);
}

//
//
// Save and load
//
//

void ParametersFromFilesTool::save(QVariant& settings)
{
    const QList< qt::SortableGroupItem * >& items = 
        m_group->getItems();

    QVariantList list;

    for (int i = 0; i < items.size(); i++) 
    {
        QVariant var;

        FilesItem * item = 
            qobject_cast< FilesItem * >(items.at(i)->getWidget());
        item->save(var);

        list << var;
    }

    settings = list;
}

void ParametersFromFilesTool::load(const QVariant& settings)
{
    clear();

    const QVariantList list = settings.toList();

    for (int i = 0; i < list.size(); i++) 
    {
        const QVariant& var = list.at(i);
        const QVariantMap& map = var.toMap();
        const QVariantList rPath = map["path"].toList();
        QList< int > path;

        for (int i = 0; i < rPath.size(); i++) 
        {
            path.push_back(rPath.at(i).toInt());
        }

        FilesItem * item = createFilesItem(
                m_model.getReflective(), path);

        if (item)
        {
            item->load(var);

            m_model.check(path);
        }
    }
}

void ParametersFromFilesTool::clear()
{
    for (inverse_map_t::const_iterator it = m_inverse_map.begin(); 
            it != m_inverse_map.end(); ++it) 
    {
        // notify to model
        m_model.uncheck(it->first->getPath());
    }

    m_map.clear();
    m_inverse_map.clear();
}

//
//
// Files item
//
//

FilesItem::FilesItem(
        OperationDescriptor_ptr reflective,
        const QList< int >& path, 
        QWidget * parent) :
    QWidget(parent), m_reflective(reflective), m_path(path)
{
    QGridLayout * layout = new QGridLayout();

    int row = 0;

    m_filesWidget = new QLineEdit();
    m_filesWidget->setReadOnly(true);
    QHBoxLayout * prefixLayout = new QHBoxLayout();
    QPushButton * browse = new QPushButton("&Browse");
    prefixLayout->addWidget(m_filesWidget);
    prefixLayout->addWidget(browse);
    layout->addWidget(new QLabel("Files"), row, 0);
    layout->addLayout(prefixLayout, row++, 1);

    m_currentFile = new QComboBox();
    layout->addWidget(new QLabel("Next file to send"), row, 0);
    layout->addWidget(m_currentFile, row++, 1);

    m_repeat = new QCheckBox();
    m_repeat->setChecked(true);
    layout->addWidget(new QLabel("Repeat"), row, 0);
    layout->addWidget(m_repeat, row++, 1);
    
    m_format = new QComboBox();
    m_format->addItem("Binary (*.bin)");
    m_format->addItem("Text (*.txt)");
    m_format->addItem("JSON (*.json)");
    layout->addWidget(new QLabel("Format"), row, 0);
    layout->addWidget(m_format, row++, 1);

    setLayout(layout);

    connect(browse, SIGNAL(clicked()),
            this, SLOT(browse()));

    connect(this, SIGNAL(nextFile(int)),
            m_currentFile, SLOT(setCurrentIndex(int)));
}

FilesItem::~FilesItem()
{
}

void FilesItem::browse()
{
    m_files = QFileDialog::getOpenFileNames(this, 
            "Select some files...", ".");

    m_filesWidget->setText(m_files.join(", "));
    m_currentFile->clear();
    m_currentFile->addItems(m_files);
}

OperationDescriptor_ptr FilesItem::getReflective() const
{
    return m_reflective;
}

//
//
// Properties
// 
//

const QStringList& FilesItem::files() const 
{
    return m_files;
}

int FilesItem::currentFile() const 
{
    return m_currentFile->currentIndex();
}

int FilesItem::format() const 
{
    return m_format->currentIndex();
}

bool FilesItem::repeat() const 
{
    return m_repeat->isChecked();
}

FilesItemProcessor_ptr FilesItem::createProcessor()
{
    FilesItemProcessor_ptr processor(
        new FilesItemProcessor(
                m_reflective,
                m_path,
                files(),
                currentFile(),
                format(),
                repeat()));

    return processor;
}

//
//
// Save and load
//
//

void FilesItem::save(QVariant& settings)
{
    QVariantMap map;

    map["operation"] = m_reflective->get_name();
    map["title"] = gui::getFieldName(m_reflective, m_path);

    QVariantList list;
    for (int i = 0; i < m_path.size(); i++) 
    {
        list << m_path.at(i);
    }
    map["path"] = list;

    map["files"] = files();
    map["current_file"] = currentFile();
    map["repeat"] = repeat();
    map["format"] = m_format->currentText();

    settings = map;
}

void FilesItem::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    m_files = map["files"].toStringList();
    m_filesWidget->setText(m_files.join(", "));
    m_currentFile->clear();
    m_currentFile->addItems(m_files);

    m_currentFile->setCurrentIndex(map["current_file"].toInt());
    m_repeat->setChecked(map["repeat"].toBool());
    m_format->setCurrentIndex(m_format->findText(map["format"].toString()));
}

// 
//
// FilesItemProcessor
//
//

FilesItemProcessor::FilesItemProcessor(
        OperationDescriptor_ptr reflective,
        const QList< int > path,
        const QStringList files,
        int currentFile,
        const int format,
        const bool repeat) :
    SenderItemProcessor(path),
    m_reflective(reflective), 
    m_files(files), 
    m_currentFile(currentFile), 
    m_format(format), 
    m_repeat(repeat)
{
}

FilesItemProcessor::~FilesItemProcessor()
{
}

void FilesItemProcessor::process( 
            TypeDescriptor_ptr reflective,
            Holder holder)
{
    using namespace ::corbasim::core;

    // std::cout << __FUNCTION__  << std::endl;

    if (m_files.size() == 0)
        return;

    file_format_factory const * factory = 
        file_format_factory::get_instance();

    file_format_helper const * helper = 
        factory->get_helper(static_cast< file_format >(m_format));

    if (helper)
    {
        if (!m_currentIStream || !m_currentIStream->good())
        {
            openFile();
        }

        bool end = false;
        int i = 0;
        while (m_currentIStream && !end 
                && i++ < m_files.size())
        {
            end = helper->load(
                    *m_currentIStream, 
                    reflective, 
                    holder);

            if (!end) openFile();
        }
    }
    else
    {
        std::cerr << "Invalid file helper!" << std::endl;
    }
}

void FilesItemProcessor::openFile()
{
    m_currentIStream.reset();

    if (m_files.size() > 0 && 
            (m_currentFile < m_files.size() || m_repeat))
    {
        if (m_repeat && m_currentFile == m_files.size())
        {
            m_currentFile = 0;
        }
    
        if (m_currentFile < m_files.size())
        {
            // std::cout << __FUNCTION__ << " " << 
            //     m_files.at(m_currentFile).toStdString() << std::endl;

            m_currentIStream.reset(new std::ifstream(
                        m_files.at(m_currentFile).toStdString().c_str()));

            // open a new file
            emit nextFile(m_currentFile);

            m_currentFile++;
        }
    }
}
