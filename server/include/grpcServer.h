#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "robotProperties.pb.h"
#include "robotServer.grpc.pb.h"
#include "robot.h"

using namespace std;
using grpc::Server;
using grpc::Status;
using robot::RobotReply;
using robot::RobotRequest;

class Robot_RPC_Server final : public robot::RobotServer::Service {
    private:
        vector<Robot*> robots;
    public: 
        Robot_RPC_Server (vector<Robot*>& robots) : Service(), robots(robots) {}        

        Status moveForward(grpc::ServerContext* context, const RobotRequest* request, RobotReply* reply) override {
            (void) context;
            (void) reply;
            
            robots[request->id()]->moveForward();
            return Status::OK;
        }

        Status moveBackward(grpc::ServerContext* context, const RobotRequest* request, RobotReply* reply) override {
            (void) context;
            (void) reply;
            
            robots[request->id()]->moveBackward();

            return Status::OK;
        }

        Status stopMove(grpc::ServerContext* context, const RobotRequest* request, RobotReply* reply) override {
            (void) context;
            (void) reply;

            robots[request->id()]->stopMove();

            return Status::OK;
        }
};

