//
// Created by lidia on 25.06.2023.
//

#ifndef TMDF_COLLECTION_TAG_H
#define TMDF_COLLECTION_TAG_H

#include <cstddef>
#include <list>
#include "tag.h"

namespace tmdf {
    template<class T>
    class collection_tag : public tag<T> {
    protected:
        collection_tag(unsigned char type, bool flag, T& value) : tag<T>(type,flag,value)  {}
    public:
        inline size_t size() const noexcept {
            switch (this->getType()) {
                case TAGLIST_TYPE:
                    return ((std::list<any_tag>*)this->m_value)->size();
                case TAGMAP_TYPE:
                    return ((std::map<std::string,any_tag>*)this->m_value)->size();
            }
        }
        inline bool empty() const noexcept {
            switch (this->getType()) {
                case TAGLIST_TYPE:
                    return ((std::list<any_tag>*)this->m_value)->empty();
                case TAGMAP_TYPE:
                    return ((std::map<std::string,any_tag>*)this->m_value)->empty();
            }
        }
        inline void clear() noexcept {
            switch (this->getType()) {
                case TAGLIST_TYPE:
                    return ((std::list<any_tag>*)this->m_value)->clear();
                case TAGMAP_TYPE:
                    return ((std::map<std::string,any_tag>*)this->m_value)->clear();
            }
        }
    };

    class taglist final : public collection_tag<std::list<any_tag>> {
    public:
        taglist(std::list<any_tag>& value) : collection_tag<std::list<any_tag>>(TAGLIST_TYPE,false,value) {}
        inline void add(any_tag& element) {
            return push_front(element);
        }/*
        void remove(const any_tag& element) {
            m_value.remove(element);
        }*/
        inline void push_front(any_tag& element) {
            return m_value->push_front(element);
        }
        inline void push_front(any_tag&& element) {
            return m_value->push_front(element);
        }
        inline void push_back(any_tag& element) {
            return m_value->push_back(element);
        }
        inline void push_back(any_tag&& element) {
            return m_value->push_back(element);
        }
        inline void pop_front() {
            return m_value->pop_front();
        }
        inline void pop_back() {
            return m_value->pop_back();
        }
        inline std::list<any_tag>::iterator begin() {
            return m_value->begin();
        }
        inline std::list<any_tag>::iterator end() {
            return m_value->end();
        }

        };
        static size_t sizeOfTagList(void* tag) {
            taglist& tl = *(taglist*)tag;
            size_t size = 1;
            for (any_tag& element : tl) {
                size+=element.payloadSize()+1;
            }
            return size;
        }
        class tagmap final : public tag<std::map<std::string, any_tag>> {
        public:
        tagmap(std::map<std::string, any_tag>& value) : tag<std::map<std::string, any_tag>>(TAGMAP_TYPE,false,value) {}
        inline any_tag& operator[](const std::string& str) {
            return m_value->operator[](str);
        }
        inline any_tag& operator[](const std::string&& str) {
            return m_value->operator[](str);
        }
        inline std::map<std::string, any_tag>::iterator begin(){
            return m_value->begin();
        };
        inline std::map<std::string, any_tag>::iterator end(){
            return m_value->end();
        };
        };
        static size_t sizeOfTagMap(void* tag) {
            tagmap& tm = *(tagmap*)tag;
            size_t size = 1;
            for (auto entry : tm) {
                size += (sizeOfTmdfString(entry.first) + entry.second.payloadSize()+1/*header*/);
            }
            return size;
        }
}
#endif //TMDF_COLLECTION_TAG_H
