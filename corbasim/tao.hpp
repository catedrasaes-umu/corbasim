// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * tao.hpp
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

#ifndef CORBASIM_TAO_HPP
#define CORBASIM_TAO_HPP

#include <tao/ORB.h>
#include <tao/Object.h>
#include <tao/Basic_Types.h>
#include <tao/String_Manager_T.h>
#include <tao/Sequence_T.h>
#include <tao/Seq_Var_T.h>
#include <tao/Seq_Out_T.h>
#include <tao/VarOut_T.h>
#include <tao/Array_VarOut_T.h>
#include <tao/PortableServer/Servant_Base.h>
#include <tao/PortableServer/PortableServer.h>

namespace corbasim 
{

struct tao 
{
    typedef ::TAO::unbounded_basic_string_sequence< char >::element_type
        string_for_seq;
    typedef ::TAO::String_Manager String_Manager;
};

} // namespace corbasim

#endif /* CORBASIM_TAO_HPP */

