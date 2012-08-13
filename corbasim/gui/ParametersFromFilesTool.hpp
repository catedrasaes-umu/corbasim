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
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/OperationParametersModel.hpp>
#include <corbasim/gui/InputRequestProcessor.hpp>
#include <map>

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
    // TODO Q_PROPERTY files format repeat
public:

    FilesItem(
            core::operation_reflective_base const * reflective,
            const QList< int >& path, 
            QWidget * parent = 0);
    virtual ~FilesItem();

    core::operation_reflective_base const * getReflective() const;

    inline const QList< int >& getPath() const
    {
        return m_path;
    }

    void save(QVariant& settings);
    void load(const QVariant& settings);

protected slots:

    void browse();

protected:

    core::operation_reflective_base const * m_reflective;
    const QList< int > m_path;

    QStringList m_files;
    QLineEdit * m_filesWidget;
    QComboBox * m_format;
    QCheckBox * m_repeat;
};

class CORBASIM_GUI_DECLSPEC ParametersFromFilesTool : public QWidget
{
    Q_OBJECT
public:

    ParametersFromFilesTool(QWidget * parent = 0);
    virtual ~ParametersFromFilesTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void initialize(
            ::corbasim::core::operation_reflective_base const * reflective);

public slots:

    FilesItem * createFilesItem(
            core::operation_reflective_base const * reflective,
            const QList< int >& path);

    void deleteFilesItem(
            core::operation_reflective_base const * reflective,
            const QList< int >& path);

protected slots:

    void deleteRequested(corbasim::qt::SortableGroupItem *);

protected:
    OperationParametersModel m_model;
    qt::SortableGroup * m_group;

    typedef tag_t key_t;
    typedef std::map< key_t, QList< FilesItem * > > map_t;
    typedef std::map< FilesItem *, key_t > inverse_map_t;

    map_t m_map;
    inverse_map_t m_inverse_map;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_PARAMETERSFROMFILESTOOL_HPP */

