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
#include <corbasim/gui/tools/ParametersFromFilesTool.hpp>
#include <corbasim/gui/qvariant.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/Application.hpp>
#include <limits>

#include <corbasim/qt/StartStopButton.hpp>
#include <corbasim/qt/SizeGrip.hpp>

#include <QScrollArea>
#include <QApplication>

// JSON
#include <sstream>
#include <corbasim/json/reflective.hpp>

using namespace corbasim::gui;

OperationForm::OperationForm(
        Objref_ptr object,
        OperationDescriptor_ptr factory,
        QWidget * parent) :
    QWidget(parent),
    m_reflective(factory),
    m_widget(NULL),
    m_files(NULL),
    m_sizeGrip(NULL)
{
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
    m_files->initialize(object, factory);
    tabs->addTab(m_files, "Files");

    // Main layout
    ly->addWidget(tabs);

    ly->setMargin(0);

    // Size grip
    qt::SizeGrip * sizeGrip = new qt::SizeGrip(this);
    sizeGrip->setAffectedWidget(tabs);
    sizeGrip->setVisible(false);

    //ly->addWidget(sizeGrip, 0, Qt::AlignBottom | Qt::AlignRight);
    ly->addWidget(sizeGrip);
    m_sizeGrip = sizeGrip;
    // End size grip

    setLayout(ly);
}

OperationForm::~OperationForm()
{
}

void OperationForm::showSizeGrip(bool show)
{
    m_sizeGrip->setVisible(show);
}

Request_ptr OperationForm::createRequest()
{
    return m_widget->createRequest();
}

OperationFormWidget * OperationForm::getWidget()
{
    return m_widget;
}

ParametersFromFilesTool * OperationForm::getFiles()
{
    return m_files;
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

QString OperationForm::code() const
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
        OperationDescriptor_ptr reflective,
        QWidget * parent) :
    qt::FormWidget(parent), m_reflective(reflective)
{
    const unsigned int count = reflective->get_children_count();

    m_widgets.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++)
    {
        const core::direction_type type =
            reflective->get_parameter_direction(i);

        if (type == core::DIRECTION_IN || type == core::DIRECTION_INOUT)
        {
            TypeDescriptor_ptr child = reflective->get_child(i);

            const char * child_name = reflective->get_child_name(i);

            // Without widget for files
            QWidget * child_widget = createSimpleWidget(child, this);

            m_widgets[i] = dynamic_cast< ReflectiveWidgetBase* >(
                    child_widget);

            child_widget->setObjectName(child_name);

            if (child->is_primitive() || child->is_enum())
            {
                addField(child_name, child_widget);
            }
            else
            {
                addBigField(child_name, child_widget);
            }
        }
    }

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
    Request_ptr req = m_reflective->create_request();
    Holder h = m_reflective->get_holder(req);

    if (fromQVariant(m_reflective, h, var))
    {
        setValue(req);
    }
}

QVariant OperationFormWidget::value()
{
    Request_ptr req (createRequest());
    Holder holder(m_reflective->get_holder(req));

    return toQVariant(m_reflective, holder);
}

OperationDescriptor_ptr
OperationFormWidget::getReflective() const
{
    return m_reflective;
}

Request_ptr OperationFormWidget::createRequest()
{
    Request_ptr req (m_reflective->create_request());
    Holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++)
    {
        if (m_widgets[i])
        {
            Holder child_holder(m_reflective->get_child_value(holder, i));
            m_widgets[i]->toHolder(child_holder);
        }
    }

    return req;
}

void OperationFormWidget::setValue(Request_ptr req)
{
    Holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++)
    {
        if (m_widgets[i])
        {
            Holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->fromHolder(child_holder);
        }
    }
}

//
//
// Events
//
//
bool OperationFormWidget::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::ChildAdded)
    {
        QChildEvent *cEvent = static_cast< QChildEvent * >(event);

        childEvent(cEvent);
    }
    else if (event->type() == QEvent::DragEnter)
    {
        QDragEnterEvent *dragEvent = static_cast< QDragEnterEvent * >(event);

        dragEnterEvent(dragEvent);

        return true;
    }
    else if (event->type() == QEvent::DragLeave)
    {
        QDragLeaveEvent *dragEvent = static_cast< QDragLeaveEvent * >(event);

        dragLeaveEvent(dragEvent);

        return true;
    }
    else if (event->type() == QEvent::Drop)
    {
        QDropEvent *cEvent = static_cast< QDropEvent * >(event);

        dropEvent(cEvent);

        return true;
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *cEvent = static_cast< QMouseEvent * >(event);

        mouseMoveEvent(cEvent);
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *cEvent = static_cast< QMouseEvent * >(event);

        mousePressEvent(cEvent);
    }

    return false;
}

void OperationFormWidget::childEvent(QChildEvent * event)
{
    if (event->added())
    {
        /*
        if (!dynamic_cast< QAbstractSpinBox * >(event->child())
                && !dynamic_cast< QLineEdit * >(event->child())
                && !dynamic_cast< QComboBox * >(event->child())
                && !dynamic_cast< QCheckBox * >(event->child()))
        */
            event->child()->installEventFilter(this);
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
        Request_ptr req = m_reflective->create_request();
        Holder holder = m_reflective->get_holder(req);

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
    Request_ptr req = createRequest();
    Holder holder = m_reflective->get_holder(req);
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
    // settings = value();
    // Isn't true. ObjrefWidget has its own settings. We have to save them.

    unsigned int count = m_reflective->get_children_count();

    QVariantMap value;
    for (unsigned int i = 0; i < count; i++)
    {
        if (m_widgets[i])
        {
            QVariant child;
            m_widgets[i]->save(child);
            value[m_reflective->get_child_name(i)] = child;
        }
    }

    settings = value;
}

void OperationFormWidget::load(const QVariant& settings)
{
    // setValue(settings);

    const QVariantMap value = settings.toMap();

    unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++)
    {
        if (m_widgets[i])
        {
            m_widgets[i]->load(
                    value[m_reflective->get_child_name(i)]);
        }
    }
}

//
//
// Operation Sender
//
//

OperationSender::OperationSender(
        Objref_ptr object,
        OperationDescriptor_ptr op,
        QWidget * parent) :
    QWidget(parent),
    m_object(object), m_reflective(op),
    m_updateForm(NULL)
{
    QVBoxLayout * mainLayout = new QVBoxLayout();

    // Form
    m_form = new OperationForm(object, op);
    mainLayout->addWidget(m_form);

    // Configuration
    QHBoxLayout * cfgLayout = new QHBoxLayout();
    m_times = new QSpinBox();
    m_times->setRange(0, std::numeric_limits< int >::max());
    m_times->setValue(1);
    m_times->setSpecialValueText("Infinite");
    m_period = new QSpinBox();
    m_period->setRange(0, std::numeric_limits< int >::max());
    m_period->setValue(100);
    m_delay = new QSpinBox();
    m_delay->setRange(0, std::numeric_limits< int >::max());
    m_delay->setValue(0);

    m_progressBar = new QProgressBar();
    m_progressBar->setFixedSize(150, 15);
    m_progressBar->setMaximum(0);
    m_progressBar->setMaximum(1);

    m_playButton = new qt::StartStopButton();
    m_playButton->setObjectName("start-stop");

    cfgLayout->addWidget(new QLabel("Times"));
    cfgLayout->addWidget(m_times);
    cfgLayout->addWidget(new QLabel("Period (ms)"));
    cfgLayout->addWidget(m_period);
    cfgLayout->addWidget(new QLabel("Delay (ms)"));
    cfgLayout->addWidget(m_delay);

    if (m_reflective->get_children_count())
    {
        cfgLayout->addWidget(new QLabel("Update form"));
        m_updateForm = new QCheckBox();
        cfgLayout->addWidget(m_updateForm);
    }

    cfgLayout->addWidget(m_progressBar);
    cfgLayout->addWidget(m_playButton);

    mainLayout->addLayout(cfgLayout);

    setLayout(mainLayout);

    // signals
    connect(m_playButton,
            SIGNAL(toggled(bool)),
            this,
            SLOT(playClicked(bool)));

    QObject * senderCtl =
        Application::currentApplication()->senderController();

    connect(
            this,
            SIGNAL(addSender(SenderConfig_ptr)),
            senderCtl,
            SLOT(addSender(SenderConfig_ptr)));
    connect(
            this,
            SIGNAL(deleteSender(SenderConfig_ptr)),
            senderCtl,
            SLOT(deleteSender(SenderConfig_ptr)));

    if (m_reflective->get_children_count())
    {
        connect(m_updateForm,
                SIGNAL(toggled(bool)),
                this,
                SLOT(activeUpdateForm(bool)));

        connect(this,
                SIGNAL(updateForm(Request_ptr)),
                m_form->getWidget(),
                SLOT(setValue(Request_ptr)));
    }
}

OperationSender::~OperationSender()
{
    reset();
}

Objref_ptr OperationSender::object() const
{
    return m_object;
}

void OperationSender::save(QVariant& settings)
{
    QVariantMap map;

    if (m_form)
        m_form->save(map["form"]);
    map["times"] = m_times->value();
    map["period"] = m_period->value();
    map["delay"] = m_delay->value();
    if (m_updateForm)
        map["update_form"] = m_updateForm->isChecked();

    settings = map;
}

void OperationSender::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (m_form)
        m_form->load(map["form"]);
    m_times->setValue(map["times"].toInt());
    m_period->setValue(map["period"].toInt());
    m_delay->setValue(map["delay"].toInt());
    if (m_updateForm)
        m_updateForm->setChecked(map["update_form"].toBool());
}

OperationForm * OperationSender::getForm() const
{
    return m_form;
}

void OperationSender::reset()
{
    if (m_config)
    {
        // disconnect
        disconnect(m_config.get(),
                SIGNAL(requestSent(Request_ptr)),
                this,
                SIGNAL(updateForm(Request_ptr)));

        disconnect(m_config.get(),
                SIGNAL(requestSent(Request_ptr)),
                this,
                SLOT(incrementBar()));

        disconnect(m_config.get(),
                SIGNAL(finished()),
                this,
                SLOT(finished()));
        emit deleteSender(m_config);

        m_config.reset();
    }
}

void OperationSender::incrementBar()
{
    m_progressBar->setValue(m_progressBar->value() + 1);
}

void OperationSender::playClicked(bool play)
{
    reset();

    if (play)
    {
        m_progressBar->setRange(0, m_times->value());
        m_progressBar->setValue(0);

        _setReadOnly(true);

        if (m_reflective->get_children_count())
        {
            // Create processors
            QList< RequestProcessor_ptr > processors;
            m_form->getFiles()->createProcessors(processors);

            m_config.reset(new SenderConfig(
                        object(),
                        m_reflective,
                        m_form->createRequest(),
                        m_form->code(),
                        processors,
                        m_times->value(),
                        m_period->value(),
                        m_delay->value()));

            // connect signals
            activeUpdateForm(m_updateForm->isChecked());
        }
        else
        {
            m_config.reset(new SenderConfig(
                        object(),
                        m_reflective,
                        m_reflective->create_request(),
                        m_times->value(),
                        m_period->value(),
                        m_delay->value()));
        }

        connect(m_config.get(),
                SIGNAL(requestSent(Request_ptr)),
                this,
                SLOT(incrementBar()));

        connect(m_config.get(),
                SIGNAL(finished()),
                this,
                SLOT(finished()));

        emit addSender(m_config);
    }
    else
    {
        _setReadOnly(false);

        if (!m_times->value())
        {
            m_progressBar->setMinimum(0);
            m_progressBar->setRange(0, 1);
            m_progressBar->setValue(1);
        }
    }
}

void OperationSender::finished()
{
    m_playButton->setChecked(false);
    _setReadOnly(false);
}

void OperationSender::activeUpdateForm(bool update)
{
    if (m_config)
    {
        if (update)
        {
            connect(m_config.get(),
                    SIGNAL(requestSent(Request_ptr)),
                    this,
                    SIGNAL(updateForm(Request_ptr)));
        }
        else
        {
            disconnect(m_config.get(),
                    SIGNAL(requestSent(Request_ptr)),
                    this,
                    SIGNAL(updateForm(Request_ptr)));
        }
    }
}

void OperationSender::stop()
{
    playClicked(false);
    finished();
}

// Read only
void OperationFormWidget::_setReadOnly(bool readOnly)
{
    for (unsigned int i = 0; i < m_widgets.size(); i++)
    {
        if (m_widgets[i])
        {
            m_widgets[i]->_setReadOnly(readOnly);
        }
    }
}

void OperationForm::_setReadOnly(bool readOnly)
{
    m_widget->_setReadOnly(readOnly);
    m_code->setReadOnly(readOnly);

    m_files->setEnabled(!readOnly);
}

void OperationSender::_setReadOnly(bool readOnly)
{
    m_form->_setReadOnly(readOnly);
    m_times->setReadOnly(readOnly);
    m_period->setReadOnly(readOnly);

    // Can change in read-only mode
    // m_updateForm->setEnabled(!readOnly);
}

