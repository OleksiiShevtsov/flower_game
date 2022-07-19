#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "common/global_settings.h"

namespace flower {

    class Map {

    public:

        Map() = delete;
        Map( const Map& ) = delete;
        Map( const Map&& ) = delete;

        Map( std::shared_ptr<sf::RenderWindow> window ) :
            m_window{ window }{}

        void drowMap(){

            for( std::size_t i{}; i < common::GlobalSettings::pixelCountX; i++ ){
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f( 1, common::GlobalSettings::pixelCountY * common::GlobalSettings::sizePixel ) );

                rectangle.setFillColor(sf::Color( 50, 50, 50 ));
                rectangle.move(sf::Vector2f( common::GlobalSettings::sizePixel * i, 0 ) );
                m_window->draw(rectangle);
            }
            for( std::size_t i{}; i < common::GlobalSettings::pixelCountY; i++ ){
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f( common::GlobalSettings::pixelCountX * common::GlobalSettings::sizePixel, 1 ) );

                rectangle.setFillColor(sf::Color( 50, 50, 50 ));
                rectangle.move( sf::Vector2f( 0, common::GlobalSettings::sizePixel * i ) );
                m_window->draw( rectangle );
            }
        }

    private:

        std::shared_ptr<sf::RenderWindow> m_window;
    };
}
