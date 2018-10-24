#pragma once

// gea includes
#include <gea/string/unicode/encode/ucs2.h>
#include <gea/string/unicode/encode/ucs4.h>

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// UCS2: class wrapper                                                       //
// ------------------------------------------------------------------------- //
struct charset_ucs2 {
    typedef uint16_t value_type;
    typedef uint32_t size_type;
    typedef value_type letter_t;

    inline static bool validate(const value_type* s);
    inline static bool validate(const value_type* s, size_t buflen);

    inline static const size_t length(const value_type* s);
    inline static const size_t length(const value_type* s, size_t buflen);
};

// ------------------------------------------------------------------------- //
// UCS4: class wrapper                                                       //
// ------------------------------------------------------------------------- //
struct charset_ucs4 {
    typedef uint32_t value_type;
    typedef uint32_t size_type;
    typedef value_type letter_t;

    inline static bool validate(const value_type* s);
    inline static bool validate(const value_type* s, size_t buflen);

    inline static const size_t length(const value_type* s);
    inline static const size_t length(const value_type* s, size_t buflen);
};

} // namespace uni //
} // namespace gea //

#include "charset_ucs.inl"
