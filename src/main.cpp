#include <iostream>

#include "SFML/Graphics.hpp"

// class Pixel : sf::Vertex
// {
//     Pixel(sf::Vector2f pos, sf::Color color)
//     {
//         // sf::Vertex(color, pos);
//     }
// };

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 240), "Test Window");
    window.setFramerateLimit(60);

    sf::VertexArray pointmap(sf::Points, 400 * 240);
    std::vector<sf::Vertex> pixels;

    for (uint32_t i = 0; i < 400 * 240; i++)
    {
        // sf::Vertex px(sf::Vector2f(i % 400, i / 400), i % 2 ? sf::Color::Green : sf::Color::Blue);
        // pixels.push_back(px);
        pointmap[i].position = sf::Vector2f(i % 400, i / 400);
        if (i % 2) pointmap[i].color = sf::Color::Green;
        else pointmap[i].color = sf::Color::Blue;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
            {
                auto mp = sf::Mouse::getPosition(window);
                std::cout << "Vec " << mp.x << "," << mp.y << "\n";
                break;
            }
            default:
                break;
            }
        }

        window.clear();
        window.draw(pointmap);

        // window.draw(&pixels[0], pixels.size(), sf::Points, sf::RenderStates::Default);
        // for (auto & px : pixels)
        // {
        //     window.draw(&px, (size_t)p, sf::Points, sf::RenderStates::Default);
        //     std::cout << px.position.x;
        // }
    }
    return 0;
}