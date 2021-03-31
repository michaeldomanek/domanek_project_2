#pragma once

#include "orientation.h"

#include <grpcpp/grpcpp.h>
#include "robotServer.grpc.pb.h"

#include <SFML/Graphics.hpp>
#include <vector>


class Robot_RPC_Client {
    private:
        std::unique_ptr<robot::RobotServer::Stub> stub;
        const int id;
    public:
        Robot_RPC_Client(std::shared_ptr<grpc::Channel> channel, int id) :
            stub(robot::RobotServer::NewStub(channel)),
            id(id)
            {}

        void moveForward();
        void moveBackward();
        void stopMove();

        void rotateLeft();
        void rotateRight();
        void stopRotate();

        void rotateWeaponLeft();
        void rotateWeaponRight();
        void stopRotateWeapon();

        void startShooting();
        void stopShooting();

        sf::Vector2f getPosition();
        float getRotation();
        float getTurretRotation();
        std::vector<RobotOrientation> getEnemyOrientations();
};