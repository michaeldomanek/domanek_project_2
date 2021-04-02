#include "grpcServer.h"
#include "spdlog/spdlog.h"

using namespace std;
using grpc::Server;
using grpc::Status;
using grpc::ServerContext;
using grpc::ServerWriter;

using robot::RobotReply;
using robot::RobotRequest;
using robot::Position;
using robot::Rotation;
using robot::Orientation;

Status Robot_RPC_Server::moveForward(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->moveForward();

    spdlog::debug("Robot {}: moveForward", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::moveBackward(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->moveBackward();

    spdlog::debug("Robot {}: moveBackward", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::stopMove(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;

    robots[request->id()]->stopMove();

    spdlog::debug("Robot {}: stopMove", request->id());

    return Status::OK;
}


Status Robot_RPC_Server::rotateLeft(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateLeft();

    spdlog::debug("Robot {}: rotateLeft", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::rotateRight(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateRight();

    spdlog::debug("Robot {}: rotateRight", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::stopRotate(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;

    robots[request->id()]->stopRotate();

    spdlog::debug("Robot {}: stopRotate", request->id());

    return Status::OK;
}


Status Robot_RPC_Server::rotateWeaponLeft(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateWeaponLeft();

    spdlog::debug("Robot {}: rotateWeaponLeft", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::rotateWeaponRight(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateWeaponRight();

    spdlog::debug("Robot {}: rotateWeaponRight", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::stopRotateWeapon(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;

    robots[request->id()]->stopRotateWeapon();

    spdlog::debug("Robot {}: stopRotateWeapon", request->id());

    return Status::OK;
}


Status Robot_RPC_Server::startShooting(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->startShooting();

    spdlog::debug("Robot {}: startShooting", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::stopShooting(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->stopShooting();

    spdlog::debug("Robot {}: stopShooting", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::getPosition(ServerContext* context, const RobotRequest* request, Position* reply) {
    (void) context;

    sf::Vector2f pos{robots[request->id()]->getPosition()};
    reply->set_x(pos.x);
    reply->set_y(pos.y);

    spdlog::debug("Robot {}: getPosition", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::getRotation(ServerContext* context, const RobotRequest* request, Rotation* reply) {
    (void) context;
    
    reply->set_alpha(robots[request->id()]->getRotation());

    spdlog::debug("Robot {}: getRotation", request->id());

    return Status::OK;
}

grpc::Status Robot_RPC_Server::getTurretRotation(grpc::ServerContext* context, const robot::RobotRequest* request, robot::Rotation* reply) {
    (void) context;
    
    reply->set_alpha(robots[request->id()]->getTurretRotation());

    spdlog::debug("Robot {}: getTurretRotation", request->id());

    return Status::OK;
}

Status Robot_RPC_Server::getEnemiesRobotInformations(ServerContext* context, const RobotRequest* request, ServerWriter< Orientation>* writer) {
    (void) context;

    for(size_t i = 0; i != robots.size(); i++) {
        Robot* robo{robots[i]};

        if (i != (size_t)request->id() and not robo->isDead()) {
            Orientation orientation;
            Position pos;
            Rotation rotation;
            Rotation turretRotation;

            orientation.set_id(i);
            orientation.set_name(robo->getName());
            orientation.set_x(robo->getPosition().x);
            orientation.set_y(robo->getPosition().y);
            orientation.set_rotation(robo->getRotation());
            orientation.set_weaponrotation(robo->getTurretRotation());
            
            writer->Write(orientation);
        }
    }

    spdlog::debug("Robot {}: getEnemiesRobotInformations", request->id());
    
    return Status::OK;
}