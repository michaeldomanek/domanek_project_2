#pragma once

#include "bullet.h"
#include "robot.h"

#include <vector>

class Window {
    private:
        static std::vector<Bullet> bullets;
        static std::vector<Robot*> robots;

        sf::RenderWindow window;
        sf::FloatRect wall;

        void showAllBullets();
        void showRobots();
    public:
        Window(unsigned int width):
        window(sf::VideoMode(width, width), "Robotgame"),
        wall(0, 0, (float)width, (float)width)
        {
            window.setFramerateLimit(120);

            sf::Image icon;
            icon.loadFromFile("../src/resources/icon.png");
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }

        static void addBullet(sf::Sprite turret, float speed);
        static void addRobot(Robot*);
        void moveAllBullets();
        bool isOpen();
        void clear();
        void handleEvent();
        void draw();
        void display();
};