#ifndef CELL_H
#define CELL_H

#include <cstdint>
#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

// This saves space over a Vector2i
typedef enum
{
    LEFT,
    UP_LEFT,
    UP,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
} cell_dir_t;

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

    explicit CellMutData(cell_t cell_type);
};

// Behaviour is different for all cell types
// We store non-mutable data here as there is no point having multiple copies
class CellBehaviour
{
public:
    virtual void cellInit(CellMutData& cell, cell_t type);

    // We take the whole vector because we need context of surrounding cells
    virtual void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y);

private:
    sf::Color max_color;
    sf::Color min_color;
};


// This is the outward facing API for interacting with cells, internally it decides what cell behaviour to use
void cellInit(CellMutData& cell, cell_t type);
void cellUpdate(std::vector<CellMutData>& cells, uint32_t x, uint32_t y);

#endif //CELL_H