#pragma once

#include "bullet.h"
#include "robot.h"
#include "bulletConfiguration.h"
#include "robotStartConfiguration.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
    private:
        std::vector<Bullet> bullets;
        std::vector<Robot*> robots;
        std::vector<sf::Sprite> deadBodies;

        unsigned int maxPlayers;
        BulletConfiguration config;

        sf::FloatRect border;
        sf::RenderWindow window;

        std::vector<RobotStartConfiguration> startConfigs;

        sf::Texture explosionTexture;
        sf::Sprite explosion;

        void showAllDeadBodies();
        void showAllBullets();
        void showRobots();

        Window(const unsigned int& width, const unsigned int& maxPlayers, const BulletConfiguration& config):
            maxPlayers(maxPlayers),
            config(config),
            border(0, 0, (float)width, (float)width),
            window(sf::VideoMode(width, width), "Robotgame"),
            startConfigs(RobotStartConfiguration::getStartConfigs(width))
        {
            window.setFramerateLimit(120);

            sf::Image icon;
            icon.loadFromFile("../src/resources/icon.png");
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

            explosionTexture.loadFromFile("../src/resources/explosion.png");
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

        RobotStartConfiguration getAvailablePosition();

        static Window& getInstance(const unsigned int& width=0, const unsigned int& maxPlayers=0, const BulletConfiguration& config={0, 0, 0}) {
            static Window instance(width, maxPlayers, config);
            return instance;
        }

        Window(Window const&)          = delete;
        void operator=(Window const&)  = delete;
};