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
        Bullet(sf::Sprite turret, Robot* attacker, BulletConfiguration config): 
            speed(config.getSpeed()),
            damage(config.getDamage()),
            attacker(attacker)
        {
            const unsigned int size{config.getSize()};

            sf::Texture tex; 
            tex.create(size, size);

            sprite.setTexture(tex);
            sprite.setPosition(turret.getPosition());
            sprite.setRotation(turret.getRotation());
            sprite.setColor(sf::Color::White);
            sprite.setOrigin(size / 2, size / 2);
            sprite.setScale(1.5, 1.5);

            //move to firepoint
            movement = getMoveVector(speed);
            sprite.move(25 * 1.5 * movement.x / speed, 25 * 1.5 * movement.y / speed);
        };
        
        void move();

        sf::Sprite getSprite();
        Robot* getAttacker();
        float getDamage();
};