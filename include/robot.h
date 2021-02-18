#pragma once

#include <string>

class Robot {
    private:
        std::string name;
    public:
        Robot();
        void move(float speed);
        void rotate(float speed);
        void stop(); //stops move and rotate
        void rotateWeapon(float speed);
        void shoot();
        const sf::Vector2f& getPosition();
        float getRotation();
};