CORBASIM
========

C++ framework for automatic generation of testing tools for CORBA-based applications.
Or in other words, CORBASIM aims to be the SoapUI for CORBA-based applications.

CORBASIM has a code generator that generates CORBASIM plug-ins from IDL interfaces.
These plug-ins may be used with the CORBASIM generic application (corbasim_app).

GitHub mirror for https://code.google.com/p/corbasim/


![corbasim_app](https://raw.githubusercontent.com/catedrasaes-umu/corbasim/images/corbasim.png)

Example
-------

Generate a plug-in from your CORBA interfaces.

```idl
module Test
{
    struct Date
    {
        long year;
        long month;
        long day;
    };

    struct Time
    {
        long hours;
        long minutes;
        float seconds;
    };

    interface Example
    {
        void sayHello(in string to);
        void setDateTime(in Date date, in Time time);
    };
};
```

```
$ corbasim_make -n test_plugin test.idl
$ cmake .
$ make
```

Given the example and the steps above, corbasim will generate two libraries:

* libtest_plugin_idl.so - Common code for all interfaces defined in test.idl.
* libcorbasim_reflective_Test_Example.so - Actual corbasim plug-in for Test::Example interface. 

Launch corbasim_app loading your plug-ins:

```
$ corbasim_app -d /path/to/your/plug-ins/directory
```


Compilation and installation
----------------------------

Requeriments:

* JRE
* C++ compiler. Tested with GCC and Clang
* Boost C++ Libraries
* Qt4 or Qt5, components: Widgets, Script, ScriptTools.
* A CORBA ORB implementation in C++. Widely tested with ACE TAO

Steps to compile and install:

```
$ cp corbasim.cfg.base corbasim.cfg
$ vim corbasim.cfg
$ ./configure -c corbasim.cfg
$ cd build && make && make install
```

ORB support
-----------

CORBASIM has been developed with TAO (The ACE ORB) and tested with serveral of its versions.
However, it could be used with some other ORB implementations in C++.
