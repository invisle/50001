#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"
#include <algorithm>
#include <iomanip>
#include <functional>


namespace kalingasan
{
	bool isEven(const Polygon& polygon);
    bool isOdd(const Polygon& polygon);
    bool parsePolygonFromString(const std::string& str, Polygon& out);
    int orientation(const Point& a, const Point& b, const Point& c);
    bool onSegment(const Point& p, const Point& a, const Point& b);
    bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d);
    bool polygonsIntersect(const Polygon& a, const Polygon& b);
    bool pointInPolygon(const Point& p, const Polygon& poly);

	bool handleArea(const std::vector<Polygon>& polygons, std::istringstream& iss);
	bool handleMaximum(const std::vector<Polygon>& polygons, std::istringstream& iss);
    bool handleMinimum(const std::vector<Polygon>& polygons, std::istringstream& iss);
    bool handleCount(const std::vector<Polygon>& polygons, std::istringstream& iss);
    bool handleRmecho(std::vector<Polygon>& polygons, std::istringstream& iss);
    bool handleIntersections(const std::vector<Polygon>& polygons, std::istringstream& iss);

    struct AreaCompare
    {
        bool operator()(const Polygon& a, const Polygon& b) const
        {
            return area(a) < area(b);
        }
    };
    struct VertexCountCompare
    {
        bool operator()(const Polygon& a, const Polygon& b) const
        {
            return a.points_.size() < b.points_.size();
        }
    };
    struct VertexCountEqual
    {
        size_t target;
        bool operator()(const Polygon& polygon) const
        {
            return polygon.points_.size() == target;
        }
    };
    constexpr const char* ERROR = "<INVALID COMMAND>";
}

#endif
