//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_BOOL_TAG_H
#define TMDF_BOOL_TAG_H

#include "tag.h"

namespace tmdf {
    class bool_tag final : public tag<bool> {
    public:
        bool_tag(bool value) : tag<bool>(BOOL_TAG_TYPE,false,value) {}

        inline bool operator and(const bool_tag& other) const {
            return *m_value and *other.m_value;
        }
        inline bool operator or(const bool_tag& other) const {
            return *m_value or *other.m_value;
        }
        inline bool operator xor(const bool_tag& other) const {
            return *m_value xor *other.m_value;
        }
        inline bool operator not() const {
            return not m_value;
        }
    };
}
#endif //TMDF_BOOL_TAG_H
