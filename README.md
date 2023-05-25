# Install prerequisites:
Build and install gRPC and Protocol Buffers using [Quick Start Quide](https://grpc.io/docs/languages/cpp/quickstart/) (up until "Build the Example").

# Build server and client:
```sh
 $ mkdir build
 $ cd build
 $ cmake ..
 $ cmake --build .
```

# Run server
```sh
 $ ./simple_server <port>
```

# Run client
```sh
 $ ./simple_client <ip>:<port>
```
