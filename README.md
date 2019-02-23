# Client 
  Send request to read value of specified key

# Server
  Return value of specified key

# Build
## Install proto and gRPC
### On ubuntu 18.04
sudo apt-get install build-essential autoconf libtool pkg-config automake curl
git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
cd grpc
git submodule update --init
 
### Build and install protobuf
 - cd ./third_party/protobuf
 - ./autogen.sh
 - ./configure --prefix=/opt/protobuf
 - make -j `nproc`
 - sudo make install
  
### Build and install gRPC
 - cd ../..
 - make -j `nproc` PROTOC=/opt/protobuf/bin/protoc 
 - sudo make prefix=/opt/grpc install

## Cmake
 - cd server
 - mkdir build && cd build
 - cmake ..
 - make
