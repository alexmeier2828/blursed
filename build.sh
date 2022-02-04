#bin/bash!
mkdir build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -D CMAKE_C_FLAGS_DEBUG='-00 -g3' ./ -B ./build

cd ./build
make 
cd ../
