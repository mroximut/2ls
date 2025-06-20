#!/bin/bash

# if [ "$1" != "" ]
# then
#   COMPILER="$1"
# fi

#git submodule update --init --recursive
cd lib/cbmc
git checkout 2ls5.61
./build_with_cadical.sh
# git checkout $CBMC_VERSION
# if grep '^MINISAT2' src/config.inc > /dev/null
# then
#   make -C src minisat2-download > /dev/null
# elif grep '^GLUCOSE' src/config.inc
# then
#   make -C src glucose-download
# else
#   echo "SAT solver not supported"
#   exit 1
# fi
# if [ "$COMPILER" != "" ]
# then
#   make -C src CXX=$COMPILER $2
# else
#   make -C src $2
# fi
cd ../..
make -C src LIBS="$PWD/lib/cbmc/cadical/build/libcadical.a" IPASIR=$PWD/lib/cbmc/cadical/src -j16
# if [ "$COMPILER" != "" ]
# then
#   make -C src CXX=$COMPILER $2
# else
#   make -C src $2
# fi

echo "The executable is src/2ls/2ls"
