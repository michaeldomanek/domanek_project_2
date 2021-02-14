#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>
#include <unistd.h>

using namespace std;

int main()
{
    const unsigned width = 700;
    const unsigned height= 700;

    sf::RenderWindow window(sf::VideoMode(width, height), "Robotgame");

    sf::Texture texture;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 70, 70));
    sprite.setColor(sf::Color(255, 255, 255, 200));
    sprite.setPosition(100, 25);

    while (window.isOpen()) {

        window.clear(sf::Color::Black);

        sprite.move(1, 1);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(sprite);
        window.display();
        
        usleep(10000);
    }

    return 0;
}
