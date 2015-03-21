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

```
$ corbasim_make -n test_plugin test.idl
$ cmake .
$ make
```

Launch corbasim_app loading your plug-ins:

```
$ corbasim_app -d /path/tp/your/plug-ins/directory
```


Compilation and installation
----------------------------

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
