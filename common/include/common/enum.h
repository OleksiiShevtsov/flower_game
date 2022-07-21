#pragma once

namespace flower::common
{
    enum DirectionSnake {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN,
        MOTIONLESS
    };

    enum SnakeState{
        READY,
        STAND
    };
}
