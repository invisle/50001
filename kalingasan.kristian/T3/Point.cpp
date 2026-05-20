#include "Point.hpp"

namespace kalingasan
{
    std::istream& operator>>(std::istream& in, Point& point)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> DelimeterIO{ '(' };
        int x, y;
        in >> x >> DelimeterIO{ ';' } >> y >> DelimeterIO{ ')' };
        if (in)
        {
            point.x_ = x;
            point.y_ = y;
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    bool operator==(const Point& a, const Point& b)
    {
        return a.x_ == b.x_ && a.y_ == b.y_;
    }
}
