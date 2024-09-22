#ifndef CELL_H
#define CELL_H

#include "SFML/System/Vector2.hpp"

typedef enum
{
    AIR,
    WATER,
    SAND,
    WALL,

    CELL_COUNT,
} cell_t;

class CellData
{
public:
    cell_t type;
    bool checked;
    sf::Vector2i dir;
    explicit CellData(cell_t cell_type);
};


class Cell
{

};

#endif //CELL_H