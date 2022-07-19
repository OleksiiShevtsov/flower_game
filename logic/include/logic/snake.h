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
            m_currentDirection{ common::Direction::MOTIONLESS },
            m_pastDirection{ common::Direction::MOTIONLESS },
            m_posturePastDirection{ common::Direction::MOTIONLESS }{
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

        // TODO
        void getAvailableDirection(){
            m_availableDirection.clear();
            m_availableDirection.push_back( common::Direction::LEFT );
            m_availableDirection.push_back( common::Direction::RIGHT );
            m_availableDirection.push_back( common::Direction::UP );
            m_availableDirection.push_back( common::Direction::DOWN );

            srand(time(NULL));
            m_currentDirection = m_availableDirection[ rand() % m_availableDirection.size() ];
        }

        // TODO move to drow Class
        void drowSnake( std::shared_ptr<sf::RenderWindow> window ){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f( common::GlobalSettings::sizePixel, common::GlobalSettings::sizePixel ) );
            rectangle.setFillColor(sf::Color( 200, 100, 100 ));
            rectangle.move(sf::Vector2f( m_tail[0].x * common::GlobalSettings::sizePixel, m_tail[0].y * common::GlobalSettings::sizePixel ) );
            window->draw(rectangle);
        }

        void snakeWaiting(){
            m_snakeState = common::SnakeState::STAND;
            m_waitingForNextDirection = std::make_unique<std::thread>(&Snake::waitingForNextState, this);
            m_waitingForNextDirection->detach();
        }

        void move(){

            getAvailableDirection();
            switch ( m_currentDirection )
            {
                case common::Direction::LEFT: movingItem( -1, 0 ); break;
                case common::Direction::RIGHT: movingItem( 1, 0 ); break;
                case common::Direction::UP: movingItem( 0, 1 ); break;
                case common::Direction::DOWN: movingItem( 0, -1 ); break;
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
        common::Direction m_currentDirection;
        common::Direction m_pastDirection;
        common::Direction m_posturePastDirection;
        std::vector<common::Direction> m_availableDirection;
        std::unique_ptr<std::thread> m_waitingForNextDirection;
    };
}
