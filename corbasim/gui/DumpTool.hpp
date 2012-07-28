// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DumpTool.hpp
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

#ifndef CORBASIM_GUI_DUMPTOOL_HPP
#define CORBASIM_GUI_DUMPTOOL_HPP

#include <QtGui>
#include <corbasim/gui/ParametersModel.hpp>
#include <corbasim/gui/InputRequestProcessor.hpp>
#include <map>

#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace qt 
{
class SortableGroup;
class SortableGroupItem;
} // namespace qt

namespace gui 
{

class CORBASIM_GUI_DECLSPEC DumpProcessor : public QObject,
    public gui::RequestProcessor
{
    Q_OBJECT
public:

    enum Format
    {
        FORMAT_BINARY,
        FORMAT_TEXT,
        FORMAT_JSON,
        FORMAT_MAX
    };

    struct Config
    {
        bool multipleFiles;
        std::string filePrefix;
        Format format;
        unsigned int suffixLength;
    };

    DumpProcessor(const QString& id,
            const gui::ReflectivePath_t path,
            const Config& config);
    ~DumpProcessor();

    void process(event::request_ptr req, 
            core::reflective_base const * ref,
            core::holder hold);

protected:

    void nextFile();

    const Config m_config;
    unsigned int m_currentIndex;
    std::string m_nextFile;
    std::string m_extension;
};

class CORBASIM_GUI_DECLSPEC Dumper : public QWidget
{
    Q_OBJECT
public:

    Dumper(const QString& id,
            core::operation_reflective_base const * reflective,
            const QList< int >& path, 
            QWidget * parent = 0);
    virtual ~Dumper();

    core::operation_reflective_base const * getReflective() const;

    inline const QList< int >& getPath() const
    {
        return m_path;
    }

    inline gui::RequestProcessor_ptr getProcessor() const
    {
        return m_processor;
    }

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void doStart(bool);
    void reset();

protected slots:

    void browse();
    void setEnabled(bool);

signals:

    void addProcessor(corbasim::gui::RequestProcessor_ptr);
    void removeProcessor(corbasim::gui::RequestProcessor_ptr);

protected:

    gui::RequestProcessor_ptr m_processor;

    const QString m_id;
    core::operation_reflective_base const * m_reflective;
    const QList< int > m_path;

    QLineEdit * m_filePrefix;
    QComboBox * m_format;
    QSpinBox * m_suffixLength;
    QCheckBox * m_multipleFiles;
    QPushButton * m_startStopButton;
};

class CORBASIM_GUI_DECLSPEC DumpTool : public QWidget
{
    Q_OBJECT
public:

    DumpTool(QWidget * parent = 0);
    virtual ~DumpTool();

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void registerInstance(const QString& name,
            const corbasim::core::interface_reflective_base * reflective);

    void unregisterInstance(const QString& name);

    Dumper * createDumper(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

    void deleteDumper(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

protected slots:

    void deleteRequested(corbasim::qt::SortableGroupItem *);

protected:
    ParametersModel m_model;
    qt::SortableGroup * m_group;

    typedef std::pair< QString, tag_t > key_t;
    typedef std::map< key_t, QList< Dumper * > > map_t;
    typedef std::map< Dumper *, key_t > inverse_map_t;

    map_t m_map;
    inverse_map_t m_inverse_map;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_DUMPTOOL_HPP */
