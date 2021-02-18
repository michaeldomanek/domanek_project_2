#pragma once

#include <SFML/Graphics.hpp>

class Bullet {
    private:
        sf::Sprite sprite;
        float speed;
        float damage;
        void move_(float, float);
    public:
        Bullet(sf::Sprite turret, float speed): 
            speed(speed) 
            {
                sf::Texture tex; 
                tex.create(2, 2);

                sprite.setTexture(tex);
                sprite.setPosition(turret.getPosition());
                sprite.setRotation(turret.getRotation());
                sprite.setColor(sf::Color::White);
                sprite.setOrigin(1, 1);
                sprite.setScale(1.5, 1.5);
                move_(25 * 1.5, 25 * 1.5);
            };
        sf::Sprite getSprite();
        float getSpeed();
        void move();
};