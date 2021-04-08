#include "robotClient.h"

using namespace std;

int main() {
    string port{"1113"};
    string name{"Random client"};
    string grpcPort{"50051"};

    RobotProperties properties{name, sf::Color::Green};

    RobotConfiguration config;

    int id = Game::connectToGame(port, properties, config);

    if(id >= 0) {
        try {
            fmt::print("Game stated! Robot id: {}\n", id);

            Robot_RPC_Client robotClient = Game::getRobot_RPC_Client(grpcPort, id);

            robotClient.moveForward();
            robotClient.startShooting();
            robotClient.rotateLeft();
            robotClient.rotateWeaponLeft();
        } catch (exception& e) {
            fmt::print("Game ended!\n");
        }
    }
}