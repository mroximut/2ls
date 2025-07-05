#!/bin/bash

if [ ! -d "lib/cbmc" ]; then
  mkdir -p lib
  cd lib
  git clone git@github.com:mroximut/cbmc.git --branch 2ls5.61_connector
  cd ..
fi


cd lib/cbmc
bash ./build_with_mallob.sh

cd ../..
rm ./src/2ls/lib2ls.a ./src/solver/solver.a
bash ./lib/cbmc/build_with_mallob.sh

echo "The executable is src/2ls/2ls"
