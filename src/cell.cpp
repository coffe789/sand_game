#include "cells/sand_cell.h"
#include "cell.h"

#include <iostream>

#include "sandbox.h"
#include "cells/water_cell.h"

typedef struct
{
    CellBehaviour* behaviour;
    sf::Color min_color;
    sf::Color max_color;
    float color_bias;
} cell_description_t;

static cell_description_t cell_descriptions[CELL_COUNT] =
{
    [AIR] = {
        .behaviour = new CellBehaviour(),
        .min_color = sf::Color(0, 0, 0, 0),
        .max_color = sf::Color(0, 0, 0, 0),
        .color_bias = 0.0f,
    },
    [WATER] = {
        .behaviour = new WaterCell(),
        .min_color = sf::Color(0, 0, 100),
        .max_color = sf::Color(0, 30, 255),
        .color_bias = 0.9f,
    },
    [SAND] = {
        .behaviour = new SandCell(),
        .min_color = sf::Color(0xF2 / 2, 0xCA / 2, 0x00),
        .max_color = sf::Color(0xCC, 0x99, 0x00),
        .color_bias = 0.99f,
    },
    [WALL] = {
        .behaviour = new CellBehaviour(),
        .min_color = sf::Color(90, 80, 80),
        .max_color = sf::Color(120, 120, 120),
        .color_bias = 0.5f,
    },
};

CellMutData::CellMutData(cell_t cell_type) :
    dir {}, type {cell_type}, checked {false}
{
    cell_descriptions[type].behaviour->cellInit(*this, type);
}

void CellBehaviour::cellInit(CellMutData &cell, cell_t type)
{
    double scale = (double)rand() / ((double)RAND_MAX + 1) * cell_descriptions[type].color_bias;

    auto &min_color = cell_descriptions[type].min_color;
    auto &max_color = cell_descriptions[type].max_color;

    cell.color.r = static_cast<sf::Uint8>(min_color.r + ((max_color.r - min_color.r) * scale));
    cell.color.g = static_cast<sf::Uint8>(min_color.g + ((max_color.g - min_color.g) * scale));
    cell.color.b = static_cast<sf::Uint8>(min_color.b + ((max_color.b - min_color.b) * scale));
    cell.color.a = static_cast<sf::Uint8>(min_color.a + ((max_color.a - min_color.a) * scale));
}

void CellBehaviour::cellUpdate(std::vector<CellMutData> &cells, uint32_t x, uint32_t y)
{
    // TODO add default functionality
}

void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y)
{
    cell_descriptions[cells[x + y * SANDBOX_X].type].behaviour->cellUpdate(cells, x, y);
}