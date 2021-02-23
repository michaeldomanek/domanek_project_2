#pragma once

class Robot;
class Bullet;
class Window;

#include "bullet.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
    private:
        static std::vector<Bullet> bullets;
        static std::vector<Robot*> robots;

        unsigned int width = 950;
        sf::FloatRect border{0, 0, (float)width, (float)width};
        sf::RenderWindow window{sf::VideoMode(width, width), "Robotgame"};

        void showAllBullets();
        void showRobots();
    
        Window()
        {
            window.setFramerateLimit(120);

            sf::Image icon;
            icon.loadFromFile("../src/resources/icon.png");
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }
    public:
        static void addBullet(sf::Sprite turret, Robot* attacker, float speed, float damage);
        static void addRobot(Robot*);
        sf::FloatRect getBorder();
        void moveAllBullets();
        void bulletHit();
        bool isOpen();
        void clear();
        void handleEvent();
        void draw();
        void display();

        static Window& getInstance()
        {
            static Window instance;
            return instance;
        }

        Window(Window const&)          = delete;
        void operator=(Window const&)  = delete;
};