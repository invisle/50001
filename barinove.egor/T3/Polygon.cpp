#include "Polygon.h"
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include <fstream>

double area(const Polygon& p) {
    const auto& pts = p.points;
    const size_t n = pts.size();
    if (n < 3) {
        return 0.0;
    }

    double sum = 0;
    for (size_t i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        sum += pts[i].x * pts[j].y;
        sum -= pts[i].y * pts[j].x;
    }

    return std::abs(sum)/2;
}

bool operator==(const Polygon& a, const Polygon& b) {
    return (a.points.size() == b.points.size()) &&
        std::equal(a.points.begin(), a.points.end(),
            b.points.begin(),
            [](const Point& p1, const Point& p2) {
                return p1.x == p2.x && p1.y == p2.y;
            });
}

Polygon parsePolygon(const std::string& str) {
    std::istringstream iss(str);
    int n;
    iss >> n;
    if (iss.fail()) throw std::runtime_error("Invalid format");
    if (n < 3) throw std::runtime_error("Polygon must have at least 3 vertices");

    Polygon p;
    std::generate_n(std::back_inserter(p.points), n, [&iss]() {
        char open, sep, close;
        int x, y;
        iss >> open >> x >> sep >> y >> close;
        if (iss.fail() || open != '(' || sep != ';' || close != ')') {
            throw std::runtime_error("Invalid vertex");
        }
        return Point{ x, y };
        });

    char leftover;
    if (iss >> leftover) {
        throw std::runtime_error("Extra characters after polygon");
    }

    return p;
}

std::vector<Polygon> readShapesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<Polygon> result;
    std::string line;
    while (std::getline(file, line)) {
        try {
            result.push_back(parsePolygon(line));
        }
        catch (...) {}
    }

    return result;
}

