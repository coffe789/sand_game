#include <cstdint>
#include "sandbox.h"

#include <iostream>

#include "SFML/Graphics.hpp"

CellData::CellData()
{
    type = AIR;
}

Sandbox::Sandbox() :
color_buf{}
{
    point_data = std::vector<CellData>(SANDBOX_X * SANDBOX_Y);

    texture = sf::Texture();
    texture.create(SANDBOX_X, SANDBOX_Y);

    texture_rect = sf::RectangleShape(sf::Vector2f(SANDBOX_X, SANDBOX_Y));
    texture_rect.setTexture(&texture);

    for (uint32_t i = 0; i < point_data.size(); i++)
    {
        point_data[i].type = i % 3 ? AIR : WATER;
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

void Sandbox::updatePointData()
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

}

void Sandbox::updateColorBuf()
{
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

void Sandbox::update()
{
    updatePointData();
    updateColorBuf();
}

inline void Sandbox::fillCell(uint32_t x, uint32_t y, cell_t type)
{
    if (x >= SANDBOX_X || y >= SANDBOX_Y)
    {
        return;
    }
    point_data[x + y * SANDBOX_X].type = type;
}

// Helper function for paintCells
void Sandbox::paintHorizontal(int32_t x1, int32_t x2, int32_t y, cell_t type)
{
    for (auto x = x1; x <= x2; x++)
    {
        fillCell(x, y, type);
    }
}

// Draw a circle of cells
void Sandbox::paintCells(int32_t xc, int32_t yc, int32_t radius, cell_t type)
{
    int32_t x = 0, y = radius;
    int32_t p = 1 - radius; // Initial decision parameter

    while (x <= y)
    {
        paintHorizontal(xc - x, xc + x, yc + y, type); // Octant 1 and 8
        paintHorizontal(xc - x, xc + x, yc - y, type); // Octant 4 and 5
        paintHorizontal(xc - y, xc + y, yc + x, type); // Octant 2 and 7
        paintHorizontal(xc - y, xc + y, yc - x, type); // Octant 3 and 6

        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        } else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void Sandbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(texture_rect, states);
}