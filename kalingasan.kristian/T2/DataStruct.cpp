#include "DataStruct.hpp"

namespace kalingasan
{

    //std::istream& operator>>(std::istream& in, LabelIO&& dest)
    //{
    //    std::istream::sentry sentry(in);
    //    if (!sentry)
    //    {
    //        return in;
    //    }
    //    std::string label = "";
    //    if ((in >> label) && (label != dest.exp))
    //    {
    //        in.setstate(std::ios::failbit);
    //    }
    //    return in;
    //}

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        iofmtguard fmtguard(in);
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
        in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
        while (in && !(hasKey1 && hasKey2 && hasKey3))
        {
            std::string keyNumber;
            in >> KeyIO{ keyNumber };
            if (keyNumber == "key1" && !hasKey1)
            {
                in >> LongLongIO{ input.key1 };
                hasKey1 = in ? true : false;
            }
            else if (keyNumber == "key2" && !hasKey2)
            {
                in >> ComplexIO{ input.key2 };
                hasKey2 = in ? true : false;
            }
            else if (keyNumber == "key3" && !hasKey3)
            {
                in >> StringIO{ input.key3 };
                hasKey3 = in ? true : false;
            }
            else
            {
                in.setstate(std::ios::failbit);
            }
            in >> DelimiterIO{ ':' };
        }
        if (in >> DelimiterIO{ ')' } && in && hasKey1 && hasKey2 && hasKey3)
        {
            dest = std::move(input);
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        //(:key1 10ll:key2 #c(1.0 -1.0):key3 "Data":)
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 " << src.key1 << "ll:key2 #c(";
        out << std::fixed << std::setprecision(1) << src.key2.real() << ' ' << src.key2.imag();
        out << "):key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool operator<(DataStruct& first, DataStruct second)
    {
        if (first.key1 != second.key1)
        {
            return first.key1 < second.key1;
        }
        double firstComplex = std::abs(first.key2);
        double secondComplex = std::abs(second.key2);
        if (firstComplex != secondComplex)
        {
            return firstComplex < secondComplex;
        }
        return first.key3.size() < second.key3.size();
    }
}
