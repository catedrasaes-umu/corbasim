// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * launcher.cpp
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

#include <iostream>
#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QProcess proc;
    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    proc.setProcessChannelMode(QProcess::ForwardedChannels);

    QStringList args;
    for (int i = 1; i < argc; i++) 
    {
        args << argv[i];
    }

    const QString applicationDirPath(
            QCoreApplication::applicationDirPath());

    // add LD_LIBRARY_PATH
    const QString libraryDirPath(applicationDirPath + "/../lib");

    QString ldLibraryPath = env.value("LD_LIBRARY_PATH");

    if (!ldLibraryPath.isEmpty()) ldLibraryPath += ':';

    ldLibraryPath += libraryDirPath;

    env.insert("LD_LIBRARY_PATH", ldLibraryPath);

    proc.setProcessEnvironment(env);

    proc.start(QCoreApplication::applicationFilePath()
            + ".real", args);


    if (!proc.waitForStarted(-1))
    {
        std::cerr << "Unable to launch!" << std::endl;
        return -1;
    }

    // wait for its end
    proc.waitForFinished(-1);
    
    return proc.exitCode();
}
