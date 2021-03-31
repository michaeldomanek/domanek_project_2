#pragma once

#include <SFML/Graphics.hpp>


class RobotOrientation {
    private:
        const sf::Vector2f pos;
        const float rotation;
        const float turretRotation;

    public:
        RobotOrientation(sf::Vector2f pos, float rotation, float turretRotation):
        pos(pos),
        rotation(rotation),
        turretRotation(turretRotation)
        {}

        sf::Vector2f getPosition() {
            return pos;
        }

        float getRotation() {
            return rotation;
        }

        float getTurretRotation() {
            return turretRotation;
        }
};