#include <iostream>

#include "SFML/Graphics.hpp"
#include "input_event.h"
#include "sandbox.h"

#define WINDOW_X 800
#define WINDOW_Y 480

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Cells");
    window.setFramerateLimit(60);

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
    text.setString("Hello world");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(10,10));

    auto sb = Sandbox();

    srand(clock());

    while (window.isOpen())
    {
        process_input(window, sb.point_data);

        // Update state
        sb.UpdatePointData();

        // Draw state
        window.clear(sf::Color::Black);
        window.draw(sb);
        window.draw(text);

        window.display();
    }
    return 0;
}