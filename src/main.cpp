#include <iostream>

#include "SFML/Graphics.hpp"

#define SCREEN_X 400
#define SCREEN_Y 240

typedef enum
{
    AIR,
    WATER,
    SAND,
} cell_t;

class CellData
{
public:
    cell_t type = AIR;
};

void handle_events(sf::RenderWindow &window, std::vector<CellData>& point_data)
{
    static bool mouse_pressed = false;

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
        point_data[mp.x + mp.y * SCREEN_X].type = SAND;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        auto mp = sf::Mouse::getPosition(window);
        point_data[mp.x + mp.y * SCREEN_X].type = WATER;
    }
}

bool try_move_to(std::vector<CellData>& point_data, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (x2 < 0 || x2 >= SCREEN_X || y2 < 0 || y2 >= SCREEN_Y)
    {
        return false;
    }
    if (point_data[x2 + y2 * SCREEN_X].type < point_data[x1 + y1 * SCREEN_X].type)
    {
        auto tmp = point_data[x1 + y1 * SCREEN_X].type;
        point_data[x1 + y1 * SCREEN_X].type = point_data[x2 + y2 * SCREEN_X].type;
        point_data[x2 + y2 * SCREEN_X].type = tmp;
        return true;
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Cells");
    window.setFramerateLimit(60);

    sf::VertexArray points(sf::Points, SCREEN_X * SCREEN_Y);
    std::vector<CellData> point_data(SCREEN_X * SCREEN_Y);

    srand(clock());

    // Initial state
    for (uint32_t i = 0; i < SCREEN_X * SCREEN_Y; i++)
    {
        points[i].position = sf::Vector2f(i % 400, i / 400);

        point_data[i].type = i % 3 ? WATER : AIR;
    }

    while (window.isOpen())
    {
        handle_events(window, point_data);

        // Update state
        for (auto y = SCREEN_Y - 1; y >= 0; y--)
        {
            for (auto x = SCREEN_X - 1; x >= 0; x--)
            {
                switch (point_data[x + y * SCREEN_X].type)
                {
                case AIR:
                    break;
                case SAND:
                    if (try_move_to(point_data, x, y, x + 0, y + 1)) break;
                    if (rand() % 2)
                    {
                        if (try_move_to(point_data, x, y, x + 1, y + 1)) break;
                        if (try_move_to(point_data, x, y, x - 1, y + 1)) break;
                    } else
                    {
                        if (try_move_to(point_data, x, y, x - 1, y + 1)) break;
                        if (try_move_to(point_data, x, y, x + 1, y + 1)) break;
                    }
                    break;
                case WATER:
                    if (try_move_to(point_data, x, y, x + 0, y + 1)) break;
                    if (rand() % 2)
                    {
                        if (try_move_to(point_data, x, y, x + 1, y + 1)) break;
                        if (try_move_to(point_data, x, y, x - 1, y + 1)) break;
                        if (try_move_to(point_data, x, y, x + 1, y + 0)) break;
                        if (try_move_to(point_data, x, y, x - 1, y + 0)) break;
                    } else
                    {
                        if (try_move_to(point_data, x, y, x - 1, y + 1)) break;
                        if (try_move_to(point_data, x, y, x + 1, y + 1)) break;
                        if (try_move_to(point_data, x, y, x - 1, y + 0)) break;
                        if (try_move_to(point_data, x, y, x + 1, y + 0)) break;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        // Draw state
        window.clear(sf::Color::Black);
        for (auto i = 0; i < SCREEN_X * SCREEN_Y; i++)
        {
            switch (point_data[i].type)
            {
            case AIR:
                points[i].color = sf::Color::Black;
                break;
            case SAND:
                points[i].color = sf::Color::Yellow;
                break;
            case WATER:
                points[i].color = sf::Color::Blue;
                break;
            default:
                break;
            }
        }
        window.draw(points);

        window.display();
    }
    return 0;
}