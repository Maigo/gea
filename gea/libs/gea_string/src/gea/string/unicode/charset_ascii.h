#pragma once

// gea includes
#include <gea/string/unicode/encode/ascii.h>

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// ASCII: class wrapper                                                       //
// ------------------------------------------------------------------------- //
struct charset_ascii {
    // type definitions
    typedef char       value_type;
    typedef uint32_t   size_type;
    typedef value_type letter_type;

    // constants
    static const size_type size_null = sizeof(ascii::ASCII_NULL);

    // functions
    inline static const size_type size(const letter_type c); // size returns # of byte of given letter or string
    inline static const size_type size(const value_type* s);

    inline static const size_type length(const value_type* s); // length returns # of letters of given string
    inline static const size_type length(const value_type* s, const value_type* e);
    inline static const size_type length(const value_type* s, size_type buflen);

    inline static void null_terminate(value_type* s);
    inline static value_type* uninitialized_fill_n(value_type* s, size_type n, letter_type c);
    inline static value_type* uninitialized_copy(const value_type* src, const value_type* src_end, value_type* dst);

    inline static bool validate(const value_type* s);
    inline static bool validate(const value_type* s, size_type buflen);
};

} // namespace uni //
} // namespace gea //

#include "charset_ascii.inl"
