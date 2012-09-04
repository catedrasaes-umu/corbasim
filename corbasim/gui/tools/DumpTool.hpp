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
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/tools/AbstractInputTool.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC Dumper : public AbstractInputItem
{
    Q_OBJECT
public:

    Dumper(Objref_ptr objref,
            OperationDescriptor_ptr reflective,
            const QList< int >& path, 
            QWidget * parent = 0);
    virtual ~Dumper();

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void doStart(bool);

protected slots:

    void browse();
    void setEnabled(bool);

protected:

    QLineEdit * m_filePrefix;
    QComboBox * m_format;
    QSpinBox * m_suffixLength;
    QCheckBox * m_multipleFiles;
    QPushButton * m_startStopButton;
};

class CORBASIM_GUI_DECLSPEC DumpTool : public AbstractInputTool
{
    Q_OBJECT
public:

    DumpTool(QWidget * parent = 0);
    virtual ~DumpTool();

protected:

    AbstractInputItem * createItem(
            Objref_ptr objref, 
            OperationDescriptor_ptr reflective,
            const QList< int >& path);

};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_DUMPTOOL_HPP */
