#ifndef SANDBOX_H
#define SANDBOX_H

#define SANDBOX_X 400
#define SANDBOX_Y 400

#include <cstdint>
#include "SFML/Graphics/VertexArray.hpp"

typedef enum
{
    AIR,
    WATER,
    SAND,
} cell_t;

class CellData
{
public:
    cell_t type;
    CellData();
};

bool try_move_to(std::vector<CellData>& point_data, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

class Sandbox : public sf::Drawable
{
public:
    sf::VertexArray points;
    std::vector<CellData> point_data;

    Sandbox();

    void UpdatePointData();
    void fillCell(int x, int y, cell_t type);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //SANDBOX_H