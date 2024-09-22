#ifndef SAND_CELL_H
#define SAND_CELL_H
#include "../cell.h"

class SandCell : public CellBehaviour
{
public:
    void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y) override;
};

#endif //SAND_CELL_H