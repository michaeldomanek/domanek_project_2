#include "robot.h"
#include "bullet.h"
#include "window.h"

#include <SFML/Graphics.hpp>
#include <math.h>

void Robot::move() {
    if (moveSign) {
        robot.move(movement.x * moveSign, movement.y * moveSign);
        turret.move(movement.x * moveSign, movement.y * moveSign);
    }
}

void Robot::moveForward() {
    moveSign = 1;
}

void Robot::moveBackward() {
    moveSign = -1;
}

void Robot::stopMove() {
    moveSign = false;
}

void Robot::rotate() {
    if (rotateSign) {
        robot.setRotation(robot.getRotation() + (robotRotion * rotateSign));
        turret.setRotation(turret.getRotation() + (robotRotion * rotateSign));

        movement = getMoveVector();
    }
}

void Robot::rotateLeft() {
    rotateSign = -1;
}

void Robot::rotateRight() {
    rotateSign = 1;
}

void Robot::stopRotate() {
    rotateSign = false;
}

void Robot::rotateWeapon() {
    if (rotateTurretSign) {
        turret.setRotation(turret.getRotation() + (turretRotation * rotateTurretSign));
    }
}

void Robot::rotateWeaponLeft() {
    rotateTurretSign = -1;
}

void Robot::rotateWeaponRight() {
    rotateTurretSign = 1;
}

void Robot::stopRotateWeapon() {
    rotateTurretSign = false;
}

void Robot::shoot() {
    if (wantToShoot && fireCountdown.getElapsedTime().asMilliseconds() > 500) {
        Window::addBullet(turret, 5);
        fireCountdown.restart();
    }
}

void Robot::startShooting() {
    wantToShoot = true;
}

void Robot::stopShooting() {
    wantToShoot = false;
}

void Robot::performActions() {
    move();
    rotate();
    rotateWeapon();
    shoot();
}

sf::Vector2f Robot::getPosition() {
    return robot.getPosition();
}

float Robot::getRotation() {
    return robot.getRotation();
}

float Robot::getTurretRotation() {
    return turret.getRotation();
}

const sf::Sprite& Robot::getRobotSprite() {
    return robot;
}

const sf::Sprite& Robot::getTurretSprite() {
    return turret;
}

sf::Vector2f Robot::getMoveVector() {
    float angle = robot.getRotation() * M_PI / 180;
    return sf::Vector2f{sin(angle) * speed, cos(angle) * -speed};
}