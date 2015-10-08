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
#include <boost/shared_ptr.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>
#include <corbasim/gui/script/ScriptEvaluator.hpp>

namespace corbasim
{
namespace gui
{

class SenderConfig;

typedef boost::shared_ptr< SenderConfig > SenderConfig_ptr;

class Sender;

class SenderController;

class CORBASIM_GUI_DECLSPEC SenderConfig : public QObject
{
    Q_OBJECT
public:

    SenderConfig(
        Objref_ptr object,
        OperationDescriptor_ptr operation,
        Request_ptr request,
        const QString& code,
        const QList< RequestProcessor_ptr >& processors,
        int times,
        unsigned int period,
        unsigned int initDelay = 0);
    SenderConfig(
        Objref_ptr object,
        OperationDescriptor_ptr operation,
        Request_ptr request,
        int times,
        unsigned int period,
        unsigned int initDelay = 0);
    ~SenderConfig();

    // Accessors
    Objref_ptr object() const;
    OperationDescriptor_ptr operation() const;
    Request_ptr request() const;
    const QString& code() const;
    const QList< RequestProcessor_ptr >& processors() const;
    int times();
    unsigned int period() const;
    unsigned int initDelay() const;

public slots:

    void notifyRequestSent(Request_ptr);
    void notifyFinished();

signals:

    void requestSent(Request_ptr);
    void finished();

protected:

    Objref_ptr m_object;
    OperationDescriptor_ptr m_operation;
    Request_ptr m_request;
    const QString m_code;
    const QList< RequestProcessor_ptr > m_processors;
    const int m_times;
    const unsigned int m_period;
    const unsigned int m_initDelay;
};

class CORBASIM_GUI_DECLSPEC Sender : public QObject
{
    Q_OBJECT
public:
    ~Sender();
signals:

    void finished(SenderConfig_ptr);
    void sendRequest(Request_ptr);
    void error(const QString& err);

protected:
    Sender();
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

public slots:

    void addSender(SenderConfig_ptr cfg);
    void deleteSender(SenderConfig_ptr cfg);

signals:

    void error(const QString& err);

protected:

    struct Data;
    Data  *m_data;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SENDER_HPP */

