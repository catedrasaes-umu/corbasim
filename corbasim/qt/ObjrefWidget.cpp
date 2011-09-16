#include "ObjrefWidget.hpp"
#include <string>

using namespace corbasim::qt;

ObjrefWidget::ObjrefWidget(core::reference_validator_base* validator,
        QWidget * parent) :
    QWidget(parent), m_validator(validator)
{
    QHBoxLayout * layout = new QHBoxLayout;
#if 0
    m_selector = new QComboBox;
    layout->addWidget(m_selector);
#endif
    m_stack = new QStackedWidget;
    layout->addWidget(m_stack);

    m_status = new Status;
    layout->addWidget(m_status);
#if 0
    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)),
            m_stack, SLOT(setCurrentIndex(int)));
#endif
    {
        // IOR
        // m_selector->addItem("IOR");
        m_ior = new QTextEdit;
        m_stack->addWidget(m_ior);
        m_ior->setMaximumHeight(90);

        QObject::connect(m_ior, SIGNAL(textChanged()), this, 
                SLOT(valueChanged()));
#if 0
        // IOR from file
        m_selector->addItem("IOR from file");
        
        // NameService query
        m_selector->addItem("Name service query");
#endif
    }

    setLayout(layout);

    setMaximumHeight(90);

    // Obtiene el ORB por defecto
    int argc = 0;
    m_orb = CORBA::ORB_init(argc, NULL);
}

ObjrefWidget::~ObjrefWidget()
{
}

void ObjrefWidget::valueChanged()
{
    CORBA::Object_var ref;
        
    try {
#if 0
        switch(0)//switch(m_stack->currentIndex())
        {
        // IOR
        case 0:
        default:
        {
#endif
            std::string str = m_ior->toPlainText().toStdString();
            ref = m_orb->string_to_object(str.c_str());
#if 0
            break;
        }
#endif
        m_validator->set_reference(ref);
#if 0
        }
#endif
    } catch (...) {
    }

    if (m_validator->is_nil())
        m_status->setRedLight();
    else
        m_status->setGreenLight();
}

void ObjrefWidget::validatorHasChanged()
{
    if (m_validator->is_nil())
    {
        m_status->setRedLight();
        m_ior->clear();
    }
    else
    {
        m_status->setGreenLight();

        CORBA::Object_ptr ref = m_validator->get_reference();

        try {
            std::string str = m_orb->object_to_string(ref);
            m_ior->setPlainText(str.c_str());
        } catch (...) {
            m_status->setGreenLight();
        }
    }
}

