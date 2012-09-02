// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SenderSequence.hpp
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

#ifndef CORBASIM_GUI_SENDERSEQUENCE_HPP
#define CORBASIM_GUI_SENDERSEQUENCE_HPP

#include <corbasim/gui/export.hpp>
#include <corbasim/gui/tools/AbstractSequenceTool.hpp>

namespace corbasim 
{
namespace gui 
{

class OperationSender;

class CORBASIM_GUI_DECLSPEC SenderSequenceItem : 
    public AbstractSequenceItem
{
    Q_OBJECT
public:
    SenderSequenceItem(Objref_ptr object,
            OperationDescriptor_ptr operation,
            QWidget * parent = 0);
    virtual ~SenderSequenceItem();

public slots:
    
    void showDetails(bool show);

protected:

    void doSave(QVariantMap& map);
    void doLoad(const QVariantMap& map);

    OperationSender * m_dlg;
};

class CORBASIM_GUI_DECLSPEC SenderSequenceTool : 
    public AbstractSequenceTool
{
    Q_OBJECT
public:
    SenderSequenceTool(QWidget * parent = 0);
    virtual ~SenderSequenceTool();

protected:

    AbstractSequenceItem * createAbstractItem(
            Objref_ptr object, 
            OperationDescriptor_ptr op);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SENDERSEQUENCE_HPP */

