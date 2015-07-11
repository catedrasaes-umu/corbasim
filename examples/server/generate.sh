#!/bin/bash

DIR=`dirname $0`
DIR=`cd $DIR; pwd`

cd ${DIR}

${DIR}/../../corbasim_idl/bin/corbasim_idl -Gserver server_example.idl
