#pragma once

#include "robot.h"
#include "bulletConfiguration.h"

#include <SFML/Graphics.hpp>

class Bullet {
    private:
        sf::Sprite sprite;
        float speed;
        float damage;
        Robot* attacker;
        sf::Vector2f movement;
        sf::Vector2f getMoveVector(float speed);
    public:
        Bullet(sf::Sprite turret, Robot* attacker, BulletConfiguration config);
        
        void move();
        sf::Sprite getSprite();
        Robot* getAttacker();
        float getDamage();
};