#pragma once

#include "bullet.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
    private:
        std::vector<Bullet> bullets;
        std::vector<Robot*> robots;

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
        void addBullet(sf::Sprite turret, Robot* attacker, float speed, float damage);
        void addRobot(Robot*);
        void removeRobot(Robot *robot);

        sf::FloatRect getBorder();
        std::vector<Robot*> getRobots();
        
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