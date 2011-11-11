#include "simpleC.h"
#include "simple_adapted.hpp"
#include <corbasim/json/parser.hpp>
#include <corbasim/json/writer.hpp>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
    SimpleExample::St st1;
    bool res = corbasim::json::parse(st1, "{\"b\": 100}", 10);
    std::cout << res << std::endl;
    std::cout << st1.b << std::endl;

    SimpleExample::Hijo h;
    res = corbasim::json::parse(h, "{\"b\": 100}", 10);
    std::cout << res << std::endl;
    std::cout << "b: " << h.b << std::endl;

    std::string str("{\"b\": 100, \"s\": \"prueba\",\"l\": true}");
    SimpleExample::Hijo h2;
    res = corbasim::json::parse(h2, str);
    std::cout << res << std::endl;
    std::cout << "b: " << h2.b << std::endl;
    std::cout << "s: " << h2.s << std::endl;
    std::cout << "l: " << h2.l << std::endl;

    SimpleExample::Padre p;
    str = "{\"h\": {\"b\": 100}}";
    res = corbasim::json::parse(p, str);
    std::cout << res << std::endl;
    std::cout << "b: " << p.h.b << std::endl;
    
    str = "{\"h\": {\"b\": 100, \"s\": \"prueba\",\"l\": true}}";
    SimpleExample::Padre p2;
    res = corbasim::json::parse(p2, str);
    std::cout << res << std::endl;
    std::cout << "b: " << p2.h.b << std::endl;
    std::cout << "s: " << p2.h.s << std::endl;
    std::cout << "l: " << p2.h.l << std::endl;

    str = "{\"p\": [{\"h\": {\"b\": 100, \"s\": \"prueba\",\"l\": true}}]}";
    SimpleExample::Abuelo ab;
    res = corbasim::json::parse(ab, str);
    std::cout << "b: " << ab.p[0].h.b << std::endl;
    std::cout << "s: " << ab.p[0].h.s << std::endl;
    std::cout << "l: " << ab.p[0].h.l << std::endl;


    std::cout << std::endl << std::endl << std::endl;

    str = "{\"l\": [0,1,2,3,4,5], \"b\": 1560}";
    SimpleExample::St st2;
    res = corbasim::json::parse(st2, str);
    std::cout << res << std::endl;
    std::cout << st2.b << std::endl;
    std::cout << st2.l.length() << std::endl;

    for (int i = 0; i < st2.l.length(); i++) 
        std::cout << "l[" << i << "] = " << st2.l[i] << std::endl;


    corbasim::json::write(std::cout, st2); 
    std::cout << std::endl << std::endl << std::endl;

    corbasim::json::write(std::cout, ab); 
    std::cout << std::endl << std::endl << std::endl;

    std::ostringstream oss;
    corbasim::json::write(oss, ab); 
    SimpleExample::Abuelo ab2;
    res = corbasim::json::parse(ab2, oss.str());

    std::map< std::string, std::string > mapa;
    mapa["hola"] = "adios";
    mapa["adios"] = "hola";
    mapa["ciao"] = ":S";
    corbasim::json::write(std::cout, mapa); 
    
    std::cout << std::endl << std::endl << std::endl;
    
    std::ostringstream oss2;
    std::map< std::string, std::string > mapa2;
    corbasim::json::write(oss2, mapa);
    res = corbasim::json::parse(mapa2, oss2.str());

    corbasim::json::write(std::cout, mapa2); 
    std::cout << std::endl << std::endl << std::endl;

    {
        std::list< std::map< std::string, std::string > > maplist;
        maplist.push_back(mapa);
        maplist.push_back(mapa2);
        maplist.push_back(mapa);
        maplist.push_back(mapa2);
        corbasim::json::write(std::cout, maplist); 
        std::cout << std::endl << std::endl << std::endl;
    }

    {
        std::vector< std::map< std::string, std::string > > maplist;
        maplist.push_back(mapa);
        maplist.push_back(mapa2);
        maplist.push_back(mapa);
        maplist.push_back(mapa2);
        corbasim::json::write(std::cout, maplist); 
        std::cout << std::endl << std::endl << std::endl;
    }

    {
        std::deque< std::map< std::string, std::string > > maplist;
        maplist.push_back(mapa);
        maplist.push_back(mapa2);
        maplist.push_back(mapa);
        maplist.push_back(mapa2);
        corbasim::json::write(std::cout, maplist); 
        std::cout << std::endl << std::endl << std::endl;
    }

    {
        std::ostringstream oss;
        SimpleExample::St mSt, mSt2;

        mSt.ss.length(10);
        for (int i = 0; i < 10; i++) 
        {
            mSt.ss[i] = "prueba";
        }
        
        corbasim::json::write(std::cout, mSt); 
        corbasim::json::write(oss, mSt); 
        std::cout << std::endl << std::endl << std::endl;
        
        res = corbasim::json::parse(mSt2, oss.str());
        corbasim::json::write(std::cout, mSt2); 
        std::cout << std::endl << std::endl << std::endl;
    }

}

