#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "input_event.h"
#include "sandbox.h"

#define WINDOW_X 800
#define WINDOW_Y 480

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Cells");
    auto sb = Sandbox();

    // window.setFramerateLimit(60);

    float fps;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime = clock.getElapsedTime();

    // TODO determine whether we really need a view
    // auto w_size = window.getSize();
    // sf::View view(sf::Vector2f(w_size.x / 2, w_size.y / 2), sf::Vector2f(w_size.x, w_size.y));
    // view.setViewport(sf::FloatRect(0.05f, 0.05f, 1.0f, 1.0f));
    // window.setView(view);

    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("font/comic.ttf"))
    {
        return 1;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(10,10));

    while (window.isOpen())
    {
        processInput(window, sb);

        // Update state
        sb.update();
        text.setString(std::to_string(std::floor(1.0f / (currentTime.asSeconds() - previousTime.asSeconds()))));

        // Draw state
        window.clear(sf::Color::Black);
        window.draw(sb);
        window.draw(text);

        window.display();

        previousTime = currentTime;
        currentTime = clock.getElapsedTime();
    }
    return 0;
}