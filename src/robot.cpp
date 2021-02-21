#include "robot.h"
#include "bullet.h"

#include <SFML/Graphics.hpp>
#include <math.h>
#include <optional>

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

std::optional<Bullet> Robot::shoot() {
    if (fireCountdown.getElapsedTime().asMilliseconds() > 500) {
        // bullets.push_back(Bullet{turret, 6});
        fireCountdown.restart();
        return Bullet{turret, 5};
    }
    return {};
}

void Robot::performActions() {
    move();
    rotate();
    rotateWeapon();
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

void Robot::drawRobot(sf::RenderWindow *window) {
    window->draw(robot);
    window->draw(turret);
}

sf::Vector2f Robot::getMoveVector() {
    float angle = robot.getRotation() * M_PI / 180;
    return sf::Vector2f{sin(angle) * speed, cos(angle) * -speed};
}