#pragma once

// gea includes
#include <gea/string/unicode/encode/utf8.h>
#include <gea/string/unicode/encode/utf16.h>
#include <gea/string/unicode/encode/utf32.h>

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// UTF8: class wrapper                                                       //
// ------------------------------------------------------------------------- //
struct charset_utf8 {
    typedef uint8_t value_type;
    typedef uint32_t size_type;
    typedef uint32_t letter_t; // make variable?

    inline static bool validate(const value_type* s);
    inline static bool validate(const value_type* s, size_t buflen);

    inline static const size_t length(const value_type* s);
    inline static const size_t length(const value_type* s, size_t buflen);
};

// ------------------------------------------------------------------------- //
// UTF16: class wrapper                                                       //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// UTF32: class wrapper                                                       //
// ------------------------------------------------------------------------- //

} // namespace uni //
} // namespace gea //

#include "charset_utf.inl"
