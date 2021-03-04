#include "bullet.h"
#include "window.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include "spdlog/fmt/fmt.h"

#include <string>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

void Robot::move() {
    if (moveSign) {
        robot.move(movement.x * moveSign, movement.y * moveSign);
        turret.move(movement.x * moveSign, movement.y * moveSign);
        nameText.move(movement.x * moveSign, movement.y * moveSign);
        healthText.move(movement.x * moveSign, movement.y * moveSign);

        sf::FloatRect robotBounds{robot.getGlobalBounds()};

        for(Robot* robo: window.getRobots()) {
            if (this != robo && robotBounds.intersects(robo->getGlobalBounds())) {
                robot.move(movement.x * -moveSign, movement.y * -moveSign);
                turret.move(movement.x * -moveSign, movement.y * -moveSign);
                nameText.move(movement.x * -moveSign, movement.y * -moveSign);
                healthText.move(movement.x * -moveSign, movement.y * -moveSign);
            }
        }

        if (robotBounds.intersects(robotBorder)) {
            float posX{min(max(robotBorder.left, robot.getPosition().x), robotBorder.width)};
            float posY{min(max(robotBorder.top, robot.getPosition().y), robotBorder.height)};
            robot.setPosition(posX, posY);
            turret.setPosition(posX, posY);
            nameText.setPosition(posX, posY + robot.getLocalBounds().width * 1.5);
            healthText.setPosition(posX, posY - robot.getLocalBounds().width * 1.5);
        }
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
    const float robotRotation{config.getRobotRotation()};
    robot.setRotation(robot.getRotation() + (robotRotation * rotateSign));
    turret.setRotation(turret.getRotation() + (robotRotation * rotateSign));

    if (rotateSign) {
        for(Robot* robo: window.getRobots()) {
            if (this != robo && robot.getGlobalBounds().intersects(robo->getGlobalBounds())) {
                robot.setRotation(robot.getRotation() + (robotRotation * -rotateSign));
                turret.setRotation(turret.getRotation() + (robotRotation * -rotateSign));
                break;
            }
        }

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
        turret.setRotation(turret.getRotation() + (config.getTurretRotation() * rotateTurretSign));
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
        window.addBullet(turret, this);
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

void Robot::substractHealth(float damage) {
    health -= damage;
    healthText.setString(fmt::format("{:.1f}", health));

    if (health <= 0) {
        window.removeRobot(this);
        dead = true;
    }
}

void Robot::setRotation(float rotation)  {
    robot.setRotation(rotation);
    turret.setRotation(rotation);
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

const sf::FloatRect Robot::getGlobalBounds() {
    return robot.getGlobalBounds();
}

bool Robot::isDead() {
    return dead;
}

string Robot::getName() {
    return properties.getName();
}

sf::Text Robot::getNameText() {
    return nameText;
}

sf::Text Robot::getHealthText() {
    return healthText;
}

sf::Vector2f Robot::getMoveVector() {
    const float angle{robot.getRotation() * (float)M_PI / 180.0f};
    const float speed{config.getSpeed()};
    return sf::Vector2f{sin(angle) * speed, cos(angle) * -speed};
}

void Robot::initialiseText(sf::Text& text, string input) {
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top  + textRect.height / 2.0f);
    sf::Vector2f pos{robot.getPosition()};
    pos.y = pos.y + robot.getLocalBounds().width * 1.5;
    text.setPosition(pos);
}