#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const unsigned int width = 700;
const unsigned int height = 700;
const unsigned int robotWidth = 38;

int main() {

    sf::RenderWindow window(sf::VideoMode(width, height), "Robotgame");
    window.setFramerateLimit(60);

    sf::Image icon;
    icon.loadFromFile("../src/resources/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture robotTexture;
    robotTexture.loadFromFile("../src/resources/body2.png");

    sf::Texture turretTexture;
    turretTexture.loadFromFile("../src/resources/turret.png");

    sf::Sprite robot;
    sf::Sprite turret;
    robot.setTexture(robotTexture);
    turret.setTexture(turretTexture);
    
    robot.setOrigin(robot.getLocalBounds().width / 2, robot.getLocalBounds().height / 2);
    turret.setOrigin(turret.getLocalBounds().width / 2, turret.getLocalBounds().height / 2);

    robot.setPosition(200, 200);
    turret.setPosition(200, 200);


    while (window.isOpen()) {
        window.clear(sf::Color::White);

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
            robot.setRotation(robot.getRotation() - 1);
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
            robot.setRotation(robot.getRotation() + 1);
        }

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
            float angle = robot.getRotation() * M_PI / 180;
            robot.move(sin(angle) * -2, cos(angle) * 2);
            turret.move(sin(angle) * -2, cos(angle) * 2);
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
            float angle = robot.getRotation() * M_PI / 180;
            robot.move(sin(angle) * 2, cos(angle) * -2);
            turret.move(sin(angle) * 2, cos(angle) * -2);
        }

        if (sf::Keyboard::isKeyPressed( sf::Keyboard::Q )) {
            turret.setRotation(turret.getRotation() - 1.5);
        } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::E )) {
            turret.setRotation(turret.getRotation() + 1.5);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(robot);
        window.draw(turret);
        window.display();
    }

    return 0;
}
