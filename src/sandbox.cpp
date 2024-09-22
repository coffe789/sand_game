#include <cstdint>
#include "sandbox.h"

#include <cassert>
#include <iostream>
#include <random>

#include "SFML/Graphics.hpp"

Sandbox::Sandbox() :
color_buf {}, paint_state {.radius = 0, .type = SAND, .alt_type = AIR}
{
    point_data = std::vector<CellMutData>(SANDBOX_X * SANDBOX_Y);

    texture = sf::Texture();
    texture.create(SANDBOX_X, SANDBOX_Y);

    texture_rect = sf::RectangleShape(sf::Vector2f(SANDBOX_X, SANDBOX_Y));
    texture_rect.setTexture(&texture);

    for (auto i = 0; i < point_data.size(); i++)
    {
        point_data[i] = CellMutData(AIR);
    }
}

bool try_move_to(std::vector<CellMutData>& point_data, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (x2 < 0 || x2 >= SANDBOX_X || y2 < 0 || y2 >= SANDBOX_Y)
    {
        return false;
    }

    assert(!(x1 < 0 || x1 >= SANDBOX_X || y1 < 0 || y1 >= SANDBOX_Y));
    assert(abs(x1-x2) <= 1 && abs(y1-y2) <= 1);

    if (point_data[x1 + y1 * SANDBOX_X].checked)
    {
        return false;
    }

    if (point_data[x2 + y2 * SANDBOX_X].type < point_data[x1 + y1 * SANDBOX_X].type)
    {
        point_data[x2 + y2 * SANDBOX_X].checked = true;
        point_data[x1 + y1 * SANDBOX_X].checked = true;

        auto tmp = point_data[x1 + y1 * SANDBOX_X];
        point_data[x1 + y1 * SANDBOX_X] = point_data[x2 + y2 * SANDBOX_X];
        point_data[x2 + y2 * SANDBOX_X] = tmp;
        return true;
    }
    return false;
}

void Sandbox::updatePointData()
{
    for (auto y = SANDBOX_Y - 1; y >= 0; y--)
    {
        if (rand() & 1)
        {
            for (auto x = SANDBOX_X - 1; x >= 0; x--)
            {
                cellUpdate(point_data, x, y);
            }
        }
        else
        {
            for (auto x = 0; x < SANDBOX_X; x++)
            {
                cellUpdate(point_data, x, y);
            }
        }
    }

    // Unset checked for next pass
    for (auto &cdata : point_data)
    {
        cdata.checked = false;
    }
}

void Sandbox::updateColorBuf()
{
    for (auto i = 0; i < SANDBOX_X * SANDBOX_Y; i++)
    {
        memcpy(color_buf + i * 4, &point_data[i].color, 4);
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

    point_data[x + y * SANDBOX_X] = CellMutData(type);
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

void Sandbox::paintCells(int32_t xc, int32_t yc, bool alt)
{
    if (alt)
    {
        paintCells(xc, yc, paint_state.radius, paint_state.alt_type);
    } else
    {
        paintCells(xc, yc, paint_state.radius, paint_state.type);
    }
}

void Sandbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(texture_rect, states);
}

void Sandbox::updatePaintRadius(float delta)
{
    if (delta > 0.0)
    {
        paint_state.radius = std::min(paint_state.radius + 1.0f, 20.0f);
    } else if (delta < 0.0)
    {
        paint_state.radius = std::max(paint_state.radius - 1.0f, 0.0f);
    }
}

void Sandbox::updatePaintType(cell_t type)
{
    if (type >= CELL_COUNT)
    {
        return;
    }
    paint_state.type = type;
}