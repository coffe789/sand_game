#include "cells/sand_cell.h"
#include "cell.h"

#include <iostream>

#include "sandbox.h"

static CellBehaviour* behaviour_map[CELL_COUNT] =
{
    [AIR] = new CellBehaviour(),
    [WATER] = new CellBehaviour(),
    [SAND] = new SandCell(),
    [WALL] = new CellBehaviour(),
};

void CellBehaviour::cellInit(CellMutData &cell, cell_t type)
{
    // TODO add default functionality
}

void CellBehaviour::cellUpdate(std::vector<CellMutData> &cells, uint32_t x, uint32_t y)
{
    // TODO add default functionality
    std::cout << "AHAHAHAH\n";
}



void cellInit(CellMutData& cell, cell_t type)
{
    behaviour_map[type]->cellInit(cell, type);
}

void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y)
{
    behaviour_map[cells[x + y * SANDBOX_X].type]->cellUpdate(cells, x, y);
}