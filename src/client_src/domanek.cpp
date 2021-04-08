#include "robotClient.h"
#include <math.h>

using namespace std;

int main() {
    string port{"1113"};
    string name{"Michael"};
    string grpcPort{"50051"};

    RobotProperties properties{name, sf::Color::Blue};

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
            
            robotClient.startShooting();
            robotClient.moveForward();
            sleep(4);
            robotClient.stopMove();

            while(true) {
                sf::Vector2f enemypos{robotClient.getEnemiesRobotInformations()[0].getPosition()};
                sf::Vector2f pos{robotClient.getPosition()};
                float rot{robotClient.getTurretRotation()};

                float slope{(enemypos.y - pos.y) / (enemypos.x - pos.x)};
                // fmt::print("rot: {}\n", rot);
                // fmt::print("x: {} | y: {}\n", pos.x, pos.y);
                // fmt::print("ex: {} | ey: {}\n", enemypos.x, enemypos.y);

                bool xGreater{pos.x > enemypos.x};
                bool yGreater{pos.y > enemypos.y};
                float degrees{abs(atan(slope) * (180.0f / (float)M_PI))};

                float delta{1};
                float desiredRot;
                bool rotateLeft;

                if(xGreater and yGreater) {  //left top
                    desiredRot = 270 + degrees; 
                    rotateLeft = rot < 90 + degrees or rot > desiredRot + delta;
                } else if(!xGreater and yGreater) { //right top
                    desiredRot = 90 - degrees;
                    rotateLeft = rot < 180 + degrees and rot > desiredRot + delta; 
                } else if(!xGreater and !yGreater) {  //right bottom
                    desiredRot = degrees;
                    rotateLeft = rot < 270 + degrees and rot > 90 + desiredRot + delta;
                } else { //left bottom
                    desiredRot = 180 + (90 - degrees);
                    rotateLeft = rot < degrees or rot > desiredRot + delta;
                }

                // fmt::print("desired rot {}\n", desiredRot);
                // fmt::print("rotateLeft: {}\n", rotateLeft);

                if(rot > desiredRot - delta and rot < desiredRot + delta) {
                    robotClient.stopRotateWeapon();
                } else if(rotateLeft) {
                    robotClient.rotateWeaponLeft();
                } else {
                    robotClient.rotateWeaponRight();
                }

                usleep(10000);
            }
        } catch (exception& e) {
            fmt::print("Game ended\n");
        }
    }
}