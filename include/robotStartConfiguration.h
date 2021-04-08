#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

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

        static std::vector<RobotStartConfiguration> getStartConfigs(unsigned int width) {
            std::vector<RobotStartConfiguration> startConfigs{
                {{40           , 40           }, 125}, 
                {{40           , width - 40.0f},  35},
                {{width - 40.0f, 40           }, 215},
                {{width - 40.0f, width - 40.0f}, 305}
            };

            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(std::begin(startConfigs), std::end(startConfigs), std::default_random_engine(seed));
            return startConfigs;
        }
};