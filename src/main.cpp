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

void update_frame(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 200), "The title");

    // Game loop
    while (window.isOpen())
    {
        handle_input(window);

        update_frame(window);

        window.display();
    }

    return 0;
}