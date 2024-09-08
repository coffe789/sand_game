#include <cstdint>
#include "sandbox.h"

#include "SFML/Graphics.hpp"

CellData::CellData()
{
    type = AIR;
}

Sandbox::Sandbox() :
color_buf{0}
{
    point_data = std::vector<CellData>(SANDBOX_X * SANDBOX_Y);

    texture = sf::Texture();
    texture.create(SANDBOX_X, SANDBOX_Y);

    texture_rect = sf::RectangleShape(sf::Vector2f(SANDBOX_X, SANDBOX_Y));
    texture_rect.setTexture(&texture);

    for (uint32_t i = 0; i < SANDBOX_X * SANDBOX_Y; i++)
    {
        point_data[i].type = i % 3 ? WATER : AIR;
    }
}

bool try_move_to(std::vector<CellData>& point_data, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (x2 < 0 || x2 >= SANDBOX_X || y2 < 0 || y2 >= SANDBOX_Y)
    {
        return false;
    }
    // Not validating x1 and y1 because we trust the user..

    if (point_data[x2 + y2 * SANDBOX_X].type < point_data[x1 + y1 * SANDBOX_X].type)
    {
        auto tmp = point_data[x1 + y1 * SANDBOX_X].type;
        point_data[x1 + y1 * SANDBOX_X].type = point_data[x2 + y2 * SANDBOX_X].type;
        point_data[x2 + y2 * SANDBOX_X].type = tmp;
        return true;
    }
    return false;
}

void Sandbox::UpdatePointData()
{
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

    for (auto i = 0; i < SANDBOX_X * SANDBOX_Y; i++)
    {
        switch (point_data[i].type)
        {
        case AIR:
            color_buf[i * 4] = 0x0;
            color_buf[i * 4 + 1] = 0x0;
            color_buf[i * 4 + 2] = 0x0;
            color_buf[i * 4 + 3] = 0xFF;
            break;
        case SAND:
            color_buf[i * 4] = 0xFF;
            color_buf[i * 4 + 1] = 0xFF;
            color_buf[i * 4 + 2] = 0x0;
            color_buf[i * 4 + 3] = 0xFF;
            break;
        case WATER:
            color_buf[i * 4] = 0x0;
            color_buf[i * 4 + 1] = 0x0;
            color_buf[i * 4 + 2] = 0xFF;
            color_buf[i * 4 + 3] = 0xFF;
            break;
        default:
            break;
        }
    }
    texture.update(color_buf);
}

void Sandbox::fillCell(int x, int y, cell_t type)
{
    if (x < 0 || x >= SANDBOX_X || y < 0 || y >= SANDBOX_Y)
    {
        return;
    }
    point_data[x + y * SANDBOX_X].type = type;
}

void Sandbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(texture_rect, states);
}