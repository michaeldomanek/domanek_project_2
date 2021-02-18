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

void Bullet::move_(float speedX, float speedY) {
    float angle = sprite.getRotation() * M_PI / 180;
    sprite.move(sin(angle) * speedX, cos(angle) * -speedY);
}

void Bullet::move() {
    move_(speed, speed);
}