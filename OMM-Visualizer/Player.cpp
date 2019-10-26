# include "Player.h"

Player::Player()
      : pos(0, 0)
{
}

Player::Player(omm::Point p)
      : pos(p)
{
}

Player::Player(int32 _y,int32 _x)
      : pos(_y,_x)
{
}