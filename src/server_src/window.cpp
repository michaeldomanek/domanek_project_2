#include "bullet.h"
#include "window.h"
#include "robot.h"
#include "robotStartConfiguration.h"

#include <SFML/Graphics.hpp>
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/bundled/color.h"
#include "spdlog/spdlog.h"

#include <vector>
#include <algorithm>

using namespace std;

Window::Window(const unsigned int& width, const unsigned int& maxPlayers, const BulletConfiguration& config):
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

void Window::addBullet(sf::Sprite turret, Robot* attacker) {
    Bullet bullet{turret, attacker, config};
    bullets.push_back(bullet);
}

void Window::addRobot(Robot *robot) {
    robots.push_back(robot);

    //todo check for maxPlayers

    string name{robot->getName()};
    size_t players{robots.size()};
    string message{"Robot: {0} started playing! [{1} / {2}] player{3}"};

    fmt::print(message, fmt::format(fmt::fg(fmt::color::royal_blue), name), players, maxPlayers, "\n");

    spdlog::info(message, name, players, maxPlayers,"");
}

void Window::removeRobot(Robot *robot) {
    if (robots.size() > 1) {
        sf::Sprite deadRobot{robot->getRobotSprite()};
        deadRobot.setTexture(explosionTexture);

        robots.erase(remove(robots.begin(), robots.end(), robot), robots.end());
        deadBodies.push_back(deadRobot);

        string name{robot->getName()};
        size_t players{robots.size()};
        string message_dead{"Robot: {0} is dead! [{1} / {2}] player left{3}"};

        fmt::print(message_dead, fmt::format(fmt::fg(fmt::color::orange), name), players, maxPlayers, "\n");

        spdlog::info(message_dead, name, players, maxPlayers, "");
    
        if (robots.size() == 1) {
            string message_gameover{"Robot: {0} won!{1}"};
            string winner_name{robots.back()->getName()};
            
            fmt::print(fmt::fg(fmt::color::crimson), "===========GAME OVER!==============\n");
            fmt::print(message_gameover, fmt::format(fmt::fg(fmt::color::lime), winner_name), "\n");

            spdlog::info(message_gameover, winner_name, "");

            window.close();
        }
    }
}

vector<Robot*> Window::getRobots() {
    return robots;
}

sf::FloatRect Window::getBorder() {
    return border;
}

void Window::moveAllBullets() {
    for(Bullet& bullet: bullets) {
        bullet.move();
    }
}

void Window::showAllBullets() {
    for(Bullet& bullet: bullets) {
        window.draw(bullet.getSprite());
    }
}

bool Window::isOpen() {
    return window.isOpen();
}

void Window::clear() {
    window.clear(sf::Color{133, 125, 122}); //grey
}

void Window::bulletHit() {
    if (bullets.size() > 0) {
        for (vector<Bullet>::iterator bullet = bullets.begin(); bullets.size() > 0 && bullet != bullets.end();) {
            bool increamentBullet{true};
            sf::FloatRect bulletRect {bullet->getSprite().getGlobalBounds()};

            if(!bulletRect.intersects(border)){        
                bullets.erase(bullet);
            } else {
                for(Robot* robot: robots) {
                    if(robot != bullet->getAttacker() && bulletRect.intersects(robot->getRobotSprite().getGlobalBounds())) {
                        robot->substractHealth(bullet->getDamage());
                        bullets.erase(bullet);
                        increamentBullet = false;
                        break;
                    }
                }

                if (increamentBullet) {
                    ++bullet;
                }
            }
        }
    }
}

void Window::handleEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Window::showAllDeadBodies() {
    for(sf::Sprite deadBody: deadBodies) {
        window.draw(deadBody);
    }
}

void Window::showRobots() {
    for(Robot* robot: robots) {
        window.draw(robot->getRobotSprite());
        window.draw(robot->getTurretSprite());
        window.draw(robot->getNameText());
        window.draw(robot->getHealthText());
    }
}

void Window::draw() {
    showAllDeadBodies();
    showAllBullets();
    showRobots();
}

void Window::display() {
    window.display();
}

RobotStartConfiguration Window::getAvailablePosition() {
    static int current{0};
    return startConfigs[current++];
}