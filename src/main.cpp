#include "bullet.h"
#include "robot.h"
#include "window.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const unsigned int width{1000};

int main() {
    Robot robo{"robot1", 2.0f};
    Robot robo2{"robot1", 2.0f};
    Window window{950};
    window.addRobot(&robo);
    window.addRobot(&robo2);

    while (window.isOpen()) {
        window.clear();

        robo.stopMove();
        robo2.stopMove();
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

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
            robo2.moveForward();
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
            robo2.moveBackward();
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
        robo2.performActions();
        window.moveAllBullets();
        window.handleEvent();
        window.draw();

        // for(auto &bullet: bullets) {
        //     bullet.move();
        // }

        // for (vector<Bullet>::iterator bullet = bullets.begin(); bullets.size() > 0 && bullet != bullets.end(); ++bullet) {            
        //     sf::FloatRect bulletRect {bullet->getSprite().getGlobalBounds()};
        //     if(!bulletRect.intersects(wall)){        
        //         bullets.erase(bullet);
        //     }
        // }

        // for(auto &bullet: bullets) {
        //     window.draw(bullet.getSprite());            
        // }
     
        window.display();
    }
}
