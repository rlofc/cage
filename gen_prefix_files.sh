#!/bin/bash
echo "#ifdef CAGE_PREFIX" > src/begin_prefix.h
ctags -x --c-kinds=pgs-d src/*.h | cut -f1 -d' ' |\
  while read symbol; do echo "#define $symbol cage_$symbol" ; done >> src/begin_prefix.h
ctags -x --c-kinds=e src/*.h | cut -f1 -d' ' |\
  while read symbol; do echo "#define $symbol CAGE_$symbol" ; done >> src/begin_prefix.h
echo "#endif" >> src/begin_prefix.h
echo "#ifdef CAGE_PREFIX" > src/end_prefix.h
ctags -x --c-kinds=pges-d src/*.h | cut -f1 -d' ' |\
  while read symbol; do echo "#undef $symbol" ; done >> src/end_prefix.h 
echo "#endif" >> src/end_prefix.h

