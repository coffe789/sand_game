#include "input_event.h"
#include "SFML/Graphics.hpp"
#include "sandbox.h"

void process_input(sf::RenderWindow &window, std::vector<CellData>& point_data)
{
    static bool mouse_pressed = false; // TODO let us hold down the mouse

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto mp = sf::Mouse::getPosition(window);
        point_data[mp.x + mp.y * SANDBOX_X].type = SAND;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        const auto mp = sf::Mouse::getPosition(window);
        point_data[mp.x + mp.y * SANDBOX_X].type = AIR;
    }
}