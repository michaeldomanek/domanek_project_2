#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "robotServer.grpc.pb.h"

using grpc::ClientContext;
using grpc::Status;
using robot::RobotServer;
using robot::RobotReply;
using robot::RobotRequest;

class Robot_RPC_Client {
    public:
        Robot_RPC_Client(std::shared_ptr<grpc::Channel> channel)
            : stub_(RobotServer::NewStub(channel)) {}

        void moveForward(const int& id) {
            ClientContext context;
            RobotReply reply;
            RobotRequest request;
            request.set_id(id);

            Status status = stub_->moveForward(&context, request, &reply);

            if (!status.ok()) {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }

        void moveBackward(const int& id) {
            ClientContext context;
            RobotReply reply;
            RobotRequest request;
            request.set_id(id);

            Status status = stub_->moveBackward(&context, request, &reply);

            if (!status.ok()) {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }

        void stopMove(const int& id) {
            ClientContext context;
            RobotReply reply;
            RobotRequest request;
            request.set_id(id);

            Status status = stub_->stopMove(&context, request, &reply);

            if (!status.ok()) {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }

    private:
        std::unique_ptr<RobotServer::Stub> stub_;
};