//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_ARRAY_TAG_H
#define TMDF_ARRAY_TAG_H

#include "tag.h"

namespace tmdf {
    /*
     * first 4 bytes - array length
     * elements must be found via [pointer+4 bytes]
     */
    template<typename T>
    class array_tag : public tag<T> {
    public:
        array_tag(unsigned char type, bool flag, int length, int lengthSize = 4) : tag<T>(type, flag, (T*)malloc(sizeof(T) * length + lengthSize))  {
            int size_in_bytes = sizeof(T)*length + lengthSize;
            ((int*)this->m_value)[0] = length;
            for (int i = 4; i < size_in_bytes; ++i) {
                ((char*)this->m_value)[i] = 0;
            }
        }
        int length() const {
            return ((int*)this->m_value)[0];
        }
        T& operator[](int index) {
            char* pointer0 = ((char*)this->m_value+lengthSize());//array length offset
            T* pointer = (T*)pointer0;
            return pointer[index];
        }
        int lengthSize() {
            if (this->getType() == BOOL_ARRAY_TAG_TYPE || this->getType() == TAG_ARRAY_TAG_TYPE || this->getType() == CHAR_ARRAY_TAG_TYPE) {
                return this->flag() ? 2 : 4;
            }
            return 4;
        }
    };
    template<typename T>
    static size_t sizeOfArrayTag(void* tag) {
        array_tag<T>& at = *(array_tag<T>*)tag;
        return at.length()*sizeof(T)+at.lengthSize();
    }


    class byte_array_tag : public array_tag<signed char> {
    public:
        byte_array_tag(int length) : array_tag<signed char>(BYTE_ARRAY_TAG_TYPE,false,length) {}
    };
    class unsigned_byte_array_tag : public array_tag<unsigned char> {
    public:
        unsigned_byte_array_tag(int length) : array_tag<unsigned char>(BYTE_ARRAY_TAG_TYPE,true,length) {}
    };

    class short_array_tag : public array_tag<short> {
    public:
        short_array_tag(int length) : array_tag<short>(SHORT_ARRAY_TAG_TYPE,false,length) {}
    };
    class unsigned_short_array_tag : public array_tag<unsigned short> {
    public:
        unsigned_short_array_tag(int length) : array_tag<unsigned short>(SHORT_ARRAY_TAG_TYPE,true,length) {}
    };

    class int_array_tag : public array_tag<int> {
    public:
        int_array_tag(int length) : array_tag<int>(INT_ARRAY_TAG_TYPE,false,length) {}
    };
    class unsigned_int_array_tag : public array_tag<unsigned int> {
    public:
        unsigned_int_array_tag(int length) : array_tag<unsigned int>(INT_ARRAY_TAG_TYPE,false,length) {}
    };
    class long_array_tag : public array_tag<long long> {
    public:
        long_array_tag(int length) : array_tag<long long>(LONG_ARRAY_TAG_TYPE,false,length) {}
    };
    class unsigned_long_array_tag : public array_tag<unsigned long long> {
    public:
        unsigned_long_array_tag(int length) : array_tag<unsigned long long>(LONG_ARRAY_TAG_TYPE,true,length) {}
    };

    class float_array_tag : public array_tag<float> {
    public:
        float_array_tag(int length) : array_tag<float>(FLOAT_ARRAY_TAG_TYPE,false,length) {}
    };
    class double_array_tag : public array_tag<double> {
    public:
        double_array_tag(int length) : array_tag<double>(DOUBLE_ARRAY_TAG_TYPE,false,length) {}
    };

    class bool_array_tag : public array_tag<bool> {
    public:
        bool_array_tag(int length) : array_tag<bool>(BOOL_ARRAY_TAG_TYPE,false,length) {}
    };
    class bool_s_array_tag : public array_tag<bool> {
    public:
        bool_s_array_tag(int length) : array_tag<bool>(BOOL_ARRAY_TAG_TYPE,true,length,2) {}
    };

    class tag_array : public array_tag<any_tag> {
    public:
        tag_array(int length) : array_tag<any_tag>(TAG_ARRAY_TAG_TYPE,false,length) {}
    };
    class tag_s_array : public array_tag<any_tag> {
    public:
        tag_s_array(int length) : array_tag<any_tag>(TAG_ARRAY_TAG_TYPE,true,length,2) {}
    };
    static size_t sizeOfTagArray(void* tag) {
        tag_array& iat = *(tag_array*)tag;
        int length = iat.lengthSize();
        for (int i = 0; i < iat.length(); ++i) {
            length += iat[i].tagSize((std::string&)"");
        }
        return length;
    }


    class char_array_tag : public array_tag<wchar_t> {
    public:
        char_array_tag(int length) : array_tag<wchar_t>(CHAR_ARRAY_TAG_TYPE,false,length) {}
    };
    class char_s_array_tag : public array_tag<wchar_t> {
    public:
        char_s_array_tag(int length) : array_tag<wchar_t>(CHAR_ARRAY_TAG_TYPE,true,length,2) {}
    };
}
#endif //TMDF_ARRAY_TAG_H
