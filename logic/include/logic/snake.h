#pragma once

#include <vector>
#include <memory>

#include "common/type.h"
#include "common/enum.h"

namespace flower {

    class Snake {

        struct Item;

    public:

        Snake( common::Coordinate x, common::Coordinate y );

        common::Coordinate getCoordinateHeadX();
        common::Coordinate getCoordinateHeadY();
        std::vector<Item> getTail();
        common::Direction getDirection();

        void setDirection( common::Direction currentDirection );

        void move();
        void incrementSnake( common::Coordinate x, common::Coordinate y );

    private:

        void movingItem( common::Coordinate x, common::Coordinate y );

        struct Item {
            common::Coordinate x;
            common::Coordinate y;
        };

        std::vector< Item > m_tail;
        common::Direction m_currentDirection;
    };
}
