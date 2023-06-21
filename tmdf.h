//
// Created by lidia on 03.03.2023.
//

#include <string>
#include <list>
#include <map>

#ifndef TMDF_H
#define TMDF_H

namespace tmdf {
    const static unsigned int
    BYTE_TAG_TYPE = 1,
    SHORT_TAG_TYPE = 2,
    INT_TAG_TYPE = 3,
    LONG_TAG_TYPE = 4,
    FLOAT_TAG_TYPE = 5,
    DOUBLE_TAG_TYPE = 6,
    BOOL_TAG_TYPE = 7,
    STRING_UTF8_TAG_TYPE = 8,
    TAGLIST_TYPE = 9,
    TAGMAP_TYPE = 10,
    BYTE_ARRAY_TAG_TYPE = 11,
    SHORT_ARRAY_TAG_TYPE = 12,
    INT_ARRAY_TAG_TYPE = 13,
    LONG_ARRAY_TAG_TYPE = 14,
    FLOAT_ARRAY_TAG_TYPE = 15,
    DOUBLE_ARRAY_TAG_TYPE = 16,
    BOOL_ARRAY_TAG_TYPE = 17,
    TAG_ARRAY_TAG_TYPE = 18,
    STRING_UTF16_TAG_TYPE = 19,
    CHAR_ARRAY_TAG_TYPE = 20;

    struct tag_type {
        unsigned char typeID:7;
        unsigned char flag:1;
        tag_type(unsigned char typeID, bool flag) : typeID(typeID), flag(flag) {}
        signed char byte() {
            return *(signed char*)this;
        }
    };

    struct nothing;

    template<class T> class tag {
        const tag_type _type;
    protected:
        tag(unsigned char type, bool flag) :  _type(type, flag)  {

        }
    public:
        virtual T* value() = 0;

        T getValue() {
            return *value();
        }
        void setValue(T& value) {
            this->*value() = value;
        }

        unsigned char getType() {
            return _type.typeID;
        }
        bool flag() {
            return _type.flag;
        }
        virtual int size() = 0;
    };

    typedef tag<nothing> any_tag;



    class byte_tag final : public tag<signed char>{
        signed char _value;
    public:
        byte_tag(signed char value) : tag<signed char>(BYTE_TAG_TYPE,false) {
            _value = value;
        }
        signed char * value() override {
            return &_value;
        }
        int size() override {
            return 1;
        }
    };






}

#endif //TMDF_H