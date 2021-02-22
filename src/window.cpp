#include "window.h"
#include "bullet.h"

#include <vector>

using namespace std;

void Window::addBullet(sf::Sprite turret, float speed) {
    Bullet bullet{turret, speed};
    bullets.push_back(bullet);
}

void Window::addRobot(Robot *robot) {
    robots.push_back(robot);
}

void Window::moveAllBullets() {
    for(Bullet &bullet: bullets) {
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

vector<Bullet> Window::bullets;
vector<Robot*> Window::robots;