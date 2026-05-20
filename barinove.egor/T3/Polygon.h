#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>


struct Point {
    int x, y;
};

struct Polygon {
    std::vector< Point > points;
};

double area(const Polygon& p);
bool operator==(const Polygon& a, const Polygon& b);
Polygon parsePolygon(const std::string& str);
std::vector<Polygon> readShapesFromFile(const std::string& filename);

#endif

