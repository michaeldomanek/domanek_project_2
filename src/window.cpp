#include "bullet.h"
#include "window.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/bundled/color.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void Window::addBullet(sf::Sprite turret, Robot* attacker) {
    Bullet bullet{turret, attacker, config};
    bullets.push_back(bullet);
}

void Window::addRobot(Robot *robot) {
    robots.push_back(robot);
}

void Window::removeRobot(Robot *robot) {
    sf::Sprite deadRobot{robot->getRobotSprite()};
    deadRobot.setTexture(explosionTexture);

    robots.erase(remove(robots.begin(), robots.end(), robot), robots.end());
    deadBodies.push_back(deadRobot);

    if (robots.size() == 1) {
        window.close();
        fmt::print("GAME OVER!\n");
        fmt::print("Robot: ");
        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, robots.back()->getName());
        fmt::print(" won!\n");
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
    for(Bullet &bullet: bullets) {
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
            bool increamentBullet{};
            sf::FloatRect bulletRect {bullet->getSprite().getGlobalBounds()};

            if(!bulletRect.intersects(border)){        
                bullets.erase(bullet);
            } else {
                increamentBullet = true;
            }

            for(Robot* robot: robots) {
                if(robot != bullet->getAttacker() && bulletRect.intersects(robot->getRobotSprite().getGlobalBounds())) {
                    robot->substractHealth(bullet->getDamage());
                    bullets.erase(bullet);
                    increamentBullet = true;
                }
            }

            if (increamentBullet) {
                ++bullet;
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