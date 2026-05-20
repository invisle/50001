#include "commands.hpp"
namespace kalingasan
{
    using namespace std::placeholders;
    bool isEven(const Polygon& polygon)
    {
        return polygon.points_.size() % 2 == 0;
    }
    bool isOdd(const Polygon& polygon)
    {
        return polygon.points_.size() % 2 == 1;
    }
    bool parsePolygonFromString(const std::string& str, Polygon& out)
    {
        std::istringstream iss(str);
        if (iss >> out)
        {
            return true;
        }
        return false;
    }
    int orientation(const Point& a, const Point& b, const Point& c)
    {
        long long val = static_cast<long long>(b.y_ - a.y_) * (c.x_ - b.x_) -
            static_cast<long long>(b.x_ - a.x_) * (c.y_ - b.y_);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
    }
    bool onSegment(const Point& p, const Point& a, const Point& b)
    {
        return std::min(a.x_, b.x_) <= p.x_ && p.x_ <= std::max(a.x_, b.x_) &&
            std::min(a.y_, b.y_) <= p.y_ && p.y_ <= std::max(a.y_, b.y_);
    }
    bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d)
    {
        int o1 = orientation(a, b, c);
        int o2 = orientation(a, b, d);
        int o3 = orientation(c, d, a);
        int o4 = orientation(c, d, b);

        if (o1 != o2 && o3 != o4)
        {
            return true;
        }
        if (o1 == 0 && onSegment(c, a, b))
        {
            return true;
        }
        if (o2 == 0 && onSegment(d, a, b))
        {
            return true;
        }
        if (o3 == 0 && onSegment(a, c, d))
        {
            return true;
        }
        if (o4 == 0 && onSegment(b, c, d))
        {
            return true;
        }
        return false;
    }
    bool pointInPolygon(const Point& point, const Polygon& polygon)
    {
        const auto& points = polygon.points_;
        if (points.size() < 3) return false;

        int count = 0;
        for (size_t i = 0; i < points.size(); ++i)
        {
            const Point& a = points[i];
            const Point& b = points[(i + 1) % points.size()];
            if (onSegment(point, a, b))
            {
                return true;
            }
            if ((a.y_ > point.y_) != (b.y_ > point.y_))
            {
                long long xIntersect = static_cast<long long>(a.x_) +
                    static_cast<long long>(point.y_ - a.y_) *
                    static_cast<long long>(b.x_ - a.x_) /
                    static_cast<long long>(b.y_ - a.y_);
                if (xIntersect > point.x_)
                {
                    ++count;
                }
            }
        }
        return count % 2 == 1;
    }
    bool polygonsIntersect(const Polygon& a, const Polygon& b)
    {
        for (size_t i = 0; i < a.points_.size(); ++i)
        {
            const Point& a1 = a.points_[i];
            const Point& a2 = a.points_[(i + 1) % a.points_.size()];
            for (size_t j = 0; j < b.points_.size(); ++j)
            {
                const Point& b1 = b.points_[j];
                const Point& b2 = b.points_[(j + 1) % b.points_.size()];
                if (segmentsIntersect(a1, a2, b1, b2))
                {
                    return true;
                }
            }
        }
        if (std::any_of(b.points_.begin(), b.points_.end(),
            [&a](const Point& p) { return pointInPolygon(p, a); }))
        {
            return true;
        }
        if (std::any_of(a.points_.begin(), a.points_.end(),
            [&b](const Point& p) { return pointInPolygon(p, b); }))
        {
            return true;
        }
        return false;
    }
<<<<<<< HEAD
<<<<<<< HEAD
	bool handleArea(const std::vector<Polygon>& polygons, std::istringstream& iss)
	{
		std::string argument;
		iss >> argument;
		double result = 0.0;
		if (argument.empty())
		{
			return false;
		}
		else if (argument == "EVEN")
		{
			result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
				[](double sum, const Polygon& polygon) {
					return sum + (isEven(polygon) ? area(polygon) : 0);
				});
			std::cout << std::fixed << std::setprecision(1) << result << std::endl;
		}
		else if (argument == "ODD")
		{
			result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
				[](double sum, const Polygon& polygon) {
					return sum + (isEven(polygon) ? 0 : area(polygon));
				});
			std::cout << std::fixed << std::setprecision(1) << result << std::endl;
		}
		else if (argument == "MEAN")
		{
			if (polygons.empty())
			{
				return false;
			}
			result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
				[](double acc, const Polygon& p) { return acc + area(p); });
			std::cout << std::fixed << std::setprecision(1) << result / polygons.size() << std::endl;
		}
		else
		{
			size_t vertexCount;
			try {
				vertexCount = std::stoul(argument);
			}
			catch (...) {
				std::cout << ERROR << std::endl;
				return false;
			}
			result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
				[vertexCount](double sum, const Polygon& polygon) {
					return sum + (polygon.points_.size() == vertexCount ? area(polygon) : 0.0);
				});
			std::cout << std::fixed << std::setprecision(1) << result << std::endl;
		}
        return true;
	}
=======
=======
>>>>>>> 0ef85294869605476a6f2aec621b1b257d3e3684
    bool handleArea(const std::vector<Polygon>& polygons, std::istringstream& iss)
    {
        std::string argument;
        iss >> argument;
        double result = 0.0;

        if (argument.empty())
        {
            return false;
        }
        else if (argument == "EVEN")
        {
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double sum, const Polygon& polygon) {
                    return sum + (isEven(polygon) ? area(polygon) : 0.0);
                });
            std::cout << std::fixed << std::setprecision(1) << result << std::endl;
        }
        else if (argument == "ODD")
        {
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double sum, const Polygon& polygon) {
                    return sum + (isEven(polygon) ? 0.0 : area(polygon));
                });
            std::cout << std::fixed << std::setprecision(1) << result << std::endl;
        }
        else if (argument == "MEAN")
        {
            if (polygons.empty())
            {
                return false;
            }
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) { return acc + area(p); });
            std::cout << std::fixed << std::setprecision(1) << result / polygons.size() << std::endl;
        }
        else
        {
            size_t vertexCount;
            try {
                vertexCount = std::stoul(argument);
            }
            catch (...) {
                std::cout << ERROR << std::endl;
                return false;
            }
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [vertexCount](double sum, const Polygon& polygon) {
                    return sum + (polygon.points_.size() == vertexCount ? area(polygon) : 0.0);
                });
            std::cout << std::fixed << std::setprecision(1) << result << std::endl;
        }
        return true;
    }
<<<<<<< HEAD
>>>>>>> 46779e6045f8cade9cb5bf9d950e0a5c5f6c92fa
=======
>>>>>>> 0ef85294869605476a6f2aec621b1b257d3e3684
    bool handleMaximum(const std::vector<Polygon>& polygons, std::istringstream& iss)
    {
        std::string argument;
        iss >> argument;
        if (argument.empty() || polygons.empty())
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        if (argument == "AREA")
        {
            auto max = std::max_element(polygons.begin(), polygons.end(), AreaCompare());
            std::cout << std::fixed << std::setprecision(1) << area(*max) << std::endl;
        }
        else if (argument == "VERTEXES")
        {
            auto max = std::max_element(polygons.begin(), polygons.end(), VertexCountCompare());
            std::cout << max->points_.size() << std::endl;
        }
        else
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        return true;
    }
    bool handleMinimum(const std::vector<Polygon>& polygons, std::istringstream& iss)
    {
        std::string argument;
        iss >> argument;
        if (argument.empty() || polygons.empty())
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        if (argument == "AREA")
        {
            auto min = std::min_element(polygons.begin(), polygons.end(), AreaCompare());
            std::cout << std::fixed << std::setprecision(1) << area(*min) << std::endl;
        }
        else if (argument == "VERTEXES")
        {
            auto min = std::min_element(polygons.begin(), polygons.end(), VertexCountCompare());
            std::cout << min->points_.size() << std::endl;
        }
        else
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        return true;
    }
    bool handleCount(const std::vector<Polygon>& polygons, std::istringstream& iss)
    {
        std::string argument;
        iss >> argument;
        if (argument.empty())
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        size_t count;
        if (argument == "EVEN")
        {
            count = std::count_if(polygons.begin(), polygons.end(),
                std::bind(isEven, std::placeholders::_1));
            std::cout << count << std::endl;
        }
        else if (argument == "ODD")
        {
            count = std::count_if(polygons.begin(), polygons.end(),
                std::bind(isOdd, std::placeholders::_1));
            std::cout << count << std::endl;
        }
        else
        {
            size_t vertexCount;
            try {
                vertexCount = std::stoul(argument);
            }
            catch (...) {
                std::cout << ERROR << std::endl;
                return false;
            }
            count = std::count_if(polygons.begin(), polygons.end(),
                VertexCountEqual{ vertexCount });
            std::cout << count << std::endl;
        }
        return true;
    }
    bool handleRmecho(std::vector<Polygon>& polygons, std::istringstream& iss)
    {
        std::string rest;
        std::getline(iss, rest);
        Polygon target;
        if (!parsePolygonFromString(rest, target))
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        size_t oldSize = polygons.size();
        auto newEnd = std::unique(polygons.begin(), polygons.end(),
            [&target](const Polygon& a, const Polygon& b) {
                return a == target && b == target;
            });
        polygons.erase(newEnd, polygons.end());
        std::cout << (oldSize - polygons.size()) << std::endl;
        return true;
    }
    bool handleIntersections(const std::vector<Polygon>& polygons, std::istringstream& iss)
    {
        std::string rest;
        std::getline(iss, rest);
        Polygon target;
        if (!parsePolygonFromString(rest, target))
        {
            std::cout << ERROR << std::endl;
            return false;
        }
        size_t cnt = std::count_if(polygons.begin(), polygons.end(),
            [&target](const Polygon& p) {
                return polygonsIntersect(p, target);
            });
        std::cout << cnt << std::endl;
        return true;
    }
}
