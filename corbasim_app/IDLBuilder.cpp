// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IDLBuilder.cpp
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

#include "IDLBuilder.hpp"

using namespace corbasim::app;

IDLBuilder::IDLBuilder(QObject * parent) :
    QObject(parent)
{
    m_tmpDir = QString("/tmp/corbasim-%1").arg(
            QCoreApplication::applicationPid());

    m_fs.mkdir(m_tmpDir, true);
}

IDLBuilder::~IDLBuilder()
{
    m_fs.rmdir(m_tmpDir, true);
}

void IDLBuilder::build(const QString& installDir, const QStringList& files)
{
    int step = 0;
    // Step 0 - TODO check input files

    emit progress(step++);

    // Random job name
    const QString jobName(
            QDateTime::currentDateTime().toString("YYYYMMDDhhmmsszzz"));
    const QString workingDir = m_tmpDir + jobName;
    const QString buildDir = workingDir + "/build";
    const QString idlFile = workingDir + "/" + jobName + ".idl";

    m_fs.mkdir(workingDir, true);
    m_fs.mkdir(buildDir, true);

    // Step 1 - IDL preprocessing
    QProcess cat;
    QProcess cpp;
    QProcess grep;

    cat.setStandardOutputProcess(&cpp);
    cpp.setStandardOutputProcess(&grep);
    grep.setStandardOutputFile(idlFile);

    cat.start("cat", files);
    cpp.start("cpp");
    // Elimina las lineas de preprocesado
    grep.start("grep", QStringList() << "-v" << "^#");

    grep.waitForFinished(-1);
    cpp.waitForFinished(-1);
    cat.waitForFinished(-1);

    emit progress(step++);

    // Step 2 - IDL Compilation
    QProcess corbasim_idl;
    corbasim_idl.setWorkingDirectory(workingDir);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", 
            QCoreApplication::applicationDirPath() + ":" +
            env.value("PATH"));
    corbasim_idl.setProcessEnvironment(env);
    corbasim_idl.start("corbasim_idl", QStringList() << idlFile);

    if (!corbasim_idl.waitForStarted())
    {
        emit error("C++ files generation error!");
        return;
    }

    corbasim_idl.waitForFinished(-1);

    emit progress(step++);

    // Step 3 - Generate CMakeLists.txt
    QFile cmakelists(workingDir + "/CMakeLists.txt");
    cmakelists.open(QIODevice::WriteOnly);

    QTextStream os(&cmakelists);

    os << "cmake_minimum_required(VERSION 2.6)\n";
    os << "project(" << jobName << " CXX)\n\n";

    os << "if(UNIX)\n";
    os << "\tset(Boost_USE_MULTITHREADED OFF)\n";
    os << "endif()\n";
    os << "find_package(Boost 1.45.0 REQUIRED)\n";
    os << "include_directories(${Boost_INCLUDE_DIRS})\n";

    os << "include(" << jobName << ".cmake)\n";

    cmakelists.close();

    emit progress(step++);

    // Step 4 - Create compilation cache
    QProcess cmake;
    QStringList cmakeOptions;

    cmake.setWorkingDirectory(buildDir);

    cmakeOptions << "-DCMAKE_BUILD_TYPE=Release";
    cmakeOptions << QString("-DCMAKE_INSTALL_PREFIX=") + installDir;
    cmakeOptions << "..";

    cmake.start("cmake", cmakeOptions);
    cmake.waitForFinished(-1);
    
    emit progress(step++);

    // Step 5 - Compiling
    QProcess make;
    make.setWorkingDirectory(buildDir);
    make.start("make");
    make.waitForFinished(-1);

    emit progress(step++);

    // Step 6 - Installing
    QProcess install;
    install.setWorkingDirectory(buildDir);
    install.start("make", QStringList() << "install");
    install.waitForFinished(-1);

    emit progress(step++);
}

