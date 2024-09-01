#include <iostream>
#include <SFML/Graphics.hpp>

void handle_input(sf::RenderWindow &window)
{
    // Handle input
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
            {
                window.setTitle("Space pressed");
            }
            break;

        case sf::Event::EventType::KeyReleased:
            if (event.key.code == sf::Keyboard::Space)
            {
                window.setTitle("Space released");
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            break;

        default:
            break;
        }
    }
}

void init_shape(sf::RectangleShape& shape, sf::Vector2f const&pos, sf::Color const& color)
{
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setOrigin(shape.getSize() * 0.5f);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 180), "The title");
    window.setFramerateLimit(60);

    sf::Vector2f startPos = sf::Vector2f(50, 50);
    sf::RectangleShape playerRect(sf::Vector2f(50, 50));
    init_shape(playerRect, startPos, sf::Color::Green);
    sf::RectangleShape targetRect(sf::Vector2f(50, 50));
    init_shape(targetRect, sf::Vector2f(400, 50), sf::Color::Blue);
    sf::RectangleShape badRect(sf::Vector2f(50, 100));
    init_shape(badRect, sf::Vector2f(250, 50), sf::Color::Red);


    // Game loop
    while (window.isOpen())
    {
        // Input handling
        handle_input(window);

        // Update frame
        playerRect.move(1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            playerRect.move(0, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            playerRect.move(0, -1);

        if (playerRect.getGlobalBounds().intersects((targetRect.getGlobalBounds())))
            window.close();
        if (playerRect.getGlobalBounds().intersects((badRect.getGlobalBounds())))
            playerRect.setPosition(startPos);

        // Render frame
        window.clear(sf::Color::Black);
        window.draw(playerRect);
        window.draw(targetRect);
        window.draw(badRect);

        window.display();
    }

    return 0;
}