#include "SFML/Graphics.hpp"
#include "sandbox.h"
#include "cell.h"
#include "input_event.h"

static void processMouseInput(sf::RenderWindow &window, Sandbox& sb)
{
    // TODO use these to draw lines rather than circles
    static auto m_pos_prev = sf::Vector2i(0, 0);
    static auto m_pressed_prev = false;

    auto m_pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    bool m_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sb.paintCells(m_pos.x, m_pos.y, false);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        sb.paintCells(m_pos.x, m_pos.y, true);
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
        case sf::Event::MouseWheelScrolled:
            if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                sb.updatePaintRadius(event.mouseWheelScroll.delta);
            }
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Num1:
            case sf::Keyboard::Num2:
            case sf::Keyboard::Num3:
            case sf::Keyboard::Num4:
            case sf::Keyboard::Num5:
            case sf::Keyboard::Num6:
            case sf::Keyboard::Num7:
            case sf::Keyboard::Num8:
            case sf::Keyboard::Num9:
                sb.updatePaintType(static_cast<cell_t>(event.key.code - sf::Keyboard::Num0));
                break;
            }
        default:
            break;
        }
    }

    processMouseInput(window, sb);
}