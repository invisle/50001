#include "IOTypes.hpp"

namespace kalingasan
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        iofmtguard fmtguard(in);
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
        iofmtguard fmtguard(in);
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        long long key;
        in >> key;
        if (!in)
        {
            return in;
        }
        if (in.peek() == 'l' || in.peek() == 'L')
        {
            in.get();
            if (in.peek() == 'l' || in.peek() == 'L')
            {
                in.get();
            }
            else
            {
                in.setstate(std::ios::failbit);
            }
        }
        dest.ref = key;
        return in;
    }

    std::istream& operator>>(std::istream& in, ComplexIO&& dest)
    {
        iofmtguard fmtguard(in);
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' };
        double real, imaginary;
        in >> real >> imaginary >> DelimiterIO{ ')' };
        if (in)
        {
            dest.ref = std::complex<double>(real, imaginary);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        iofmtguard fmtguard(in);
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, KeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string key;
        in >> key;
        if (in)
        {
            dest.ref = key;
        }
        bool isCorrect = dest.ref == "key1" || dest.ref == "key2" || dest.ref == "key3";
        if (!isCorrect)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}
