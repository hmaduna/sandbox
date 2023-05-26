# Simple service using gRPC

## Installing pre-requisites
### Linux
Build and install gRPC and Protocol Buffers using [Quick Start Guide](https://grpc.io/docs/languages/cpp/quickstart/) (up until "Build the Example").

Build and install spdlog:
``` sh
 $ git clone https://github.com/gabime/spdlog.git
 $ cd spdlog && mkdir build && cd build
 $ cmake .. && make -j
 $ cmake --install . --prefix ~/.local
```

### Windows
Install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) to get Visual C++ compiler.

Follow [C++ Building Guide](https://github.com/grpc/grpc/blob/master/BUILDING.md) to build gRPC and Protocol Buffers.

After build, use this command to install gRPC and Protocol Buffers:
```sh
 > cmake --install .
```
Add "C:\Program Files (x86)\grpc\bin" to PATH environment variable.

Build and install spdlog:
``` sh
 > git clone https://github.com/gabime/spdlog.git
 > cd spdlog && mkdir build && cd build
 > cmake ..
 > cmake --install .
```

## Building server and client
### Linux
```sh
 $ mkdir build
 $ cd build
 $ cmake ..
 $ cmake --build .
```
### Windows (using Visual Studio 2019 or later)
```sh
 > md .build
 > cd .build
 > cmake .. -G "Visual Studio 16 2019"
 > cmake --build . --config Release
```

## Running server
### Linux
```sh
 $ ./simple_server [--port <port>]
```
### Windows
```sh
 > cd Release
 > simple_server.exe [--port <port>]
```
Default port is 50051.

## Running client
### Linux
```sh
 $ ./simple_client [--target <ip:port>]
```
### Windows
```sh
 > cd Release
 > simple_client.exe [--target <ip:port>]
```
Default target is localhost:50051.
