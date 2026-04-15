#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "DataStruct.hpp"

int main()
{
    using kalingasan::DataStruct;
    std::vector<DataStruct> data;
    //std::istringstream iss("(:key1 10ull:key2 #c(1.0 -1.0):key3 \"Data\":)");
    while (!std::cin.eof())
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
        if (!std::cin.eof() && std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(data.begin(), data.end());
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout)
    );
}
