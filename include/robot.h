#pragma once

class Robot;
class Bullet;
class Window;

#include "bullet.h"
#include "window.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include <iostream>

class Robot {
    private:
        std::string name;
        float speed{2.0f};
        float health{10.0f};
        bool dead{};
        
        const float robotRotion{1};
        const float turretRotation{1.5f};

        char moveSign{};
        char rotateSign{};
        char rotateTurretSign{};
        bool wantToShoot{};

        sf::Clock fireCountdown;
        Window& window{Window::getInstance()};
        sf::FloatRect border{window.getBorder()};
        sf::FloatRect robotBorder;

        sf::Texture robotTexture;
        sf::Texture turretTexture;
        sf::Sprite robot;
        sf::Sprite turret;
        
        sf::Vector2f movement;
        sf::Vector2f getMoveVector();

        void move();
        void rotate();
        void rotateWeapon();
        void shoot();
    public:
        Robot(std::string name, float posX, float posY):
        name(name)
        {
            robotTexture.loadFromFile("../src/resources/body2.png");
            turretTexture.loadFromFile("../src/resources/turret.png");

            robot.setTexture(robotTexture);
            turret.setTexture(turretTexture);
            
            robot.setOrigin(robot.getLocalBounds().width / 2, robot.getLocalBounds().height / 2);
            turret.setOrigin(turret.getLocalBounds().width / 2, turret.getLocalBounds().height / 2);

            robot.setScale(1.5, 1.5);
            turret.setScale(1.5, 1.5);

            movement = getMoveVector();
            robotBorder = {robot.getLocalBounds().width, 
                            robot.getLocalBounds().height, 
                            border.width - robot.getLocalBounds().width, 
                            border.height - robot.getLocalBounds().height};

            posX = std::min(std::max(robotBorder.left, posX), robotBorder.width);
            posY = std::min(std::max(robotBorder.top, posY), robotBorder.height);
            robot.setPosition(posX, posY);
            turret.setPosition(posX, posY);
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

        void startShooting();
        void stopShooting();

        void performActions();

        void substractHealth(float damage);

        sf::Vector2f getPosition();
        float getRotation();
        float getTurretRotation();
        const sf::Sprite& getRobotSprite();
        const sf::Sprite& getTurretSprite();
        const sf::FloatRect getGlobalBounds();
        bool isDead();
        std::string getName();
};