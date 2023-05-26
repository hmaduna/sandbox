cmake_minimum_required(VERSION 3.8)

project(simple_service)

# find spdlog installation
if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

# find Protobuf installation
# looks for protobuf-config.cmake file installed by Protobuf's cmake installation
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# find gRPC installation
# looks for gRPCConfig.cmake file installed by gRPC's cmake installation
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# proto file
get_filename_component(ss_proto "simple_service.proto" ABSOLUTE)
get_filename_component(ss_proto_path "${ss_proto}" PATH)

# generated sources
set(ss_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/simple_service.pb.cc")
set(ss_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/simple_service.pb.h")
set(ss_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/simple_service.grpc.pb.cc")
set(ss_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/simple_service.grpc.pb.h")
add_custom_command(
      OUTPUT "${ss_proto_srcs}" "${ss_proto_hdrs}" "${ss_grpc_srcs}" "${ss_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${ss_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${ss_proto}"
      DEPENDS "${ss_proto}")

# include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# ss_grpc_proto
add_library(ss_grpc_proto
  ${ss_grpc_srcs}
  ${ss_grpc_hdrs}
  ${ss_proto_srcs}
  ${ss_proto_hdrs})
target_link_libraries(ss_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# targets simple_(client|server)
foreach(_target
  simple_client simple_server)
  add_executable(${_target} "${_target}.cc")
  target_link_libraries(${_target}
    ss_grpc_proto
    absl::flags
    absl::flags_parse
    spdlog::spdlog
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()
