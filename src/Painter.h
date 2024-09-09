#ifndef PAINTER_H
#define PAINTER_H

#include <cstdint>
#include "sandbox.h"

class Painter
{
public:
    Painter();
private:
    cell_t selected_type;
    int32_t radius;
};

#endif //PAINTER_H