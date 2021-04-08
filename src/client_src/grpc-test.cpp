#include "robotClient.h"

using namespace std;

int main() {
    string port{"1113"};
    string name{"Grpc test client"};
    string grpcPort{"50051"};

    RobotProperties properties{name, sf::Color::Magenta};

    RobotConfiguration config;

    int id = Game::connectToGame(port, properties, config);

    fmt::print("speed: {}, health: {}, rotation: {}, turret: {}, fire: {}, shoot-move: {}\n", 
               config.getSpeed(), config.getHealth(), config.getRobotRotation(), 
               config.getTurretRotation(), config.getMinFireCountdown(), config.canShootAndMove()
    );

    if(id >= 0) {
        try {
            fmt::print("Game stated! Robot id: {}\n", id);

            Robot_RPC_Client robotClient = Game::getRobot_RPC_Client(grpcPort, id);

            robotClient.moveForward();
            sleep(2);

            while(true) {
                robotClient.moveForward();
                sleep(1);
                robotClient.moveBackward();
                sleep(1);
                robotClient.stopMove();
                sleep(1);
                robotClient.rotateLeft();
                sleep(1);
                robotClient.rotateRight();
                sleep(1);
                robotClient.stopRotate();
                sleep(1);
                robotClient.rotateWeaponLeft();
                sleep(1);
                robotClient.rotateWeaponRight();
                sleep(1);
                robotClient.stopRotateWeapon();
                sleep(1);
                robotClient.startShooting();
                sleep(1);
                robotClient.stopShooting();
                sleep(1);

                sf::Vector2f pos{robotClient.getPosition()};
                fmt::print("x: {} | y: {}\n", pos.x, pos.y);

                float rotation{robotClient.getRotation()};
                fmt::print("rotation: {}\n", rotation);

                float weaponRotation{robotClient.getTurretRotation()};
                fmt::print("weapon rotation: {}\n", weaponRotation);

                for (auto info : robotClient.getEnemiesRobotInformations()) {
                    fmt::print("id: {} | name: {} | x: {} | y: {} | rotation: {} | weapon rotation: {}\n", 
                        info.getID(), info.getName(),
                        info.getPosition().x, info.getPosition().y, 
                        info.getRotation(), info.getTurretRotation()
                    );
                }

                sleep(1);
            }
        } catch (exception& e) {
            fmt::print("Game ended\n");
        }
    }
}