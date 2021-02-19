#include "robot.h"

#include <SFML/Graphics.hpp>
#include <math.h>

void Robot::move() {
    robot.move(movement.x, movement.y);
    turret.move(movement.x, movement.y);
}

void Robot::rotate(short sign) {
    robot.setRotation(robot.getRotation() + (robotRotion * sign));
    turret.setRotation(turret.getRotation() + (robotRotion * sign));

    movement = getMoveVector();
}

void Robot::stop() {
    movement = sf::Vector2f{0, 0};
}

void Robot::rotateWeapon(short sign) {
    turret.setRotation(turret.getRotation() + (turretRotation * sign));
}

void Robot::rotateWeaponLeft() {
    rotateWeapon(-1);
}

void Robot::rotateWeaponRight() {
    rotateWeapon(1);
}

void Robot::shoot() {

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

sf::Vector2f Robot::getMoveVector() {
    float angle = robot.getRotation() * M_PI / 180;
    return sf::Vector2f{sin(angle) * speed, cos(angle) * -speed};
}