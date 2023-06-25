//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_NUMERICAL_TAG_H
#define TMDF_NUMERICAL_TAG_H

#include <type_traits>
#include "tag.h"

namespace tmdf {

    template <
            typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    class numerical_tag : public tag<T> {
    protected:
        numerical_tag(unsigned char type, bool flag, T value) :  tag<T>(type,flag,value)  {}
    public:
        int intValue() {
            return (int)this->m_value;
        }
        long long longValue() {
            return (long long)this->m_value;
        }
        double doubleValue() {
            return (double)this->m_value;
        }
    };

    class byte_tag final : public numerical_tag<signed char> {
    public:
        byte_tag(signed char value) : numerical_tag<signed char>(BYTE_TAG_TYPE,false,value) {}
        byte_tag(int value) : byte_tag((signed char)value) {}
    };


    class unsigned_byte_tag final : public numerical_tag<unsigned char> {
    public:
        unsigned_byte_tag(unsigned char value) : numerical_tag<unsigned char>(BYTE_TAG_TYPE,true,value) {}
        unsigned_byte_tag(unsigned int value) : unsigned_byte_tag((unsigned char)value) {}
    };

    class short_tag final : public numerical_tag<signed short> {
    public:
        short_tag(signed short value) : numerical_tag<signed short>(SHORT_TAG_TYPE,false,value) {}
    };

    class unsigned_short_tag final : public numerical_tag<unsigned short> {
    public:
        unsigned_short_tag(unsigned short value) : numerical_tag<unsigned short>(SHORT_TAG_TYPE,true,value) {}
    };

    class int_tag final : public numerical_tag<int> {
    public:
        int_tag(int value) : numerical_tag<int>(INT_TAG_TYPE,false,value) {}
    };

    class unsigned_int_tag final : public numerical_tag<unsigned int> {
    public:
        unsigned_int_tag(unsigned int value) : numerical_tag<unsigned int>(LONG_TAG_TYPE,true,value) {}
    };


    class long_tag final : public numerical_tag<long long> {
    public:
        long_tag(long long value) : numerical_tag<long long>(INT_TAG_TYPE,false,value) {}
    };

    class unsigned_long_tag final : public numerical_tag<unsigned long long> {
    public:
        unsigned_long_tag(unsigned long long value) : numerical_tag<unsigned long long>(LONG_TAG_TYPE,true,value) {}
    };


    class float_tag final : public numerical_tag<float> {
    public:
        float_tag(float value) : numerical_tag<float>(FLOAT_TAG_TYPE,false,value) {}
    };

    class double_tag final : public numerical_tag<double> {
    public:
        double_tag(double value) : numerical_tag<double>(DOUBLE_TAG_TYPE,false,value) {}
    };
}
#endif //TMDF_NUMERICAL_TAG_H
