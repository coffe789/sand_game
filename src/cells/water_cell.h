#ifndef WATER_CELL_H
#define WATER_CELL_H
#include "../cell.h"

class WaterCell : public CellBehaviour
{
    void cellInit(CellMutData& cell, cell_t type) override;
    void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y) override;
};

#endif //WATER_CELL_H