#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "spdlog/spdlog.h"

#include "simple_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using simple_service::SimpleService;
using simple_service::SimpleRequest;
using simple_service::SimpleReply;

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

class SimpleServiceImpl final : public SimpleService::Service {
  Status Ping(ServerContext* context, const SimpleRequest* request,
                  SimpleReply* reply) override {
    spdlog::info("Ping from client");
    return Status::OK;
  }
};

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  SimpleServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());

  spdlog::info("Server listening on {}", server_address);

  server->Wait();
}

int main(int argc, char** argv) {
  absl::SetProgramUsageMessage(absl::StrCat("Sample usage:\n", argv[0], " --port 1234"));
  absl::ParseCommandLine(argc, argv);
  uint16_t port = absl::GetFlag(FLAGS_port);

  RunServer(port);

  return 0;
}
