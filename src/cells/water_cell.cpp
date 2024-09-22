#include <stdlib.h>
#include <cassert>

#include "../sandbox.h"
#include "water_cell.h"

void WaterCell::cellInit(CellMutData& cell, cell_t type)
{
    CellBehaviour::cellInit(cell, type);

    cell.dir = (rand() & 1) ? sf::Vector2i(1, 0) : sf::Vector2i(-1, 0);
}

void WaterCell::cellUpdate(std::vector<CellMutData> &cells, uint32_t x, uint32_t y)
{
    assert(cells[x + y * SANDBOX_X].dir.x != 0);

    if (try_move_to(cells, x, y, x, y + 1)) return; // Down
    if (cells[x + y * SANDBOX_X].dir.x == 1)
    {
        if (try_move_to(cells, x, y, x + 1, y)) {return;}
    } else
    {
        if (try_move_to(cells, x, y, x - 1, y)) {return;}
    }
    // Couldn't go the direction we wanted, change direction
    cells[x + y * SANDBOX_X].dir.x *= - 1;
}