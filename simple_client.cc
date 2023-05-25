#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>

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
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<SimpleService::Stub> stub_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  std::string target_str = absl::GetFlag(FLAGS_target);
  if (argc > 1) {
    target_str = argv[1];
  }

  SimpleClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  for (;;) {
    std::string reply = client.Ping();
    std::cout << "Client received: " << reply << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  return 0;
}
