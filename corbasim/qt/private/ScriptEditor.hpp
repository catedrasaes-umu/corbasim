// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEditor.hpp
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

#ifndef CORBASIM_QT_PRIVATE_SCRIPTEDITOR_HPP
#define CORBASIM_QT_PRIVATE_SCRIPTEDITOR_HPP

#include "codeeditor.h"
#include "qscriptsyntaxhighlighter_p.h"
#include <corbasim/qt/export.hpp>

namespace corbasim
{
namespace qt
{
namespace priv
{

class CORBASIM_QT_DECLSPEC ScriptEditor : public CodeEditor
{
    Q_OBJECT
public:
    ScriptEditor(QWidget * parent = 0);
    virtual ~ScriptEditor();

protected:
    tp::qt::QScriptSyntaxHighlighter m_ssh;
};

} // namespace priv
} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_PRIVATE_SCRIPTEDITOR_HPP */

