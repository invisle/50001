#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <sstream>
#include <numeric>
#include "Point.hpp"

namespace kalingasan
{
    struct Polygon
    {
        std::vector<Point> points_;
    };

    std::istream& operator>>(std::istream& in, Polygon& polygon);
    bool operator==(const Polygon& a, const Polygon& b);
    double area(const Polygon& polygon);
}

#endif
