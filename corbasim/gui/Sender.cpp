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
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/item/ModelNode.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>
#include <iostream>
#include <exception>

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

void SenderController::start(unsigned int numberOfThreads)
{
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
    connect(sender.get(),
            SIGNAL(finished(SenderConfig_ptr)),
            this,
            SLOT(deleteSender(SenderConfig_ptr)));

    // error notification
    connect(sender.get(),
            SIGNAL(error(const QString&)),
            this,
            SIGNAL(error(const QString&)));

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
    m_timer(ioService),
    m_config(config),
    m_currentTime(0),
    m_evaluator(config->operation(), this)
{
    connect(this,
            SIGNAL(sendRequest(Request_ptr)),
            config->object().get(),
            SLOT(sendRequest(Request_ptr)));
}

Sender::~Sender()
{
}

void Sender::start(Sender_weak weak)
{
    Sender_ptr ptr (weak.lock());

    if (!ptr)
        return;

    m_evaluator.evaluate(m_config->code());

    bool hasErr = m_evaluator.hasError();

    if (!hasErr)
    {
        OperationDescriptor_ptr op = m_config->operation();

        // Clone the original request
        // We can't modify an emited request
        Holder srcHolder = op->get_holder(m_config->request());

        m_request = op->create_request();
        Holder dstHolder = op->get_holder(m_request);

        op->copy(srcHolder, dstHolder);

        // m_request is the working request
        m_evaluator.init(m_request);

        hasErr = m_evaluator.hasError();
    }

    if (!hasErr)
    {
        m_timer.expires_from_now(
                boost::posix_time::milliseconds(
                    m_config->initDelay()));

        m_timer.async_wait(
                boost::bind(&Sender::handleTimeout,
                    this, weak, _1));
    }
    else
    {
        m_config->notifyFinished();

        emit finished(m_config);

        emit error(m_evaluator.error());
    }
}

void Sender::cancel()
{
    m_timer.cancel();
}

void Sender::process()
{
    OperationDescriptor_ptr op = m_config->operation();

    Holder srcHolder = op->get_holder(m_request);

    // preFunc
    m_evaluator.pre(m_request);
    if (m_evaluator.hasError()) throw m_evaluator.error();

    // processors
    typedef QList< RequestProcessor_ptr > processors_t;
    const processors_t& processors = m_config->processors();

    for (processors_t::const_iterator it = processors.begin();
            it != processors.end(); ++it)
    {
        applyProcessor(m_request, *it, srcHolder);
    }

    // postFunc
    m_evaluator.post(m_request);
    if (m_evaluator.hasError()) throw m_evaluator.error();

    // Clone request
    // We can't emit a request we're going to modify
    Request_ptr request = op->create_request();
    Holder dstHolder = op->get_holder(request);

    op->copy(srcHolder, dstHolder);

    // emit request
    emit sendRequest(request);
    m_config->notifyRequestSent(request);
}

void Sender::applyProcessor(
        Request_ptr request,
        RequestProcessor_ptr processor,
        Holder holder)
{
    const QList< int >& path = processor->path();

    OperationDescriptor_ptr op = m_config->operation();

    // Results
    TypeDescriptor_ptr descriptor = NULL;
    Holder value;

    bool res = followPath(op, holder, path,
            // Results
            descriptor, value);

    if (res)
        processor->process(request, descriptor, value);
}

void Sender::scheduleTimer(Sender_weak weak)
{
    namespace ptime = boost::posix_time;

    m_timer.expires_at(m_timer.expires_at() +
            ptime::milliseconds(m_config->period()));

    m_timer.async_wait(
            boost::bind(&Sender::handleTimeout,
                this, weak, _1));
}

void Sender::handleTimeout(
        Sender_weak weak,
        const boost::system::error_code& err)
{
    if (err)
        return;

    Sender_ptr ptr = weak.lock();
    if (!ptr)
        return;

    try
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
    catch(const QString& ex)
    {
        m_config->notifyFinished();
        emit finished(m_config);
        emit error(ex);
    }
}

//
//
// Sender Config
//
//

SenderConfig::SenderConfig(
        Objref_ptr object,
        OperationDescriptor_ptr operation,
        Request_ptr request,
        const QString& code,
        const QList< RequestProcessor_ptr >& processors,
        int times,
        unsigned int period,
        unsigned int initDelay) :
    m_object(object), m_operation(operation),
    m_request(request),
    m_code(code), m_processors(processors),
    m_times(times), m_period(period),
    m_initDelay(initDelay)
{
}

SenderConfig::SenderConfig(
        Objref_ptr object,
        OperationDescriptor_ptr operation,
        Request_ptr request,
        int times,
        unsigned int period,
        unsigned int initDelay) :
    m_object(object), m_operation(operation),
    m_request(request),
    m_times(times), m_period(period),
    m_initDelay(initDelay)
{
}

SenderConfig::~SenderConfig()
{
}

// Accessors
Objref_ptr SenderConfig::object() const
{
    return m_object;
}

OperationDescriptor_ptr
SenderConfig::operation() const
{
    return m_operation;
}

Request_ptr SenderConfig::request() const
{
    return m_request;
}

const QString& SenderConfig::code() const
{
    return m_code;
}

const QList< RequestProcessor_ptr >&
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

unsigned int SenderConfig::initDelay() const
{
    return m_initDelay;
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

