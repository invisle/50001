#ifndef IO_TYPES_HPP
#define IO_TYPES_HPP

#include "Iofmtguard.hpp"
#include <complex>

namespace kalingasan
{
    struct DelimiterIO
    {
        char exp;
    };
    struct LongLongIO
    {
        long long& ref;
    };
    struct ComplexIO
    {
        std::complex<double>& ref;
    };
    struct StringIO
    {
        std::string& ref;
    };
    struct KeyIO
    {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    std::istream& operator>>(std::istream& in, ComplexIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, KeyIO&& dest);
}

#endif
