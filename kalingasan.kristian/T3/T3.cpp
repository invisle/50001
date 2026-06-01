#include <fstream>
#include "commands.hpp"
#include "Polygon.hpp"

int main(int argc, char* argv[])
{
    try
    {
        using namespace kalingasan;
        if (argc != 2)
        {
            std::cerr << "Wrong amount of parameters" << std::endl;
            return 1;
        }
        std::ifstream input(argv[1]);
        if (!input.is_open())
        {
            std::cerr << "Cannot open file: " << argv[1] << std::endl;
            return 1;
        }
        std::vector<Polygon> polygons;
        std::string line;
        while (std::getline(input, line))
        {
            if (line.empty())
            {
                continue;
            }
            std::istringstream iss(line);
            Polygon polygon;
            iss >> polygon;
            Polygon empty;
            if (!(polygon == empty))
            {
                polygons.push_back(polygon);
            }
        }

        std::string commandLine;
        while (std::getline(std::cin, commandLine))
        {
            if (commandLine.empty())
            {
                continue;
            }
            std::istringstream iss(commandLine);
            std::string command;
            iss >> command;
            if (command.empty())
            {
                continue;
            }
            std::transform(command.begin(), command.end(), command.begin(), static_cast<int(*)(int)>(std::toupper));
            if (command == "AREA")
            {
                handleArea(polygons, iss);
            }
            else if (command == "MAX")
            {
                handleMaximum(polygons, iss);
            }
            else if (command == "MIN")
            {
                handleMinimum(polygons, iss);
            }
            else if (command == "COUNT")
            {
                handleCount(polygons, iss);
            }
            else if (command == "RMECHO")
            {
                handleRmecho(polygons, iss);
            }
            else if (command == "INTERSECTIONS")
            {
                handleIntersections(polygons, iss);
            }
            else
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << ba.what() << std::endl;
        return -1;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 2;
    }
}
