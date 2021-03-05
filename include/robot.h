#pragma once

class Robot;
class Bullet;

#include "bullet.h"
#include "window.h"
#include "robotConfiguration.h"
#include "robotProperties.h"

#include <SFML/Graphics.hpp>
#include "spdlog/fmt/fmt.h"
#include <algorithm>

class Robot {
    private:
        bool dead{};
        float health;

        RobotProperties properties;
        RobotConfiguration config;

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

        sf::Font font;
        sf::Text nameText;
        sf::Text healthText;

        sf::Vector2f movement;
        sf::Vector2f getMoveVector();
        void initialiseText(sf::Text&, std::string);

        void move();
        void rotate();
        void rotateWeapon();
        void shoot();

    public:
        Robot(RobotProperties properties, RobotConfiguration config):
        health(config.getHealth()),
        properties(properties),
        config(config)
        {
            robotTexture.loadFromFile("../src/resources/body-grey.png");
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
            
            sf::Vector2f pos = properties.getPosition();
            pos.x = std::min(std::max(robotBorder.left, pos.x), robotBorder.width);
            pos.y = std::min(std::max(robotBorder.top, pos.y), robotBorder.height);
            robot.setPosition(pos);
            turret.setPosition(pos);

            font.loadFromFile("../src/resources/ARIAL.TTF");
            initialiseText(nameText, properties.getName());
            initialiseText(healthText, fmt::format("{:.1f}", health));

            nameText.setPosition(pos.x, pos.y + robot.getLocalBounds().width * 1.5);
            healthText.setPosition(pos.x, pos.y - robot.getLocalBounds().width * 1.5);

            turret.setColor(properties.getColor());
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

        void setRotation(float rotation);

        sf::Vector2f getPosition();
        float getRotation();
        float getTurretRotation();
        const sf::Sprite& getRobotSprite();
        const sf::Sprite& getTurretSprite();
        const sf::FloatRect getGlobalBounds();
        bool isDead();
        std::string getName();
        sf::Text getNameText();
        sf::Text getHealthText();
};