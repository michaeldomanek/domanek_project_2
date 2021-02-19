#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Robot {
    private:
        std::string name;
        float speed;
        
        const float robotRotion{1};
        const float turretRotation{1.5f};

        sf::Clock fireCountdown;
        sf::Sprite robot;
        sf::Sprite turret;
        sf::Vector2f movement;
        sf::Vector2f getMoveVector();
        void move(short sign);
        void rotate(short sign);
        void rotateWeapon(short sign);
    public:
        Robot(std::string name, float speed):
        name(name),
        speed(speed)
        {
                sf::Texture robotTexture;
                robotTexture.loadFromFile("../src/resources/body2.png");

                sf::Texture turretTexture;
                turretTexture.loadFromFile("../src/resources/turret.png");

                robot.setTexture(robotTexture);
                turret.setTexture(turretTexture);
                
                robot.setOrigin(robot.getLocalBounds().width / 2, robot.getLocalBounds().height / 2);
                turret.setOrigin(turret.getLocalBounds().width / 2, turret.getLocalBounds().height / 2);

                robot.setPosition(200, 200);
                turret.setPosition(200, 200);

                robot.setScale(1.5, 1.5);
                turret.setScale(1.5, 1.5);
        }
        
        void moveForward();
        void moveBackward();
        void stopMove();

        void rotateLeft();
        void rotateRight();
        vpod stopRotate();
        
        void rotateWeaponLeft();
        void rotateWeaponRight();
        void stopRotate();

        void shoot();
        void stopShoot();

        sf::Vector2f getPosition();
        float getRotation();
        float getTurretRotation();
};