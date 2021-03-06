#pragma once

#include <SFML/Graphics.hpp>

class RobotStartConfiguration {
    private:
        sf::Vector2f position;
        float rotation;

    public:
        RobotStartConfiguration(sf::Vector2f position, float rotation):
            position(position),
            rotation(rotation)
        {}

        sf::Vector2f getPosition() {
            return position;
        }

        float getRotation() {
            return rotation;
        }
};