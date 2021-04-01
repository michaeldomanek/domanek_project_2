#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class RobotInformation {
    private:
        const float id;
        const std::string name;
        const sf::Vector2f pos;
        const float rotation;
        const float turretRotation;

    public:
        RobotInformation(const int& id, const std::string& name, const sf::Vector2f& pos, 
                         const float& rotation, const float& turretRotation):
            id(id),
            name(name),
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

        std::string getName() {
            return name;
        }

        int getID() {
            return id;
        }
};