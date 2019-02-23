#include <iostream>
#include <grpc++/grpc++.h>
#include "mem.grpc.pb.h"
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using protos::MemMessage;
using protos::Access;
using namespace std;

map<string, string> Map;

class  AccessServiceImpl final: public Access::Service {
    Status GetState(ServerContext* context, const MemMessage* request, MemMessage* response) override {
	if (request->key() != "") {
	    string value = Map.find(request->key())->second;

	    cout << "[GET]" << request->key() << ":" << value << endl;

	    response->set_value(value);
	    response->set_state(protos::MemMessage_type_VALID);
	    return Status::OK;
	} else {
	    response->set_state(protos::MemMessage_type_INVALID);
	    return Status::OK;
	}
    }

    Status PutState(ServerContext* context, const MemMessage* request, MemMessage* response) override {
	if (request->key() != "" and request->value() != "") {
	    Map[request->key()] = request->value();

	    cout << "[PUT]" << request->key() << ":" << request->value() << endl;

	    response->set_state(protos::MemMessage_type_VALID);
	    return Status::OK;
	} else {
	    response->set_state(protos::MemMessage_type_INVALID);
	    return Status::OK;
	}
    }
};

void RunServer() {
  string server_address("0.0.0.0:50051");

  ServerBuilder builder;
  AccessServiceImpl service;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Server listening on " << server_address << endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
