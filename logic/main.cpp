#include <SFML/Graphics.hpp>

const int sizeWindowX = 640;
const int sizeWindowY = 480;
const int sizePixel = 20;

void drowMatrix(sf::RenderWindow& window){
    for(std::size_t i{}; i < sizeWindowX/sizePixel; i++){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(1, sizeWindowY));

        rectangle.setFillColor(sf::Color(50, 50, 50));
        rectangle.move(sf::Vector2f(i*sizePixel, 0));
        window.draw(rectangle);
    }
    for(std::size_t i{}; i < sizeWindowY/sizePixel; i++){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(sizeWindowX, 1));

        rectangle.setFillColor(sf::Color(50, 50, 50));
        rectangle.move(sf::Vector2f(0, i*sizePixel));
        window.draw(rectangle);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(sizeWindowX, sizeWindowY)), "Flower");



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(25, 25, 25, 0));
        drowMatrix(window);
        window.display();
    }

    return 0;
}
