#include <iostream>
#include <bitset>
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

    static_assert(sizeof(byte_tag) == 2);
    static_assert(sizeof(short_tag) == 4);
    static_assert(sizeof(int_tag) == 8);
    static_assert(sizeof(long_tag) == 16);
    static_assert(sizeof(float_tag) == 8);
    static_assert(sizeof(double_tag) == 16);

	static_assert(sizeof(tmdf::tagHeader) == 1);


	tmdf::tagHeader h = tmdf::tagHeader(1);
    h.flag = true;
	cout << std::bitset<CHAR_BIT>(((char*)&h)[0]) << endl;
    cout << (int)((unsigned char*)&h)[0] << endl;




    tmdf::byte_tag byte;

    cout << "flag:" << byte.getFlag() << endl;




}
