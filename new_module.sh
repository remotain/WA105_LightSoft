#!/bin/bash

sed "s/template/${1}/g" $WLS_PATH/src/module_template.cc > $WLS_PATH/src/module_${1}.cc 
sed "s/template/${1}/g" $WLS_PATH/include/module_template.h > $WLS_PATH/include/module_${1}.h

sed -i -e "$ i\ 
#pragma link C++ class module_${1}+;
" $WLS_PATH/include/LinkDef.h