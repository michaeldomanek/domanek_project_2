#include "bullet.h"
#include "window.h"
#include "robot.h"
#include "robotConfiguration.h"
#include "robotProperties.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;

int main() {
    Window& window{Window::getInstance(950, 5, 19)};

    RobotConfiguration config{2.0f, 100.0f, 1.0f, 1.5f};
    RobotProperties properties{"Keyboard Controll", sf::Color::Blue, sf::Vector2f{0, 0}};
    RobotProperties properties2{"Random Controll", sf::Color::Red, sf::Vector2f{250, 250}};
    RobotProperties properties3{"Change direction on wall hit", sf::Color::Green, sf::Vector2f{700, 700}};

    Robot robo{properties, config};
    Robot robo2{properties2, config};
    Robot robo3{properties3, config};
    
    window.addRobot(&robo);
    window.addRobot(&robo2);
    window.addRobot(&robo3);

    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};

    robo.setRotation(135);

    robo2.startShooting();

    robo3.rotateWeaponRight();
    robo3.startShooting();
    robo3.moveForward();
    robo3.setRotation(dis(gen) * 2);
    

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
