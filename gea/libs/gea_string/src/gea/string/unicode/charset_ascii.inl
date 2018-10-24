#pragma once

// header include
#include "charset_ascii.h"

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// ASCII                                                                     //
// ------------------------------------------------------------------------- //
inline const charset_ascii::size_type charset_ascii::size(const letter_type) { return sizeof(letter_type); }
inline const charset_ascii::size_type charset_ascii::size(const value_type* s) { return length(s); }

inline const charset_ascii::size_type charset_ascii::length(const value_type* s) {
    size_t length = 0;
    return (ascii::str_length(reinterpret_cast<const uint8_t*>(s), length) == ascii::ASCII_OK) ? length : 0;
}
inline const charset_ascii::size_type charset_ascii::length(const value_type* s, const value_type* e) {
    return static_cast<size_type>(e - s);
}
inline const charset_ascii::size_type charset_ascii::length(const value_type* s, size_type buflen) {
    size_t length = 0;
    return (ascii::str_length_s(reinterpret_cast<const uint8_t*>(s), buflen, length) == ascii::ASCII_OK) ? length : 0;
}

inline void charset_ascii::null_terminate(value_type* s) { s[0] = ascii::ASCII_NULL; }
inline charset_ascii::value_type* charset_ascii::uninitialized_fill_n(value_type* s, size_type n, letter_type c) {
    if (n != 0)
        memset(s, static_cast<uint8_t>(c), static_cast<uint32_t>(n));
    return s + n;
}
inline charset_ascii::value_type* charset_ascii::uninitialized_copy(const value_type* src, const value_type* src_end, value_type* dst) {
    const size_type size = static_cast<size_type>(src_end - src);
    memmove(dst, src, static_cast<size_t>(size) * sizeof(value_type));
    return dst + size;
}

inline bool charset_ascii::validate(const value_type* s) {
    return (ascii::validate_string((const uint8_t*) (s)) == ascii::ASCII_OK);
}
inline bool charset_ascii::validate(const value_type* s, size_type buflen) {
    return (ascii::validate_string_s((const uint8_t*) (s), buflen) == ascii::ASCII_OK);
}

} // namespace uni //
} // namespace gea //
