#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include "IOTypes.hpp"

namespace kalingasan
{
    struct DataStruct
    {
        long long key1;
        std::complex<double> key2;
        std::string key3;
    };
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
    bool operator<(DataStruct& first, DataStruct second);
}

#endif
