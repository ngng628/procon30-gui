# pragma once
# include <vector>
# include "Point.h"
struct Player
{
    omm::Point pos;
    Player();
    Player(omm::Point);
    Player(int32,int32);
};