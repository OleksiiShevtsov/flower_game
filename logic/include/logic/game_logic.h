#pragma once

#include <vector>

#include "logic/map.h"
#include "logic/snake.h"

namespace flower {

    class GameLogic {

    public:
        GameLogic( const Map& ) = delete;
        GameLogic( const Map&& ) = delete;

        GameLogic(){
            m_window = std::make_shared< sf::RenderWindow >(
                        sf::VideoMode( sf::Vector2u( common::GlobalSettings::pixelCountX * common::GlobalSettings::sizePixel,
                                                     common::GlobalSettings::pixelCountY * common::GlobalSettings::sizePixel
                                                     ) ), "Flower" );
            m_map = std::make_unique< Map >( m_window );
            m_snakes.push_back( Snake( 10, 10) );
        }

        void startGame(){
            while (m_window->isOpen())
            {
                sf::Event event;
                while (m_window->pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        m_window->close();
                }

                m_window->clear( sf::Color( 25, 25, 25 ) );

                drawingObjects();
                gameState();

                m_window->display();
            }
        }

    private:

        // TODO
        void drawingObjects(){
            // TODO
            m_snakes[0].drowSnake(m_window);

            m_map->drowMap();
        }

        // TODO
        void gameState(){
            if(m_snakes[0].getSnakeState() == common::SnakeState::READY){
                m_snakes[0].move();
                m_snakes[0].snakeWaiting();
            }
        }

        std::vector< Snake > m_snakes;
        std::unique_ptr< Map > m_map;
        std::shared_ptr< sf::RenderWindow > m_window;
    };
}
