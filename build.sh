#!/bin/bash

if [ ! -d "lib/cbmc" ]; then
  mkdir -p lib/cbmc
  cd lib/cbmc
  git clone git@github.com:mroximut/cbmc.git --branch 2ls5.61
  cd ../..
fi
cd lib/cbmc
bash ./build_with_cadical.sh

cd ../..
make -C src LIBS="$PWD/lib/cbmc/cadical/build/libcadical.a" IPASIR=$PWD/lib/cbmc/cadical/src -j16

echo "The executable is src/2ls/2ls"
