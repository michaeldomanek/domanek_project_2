#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class RobotProperties {
    private:
        const std::string name;
        const sf::Color color;

    public:
        RobotProperties(std::string name, sf::Color color):
        name(name),
        color(color)
        {}

        std::string getName() {
            return name;
        }

        sf::Color getColor() {
            return color;
        }
};