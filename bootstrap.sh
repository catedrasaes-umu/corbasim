#! /bin/sh

CORBASIMDIR=`dirname $0`
CORBASIMDIR=`cd $CORBASIMDIR && pwd`

create_cfg ()
{
    CFG=$1
    CMAKE_OPTIONS=$2
    mkdir -p ${CFG}
    cd ${CFG}
    cmake ${CMAKE_OPTIONS} ${CORBASIMDIR}
    cd ..
}


echo -n "Insert Boost C++ Libraries path [Enter = default]: "
read line

if [ "$line" != "" ]; then
    export BOOST_ROOT=$line
fi

echo -n "Insert QT path [Enter = default]: "
read line

if [ "$line" != "" ]; then
   export PATH=$line:$PATH
fi

echo -n "Insert CORBASIM installation path [Enter = default (/usr)]: "
read line

if [ "$line" != "" ]; then
    INSTALL_PATH="-DCMAKE_INSTALL_PREFIX=$line"
fi

# default
create_cfg "build" "-DCMAKE_BUILD_TYPE=Release ${INSTALL_PATH} $@"

# dbg
# create_cfg "build-dbg" "-DCMAKE_BUILD_TYPE=Debug -DCORBASIM_TEST=1 ${INSTALL_PATH} $@"
