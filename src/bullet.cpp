#include "../include/bullet.h"

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace std;

sf::Sprite Bullet::getSprite() {
    return sprite;
}

float Bullet::getSpeed() {
    return speed;
}

sf::Vector2f Bullet::getMoveVector(float speed) {
    float angle = sprite.getRotation() * M_PI / 180;
    return sf::Vector2f{sin(angle) * speed, cos(angle) * -speed};
}

void Bullet::move() {
    sprite.move(movement.x, movement.y);
}