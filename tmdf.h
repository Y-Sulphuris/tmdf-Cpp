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




    template<class T> class tag;

    struct nothing{
        static nothing& get() {

        }
    };

    typedef tag<nothing> any_tag;

    template<class T>
    static size_t sizeOfT(void* tag) {
        return sizeof(T);
    }
    static size_t zero(void* tag) {
        return 0;
    }
    static size_t sizeOfStringUTF8Tag(void* tag);
    static size_t sizeOfStringURF16Tag(void* tag);

    static size_t (*sizeOfTag[20])(void* tag) = {
            &sizeOfT<char>,
            &sizeOfT<short>,
            &sizeOfT<int>,
            &sizeOfT<long long>,
            &sizeOfT<float>,
            &sizeOfT<double>,
            &zero,
            &sizeOfStringUTF8Tag,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
    };



    struct tag_type {
        unsigned char typeID:7;
        unsigned char flag:1;
        tag_type(unsigned char typeID, bool flag) : typeID(typeID), flag(flag) {}
        signed char byte() {
            return *(signed char*)this;
        }
    };


    template<class T> class tag {
        const tag_type m_type;
    protected:
        T* m_value;
        tag(unsigned char type, bool flag, T& value) : m_type(type, flag), m_value((T*)malloc(sizeof(value))) {

        }

    public:
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
        inline int payloadSize() {
            return sizeOfTag[getType()-1](this);
        }

        inline operator T() const {
            return m_value;
        }
    };






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



    class bool_tag final : public tag<bool> {
    public:
        bool_tag(bool value) : tag<bool>(BOOL_TAG_TYPE,false,value) {}

        inline bool operator and(bool_tag other) {
            return m_value and other.m_value;
        }
        inline bool operator or(bool_tag other) {
            return m_value or other.m_value;
        }
        inline bool operator xor(bool_tag other) {
            return m_value xor other.m_value;
        }
        inline bool_tag operator not() {
            return {not m_value};
        }
    };

    class string_utf8_tag final : public tag<std::string> {
    public:
        string_utf8_tag(std::string& value) : tag<std::string>(STRING_UTF8_TAG_TYPE,false,value) {}
    };

    static size_t sizeOfStringUTF8Tag(void* t) {
        auto* tag = (string_utf8_tag*)t;
        return (int)tag->getValue().length();
    }

    template<class T>
    class collection_tag : public tag<T> {
    protected:
        collection_tag(unsigned char type, bool flag, T& value) : tag<T>(type,flag,value)  {}
    public:
        virtual inline size_t size() const noexcept = 0;
        virtual inline bool empty() const noexcept = 0;
        virtual inline void clear() noexcept = 0;
    };

    class taglist final : public collection_tag<std::list<any_tag>> {
    public:
        taglist(std::list<any_tag>& value) : collection_tag<std::list<any_tag>>(TAGLIST_TYPE,false,value) {}
        [[nodiscard]] inline size_t size() const noexcept override {
            return m_value.size();
        }
        [[nodiscard]] inline bool empty() const noexcept override {
            return m_value.empty();
        }
        inline void clear() noexcept override {
            return m_value.clear();
        }
        inline void add(any_tag& element) {
            return push_front(element);
        }/*
        void remove(const any_tag& element) {
            m_value.remove(element);
        }*/
        inline void push_front(any_tag& element) {
            return m_value.push_front(element);
        }
        inline void push_front(any_tag&& element) {
            return m_value.push_front(element);
        }
        inline void push_back(any_tag& element) {
            return m_value.push_back(element);
        }
        inline void push_back(any_tag&& element) {
            return m_value.push_back(element);
        }
        inline void pop_front() {
            return m_value.pop_front();
        }
        inline void pop_back() {
            return m_value.pop_back();
        }
    };

class tagmap final : public tag<std::map<std::string, any_tag>> {
    public:
        tagmap(std::map<std::string, any_tag>& value) : tag<std::map<std::string, any_tag>>(TAGMAP_TYPE,false,value) {}
        [[nodiscard]] inline size_t size() const noexcept{
            return m_value.size();
        }
        inline bool empty() const noexcept{
            return m_value.empty();
        }
        inline void clear() noexcept {
            return m_value.clear();
        }
        any_tag& operator[](const std::string& str) {
            return m_value[str];
        }
    };
}

#endif //TMDF_H