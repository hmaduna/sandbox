#include <chrono>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/strings/str_cat.h"

#include <grpcpp/grpcpp.h>

#include "spdlog/spdlog.h"

#include "simple_service.grpc.pb.h"

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using simple_service::SimpleService;
using simple_service::SimpleRequest;
using simple_service::SimpleReply;

class SimpleClient {
 public:
  SimpleClient(std::shared_ptr<Channel> channel)
      : stub_(SimpleService::NewStub(channel)) {}

  std::string Ping() {
    SimpleRequest request;
    SimpleReply reply;
    ClientContext context;

    Status status = stub_->Ping(&context, request, &reply);

    if (status.ok()) {
      return "OK";
    } else {
      spdlog::error("{}: {}", status.error_code(), status.error_message());
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<SimpleService::Stub> stub_;
};

int main(int argc, char** argv) {
  absl::SetProgramUsageMessage(
  absl::StrCat("Sample usage:\n", argv[0], " --target 10.20.30.40:1234"));
  absl::ParseCommandLine(argc, argv);
  std::string target_str = absl::GetFlag(FLAGS_target);

  SimpleClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  for (;;) {
    std::string reply = client.Ping();
    spdlog::info("Client received: {}", reply);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  return 0;
}
