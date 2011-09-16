#!/bin/bash

BASEDIR=`dirname $0`

for i in ${BASEDIR}/*.idl; do
    echo "Generando $i................................." 
    ${BASEDIR}/../../corbasim_idl/bin/corbasim_idl -Gclient -Gserver -Ginjector $@ $i
done

