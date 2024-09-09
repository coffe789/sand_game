#include "input_event.h"
#include "SFML/Graphics.hpp"
#include "sandbox.h"

static void processMouseInput(sf::RenderWindow &window, Sandbox& sb)
{
    static auto m_pos_prev = sf::Vector2(0, 0);
    static auto m_pressed_prev = false;

    auto m_pos = sf::Mouse::getPosition(window);
    bool m_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sb.paintCells(m_pos.x, m_pos.y, 10, SAND);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        sb.paintCells(m_pos.x, m_pos.y, 10, AIR);
    }

    m_pos_prev = m_pos;
    m_pressed_prev = m_pressed;
}

void processInput(sf::RenderWindow &window, Sandbox& sb)
{
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

    processMouseInput(window, sb);
}