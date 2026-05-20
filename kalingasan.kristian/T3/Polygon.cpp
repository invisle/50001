#include "Polygon.hpp"

namespace kalingasan
{
    std::istream& operator>>(std::istream& in, Polygon& polygon)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        size_t vertexCount;
        if (!(in >> vertexCount))
        {
            return in;
        }
        if (vertexCount < 3)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::vector<Point> points;
        points.reserve(vertexCount);
        for (size_t i = 0; i < vertexCount; i++)
        {
            Point point;
            if (!(in >> point))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            points.push_back(point);
        }
        in >> std::ws;
        if (in.peek() != EOF)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        polygon.points_ = std::move(points);
        return in;
    }

    double area(const Polygon& polygon)
    {
        const auto& points = polygon.points_;
        if (points.size() < 3)
        {
            return 0.0;
        }
        double sum = std::inner_product(points.begin(),
            points.end() - 1,
            points.begin() + 1, 0.0,
            std::plus<>(),
            [](const Point& a, const Point& b) { return static_cast<double>(a.x_ * b.y_ - a.y_ * b.x_); });
        sum += static_cast<double>(points.back().x_ * points.front().y_ - points.back().y_ * points.front().x_);
        return abs(sum) / 2.0;
    }
    bool operator==(const Polygon& a, const Polygon& b)
    {
        return a.points_ == b.points_;
    }
}
