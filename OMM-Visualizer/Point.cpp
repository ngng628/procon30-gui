# include "Point.h"

const omm::Point omm::Point::Left{ 0, -1 };
const omm::Point omm::Point::Right{ 0, 1 };
const omm::Point omm::Point::Up{ -1, 0 };
const omm::Point omm::Point::Down{ 1, 0 };

omm::Point::Point(int32 _y, int32 _x)
    : y(_y)
    , x(_x)
{
}

omm::Point::Point(const omm::Point& point)
    : y(point.y)
    , x(point.x)
{
}

