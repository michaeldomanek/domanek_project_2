#include "robotClient.h"

using namespace std;

int main() {
    string port{"1113"};
    string name{"Rect client"};
    string grpcPort{"50051"};

    RobotProperties properties{name, sf::Color::Green};

    RobotConfiguration config;

    int id = Game::connectToGame(port, properties, config);

    if(id >= 0) {
        try {
            fmt::print("Game stated! Robot id: {}\n", id);

            Robot_RPC_Client robotClient = Game::getRobot_RPC_Client(grpcPort, id);

            robotClient.startShooting();
            robotClient.rotateWeaponLeft();
            robotClient.moveForward();
            sleep(1);
            robotClient.stopMove();

            float width{500};
            float delta{3};

            float alpha{359};

            sf::Vector2f pos{robotClient.getPosition()};
            if (pos.x < width and pos.y > width) {
                alpha = 90;
            } else if (pos.x > width and pos.y < width) {
                alpha = 270;
            } else if (pos.x < width and pos.y < width) {
                alpha = 180;
            }

            robotClient.rotateRight();

            while(robotClient.getRotation() < alpha) {
                usleep(5000);
            }

            if(alpha == 355 and robotClient.getRotation() > 1) {
                usleep(5000);
            }

            usleep(10000);

            robotClient.stopRotate();
            robotClient.moveForward();

            sleep(1);
            
            while(true) {
                sf::Vector2f pos{robotClient.getPosition()};

                if (pos.x < 170 and pos.y < 150) {
                    robotClient.stopMove();
                    robotClient.rotateLeft();
                    while (robotClient.getRotation() > 180 + delta) {
                        usleep(5000);
                    }
                    robotClient.stopRotate();
                    robotClient.moveForward();
                    sleep(1);
                } else if (pos.x < 150 and pos.y > 850) {
                    robotClient.stopMove();
                    robotClient.rotateLeft();
                    while (robotClient.getRotation() > 90 + delta) {
                        usleep(5000);
                    }
                    robotClient.stopRotate();
                    robotClient.moveForward();
                    sleep(1);
                } else if (pos.x > 800 and pos.y < 180) {
                    robotClient.stopMove();
                    robotClient.rotateLeft();
                    while (robotClient.getRotation() > 270 + delta or robotClient.getRotation() < 45) {
                        usleep(5000);
                    }
                    robotClient.stopRotate();
                    robotClient.moveForward();
                    sleep(1);
                } else if (pos.x > 800 and pos.y > 800) {
                    robotClient.stopMove();
                    robotClient.rotateLeft();
                    while (robotClient.getRotation() > delta) {
                        usleep(5000);
                    }
                    robotClient.stopRotate();
                    robotClient.moveForward();
                    sleep(1);
                }
            }

            usleep(10000);
        } catch (exception& e) {
            fmt::print("Game ended\n");
        }
    }
}