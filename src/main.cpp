#include <iostream>

#include "SFML/Graphics.hpp"

class Pixel : public sf::Vertex
{
public:
    Pixel(sf::Vector2f pos, sf::Color color)
        : Vertex(pos, color)
    {}
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 240), "Test Window");
    window.setFramerateLimit(60);

    sf::VertexArray pointmap(sf::Points, 400 * 240);
    std::vector<Pixel> pixels;

    for (uint32_t i = 0; i < 400 * 240; i++)
    {
        Pixel px(sf::Vector2f(i % 400, i / 400), i % 2 ? sf::Color::Green : sf::Color::Blue);
        pixels.push_back(px);
        // pointmap[i].position = sf::Vector2f(i % 400, i / 400);
        // if (i % 2) pointmap[i].color = sf::Color::Green;
        // else pointmap[i].color = sf::Color::Blue;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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

        window.clear(sf::Color::Black);
        // window.draw(pointmap);


        // Each pixel is drawn individually..
        // This is inefficient but we will deal with it when it's a problem
        for (auto & px : pixels)
        {
            window.draw(&px, 1, sf::Points, sf::RenderStates::Default);
        }

        window.display();
    }
    return 0;
}