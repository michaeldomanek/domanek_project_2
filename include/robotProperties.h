#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class RobotProperties {
    private:
        const std::string name;
        const sf::Color color;
        const sf::Vector2f position;

    public:
        RobotProperties(std::string name, sf::Color color, sf::Vector2f position):
        name(name),
        color(color),
        position(position)
        {}

        std::string getName() {
            return name;
        }

        sf::Color getColor() {
            return color;
        }

        sf::Vector2f getPosition() {
            return position;
        }
};