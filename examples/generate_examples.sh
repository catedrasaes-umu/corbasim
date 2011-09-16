#!/bin/bash


for i in `find . -name generate.sh`; do
    OLDPWD=`pwd`
    cd `dirname $i` ; ./generate.sh; cd $OLDPWD
done


