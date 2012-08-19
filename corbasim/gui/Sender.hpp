// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Sender.hpp
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

#ifndef CORBASIM_GUI_SENDER_HPP
#define CORBASIM_GUI_SENDER_HPP

#include <QtCore>
#include <QtScript>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/ScriptEvaluator.hpp>

namespace corbasim 
{
namespace gui 
{

class SenderConfig;

typedef boost::shared_ptr< SenderConfig > SenderConfig_ptr;

class SenderItemProcessor;

typedef boost::shared_ptr< SenderItemProcessor > 
    SenderItemProcessor_ptr;

class Sender;

typedef boost::shared_ptr< Sender > Sender_ptr;
typedef boost::weak_ptr< Sender > Sender_weak;

class SenderController;

class CORBASIM_GUI_DECLSPEC SenderConfig : public QObject
{
    Q_OBJECT
public:

    SenderConfig(
        const QString& objectId,
        ::corbasim::core::operation_reflective_base const * operation,
        ::corbasim::event::request_ptr request,
        const QString& code,
        const QList< SenderItemProcessor_ptr >& processors,
        int times,
        unsigned int period);
    ~SenderConfig();

    // Accessors
    const QString& objectId() const;
    ::corbasim::core::operation_reflective_base const * operation() const;
    ::corbasim::event::request_ptr request() const;
    const QString& code() const;
    const QList< SenderItemProcessor_ptr >& processors() const;
    int times();
    unsigned int period() const;

public slots:

    void notifyRequestSent(corbasim::event::request_ptr);
    void notifyFinished();

signals:

    void requestSent(corbasim::event::request_ptr);
    void finished();

protected:

    const QString m_objectId;
    ::corbasim::core::operation_reflective_base const * m_operation;
    ::corbasim::event::request_ptr m_request;
    const QString m_code;
    const QList< SenderItemProcessor_ptr > m_processors;
    const int m_times;
    const unsigned int m_period;
};

class CORBASIM_GUI_DECLSPEC SenderItemProcessor : public QObject
{
    Q_OBJECT
public:

    virtual ~SenderItemProcessor();

    virtual void process(
            ::corbasim::core::reflective_base const * reflective,
            ::corbasim::core::holder holder) = 0;
    
    const QList< int >& getPath() const;

protected:

    SenderItemProcessor(const QList< int >& path);

    const QList< int > m_path;
};

class CORBASIM_GUI_DECLSPEC Sender : public QObject
{
    Q_OBJECT
public:

    Sender(boost::asio::io_service& ioService,
        SenderConfig_ptr config);
    ~Sender();

    void start(Sender_weak weak);

    void cancel();

    void process();

signals:

    void finished(SenderConfig_ptr);
    void sendRequest(const QString&, corbasim::event::request_ptr);

protected:

    void scheduleTimer(
            Sender_weak weak);

    void handleTimeout(
            Sender_weak weak,
            const boost::system::error_code& error);

    void applyProcessor(
            SenderItemProcessor_ptr processor,
            core::holder holder);

    boost::asio::deadline_timer m_timer;
    SenderConfig_ptr m_config;
    int m_currentTime;

    OperationEvaluator m_evaluator;
    ::corbasim::event::request_ptr m_request;
};

class CORBASIM_GUI_DECLSPEC SenderController : public QObject
{
    Q_OBJECT
public:

    SenderController();
    ~SenderController();

    void start(unsigned int numberOfThreads = 5);
    void join();
    void stop();

    static SenderController * getInstance();

public slots:

    void addSender(SenderConfig_ptr cfg);
    void deleteSender(SenderConfig_ptr cfg);

signals:

    void sendRequest(const QString&, 
            corbasim::event::request_ptr);

protected:

    boost::thread_group m_threads;
    boost::asio::io_service m_ioService;
    boost::asio::io_service::work m_work;

    typedef QMap< SenderConfig_ptr, Sender_ptr > map_t;
    map_t m_map;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SENDER_HPP */

