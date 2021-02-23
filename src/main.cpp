#include "bullet.h"
#include "window.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main() {
    Robot robo{"robot1", 0, 0};
    Robot robo2{"robot2", 250, 250};
    Window& window{Window::getInstance()};
    window.addRobot(&robo);
    window.addRobot(&robo2);

    while (window.isOpen()) {
        window.clear();

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
        
        window.moveAllBullets();
        window.bulletHit();

        window.handleEvent();
        window.draw();     
        window.display();
    }
}
