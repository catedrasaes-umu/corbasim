#include "ObjrefWidget.hpp"
#include <string>
#include <iostream>

#include <corbasim/cosnaming/Cosnaming_adapted.hpp>
#include <corbasim/core/reference_repository.hpp>
#include <corbasim/core/reference_validator.hpp>
#include <corbasim/qt/Status.hpp>
#include <corbasim/qt/ReferenceModel.hpp>
#include <corbasim/qt/types.hpp>

#include <QtGui>

using namespace corbasim;
using namespace corbasim::qt;

ObjrefWidget::ObjrefWidget(core::reference_validator_base* validator,
        QWidget * parent) :
    QWidget(parent), m_validator(validator), m_model(NULL)
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
        m_ior->setAcceptRichText(false);
        m_stack->addWidget(m_ior);

        // IOR from file
        // m_selector->addItem("IOR from file");

        // NameService query
        m_selector->addItem("Name service query");
        // TODO m_resolve = new resolve_wt;
        m_stack->addWidget(new QWidget());
        
        m_selector->addItem("Name service query from string");
        m_resolve_str = new QTextEdit;
        m_stack->addWidget(m_resolve_str);

        // Well-known objects
        m_selector->addItem("Well-known object");
        QWidget * w = new QWidget;
        QVBoxLayout * l = new QVBoxLayout;
        m_object_selector = new QComboBox;
        l->addWidget(m_object_selector);
        w->setLayout(l);
        m_stack->addWidget(w);
    }
    mainLayout->addLayout(layout, 1, 0, 1, 4);

    setLayout(mainLayout);

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)),
            m_stack, SLOT(setCurrentIndex(int)));

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)),
            this, SLOT(valueChanged()));

    QObject::connect(m_object_selector, SIGNAL(currentIndexChanged(int)),
            this, SLOT(valueChanged()));

    QObject::connect(m_ior, SIGNAL(textChanged()), this, 
            SLOT(valueChanged()));

    QObject::connect(m_resolve_str, SIGNAL(textChanged()), this, 
            SLOT(valueChanged()));

    QObject::connect(updateBtn, SIGNAL(clicked()), this, 
            SLOT(valueChanged()));

    // Default model
    setModel(ReferenceModel::getDefaultModel());
}

ObjrefWidget::~ObjrefWidget()
{
    // TODO delete m_resolve;
    delete m_resolve_str;
}

void ObjrefWidget::setValidator(
        core::reference_validator_base * validator)
{
    m_validator = validator;

    if (!validator)
        return;

    CORBA::Object_var ref = validator->get_reference();

    if (CORBA::is_nil(ref))
        return;

    core::reference_repository * rr = 
        core::reference_repository::get_instance();

    CORBA::String_var ior = rr->object_to_string(ref);
    m_ior->setPlainText(ior.in());
    m_stack->setCurrentIndex(0);
}

void ObjrefWidget::setModel(QAbstractItemModel * model)
{
    // Disconnect
    if (m_model)
    {
        QObject::disconnect(m_model, SIGNAL(modelReset()),
                this, SLOT(modelChanged()));
    }

    m_model = model;

    // Connect
    if (m_model)
    {
        m_object_selector->setModel(model);

        QObject::connect(m_model, SIGNAL(modelReset()),
                this, SLOT(modelChanged()));
    }
}

const QString& ObjrefWidget::getNSEntry() const
{
    return m_nsEntry;
}

void ObjrefWidget::modelChanged()
{
    if (m_stack->currentIndex() == 3)
        valueChanged();
}

void ObjrefWidget::valueChanged()
{
    m_nsEntry.clear();

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
                /*
                CosNaming::Name name;
                static_cast< resolve_wt* >(m_resolve)->get_value(name);
                ref = rr->resolve(name);
                */
                // TODO convert name to m_nsEntry
            }
            break;
        // NS query from str
        case 2:
            {
                const std::string str = 
                    m_resolve_str->toPlainText().toStdString();
                ref = rr->resolve_str(str);

                m_nsEntry = str.c_str();
            }
            break;
        // Well-known objects
        case 3:
            {
                int idx = m_object_selector->currentIndex();

                if (m_model && idx != -1)
                {
                    QVariant v = m_object_selector->itemData(idx);
                    if (v.canConvert< CORBA::Object_var >())
                    {
                        ref = v.value< CORBA::Object_var >();
                    }
                }
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
        m_nsEntry.clear();
    }

    m_validator->set_reference(ref);

    // Notify its modification
    emit valueHasChanged(ref);

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

void ObjrefWidget::save(QVariant& settings)
{
    QVariantMap map;

    map["index"] = m_selector->currentIndex();
    map["ior"] = m_ior->toPlainText();
    map["ns_entry_string"] = m_resolve_str->toPlainText();
   
    int idx = m_object_selector->currentIndex();

    if (idx != -1)
    {
        map["known_object"] = m_object_selector->itemData(idx, Qt::DisplayRole);
    }

    settings = map;
}

void ObjrefWidget::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    m_selector->setCurrentIndex(map["index"].toInt());
    m_ior->setPlainText(map["ior"].toString());
    m_resolve_str->setPlainText(map["ns_entry_string"].toString());
   
    // TODO map["known_object"] = m_object_selector->itemData(idx, Qt::DisplayRole);

    valueChanged();
}

