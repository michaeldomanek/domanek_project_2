#include "grpcServer.h"

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
    return Status::OK;
}

Status Robot_RPC_Server::moveBackward(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->moveBackward();

    return Status::OK;
}

Status Robot_RPC_Server::stopMove(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;

    robots[request->id()]->stopMove();

    return Status::OK;
}


Status Robot_RPC_Server::rotateLeft(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateLeft();
    return Status::OK;
}

Status Robot_RPC_Server::rotateRight(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateRight();

    return Status::OK;
}

Status Robot_RPC_Server::stopRotate(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;

    robots[request->id()]->stopRotate();

    return Status::OK;
}


Status Robot_RPC_Server::rotateWeaponLeft(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateWeaponLeft();
    return Status::OK;
}

Status Robot_RPC_Server::rotateWeaponRight(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->rotateWeaponRight();

    return Status::OK;
}

Status Robot_RPC_Server::stopRotateWeapon(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;

    robots[request->id()]->stopRotateWeapon();

    return Status::OK;
}


Status Robot_RPC_Server::startShooting(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->startShooting();
    return Status::OK;
}

Status Robot_RPC_Server::stopShooting(ServerContext* context, const RobotRequest* request, RobotReply* reply) {
    (void) context;
    (void) reply;
    
    robots[request->id()]->stopShooting();

    return Status::OK;
}

Status Robot_RPC_Server::getPosition(ServerContext* context, const RobotRequest* request, Position* reply) {
    (void) context;

    sf::Vector2f pos{robots[request->id()]->getPosition()};
    reply->set_x(pos.x);
    reply->set_y(pos.y);

    return Status::OK;
}

Status Robot_RPC_Server::getRotation(ServerContext* context, const RobotRequest* request, Rotation* reply) {
    (void) context;
    
    reply->set_alpha(robots[request->id()]->getRotation());

    return Status::OK;
}

grpc::Status Robot_RPC_Server::getTurretRotation(grpc::ServerContext* context, const robot::RobotRequest* request, robot::Rotation* reply) {
    (void) context;
    
    reply->set_alpha(robots[request->id()]->getTurretRotation());

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
    
    return Status::OK;
}