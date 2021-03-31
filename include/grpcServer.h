#pragma once

#include <vector>

#include <grpcpp/grpcpp.h>

#include "robotServer.grpc.pb.h"
#include "robot.h"

class Robot_RPC_Server final : public robot::RobotServer::Service {
    private:
        std::vector<Robot*> robots;
    public: 
        Robot_RPC_Server (std::vector<Robot*>& robots) : Service(), robots(robots) {}        

        grpc::Status moveForward(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status moveBackward(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status stopMove(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);

        grpc::Status rotateLeft(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status rotateRight(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status stopRotate(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);

        grpc::Status rotateWeaponLeft(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status rotateWeaponRight(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status stopRotateWeapon(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);

        grpc::Status startShooting(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);
        grpc::Status stopShooting(grpc::ServerContext* context, const robot::RobotRequest* request, robot::RobotReply* response);

        grpc::Status getPosition(grpc::ServerContext* context, const robot::RobotRequest* request, robot::Position* response);
        grpc::Status getRotation(grpc::ServerContext* context, const robot::RobotRequest* request, robot::Rotation* response);
        grpc::Status getTurretRotation(grpc::ServerContext* context, const robot::RobotRequest* request, robot::Rotation* response);
        grpc::Status getEnemyOrientations(grpc::ServerContext* context, const robot::RobotRequest* request, grpc::ServerWriter< robot::Orientation>* writer);
};