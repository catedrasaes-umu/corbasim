// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IDLBuilder.hpp
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

#ifndef CORBASIM_APP_IDLBUILDER_HPP
#define CORBASIM_APP_IDLBUILDER_HPP

#include <QtCore>

namespace corbasim 
{
namespace app 
{

class IDLBuilder : public QObject
{
    Q_OBJECT
public:
    IDLBuilder(QObject * parent = 0);
    virtual ~IDLBuilder();

public slots:

    void build(const QString& installDir,
            const QStringList& files);

signals:

    void message(const QString&);
    void error(const QString&);
    void progress(int);

protected:

    QFSFileEngine m_fs;
    QString m_tmpDir;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_IDLBUILDER_HPP */

