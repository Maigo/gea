#pragma once

// header include
#include "string_parser.h"

// std includes
#include <stdlib.h>

// gea includes
#include <gea/core/string/string_builder.h>

namespace gea {

// ------------------------------------------------------------------------- //
// string_parser                                                             //
// ------------------------------------------------------------------------- //

// specializations
template <> struct string_parser<int> {
    const int operator()(const char* s) const { return atoi(s); };
    const int operator()(const char* s, const char* e) const {
        static_string_builder<32> string;
        return atoi(string.append(s, e).data());
    }
};

template <> struct string_parser<float> {
    const float operator()(const char* s) const { return static_cast<float>(atof(s)); };
    const float operator()(const char* s, const char* e) const {
        static_string_builder<32> string;
        return static_cast<float>(atof(string.append(s, e).data()));
    }
};

template <> struct string_parser<sub_string> {
    const sub_string operator()(const char* s) const { return sub_string{ s, s + strlen(s) }; };
    const sub_string operator()(const char* s, const char* e) const { return sub_string{ s, e }; };
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_parser.inl"
