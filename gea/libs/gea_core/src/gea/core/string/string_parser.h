#pragma once

//gea includes
#include <gea/core/string/string_builder.h>

namespace gea {

// ------------------------------------------------------------------------- //
// string_parser                                                             //
// ------------------------------------------------------------------------- //

template <typename T>
struct string_parser;
//    const T operator()(const char* s) const;
//    const T operator()(const char* s, const char* e) const;


// specializations
template <> struct string_parser<int>;
template <> struct string_parser<float>;
template <> struct string_parser<sub_string>;

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "string_parser.inl"
