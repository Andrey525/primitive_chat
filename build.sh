# !/bin/bash
git submodule init
git submodule update
if [[ "$1" == "Debug" || "$1" == "Release" ]]
then
    cmake -S . -B build/$1 -DCMAKE_BUILD_TYPE=$1
    cmake --build build/$1
else
    echo "build type should be else Debug or Release"
fi
exit 0
