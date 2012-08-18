// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Sender.cpp
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

#include "Sender.hpp"
#include <boost/bind.hpp>
#include <corbasim/gui/ModelNode.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>
#include <iostream>

using namespace corbasim::gui;

// 
//
// SenderController
//
//

SenderController::SenderController() :
    m_work(m_ioService)
{
}

SenderController::~SenderController()
{
}

SenderController * SenderController::getInstance()
{
    static std::auto_ptr< SenderController > _instance(new SenderController());
    return _instance.get();
}

void SenderController::start(unsigned int numberOfThreads)
{
    // std::cout << "SenderController::" 
    //     << __FUNCTION__ << std::endl;

    for (unsigned int i = 0; i < numberOfThreads; i++) 
    {
        m_threads.create_thread(boost::bind(
                    &boost::asio::io_service::run,
                    &m_ioService));
    }
}

void SenderController::join()
{
    m_threads.join_all();
}

void SenderController::stop()
{
    m_ioService.stop();
}

// slots

void SenderController::addSender(SenderConfig_ptr cfg)
{
    Sender_ptr sender(new Sender(m_ioService, cfg));

    // Self-delete
    QObject::connect(sender.get(), 
            SIGNAL(finished(SenderConfig_ptr)),
            this,
            SLOT(deleteSender(SenderConfig_ptr)));

    QObject::connect(sender.get(), 
            SIGNAL(sendRequest(const QString&, 
                    corbasim::event::request_ptr)),
            this,
            SIGNAL(sendRequest(const QString&, 
                    corbasim::event::request_ptr)));

    m_ioService.post(
            boost::bind(&Sender::start, sender, sender));

    m_map.insert(cfg, sender);
}

void SenderController::deleteSender(SenderConfig_ptr cfg)
{
    map_t::iterator it = m_map.find(cfg);

    if (it != m_map.end())
    {
        it.value()->cancel();

        m_map.erase(it);
    }
}

// 
//
// Sender
//
//


Sender::Sender(boost::asio::io_service& ioService,
    SenderConfig_ptr config) :
    m_timer(ioService), m_config(config),
    m_currentTime(0), m_clazz(&m_engine)
{
}

Sender::~Sender() 
{
}

void Sender::start(Sender_weak weak) 
{
    Sender_ptr ptr (weak.lock());

    if (ptr)
    {
        m_engine.evaluate(m_config->code());
        
        m_initFunc = m_engine.evaluate("init");
        m_preFunc = m_engine.evaluate("pre");
        m_postFunc = m_engine.evaluate("post");

        // Clone the original request
        ::corbasim::core::holder srcHolder =
            m_config->operation()->get_holder(m_config->request());
        m_request =
            m_config->operation()->create_request();
        ::corbasim::core::holder dstHolder =
            m_config->operation()->get_holder(m_request);

        m_config->operation()->copy(srcHolder, dstHolder);

        // m_request is the working request
        Node_ptr node(new Node(m_config->operation(), dstHolder));
        m_thisObject = m_engine.newObject(&m_clazz,
                m_engine.newVariant(qVariantFromValue(node)));

        if (m_initFunc.isFunction())
            m_initFunc.call(m_thisObject);

        m_timer.expires_from_now(
                boost::posix_time::milliseconds(0));

        m_timer.async_wait(
                boost::bind(&Sender::handleTimeout,this, weak, _1));
    }
}

void Sender::cancel() 
{
    m_timer.cancel();
}

void Sender::process()
{
    // preFunc
    if (m_preFunc.isFunction())
    {
        m_preFunc.call(m_thisObject);
    }

    // processors
    const QList< SenderItemProcessor_ptr >& processors =
        m_config->processors();

    for (int i = 0; i < processors.size(); i++) 
    {
        // TODO
    }
    
    // postFunc
    if (m_postFunc.isFunction())
    {
        m_postFunc.call(m_thisObject);
    }

    // clone request
    // we can't emit a request we're going to modify

    ::corbasim::event::request_ptr request =
        m_config->operation()->create_request();
    ::corbasim::core::holder srcHolder =
        m_config->operation()->get_holder(m_request);
    ::corbasim::core::holder dstHolder =
        m_config->operation()->get_holder(request);
    
    m_config->operation()->copy(srcHolder, dstHolder);

    // emit request
    emit sendRequest(m_config->objectId(), request);
    m_config->notifyRequestSent(request);
}

void Sender::scheduleTimer(Sender_weak weak)
{
    m_timer.expires_at(m_timer.expires_at() +
            boost::posix_time::milliseconds(m_config->period()));

    m_timer.async_wait(
            boost::bind(&Sender::handleTimeout,this, weak, _1));
}

void Sender::handleTimeout(
        Sender_weak weak,
        const boost::system::error_code& error)
{
    if (!error)
    {
        Sender_ptr ptr = weak.lock();
        
        if (ptr)
        {
            process();

            if (++m_currentTime == m_config->times())
            {
                m_config->notifyFinished();

                emit finished(m_config);
            }

            // Last step to ensure thread-safe
            if (m_currentTime != m_config->times())
                scheduleTimer(weak);
        }
    }
    else
    {
        // Cancel
    }
}

//
//
// Sender Config
//
//

SenderConfig::SenderConfig(
        const QString& objectId,
        ::corbasim::core::operation_reflective_base const * operation,
        ::corbasim::event::request_ptr request,
        const QString& code,
        const QList< SenderItemProcessor_ptr >& processors,
        int times,
        unsigned int period) :
    m_objectId(objectId), m_operation(operation),
    m_request(request),
    m_code(code), m_processors(processors),
    m_times(times), m_period(period)
{
}
SenderConfig::~SenderConfig()
{
}

// Accessors
const QString& SenderConfig::objectId() const
{
    return m_objectId;
}

::corbasim::core::operation_reflective_base const * 
SenderConfig::operation() const
{
    return m_operation;
}

::corbasim::event::request_ptr SenderConfig::request() const
{
    return m_request;
}

const QString& SenderConfig::code() const
{
    return m_code;
}

const QList< SenderItemProcessor_ptr >& 
SenderConfig::processors() const
{
    return m_processors;
}

int SenderConfig::times()
{
    return m_times;
}

unsigned int SenderConfig::period() const
{
    return m_period;
}

void SenderConfig::notifyRequestSent(
        corbasim::event::request_ptr request)
{
    emit requestSent(request);
}

void SenderConfig::notifyFinished()
{
    emit finished();
}

//
//
// Sender Item Processor
//
//
//

SenderItemProcessor::SenderItemProcessor(
        const QList< int >& path) :
    m_path(path)
{
}

SenderItemProcessor::~SenderItemProcessor()
{
}

const QList< int >& SenderItemProcessor::getPath() const
{
    return m_path;
}

