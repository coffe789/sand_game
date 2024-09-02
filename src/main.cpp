#include <iostream>

#include "SFML/Graphics.hpp"

#define WINDOW_X 800
#define WINDOW_Y 480

#define SANDBOX_X 400
#define SANDBOX_Y 400

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
        point_data[mp.x + mp.y * SANDBOX_X].type = SAND;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        auto mp = sf::Mouse::getPosition(window);
        point_data[mp.x + mp.y * SANDBOX_X].type = WATER;
    }
}

bool try_move_to(std::vector<CellData>& point_data, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (x2 < 0 || x2 >= SANDBOX_X || y2 < 0 || y2 >= SANDBOX_Y)
    {
        return false;
    }
    if (point_data[x2 + y2 * SANDBOX_X].type < point_data[x1 + y1 * SANDBOX_X].type)
    {
        auto tmp = point_data[x1 + y1 * SANDBOX_X].type;
        point_data[x1 + y1 * SANDBOX_X].type = point_data[x2 + y2 * SANDBOX_X].type;
        point_data[x2 + y2 * SANDBOX_X].type = tmp;
        return true;
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Cells");
    window.setFramerateLimit(60);

    auto w_size = window.getSize();
    sf::View view(sf::Vector2f(w_size.x / 2, w_size.y / 2), sf::Vector2f(w_size.x, w_size.y));
    view.setViewport(sf::FloatRect(0.05f, 0.05f, 1.0f, 1.0f));
    window.setView(view);

    sf::VertexArray points(sf::Points, SANDBOX_X * SANDBOX_Y);
    std::vector<CellData> point_data(SANDBOX_X * SANDBOX_Y);

    srand(clock());

    // Initial state
    for (uint32_t i = 0; i < SANDBOX_X * SANDBOX_Y; i++)
    {
        points[i].position = sf::Vector2f(i % 400, i / 400);

        point_data[i].type = i % 3 ? WATER : WATER;
    }

    while (window.isOpen())
    {
        handle_events(window, point_data);

        // Update state
        for (auto y = SANDBOX_Y - 1; y >= 0; y--)
        {
            for (auto x = SANDBOX_X - 1; x >= 0; x--)
            {
                switch (point_data[x + y * SANDBOX_X].type)
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
        for (auto i = 0; i < SANDBOX_X * SANDBOX_Y; i++)
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