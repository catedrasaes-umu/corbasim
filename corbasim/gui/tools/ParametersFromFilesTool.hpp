// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ParametersFromFilesTool.hpp
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

#ifndef CORBASIM_GUI_PARAMETERSFROMFILESTOOL_HPP
#define CORBASIM_GUI_PARAMETERSFROMFILESTOOL_HPP

#include <QtGui>
#include <QList>
#include <fstream>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/item/OperationParametersModel.hpp>
#include <corbasim/gui/proc/FileLoaderProcessor.hpp>

namespace corbasim 
{
namespace qt 
{
class SortableGroup;
class SortableGroupItem;
} // namespace qt

namespace gui 
{

class CORBASIM_GUI_DECLSPEC FilesItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList files READ files)
    Q_PROPERTY(int currentFile READ currentFile)
    Q_PROPERTY(int format READ format)
    Q_PROPERTY(bool repeat READ repeat)
public:

    FilesItem(
            Objref_ptr objref,
            OperationDescriptor_ptr reflective,
            const QList< int >& path, 
            QWidget * parent = 0);
    virtual ~FilesItem();

    OperationDescriptor_ptr getReflective() const;

    inline const QList< int >& path() const
    {
        return m_path;
    }

    void save(QVariant& settings);
    void load(const QVariant& settings);

    // Properties
    const QStringList& files() const;
    int currentFile() const;
    int format() const;
    bool repeat() const;

    FileLoaderProcessor_ptr createProcessor();

signals:

    void nextFile(int index);

protected slots:

    void browse();

protected:

    Objref_ptr m_objref;
    OperationDescriptor_ptr m_reflective;
    const QList< int > m_path;

    QStringList m_files;
    QLineEdit * m_filesWidget;
    QComboBox * m_currentFile;
    QComboBox * m_format;
    QCheckBox * m_repeat;
};

class CORBASIM_GUI_DECLSPEC ParametersFromFilesTool : 
    public QWidget
{
    Q_OBJECT
public:

    ParametersFromFilesTool(QWidget * parent = 0);
    virtual ~ParametersFromFilesTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void initialize(
            Objref_ptr objref,
            OperationDescriptor_ptr reflective);

    void createProcessors(QList< RequestProcessor_ptr >& processors);

public slots:

    FilesItem * createFilesItem(
            OperationDescriptor_ptr,
            const QList< int >& path);

    void deleteFilesItem(
            OperationDescriptor_ptr,
            const QList< int >& path);

    void clear();

protected slots:

    void deleteRequested(corbasim::qt::SortableGroupItem *);

protected:
    OperationParametersModel m_model;
    qt::SortableGroup * m_group;

    typedef QList< FilesItem * > items_t;
    items_t m_items;
    
    Objref_ptr m_objref;
    OperationDescriptor_ptr m_operation;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_PARAMETERSFROMFILESTOOL_HPP */

