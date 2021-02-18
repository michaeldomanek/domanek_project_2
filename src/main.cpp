#include "../include/bullet.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <utility>

using namespace std;

const unsigned int width{1000};
const unsigned int robotWidth{38};

int main() {
    vector<Bullet> bullets;

    sf::RenderWindow window(sf::VideoMode(width, width), "Robotgame");
    window.setFramerateLimit(60);

    sf::Image icon;
    icon.loadFromFile("../src/resources/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture robotTexture;
    robotTexture.loadFromFile("../src/resources/body2.png");

    sf::Texture turretTexture;
    turretTexture.loadFromFile("../src/resources/turret.png");

    sf::Sprite robot{robotTexture};
    sf::Sprite turret{turretTexture};
    
    robot.setOrigin(robot.getLocalBounds().width / 2, robot.getLocalBounds().height / 2);
    turret.setOrigin(turret.getLocalBounds().width / 2, turret.getLocalBounds().height / 2);

    robot.setPosition(200, 200);
    turret.setPosition(200, 200);

    robot.setScale(1.5, 1.5);
    turret.setScale(1.5, 1.5);

    vector<sf::FloatRect> walls;
    walls.push_back(sf::FloatRect(0, 0, width, 1));
    walls.push_back(sf::FloatRect(0, 0, 1, width));
    walls.push_back(sf::FloatRect(0, width, width, -1));
    walls.push_back(sf::FloatRect(width, 0, -1, width));


    while (window.isOpen()) {
        window.clear(sf::Color::Black);

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
            robot.setRotation(robot.getRotation() - 1);
            turret.setRotation(turret.getRotation() - 1);
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
            robot.setRotation(robot.getRotation() + 1);
            turret.setRotation(turret.getRotation() + 1);
        }

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
            float angle{robot.getRotation() * (float)M_PI / 180.0f};
            robot.move(sin(angle) * -2, cos(angle) * 2);
            turret.move(sin(angle) * -2, cos(angle) * 2);
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
            float angle{robot.getRotation() * (float)M_PI / 180.0f};
            robot.move(sin(angle) * 2, cos(angle) * -2);
            turret.move(sin(angle) * 2, cos(angle) * -2);
        }

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::Q )) {
            turret.setRotation(turret.getRotation() - 1.5);
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::E )) {
            turret.setRotation(turret.getRotation() + 1.5);
        }

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space )) {
            if(bullets.size() < 100) {
                bullets.push_back(Bullet{turret, 3});
            }   
        }

        for(auto &bullet: bullets) {
            bullet.move();
        }

        for (vector<Bullet>::iterator bullet = bullets.begin(); bullets.size() > 0 && bullet != bullets.end(); ++bullet) {            
            sf::FloatRect bulletRect {bullet->getSprite().getGlobalBounds()};
            for(auto const &wall: walls) {
                if(bulletRect.intersects(wall)){            
                    bullets.erase(bullet);
                    break;
                }
            }
        }
        

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto &bullet: bullets) {
            window.draw(bullet.getSprite());
            cout << bullets.size() << endl;
        }

        window.draw(robot);
        window.draw(turret);        
        window.display();
    }
}
