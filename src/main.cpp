#include "bullet.h"
#include "window.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;

int main() {
    Robot robo{"robot1", 0, 0};
    Robot robo2{"robot2", 250, 250};
    Robot robo3{"robot3", 700, 700};
    Window& window{Window::getInstance()};
    window.addRobot(&robo);
    window.addRobot(&robo2);
    window.addRobot(&robo3);

    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};

    robo2.startShooting();

    robo3.rotateWeaponRight();
    robo3.startShooting();
    robo3.moveForward();
    robo3.rotateLeft();
    for(int i = 0; i < dis(gen) * 2; i++) {
        robo3.performActions();
    }
    robo3.stopRotate();

    while (window.isOpen()) {
        window.clear();

        // Robot 1

        if (!robo.isDead()) {

            robo.stopMove();
            robo.stopRotate();
            robo.stopRotateWeapon();
            robo.stopShooting();

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
                robo.rotateLeft();
            } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
                robo.rotateRight();
            }

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
                robo.moveForward();
            } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
                robo.moveBackward();
            }

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::Q )) {
                robo.rotateWeaponLeft();
            } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::E )) {
                robo.rotateWeaponRight();
            }

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space )) {
                robo.startShooting();
            }

            robo.performActions();
        }

        // Robot 2

        if (!robo2.isDead()) {
            double rand{dis(gen)};

            if (rand <= 2) {
                robo2.rotateLeft();
            } else if (rand <= 7) {
                robo2.rotateRight();
            } else {
                robo2.stopRotate();
            }

            double rand2{dis(gen)};

            if (rand2 <= 6) {
                robo2.moveForward();
            } else if (rand2 <= 7) {
                robo2.moveBackward();
            } else {
                robo2.stopMove();
            }

            robo2.performActions();
        }

        // Robot 3

        if (!robo3.isDead()) {
            if (robo3.getPosition().x < 100) {
                if(robo3.getRotation() < 270) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else if (robo3.getPosition().y < 100) {
                if(robo3.getRotation() > 180) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else if (robo3.getPosition().x > 850) {
                if(robo3.getRotation() < 90) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else if (robo3.getPosition().y > 850) {
                if(robo3.getRotation() < 180) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else {
                robo3.stopRotate();
            }

            robo3.performActions();
        }

        window.moveAllBullets();
        window.bulletHit();

        window.handleEvent();
        window.draw();     
        window.display();
    }
}
