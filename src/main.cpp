#include "bullet.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const unsigned int width{1000};
const unsigned int robotWidth{38};

int main() {
    vector<Bullet> bullets;

    sf::RenderWindow window(sf::VideoMode(width, width), "Robotgame");
    window.setFramerateLimit(120);

    sf::Image icon;
    icon.loadFromFile("../src/resources/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::FloatRect wall{0, 0, width, width};

    Robot robo{"robot1", 2.5f};

    while (window.isOpen()) {
        window.clear(sf::Color::Black);

        robo.stopMove();
        robo.stopRotate();
        robo.stopRotateWeapon();

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
            if(auto bullet = robo.shoot()) {
                bullets.push_back(bullet.value());
            }
        }

        robo.performActions();
        robo.drawRobot(&window);

        for(auto &bullet: bullets) {
            bullet.move();
        }

        for (vector<Bullet>::iterator bullet = bullets.begin(); bullets.size() > 0 && bullet != bullets.end(); ++bullet) {            
            sf::FloatRect bulletRect {bullet->getSprite().getGlobalBounds()};
            if(!bulletRect.intersects(wall)){        
                bullets.erase(bullet);
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto &bullet: bullets) {
            window.draw(bullet.getSprite());            
        }
     
        window.display();
    }
}
