// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * macros_impl.hpp
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

#ifndef CORBASIM_GUI_MACROS_IMPL_HPP
#define CORBASIM_GUI_MACROS_IMPL_HPP

#define CORBASIM_M_W_impl0(fqn, impl) \
    namespace corbasim { namespace widgets { \
        template< > \
        struct widget_member< _corbasim_ ## fqn ## _corbasim_member > : \
            public detail::impl < adapted::member_type < \
                    _corbasim_ ## fqn ## _corbasim_member >::type \
                > \
        {  \
        }; \
    }} \
    /***/

#define CORBASIM_T_W_impl0(fqn, impl) \
    namespace corbasim { namespace widgets { \
        template< > \
        struct widget< fqn > : \
            public detail::impl < fqn > \
        {  \
        }; \
    }} \
    /***/

#define CORBASIM_M_W_impl1(fqn, impl, param0) \
    namespace corbasim { namespace widgets { \
        template< > \
        struct widget_member< _corbasim_ ## fqn ## _corbasim_member > : \
            public detail::impl < adapted::member_type < \
                    _corbasim_ ## fqn ## _corbasim_member >::type, \
                    param0 \
                > \
        {  \
        }; \
    }} \
    /***/

#define CORBASIM_T_W_impl1(fqn, impl, param0) \
    namespace corbasim { namespace widgets { \
        template< > \
        struct widget< fqn > : \
            public detail::impl < fqn, param0 > \
        {  \
        }; \
    }} \
    /***/

#define CORBASIM_M_W_impl2(fqn, impl, param0, param1) \
    namespace corbasim { namespace widgets { \
        template< > \
        struct widget_member< _corbasim_ ## fqn ## _corbasim_member > : \
            public detail::impl < adapted::member_type < \
                    _corbasim_ ## fqn ## _corbasim_member >::type,\
                    param0, \
                    param1 \
                > \
        {  \
        }; \
    }} \
    /***/

#define CORBASIM_T_W_impl2(fqn, impl, param0, param1) \
    namespace corbasim { namespace widgets { \
        template< > \
        struct widget< fqn > : \
            public detail::impl < fqn, param0, param1 > \
        {  \
        }; \
    }} \
    /***/

#endif /* CORBASIM_GUI_MACROS_IMPL_HPP */

