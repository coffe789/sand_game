#ifndef CELL_H
#define CELL_H

#include <cstdint>
#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

typedef enum
{
    AIR,
    WATER,
    SAND,
    WALL,

    CELL_COUNT,
} cell_t;


// Data is shared by all cell types so our cell array can store values rather than references for better cache locality
class CellMutData
{
public:
    // cell_dir_t dir; // TODO switch to this
    sf::Vector2i dir;
    cell_t type;
    bool checked;
    sf::Color color;

    CellMutData(cell_t cell_type = AIR);
    void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y);
};

// Behaviour is different for all cell types
class CellBehaviour
{
public:
    virtual void cellInit(CellMutData& cell, cell_t type);

    // We take the whole vector because we need context of surrounding cells
    virtual void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y);
};


// This is the outward facing API for interacting with cells, internally it decides what cell behaviour to use
void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y);

#endif //CELL_H