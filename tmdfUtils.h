//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_TMDFUTILS_H
#define TMDF_TMDFUTILS_H

#include <string>
#include <cstdlib>

namespace tmdf {
    size_t sizeOfTmdfString(const std::string& str) {
        return 1 + str.length();
    }

    template<class T>
    static size_t sizeOfT(void* tag) {
        return sizeof(T);
    }
    static size_t zero(void* tag) {
        return 0;
    }
    static size_t sizeOfStringUTF8Tag(void* tag);
    static size_t sizeOfStringUTF16Tag(void* tag);
    static size_t sizeOfTagList(void* tag);
    static size_t sizeOfTagMap(void* tag);
    template<typename T>
    static size_t sizeOfArrayTag(void* tag);
    static size_t sizeOfBoolArrayTag(void* tag);
    static size_t sizeOfTagArray(void* tag);

    static size_t (*sizeOfTag[20])(void* tag) = {//[i]+1 = type
            &sizeOfT<char>,
            &sizeOfT<short>,
            &sizeOfT<int>,
            &sizeOfT<long long>,
            &sizeOfT<float>,
            &sizeOfT<double>,
            &zero,
            &sizeOfStringUTF8Tag,
            &sizeOfTagList,
            &sizeOfTagMap,
            &sizeOfArrayTag<char>,
            &sizeOfArrayTag<short>,
            &sizeOfArrayTag<int>,
            &sizeOfArrayTag<long long>,
            &sizeOfArrayTag<float>,
            &sizeOfArrayTag<double>,
            &sizeOfBoolArrayTag,
            &sizeOfTagArray,
            nullptr,
            nullptr,
    };
}
#endif //TMDF_TMDFUTILS_H
