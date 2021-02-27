#include "bullet.h"
#include "window.h"
#include "robot.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void Window::addBullet(sf::Sprite turret, Robot* attacker, float speed, float damage) {
    Bullet bullet{turret, attacker, speed, damage};
    bullets.push_back(bullet);
}

void Window::addRobot(Robot *robot) {
    robots.push_back(robot);
}

void Window::removeRobot(Robot *robot) {
    robots.erase(remove(robots.begin(), robots.end(), robot), robots.end());
    if (robots.size() == 1) {
        window.close();
        cout << "GAME OVER!" << endl;
        cout << "Robot: " << robots.back()->getName() << " won!" << endl;
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
    window.clear(sf::Color::Black);
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

void Window::showRobots() {
    for(Robot* robot: robots) {
        window.draw(robot->getRobotSprite());
        window.draw(robot->getTurretSprite());
    }
}

void Window::draw() {
    showAllBullets();
    showRobots();
}

void Window::display() {
    window.display();
}