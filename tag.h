//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_TAG_H
#define TMDF_TAG_H


#include "tmdfUtils.h"

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
    union tag_type {
        struct {
            unsigned char typeID:7;
            unsigned char flag:1;
        };
        signed char byte;
        tag_type(unsigned char typeID, bool flag) : typeID(typeID), flag(flag) {}
    };

    template<class T> class tag {
        tag_type m_type;
    protected:
        T* m_value;
        tag(unsigned char type, bool flag, T& value) : m_type(type, flag), m_value((T*)malloc(sizeof(value))) {
            *m_value = value;
        }
        tag(unsigned char type, bool flag, T* value) : m_type(type, flag), m_value(value) {
            m_value = value;
        }
        tag(unsigned char type, bool flag) : m_type(type, flag), m_value(nullptr) {}
    public:
        ~tag() {
            if(m_value != nullptr) free(m_value);
        }
        inline T* value() {
            return m_value;
        };

        [[nodiscard]] inline T getValue() const {
            return *m_value;
        }

        inline void setValue(T& value) {
            *m_value = value;
        }

        /*
        tag& operator=(T& value) {
            setValue(value);
        }*/

        inline unsigned char getType() {
            return m_type.typeID;
        }
        inline bool flag() {
            return m_type.flag;
        }
        int tagSize(std::string& name) {
            return 1 + sizeOfTmdfString(name) + payloadSize();
        }
        inline int payloadSize() {
            return sizeOfTag[getType()-1](this);
        }

        //inline operator T() const {
        //    return m_value;
        //}
        //inline operator T&() const {
        //    return m_value;
        //}
    };



    class any_tag final : public tag<typeof(nullptr)> {
    public:
        any_tag() : tag(0,false) {}
    };

}
#endif //TMDF_TAG_H
