#include "robotClient.h"
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    string port{"1113"};
    string name{"MichaelV2"};
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
            sleep(3);
            robotClient.stopMove();
            sf::Clock clock;

            while(true) {
                sf::Vector2f pos{robotClient.getPosition()};

                vector<RobotInformation> enemies{robotClient.getEnemiesRobotInformations()};
                auto nearestEnemy = min_element(enemies.begin(), enemies.end(), [&pos](auto a, auto b){
                    sf::Vector2f aEnemyPos{a.getPosition()};
                    sf::Vector2f bEnemyPos{b.getPosition()};
                    return sqrt(pow(aEnemyPos.x - pos.x, 2) + pow(aEnemyPos.y - pos.y, 2)) 
                         < sqrt(pow(bEnemyPos.x - pos.x, 2) + pow(bEnemyPos.y - pos.y, 2));
                });

                sf::Vector2f enemypos{nearestEnemy->getPosition()};
                float rot{robotClient.getTurretRotation()};

                float slope{(enemypos.y - pos.y) / (enemypos.x - pos.x)};

                bool xGreater{pos.x > enemypos.x};
                bool yGreater{pos.y > enemypos.y};
                float degrees{abs(atan(slope) * (180.0f / (float)M_PI))};

                float delta{1};
                float desiredRot;
                bool rotateLeft;
                bool moveForward{true};

                fmt::print("sec: {}\n", clock.getElapsedTime().asMilliseconds());
                if(clock.getElapsedTime().asMilliseconds() > 2000) {
                    if (moveForward) {
                        moveForward = false;
                        robotClient.moveForward();
                    } else {
                        moveForward = true;
                        robotClient.moveBackward();
                    }
                    clock.restart();
                }

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