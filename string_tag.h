//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_STRING_TAG_H
#define TMDF_STRING_TAG_H

#include <string>
#include "tag.h"
#include "tmdf.h"

namespace tmdf {


    class string_utf8_tag final : public tag<std::string> {
    public:
        string_utf8_tag(std::string& value) : tag<std::string>(STRING_UTF8_TAG_TYPE,false,value) {}
    };
    static size_t sizeOfStringUTF8Tag(void* t) {
        auto* tag = (string_utf8_tag*)t;
        return (int)tag->getValue().length()+1;
    }

    class string_utf16_tag : public tag<std::wstring> {
    public:
        string_utf16_tag(std::wstring& str) : tag<std::wstring>(STRING_UTF16_TAG_TYPE,false,str) {}
    };
    static size_t sizeOfStringUTF16Tag(void* t) {
        auto* tag = (string_utf16_tag*)t;
        return (int)(tag->getValue().length() << 1)+2;
    }
}
#endif //TMDF_STRING_TAG_H
