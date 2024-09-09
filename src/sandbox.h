#ifndef SANDBOX_H
#define SANDBOX_H

#define SANDBOX_X 400
#define SANDBOX_Y 400

#include <cstdint>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
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
    Sandbox();

    inline void fillCell(uint32_t x, uint32_t y, cell_t type);
    void paintCells(int32_t xc, int32_t yc, int32_t radius, cell_t type);
    void update();

private:
    std::vector<CellData> point_data;
    sf::Texture texture;
    sf::RectangleShape texture_rect;
    uint8_t color_buf[SANDBOX_X * SANDBOX_Y * 4];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void paintHorizontal(int32_t x1, int32_t x2, int32_t y, cell_t type);
    void updatePointData();
    void updateColorBuf();
};


#endif //SANDBOX_H