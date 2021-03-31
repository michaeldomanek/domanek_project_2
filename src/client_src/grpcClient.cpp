#include "grpcClient.h"

using namespace std;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using robot::RobotServer;
using robot::RobotReply;
using robot::RobotRequest;
using robot::Position;
using robot::Rotation;
using robot::Orientation;

void Robot_RPC_Client::moveForward() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->moveForward(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::moveBackward() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->moveBackward(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::Robot_RPC_Client::stopMove() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->stopMove(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::rotateLeft() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->rotateLeft(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::rotateRight() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->rotateRight(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::stopRotate() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->stopRotate(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::rotateWeaponLeft() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->rotateWeaponLeft(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::rotateWeaponRight() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->rotateWeaponRight(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::stopRotateWeapon() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->stopRotateWeapon(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::startShooting() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->startShooting(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void Robot_RPC_Client::stopShooting() {
    ClientContext context;
    RobotReply reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->stopShooting(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

sf::Vector2f Robot_RPC_Client::getPosition() {
    ClientContext context;
    Position reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->getPosition(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return sf::Vector2f(-1, -1);
    }

    return sf::Vector2f(reply.x(), reply.y());
}

float Robot_RPC_Client::getRotation() {
    ClientContext context;
    Rotation reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->getRotation(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return -1;
    }

    return reply.alpha();
}

float Robot_RPC_Client::getTurretRotation() {
    ClientContext context;
    Rotation reply;
    RobotRequest request;
    request.set_id(id);

    Status status = stub->getTurretRotation(&context, request, &reply);

    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return -1;
    }

    return reply.alpha();
}

vector<RobotOrientation> Robot_RPC_Client::getEnemyOrientations() {
    ClientContext context;
    Orientation reply;
    RobotRequest request;
    vector<RobotOrientation> orientations;

    request.set_id(id);

    std::unique_ptr<ClientReader<Orientation>> ptr = stub->getEnemyOrientations(&context, request);

    while(ptr.get()->Read(&reply)) {
        sf::Vector2f pos{reply.position().x(), reply.position().y()};
        orientations.push_back(RobotOrientation(pos, reply.rotation().alpha(), reply.rotation().alpha()));
    }

    return orientations;
}
