#include "ObjrefWidget.hpp"
#include <string>
#include <iostream>

#include <corbasim/cosnaming/Cosnaming_adapted.hpp>
#include <corbasim/core/reference_repository.hpp>
#include <corbasim/core/reference_validator.hpp>
#include <corbasim/qt/Status.hpp>
#include <corbasim/qt/types.hpp>
#include <corbasim/qt/initialize.hpp>

#include <corbasim/gui/Application.hpp>
#include <corbasim/gui/NSManager.hpp>

#include <QtGui>

using namespace corbasim;
using namespace corbasim::gui;

ObjrefWidget::ObjrefWidget(InterfaceDescriptor_ptr iface,
        QWidget * parent) :
    QWidget(parent), m_model(NULL)
{
    setInterface(iface);

    QGridLayout * mainLayout = new QGridLayout;
    QHBoxLayout * layout = new QHBoxLayout;

    m_selector = new QComboBox;
    QLabel * label = new QLabel("Select source");
    mainLayout->addWidget(label, 0, 0);
    label->setMaximumWidth(150);
    mainLayout->addWidget(m_selector, 0, 1);

    m_stack = new QStackedWidget;
    layout->addWidget(m_stack);

    QPushButton * updateBtn = new QPushButton("Update");
    mainLayout->addWidget(updateBtn, 0, 2);

    updateBtn->setMaximumWidth(90);

    m_status = new qt::Status;
    mainLayout->addWidget(m_status, 0, 3);

    {
        // IOR
        m_selector->addItem("IOR");
        m_ior = new QTextEdit;
        m_ior->setAcceptRichText(false);
        m_stack->addWidget(m_ior);

        // NameService query
        m_selector->addItem("Name service query");
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

    connect(m_selector, SIGNAL(currentIndexChanged(int)),
            m_stack, SLOT(setCurrentIndex(int)));

    connect(m_selector, SIGNAL(currentIndexChanged(int)),
            this, SLOT(valueChanged()));

    connect(m_object_selector, SIGNAL(currentIndexChanged(int)),
            this, SLOT(valueChanged()));

    connect(m_ior, SIGNAL(textChanged()), this, 
            SLOT(valueChanged()));

    connect(m_resolve_str, SIGNAL(textChanged()), this, 
            SLOT(valueChanged()));

    connect(updateBtn, SIGNAL(clicked()), this, 
            SLOT(valueChanged()));

    connect(this, SIGNAL(resolve(Objref_ptr)),
            Application::currentApplication()->nameServiceManager(),
            SLOT(resolve(Objref_ptr)));

    // Default model
    QAbstractItemModel * model = qt::getDefaultInstanceModel();
    if (model)
    {
        setModel(model);
    }

    setMaximumHeight(100);
}

ObjrefWidget::~ObjrefWidget()
{
    delete m_resolve_str;
}


void ObjrefWidget::setValidator(core::reference_validator_ptr validator)
{
    m_objref->setValidator(validator);
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

        connect(m_model, SIGNAL(modelReset()),
                this, SLOT(modelChanged()));
    }
}

QString ObjrefWidget::getNSEntry() const
{
    if (m_stack->currentIndex() != 1)
        return QString();

    return m_objref->nsEntry();
}

void ObjrefWidget::modelChanged()
{
    // We restore the previous selected item
    int idx = m_object_selector->findText(m_currentModelItem);

    if (idx != -1)
    {
        m_object_selector->setCurrentIndex(idx);
    }

    if (m_stack->currentIndex() == 2)
    {
        valueChanged();
    }
}

void ObjrefWidget::valueChanged()
{
    CORBA::Object_var ref;
    core::reference_repository * rr = 
        core::reference_repository::get_instance();
       
    try 
    {
        switch(m_stack->currentIndex())
        {
        // NS query 
        case 1:
            {
                m_objref->setNsEntry(m_resolve_str->toPlainText());

                // Async resolution
                emit resolve(m_objref);
            }
            break;
        // Well-known objects
        case 2:
            {
                m_objref->setNsEntry(QString());

                int idx = m_object_selector->currentIndex();
                
                if (m_model && idx != -1)
                {
                    // We keep the selected item for when model
                    // reset
                    m_currentModelItem = 
                        m_object_selector->currentText();

                    QVariant v = m_object_selector->itemData(idx);
                    if (v.canConvert< CORBA::Object_var >())
                    {
                        ref = v.value< CORBA::Object_var >();
                    }
                }

                setReference(ref);
            }
            break;
         // IOR
        case 0:
        default:
            {
                m_objref->setNsEntry(QString());

                std::string str = m_ior->toPlainText().toStdString();
                ref = rr->string_to_object(str);

                setReference(ref);
            }
            break;
        }
    } 
    catch (...) 
    {
        // NIL
        setReference(ref);
    }
}

void ObjrefWidget::pasteIOR()
{
    m_ior->clear();
    m_ior->paste();
    m_selector->setCurrentIndex(0);
}

void ObjrefWidget::validatorHasChanged()
{
    if (!m_objref || m_objref->isNil())
    {
        m_status->setRedLight();
    }
    else
    {
        m_status->setGreenLight();
    }
}

void ObjrefWidget::save(QVariant& settings)
{
    QVariantMap map;

    map["index"] = m_selector->currentIndex();
    map["ior"] = m_ior->toPlainText();
    map["ns_entry_string"] = m_resolve_str->toPlainText();
   
    // known object
    map["known_object"] = m_object_selector->currentText();

    settings = map;
}

void ObjrefWidget::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    m_ior->setPlainText(map["ior"].toString());
    m_resolve_str->setPlainText(map["ns_entry_string"].toString());
   
    // known object
    const QString knownObject = map["known_object"].toString();
    int idx = m_object_selector->findText(knownObject);

    if (idx != -1)
    {
        m_object_selector->setCurrentIndex(idx);
    }
    
    // At the end...
    m_selector->setCurrentIndex(map["index"].toInt());

    // Already connected to setCurrentIndex, but anyway...
    valueChanged();
}

void ObjrefWidget::setInterface(InterfaceDescriptor_ptr iface)
{
    Objref_ptr objref(new Objref("", iface));
    setObjref(objref);
}

void ObjrefWidget::setObjref(Objref_ptr objref)
{
    if (m_objref)
    {
        disconnect(m_objref.get(), 
                SIGNAL(updatedReference(const CORBA::Object_var&)),
                this, SIGNAL(valueHasChanged(const CORBA::Object_var&)));

        disconnect(m_objref.get(), 
                SIGNAL(updatedReference(const CORBA::Object_var&)),
                this, SLOT(validatorHasChanged()));
    }

    m_objref = objref;

    if (m_objref)
    {
        connect(m_objref.get(), 
                SIGNAL(updatedReference(const CORBA::Object_var&)),
                this, SIGNAL(valueHasChanged(const CORBA::Object_var&)));

        connect(m_objref.get(), 
                SIGNAL(updatedReference(const CORBA::Object_var&)),
                this, SLOT(validatorHasChanged()));
    }
}

CORBA::Object_var ObjrefWidget::reference() const
{
    return m_objref->reference();
}

void ObjrefWidget::setReference(const CORBA::Object_var& ref)
{
    m_objref->setReference(ref);
}

