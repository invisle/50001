#ifndef IO_TYPES_HPP
#define IO_TYPES_HPP

#include <iostream>

namespace kalingasan
{
    struct DelimeterIO
    {
        char exp;
    };
    std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
}

#endif
