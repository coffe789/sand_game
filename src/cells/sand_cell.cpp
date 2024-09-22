//
// Created by Jonathan on 22/09/2024.
//

#include "sand_cell.h"

#include "../sandbox.h"
#include <cstdlib>

void SandCell::cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y)
{
    if (try_move_to(cells, x, y, x + 0, y + 1)) return;
    if (rand() % 2 == 0)
    {
        if (try_move_to(cells, x, y, x + 1, y + 1)) return;
        if (try_move_to(cells, x, y, x - 1, y + 1)) return;
    } else
    {
        if (try_move_to(cells, x, y, x - 1, y + 1)) return;
        if (try_move_to(cells, x, y, x + 1, y + 1)) return;
    }
}