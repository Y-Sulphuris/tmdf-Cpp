#include <iostream>
#include "tmdf.h"



using std::cout;
using std::endl;

using namespace tmdf;

int main() {
	static_assert(sizeof(char) == 1);
	static_assert(sizeof(short) == 2);
	static_assert(sizeof(int) == 4);
    static_assert(sizeof(long long) == 8);
    static_assert(sizeof(float) == 4);
    static_assert(sizeof(double) == 8);
    static_assert(sizeof(long double) == 16);


    static_assert(sizeof(tag_type) == 1);
    static_assert(sizeof(tag<std::any>) == 16);
    static_assert(sizeof(tag<void*>) == 16);
    static_assert(sizeof(any_tag) == 16);
    static_assert(sizeof(byte_tag) == 16);
    static_assert(sizeof(short_tag) == 16);
    static_assert(sizeof(int_tag) == 16);
    static_assert(sizeof(long_tag) == 16);
    static_assert(sizeof(float_tag) == 16);
    static_assert(sizeof(double_tag) == 16);
    static_assert(sizeof(bool_tag) == 16);
    static_assert(sizeof(taglist) == 16);
    static_assert(sizeof(tagmap) == 16);
    return 0;
}