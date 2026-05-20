#ifndef POINT_HPP
#define POINT_HPP

#include "IOTypes.hpp"
#include <ios>

namespace kalingasan
{
    struct Point
    {
        int x_, y_;
    };

    std::istream& operator>>(std::istream& in, Point& point);
    bool operator==(const Point& a, const Point& b);
}

#endif
