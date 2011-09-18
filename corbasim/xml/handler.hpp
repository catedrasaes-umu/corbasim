// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * handler.hpp
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

#ifndef CORBASIM_XML_HANDLER_HPP
#define CORBASIM_XML_HANDLER_HPP

#include <deque>
#include <boost/shared_ptr.hpp>
#include <corbasim/json/helper.hpp>
#include <corbasim/xml/type_traits.hpp>

namespace corbasim 
{
namespace xml 
{

typedef std::pair< const type_traits::char_t*, size_t > match_pair;
typedef std::deque< std::pair< match_pair, match_pair > > attr_list_t;

struct handler
{
    typedef boost::shared_ptr< json::helper::helper_base > helper_ptr;
    typedef std::map< std::string, helper_ptr > children_map_t;

    struct state_struct
    {
        helper_ptr current;
        children_map_t children;
    };

    std::deque< state_struct > state_stack;

    int m_level;

    handler(json::helper::helper_base * initial_helper) :
        m_level(0)
    {
        state_struct ss;
        ss.current = helper_ptr(initial_helper);
        state_stack.push_back(ss);
    }

    void processing_tag (match_pair const& tag,
                         attr_list_t const& attr_list) {}

    void start_tag (match_pair const& tag,
                    attr_list_t const& attr_list)
    {
        if (m_level++)
        {
            std::string tag_(tag.first, tag.second);
            state_struct& back = state_stack.back();
            
            children_map_t::iterator it = back.children.find(tag_);
            helper_ptr child;
        
            if (it == back.children.end())
            {
                child = helper_ptr(back.current->new_child(tag_));
                back.children[tag_] = child;
            }
            else
                child = it->second;

            state_struct ss;
            ss.current = child;
            state_stack.push_back(ss);
        }
            
        state_struct& back = state_stack.back();

        for (attr_list_t::const_iterator it = attr_list.begin(); 
                it != attr_list.end(); ++it) 
        {
            std::string name(it->first.first, it->first.second);
            std::string value(it->second.first, it->second.second);

            helper_ptr child(back.current->new_child(name));

            // TODO from_string
            // child->from_string(value);
            try {
                child->new_string(value);
            } catch (...)
            {
            }
        }
    }

    void end_tag (match_pair const& tag)
    {
        if (m_level--)
            state_stack.pop_back();
    }

    void characters (match_pair const& chars)
    {
        std::string value(chars.first, chars.second);
        state_struct& back = state_stack.back();

        // TODO from_string
        try {
            back.current->new_string(value);
        } catch (...)
        {
            // case for JSON arrays
            try {
                helper_ptr child(back.current->new_child());
                child->new_string(value);
            } catch (...)
            {
            }
        }
    }
};

} // namespace xml
} // namespace corbasim

#endif /* CORBASIM_XML_HANDLER_HPP */

