// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * OperationForm.cpp
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

#include "OperationForm.hpp"
#include <corbasim/qt/private/ScriptEditor.hpp>
#include <corbasim/gui/ParametersFromFilesTool.hpp>
#include <corbasim/gui/qvariant.hpp>

// JSON
#include <sstream>
#include <corbasim/json/reflective.hpp>

using namespace corbasim::gui;

OperationForm::OperationForm(QWidget * parent) :
    QWidget(parent), m_reflective(NULL), 
    m_widget(NULL),
    m_files(NULL)
{
}

OperationForm::~OperationForm()
{
}

void OperationForm::initialize(
    ::corbasim::core::operation_reflective_base const * factory)
{
    m_reflective = factory;

    QVBoxLayout * ly = new QVBoxLayout();
    QTabWidget * tabs = new QTabWidget();

    // Input form
    QScrollArea * scroll = new QScrollArea();
    m_widget = new OperationFormWidget(m_reflective);
    scroll->setWidgetResizable(true);
    scroll->setLineWidth(0);
    scroll->setFrameStyle(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setWidget(m_widget);
    tabs->addTab(scroll, "Form");

    // Script
    m_code = new qt::priv::ScriptEditor();
    tabs->addTab(m_code, "Script");
 
    // Files
    m_files = new ParametersFromFilesTool();
    m_files->initialize(factory);
    tabs->addTab(m_files, "Files");

    // Main layout
    ly->addWidget(tabs);
    ly->setMargin(0);
    setLayout(ly);
}

corbasim::event::request_ptr OperationForm::createRequest()
{
    return m_widget->createRequest();
}

OperationFormWidget * OperationForm::getWidget()
{
    return m_widget;
}

//
//
// Property code
//
//

void OperationForm::setCode(const QString& code)
{
    m_code->setPlainText(code);
}

QString OperationForm::code()
{
    return m_code->toPlainText();
}

//
//
// Save and load
//
//

void OperationForm::save(QVariant& settings)
{
    QVariantMap map;

    m_widget->save(map["form"]);
    map["code"] = m_code->toPlainText();
    m_files->save(map["files"]);

    settings = map;
}

void OperationForm::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    m_widget->load(map["form"]);
    m_code->setPlainText(map["code"].toString());
    m_files->load(map["files"]);
}

//
//
// Operation form widget
//
//

OperationFormWidget::OperationFormWidget(
        corbasim::core::operation_reflective_base const * reflective,
        QWidget * parent) :
    QWidget(parent), m_reflective(reflective)
{
    QGridLayout * layout = new QGridLayout(this);
    QLayout * mlayout = layout;

    const unsigned int count = reflective->get_children_count();

    // Max widgets per row: 2 labels + 2 widgets
    const int rowWidth = 4;
    int row = 0;
    int column = 0;

    m_widgets.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        const core::direction_type type = 
            reflective->get_parameter_direction(i);

        if (type == core::DIRECTION_IN || type == core::DIRECTION_INOUT)
        {
            core::reflective_base const * child = 
                reflective->get_child(i);

            const char * child_name = reflective->get_child_name(i);

            // Without widget for files
            QWidget * child_widget = createSimpleWidget(child, this);

            m_widgets[i] = dynamic_cast< ReflectiveWidgetBase* >(
                    child_widget);

            child_widget->setObjectName(child_name);

            if (child->is_primitive() || child->is_enum())
            {
                QLabel * label = new QLabel(child_name, this);
                label->setObjectName(QString(child_name) + "_label");

                layout->addWidget(label, row, column++);
                layout->addWidget(child_widget, row, column++);

                // Check if there are enough widgets in the 
                // current row
                if (column == rowWidth)
                {
                    row++;
                    column = 0;
                }
            }
            else
            {
                // Starts in a new row
                if (column != 0) row++;
                column = 0;

                QGroupBox * gb = new QGroupBox(child_name, this);
                gb->setObjectName(QString(child_name) + "_group");

                // Group box layout
                QHBoxLayout * cLayout = new QHBoxLayout(gb);
                cLayout->addWidget(child_widget);
                gb->setLayout(cLayout);

                layout->addWidget(gb, row++, 0, 1, rowWidth);
            }
        }
    }

    setLayout(mlayout);

    setAcceptDrops(true);
}

OperationFormWidget::~OperationFormWidget()
{
}

//
//
// Property value
//
//

void OperationFormWidget::setValue(const QVariant& var)
{
    event::request_ptr req = m_reflective->create_request();
    core::holder h = m_reflective->get_holder(req);

    if (fromQVariant(m_reflective, h, var))
    {
        setValue(req);
    }
}

QVariant OperationFormWidget::value()
{
    event::request_ptr req (createRequest());
    core::holder holder(m_reflective->get_holder(req));

    return toQVariant(m_reflective, holder);
}

corbasim::core::operation_reflective_base const * 
OperationFormWidget::getReflective() const
{
    return m_reflective;
}

corbasim::event::request_ptr OperationFormWidget::createRequest()
{
    event::request_ptr req (m_reflective->create_request());
    core::holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            core::holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->toHolder(child_holder);
        }
    }

    return req;
}

void OperationFormWidget::setValue(corbasim::event::request_ptr req)
{
    core::holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            core::holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->fromHolder(child_holder);
        }
    }
}

//
//
// Drag and drop
//
//

void OperationFormWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
}

void OperationFormWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        event->acceptProposedAction();
    }
}

void OperationFormWidget::dropEvent(QDropEvent *event)
{
    const std::string str = event->mimeData()->text().toStdString();

    try 
    {
        event::request_ptr req = m_reflective->create_request();
        core::holder holder = m_reflective->get_holder(req);

        bool res = json::parse(m_reflective, holder, 
                str.c_str(), str.size());

        if (res)
        {
            setValue(req);
            event->acceptProposedAction();
        }
    } 
    catch(...) 
    {
        // parse exception: nothing to do
    }
}

void OperationFormWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_dragStartPosition = event->pos();
}

void OperationFormWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - m_dragStartPosition).manhattanLength()
            < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    std::ostringstream oss;
    event::request_ptr req = createRequest();
    
    core::holder holder = m_reflective->get_holder(req);

    json::write(oss, m_reflective, holder);

    mimeData->setText(oss.str().c_str());
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
}

//
//
// Save and load
//
//

void OperationFormWidget::save(QVariant& settings)
{
    // There are no additional settings
    settings = value();
}

void OperationFormWidget::load(const QVariant& settings)
{
    setValue(settings);
}

