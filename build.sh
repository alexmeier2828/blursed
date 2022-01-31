#bin/bash!
mkdir build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ./src -B ./build

cd ./build
make 
cd ../
