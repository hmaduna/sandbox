# Install prerequisites:
## Linux
Build and install gRPC and Protocol Buffers using [Quick Start Guide](https://grpc.io/docs/languages/cpp/quickstart/) (up until "Build the Example").
## Windows
Install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/).
Follow [C++ Building Guide](https://github.com/grpc/grpc/blob/master/BUILDING.md) to build gRPC and Protocol Buffers.
After build, use this command to install gRPC and Protocol Buffers:
```sh
 > cmake --install .
```
Add "C:\Program Files (x86)\grpc\bin" to PATH environment variable.

# Build both server and client:
## Linux
```sh
 $ mkdir build
 $ cd build
 $ cmake ..
 $ cmake --build .
```
## Windows (using Visual Studio 2019 or later)
```sh
 > md .build
 > cd .build
 > cmake .. -G "Visual Studio 16 2019"
 > cmake --build . --config Release
```

# Run server
## Linux
```sh
 $ ./simple_server <port>
```
## Windows
```sh
 > cd Release
 > simple_server.exe <port>
```

# Run client
## Linux:
```sh
 $ ./simple_client <ip:port>
```
## Windows:
```sh
 > cd Release
 > simple_client.exe <ip:port>
```
