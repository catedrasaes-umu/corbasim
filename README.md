CORBASIM
========

C++ framework for automatic generation of testing tools for CORBA-based applications.
Or in other words, CORBASIM aims to be the SoapUI for CORBA-based applications.

CORBASIM has a code generator that generates CORBASIM plug-ins from IDL interfaces.
These plug-ins may be used with the CORBASIM generic application (corbasim_app).

GitHub mirror for https://code.google.com/p/corbasim/

Example
-------

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
