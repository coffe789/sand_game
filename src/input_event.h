#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include "sandbox.h"
#include "SFML/Graphics/RenderWindow.hpp"

void processInput(sf::RenderWindow &window, std::vector<CellData>& point_data);

#endif //INPUT_EVENT_H