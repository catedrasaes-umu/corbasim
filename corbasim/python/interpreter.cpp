// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * interpreter.cpp
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

#include "interpreter.hpp"
#include <boost/python.hpp>
#include <boost/bind.hpp>
#include <sstream>
#include <iostream>

using namespace corbasim::python;
namespace bp = boost::python;

namespace corbasim 
{
namespace python 
{

struct context : public corbasim::scripting::context
{
    boost::python::dict global;
    boost::python::dict local;
};

} // namespace python
} // namespace corbasim

interpreter::interpreter() :
    m_output(this)
{
    // TODO inicializar solo una vez
    Py_Initialize();

    context * main_ctx = new context;
    m_main_context = scripting::context_ptr(main_ctx);

    bp::object main = bp::import("__main__");

    main_ctx->global = 
        bp::extract< bp::dict >(
                main.attr("__dict__"));
    main_ctx->local = main_ctx->global;

    bp::exec("import json", main_ctx->global, main_ctx->local);

    main_ctx->global["PythonOutRedirect"] = 
        bp::class_< python_out_redirect >("PythonOutRedirect", 
                bp::init<>())
            .def("write", &python_out_redirect::write);

    bp::import("sys").attr("stderr") = m_output;
    bp::import("sys").attr("stdout") = m_output;
}

interpreter::~interpreter()
{
}

void do_call(interpreter* _this, 
        corbasim::core::operation_factory_base * factory,
        bp::object obj)
{
    corbasim::scripting::context_ptr ctx(_this->new_context());
    context * ctx_ = static_cast < context* >(ctx.get());

    ctx_->local["tmp"] = obj;

    _this->exec_code(ctx, "tmp = json.dumps(tmp)");
    
    // Extrae el objeto serializado
    obj = ctx_->local["tmp"];

    std::string json_request = bp::extract< std::string >(obj);

    // Deserializa la request en C++
    corbasim::event::request_ptr req(
            factory->from_json(json_request.c_str()));

    _this->request_signal(req);
}

void interpreter::register_factory(core::factory_base * factory)
{
    context * ctx_ = static_cast< context* >(m_main_context.get());

    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_factory_base * op = 
            factory->get_factory_by_index(i);

        const char * name = op->get_name();

        // Inserta una función en el contexto global con el
        // nombre de la operación.
        // TODO debería ser en un módulo anidado, con nombre
        // "output".
        ctx_->global[name] = 
            bp::make_function(boost::bind(&do_call, this, op, _1),
                    bp::default_call_policies(),
                    boost::mpl::vector<void, bp::object >());
    }
}

void interpreter::request_to_context(scripting::context_ptr ctx, 
        core::factory_base * factory,
        const char * name,
        event::request_ptr req)
{
    context * ctx_ = static_cast< context* >(ctx.get());
    tag_t tag = req->get_tag();

    try {

        std::ostringstream oss;
        std::string json_request;

        factory->get_factory_by_tag(tag)->to_json(req.get(), json_request);

        ctx_->local[name] = bp::str(json_request.c_str());

        oss << name << " = json.loads(" << name << ")" << std::endl;

        std::string code = oss.str();

        bp::exec(code.c_str(), ctx_->global, ctx_->local);

    } catch(...) {
        std::cerr << "Exception catched!" << std::endl;

        if (PyErr_Occurred())
            PyErr_Print();
    }
}

corbasim::scripting::context_ptr interpreter::main_context()
{
    return m_main_context;
}

corbasim::scripting::context_ptr interpreter::new_context()
{
    scripting::context_ptr ctx(new context);
    context * ctx_ = static_cast< context* >(ctx.get());
    context * main_ctx_ = static_cast< context* >(m_main_context.get());

    ctx_->global = main_ctx_->global;

    return ctx;
}

void interpreter::exec_code(scripting::context_ptr ctx, 
        const std::string& code)
{
    try {
        context * ctx_ = static_cast< context* >(ctx.get());
        bp::exec(code.c_str(), ctx_->global, ctx_->local);
    } catch (...) {
        std::cerr << "Exception catched!" << std::endl;

        if (PyErr_Occurred())
            PyErr_Print();
    }
}

