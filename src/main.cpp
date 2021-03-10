#include "bullet.h"
#include "window.h"
#include "robot.h"
#include "robotConfiguration.h"
#include "robotProperties.h"
#include "bulletConfiguration.h"

#include "CLI11.hpp"
#include <SFML/Graphics.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include <vector>
#include <math.h>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app("Robotgame");

    unsigned int width{950};
    app.add_option("-w,--width", width, "width and height of the window", true)->check(CLI::Range(500, 1500));

    float bulletSpeed{6};
    app.add_option("--bullet-speed", bulletSpeed, "the speed of the bullets", true)->check(CLI::Range(1, 50));

    float bulletDamage{20};
    app.add_option("--bullet-damage", bulletDamage, "the damage of the bullets", true);

    unsigned int bulletSize{3};
    app.add_option("--bullet-size", bulletSize, "the size of the bullets in px", true); //->check(CLI::Range(1, 10));

    float robotSpeed{2};
    app.add_option("--robot-speed", robotSpeed, "the speed of the robots", true)->check(CLI::Range(0.5f, 10.0f));

    float health{100};
    app.add_option("--health", health, "the health of the robots", true)->check(CLI::PositiveNumber);

    float robotRotation{1};
    app.add_option("--robot-rotation", robotRotation, "the robot roation speed of the robots", true)->check(CLI::Range(0.5f, 3.5f));

    float turretRotation{1.5};
    app.add_option("--turret-rotation", turretRotation, "the turret roation speed of the robots", true)->check(CLI::Range(0.5f, 5.0f));

    int minFireCountdown{500};
    app.add_option("-f,--fire-countdown", minFireCountdown, "the time after a robot can shoot again in ms", true)->check(CLI::PositiveNumber);

    unsigned int maxPlayers{4};
    app.add_option("-m,--max-players", maxPlayers, "the maximum players of the game", true)->check(CLI::Range(2, 4));

    CLI11_PARSE(app, argc, argv);

    auto file_logger = spdlog::rotating_logger_mt("file_logger", "../logs/server.log", 1048576 * 5, 3);
    spdlog::set_default_logger(file_logger);
    spdlog::set_pattern("[%Y %m %d %H:%M:%S,%e] [%l] %v");
    spdlog::set_level(spdlog::level::debug);

    RobotConfiguration config{robotSpeed, health, robotRotation, turretRotation, minFireCountdown};
    BulletConfiguration bulletConfig{bulletSpeed, bulletDamage, bulletSize};

    // This properties will be spezified by the client
    RobotProperties properties{"Keyboard Controll", sf::Color::Blue};
    RobotProperties properties2{"Random Controll", sf::Color::Red};
    RobotProperties properties3{"Change direction on wall hit", sf::Color::Green};

    Window& window{Window::getInstance(width, maxPlayers, bulletConfig)};

    Robot robo{properties, config};
    Robot robo2{properties2, config};
    Robot robo3{properties3, config};

    window.addRobot(&robo);
    window.addRobot(&robo2);
    window.addRobot(&robo3);

    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};

    robo2.startShooting();

    robo3.rotateWeaponRight();
    robo3.startShooting();
    robo3.moveForward();

    spdlog::info("Game started");

    while (window.isOpen()) {
        window.clear();

        // Robot 1

        if (!robo.isDead()) {
            robo.stopMove();
            robo.stopRotate();
            robo.stopRotateWeapon();
            robo.stopShooting();

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
                robo.rotateLeft();
            } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
                robo.rotateRight();
            }

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
                robo.moveForward();
            } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
                robo.moveBackward();
            }

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::Q )) {
                robo.rotateWeaponLeft();
            } else if (sf::Keyboard::isKeyPressed( sf::Keyboard::E )) {
                robo.rotateWeaponRight();
            }

            if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space )) {
                robo.startShooting();
            }

            robo.performActions();
        }

        // Robot 2

        if (!robo2.isDead()) {
            double rand{dis(gen)};

            if (rand <= 2) {
                robo2.rotateLeft();
            } else if (rand <= 7) {
                robo2.rotateRight();
            } else {
                robo2.stopRotate();
            }

            double rand2{dis(gen)};

            if (rand2 <= 6) {
                robo2.moveForward();
            } else if (rand2 <= 7) {
                robo2.moveBackward();
            } else {
                robo2.stopMove();
            }

            robo2.performActions();
        }

        // Robot 3

        if (!robo3.isDead()) {
            if (robo3.getPosition().x < 100) {
                if(robo3.getRotation() < 270) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else if (robo3.getPosition().y < 100) {
                if(robo3.getRotation() > 180) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else if (robo3.getPosition().x > 850) {
                if(robo3.getRotation() < 90) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else if (robo3.getPosition().y > 850) {
                if(robo3.getRotation() < 180) {
                    robo3.rotateLeft();
                } else {
                    robo3.rotateRight();
                }
            } else {
                robo3.stopRotate();
            }

            robo3.performActions();
        }

        window.moveAllBullets();
        window.bulletHit();

        window.handleEvent();
        window.draw();     
        window.display();
    }
}
