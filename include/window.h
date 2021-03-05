#pragma once

#include "bullet.h"
#include "robot.h"
#include "bulletConfiguration.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

class Window {
    private:
        std::vector<Bullet> bullets;
        std::vector<Robot*> robots;
        std::vector<sf::Sprite> deadBodies;

        BulletConfiguration config;

        sf::FloatRect border;
        sf::RenderWindow window;

        sf::Vector2f startPositions[4];

        sf::Texture explosionTexture;
        sf::Sprite explosion;

        void showAllDeadBodies();
        void showAllBullets();
        void showRobots();

        Window(const unsigned int& width, const BulletConfiguration& config):
            config(config),
            border(0, 0, (float)width, (float)width),
            window(sf::VideoMode(width, width), "Robotgame"),
            startPositions({{40, 40}, {40, width - 40.0f}, {width - 40.0f, 40}, {width - 40.0f, width - 40.0f}})
            {
                window.setFramerateLimit(120);

                sf::Image icon;
                icon.loadFromFile("../src/resources/icon.png");
                window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

                explosionTexture.loadFromFile("../src/resources/explosion.png");

                srand(unsigned(time(NULL)));
                std::random_shuffle(std::begin(startPositions), std::end(startPositions));
            }

    public:
        void addBullet(sf::Sprite turret, Robot* attacker);
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

        sf::Vector2f getAvailablePosition();

        static Window& getInstance(const unsigned int& width=0, const BulletConfiguration& config={0, 0, 0}) {
            static Window instance(width, config);
            return instance;
        }

        Window(Window const&)          = delete;
        void operator=(Window const&)  = delete;
};