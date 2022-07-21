#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <cstdlib>
#include <time.h>
#include "windows.h"

// delete
#include <SFML/Graphics.hpp>

#include "common/types.h"
#include "common/enum.h"
#include "common/global_settings.h"

namespace flower {

    class Snake {

        struct Item;

    public:

        Snake( common::Coordinate x, common::Coordinate y ) :
            m_snakeState{ common::SnakeState::READY },
            m_pastDirectionSnake{ common::DirectionSnake::MOTIONLESS },
            m_posturePastDirectionSnake{ common::DirectionSnake::MOTIONLESS }{

            srand(time(NULL));
            m_currentDirectionSnake = static_cast< common::DirectionSnake >( rand() % 4 );
            m_tail.push_back( Item{ x, y } );
            m_tail.push_back( Item{ x, y } );
            m_tail.push_back( Item{ x, y } );
            m_tail.push_back( Item{ x, y } );
        }

        common::Coordinate Snake::getCoordinateHeadX() {
            return m_tail[0].x;
        }

        common::Coordinate Snake::getCoordinateHeadY() {
            return m_tail[0].y;
        }

        common::SnakeState getSnakeState(){
            return m_snakeState;
        }

        // TODO to GameLogic
        void getAvailableDirection(){
            m_availableDirection.clear();
            if( m_currentDirectionSnake != common::DirectionSnake::LEFT ){
                m_availableDirection.push_back( common::DirectionSnake::RIGHT );
            }
            if( m_currentDirectionSnake != common::DirectionSnake::RIGHT ){
                m_availableDirection.push_back( common::DirectionSnake::LEFT );
            }
            if( m_currentDirectionSnake != common::DirectionSnake::UP ){
                m_availableDirection.push_back( common::DirectionSnake::DOWN );
            }
            if( m_currentDirectionSnake != common::DirectionSnake::DOWN ){
                m_availableDirection.push_back( common::DirectionSnake::UP );
            }

            srand(time(NULL));

            m_posturePastDirectionSnake = m_pastDirectionSnake;
            m_pastDirectionSnake = m_currentDirectionSnake;
            m_currentDirectionSnake = m_availableDirection[ rand() % m_availableDirection.size() ];
        }

        // TODO move to drow Class
        void drowSnake( std::shared_ptr<sf::RenderWindow> window ){
            for ( auto &item : m_tail ){
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f( common::GlobalSettings::sizePixel, common::GlobalSettings::sizePixel ) );
                rectangle.setFillColor(sf::Color( 200, 100, 100 ));
                rectangle.move(sf::Vector2f( item.x * common::GlobalSettings::sizePixel, item.y * common::GlobalSettings::sizePixel ) );
                window->draw(rectangle);
            }
        }

        void snakeWaiting(){
            m_snakeState = common::SnakeState::STAND;
            m_waitingForNextDirection = std::make_unique<std::thread>(&Snake::waitingForNextState, this);
            m_waitingForNextDirection->detach();
        }

        void move(){

            getAvailableDirection();
            switch ( m_currentDirectionSnake )
            {
                case common::DirectionSnake::LEFT: movingItem( -1, 0 ); break;
                case common::DirectionSnake::RIGHT: movingItem( 1, 0 ); break;
                case common::DirectionSnake::UP: movingItem( 0, 1 ); break;
                case common::DirectionSnake::DOWN: movingItem( 0, -1 ); break;
            }
        }

        void incrementSnake( common::Coordinate x, common::Coordinate y ){
            m_tail.push_back( Item{ x, y } );
        }

    private:

        void waitingForNextState(){
            Sleep(500);
            m_snakeState = common::SnakeState::READY;
        }

        void movingItem( common::Coordinate x, common::Coordinate y ){
            for (int i = m_tail.size();; --i) {

                if (i == 1) {
                    m_tail[ 0 ].x += x;
                    m_tail[ 0 ].y -= y;
                    return;
                }
                int flag = true;
                if (i == m_tail.size()) {
                    for (int j = 0; j < m_tail.size() - 1; ++j) {
                        if ( m_tail[ m_tail.size() - 1 ].x == m_tail[ j ].x &&
                            m_tail[ m_tail.size() - 1 ].y == m_tail[ j ].y ) {
                            flag = false;
                        }
                    }
                    if (flag) {
                        m_tail[ i - 1 ].x = m_tail[ i - 2 ].x;
                        m_tail[ i - 1 ].y = m_tail[ i - 2 ].y;
                    }
                }
                else {
                    m_tail[ i - 1 ].x = m_tail[ i - 2 ].x;
                    m_tail[ i - 1 ].y = m_tail[ i - 2 ].y;
                }
            }
        }

        struct Item {
            common::Coordinate x;
            common::Coordinate y;
        };

        std::vector< Item > m_tail;
        common::SnakeState m_snakeState;
        common::DirectionSnake m_currentDirectionSnake;
        common::DirectionSnake m_pastDirectionSnake;
        common::DirectionSnake m_posturePastDirectionSnake;
        std::vector<common::DirectionSnake> m_availableDirection;
        std::unique_ptr<std::thread> m_waitingForNextDirection;
    };
}
