#pragma once

#include "bullet.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

class Robot {
    private:
        std::string name;
        float speed;
        
        const float robotRotion{1};
        const float turretRotation{1.5f};

        char moveSign{};
        char rotateSign{};
        char rotateTurretSign{};

        sf::Clock fireCountdown;

        sf::Texture robotTexture;
        sf::Texture turretTexture;
        sf::Sprite robot;
        sf::Sprite turret;
        
        sf::Vector2f movement;
        sf::Vector2f getMoveVector();

        void move();
        void rotate();
        void rotateWeapon();
    public:
        Robot(std::string name, float speed):
        name(name),
        speed(speed)
        {
                robotTexture.loadFromFile("../src/resources/body2.png");
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
        void stopRotate();
        
        void rotateWeaponLeft();
        void rotateWeaponRight();
        void stopRotateWeapon();

        std::optional<Bullet> shoot();
        void stopShoot();

        void performActions();
        void drawRobot(sf::RenderWindow*);

        sf::Vector2f getPosition();
        float getRotation();
        float getTurretRotation();
};