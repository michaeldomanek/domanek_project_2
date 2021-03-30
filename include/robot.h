#pragma once

class Robot;
class Bullet;

#include "bullet.h"
#include "window.h"
#include "robotConfiguration.h"
#include "robotProperties.h"
#include "robotStartConfiguration.h"

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
        Window& window;
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
        Robot(RobotProperties properties, RobotConfiguration config);
        
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