#include "ObjrefWidget.hpp"
#include <string>
#include <iostream>

#include <corbasim/cosnaming/Cosnaming_adapted.hpp>
#include <corbasim/gui/widgets.hpp>
#include <corbasim/core/reference_repository.hpp>

using namespace corbasim::qt;

typedef corbasim::widgets::widget< 
    CosNaming::Name > resolve_wt;

ObjrefWidget::ObjrefWidget(core::reference_validator_base* validator,
        QWidget * parent) :
    QWidget(parent), m_validator(validator)
{
    QGridLayout * mainLayout = new QGridLayout;
    QHBoxLayout * layout = new QHBoxLayout;

    m_selector = new QComboBox;
    mainLayout->addWidget(new QLabel("Select source"), 0, 0);
    mainLayout->addWidget(m_selector, 0, 1);

    m_stack = new QStackedWidget;
    layout->addWidget(m_stack);

    QPushButton * updateBtn = new QPushButton("Update");
    mainLayout->addWidget(updateBtn, 0, 2);

    m_status = new Status;
    mainLayout->addWidget(m_status, 0, 3);

    {
        // IOR
        m_selector->addItem("IOR");
        m_ior = new QTextEdit;
        m_stack->addWidget(m_ior);

        // IOR from file
        // m_selector->addItem("IOR from file");

        // NameService query
        m_selector->addItem("Name service query");
        m_resolve = new resolve_wt;
        m_stack->addWidget(m_resolve->getWidget());
        
        m_selector->addItem("Name service query from string");
        m_resolve_str = new QTextEdit;
        m_stack->addWidget(m_resolve_str);
    }
    mainLayout->addLayout(layout, 1, 0, 1, 4);

    setLayout(mainLayout);

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)),
            m_stack, SLOT(setCurrentIndex(int)));

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)),
            this, SLOT(valueChanged()));

    QObject::connect(m_ior, SIGNAL(textChanged()), this, 
            SLOT(valueChanged()));

    QObject::connect(m_resolve_str, SIGNAL(textChanged()), this, 
            SLOT(valueChanged()));

    QObject::connect(updateBtn, SIGNAL(clicked()), this, 
            SLOT(valueChanged()));
}

ObjrefWidget::~ObjrefWidget()
{
    delete m_resolve;
    delete m_resolve_str;
}

void ObjrefWidget::setValidator(
        core::reference_validator_base * validator)
{
    m_validator = validator;
}

void ObjrefWidget::valueChanged()
{
    if (!m_validator)
    {
        m_status->setRedLight();
        return;
    }

    CORBA::Object_var ref;
    core::reference_repository * rr = 
        core::reference_repository::get_instance();
       
    try {
        switch(m_stack->currentIndex())
        {
        // NS query
        case 1:
            {
                CosNaming::Name name;
                static_cast< resolve_wt* >(m_resolve)->get_value(name);
                ref = rr->resolve(name);
            }
            break;
        // NS query from str
        case 2:
            {
                std::string str = 
                    m_resolve_str->toPlainText().toStdString();
                ref = rr->resolve_str(str);
            }
            break;
         // IOR
        case 0:
        default:
            {
                std::string str = m_ior->toPlainText().toStdString();
                ref = rr->string_to_object(str);
            }
            break;
        }
    } catch (...) {
    }

    m_validator->set_reference(ref);

    if (m_validator->is_nil())
        m_status->setRedLight();
    else
        m_status->setGreenLight();
}

void ObjrefWidget::pasteIOR()
{
    m_ior->clear();
    m_ior->paste();
    m_selector->setCurrentIndex(0);
}

void ObjrefWidget::validatorHasChanged()
{
    if (!m_validator)
    {
        m_status->setRedLight();
        return;
    }

    if (m_validator->is_nil())
    {
        m_status->setRedLight();
        m_ior->clear();
    }
    else
    {
        core::reference_repository * rr = 
            core::reference_repository::get_instance();

        CORBA::Object_var ref = m_validator->get_reference();
        CORBA::String_var str = rr->object_to_string(ref);
        
        m_ior->setPlainText(str.in());
        m_selector->setCurrentIndex(0);
    }
}

