#include "bullet.h"
#include "robot.h"

#include <math.h>
#include <SFML/Graphics.hpp>

using namespace std;

Bullet::Bullet(sf::Sprite turret, Robot* attacker, BulletConfiguration config): 
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
}

sf::Vector2f Bullet::getMoveVector(float speed) {
    float angle = sprite.getRotation() * M_PI / 180;
    return sf::Vector2f{sin(angle) * speed, cos(angle) * -speed};
}

void Bullet::move() {
    sprite.move(movement.x, movement.y);
}

sf::Sprite Bullet::getSprite() {
    return sprite;
}

Robot* Bullet::getAttacker() {
    return attacker;
}

float Bullet::getDamage() {
    return damage;
}