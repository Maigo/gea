#pragma once

// header include
#include "charset_utf.h"

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// UTF8                                                                      //
// ------------------------------------------------------------------------- //
inline bool charset_utf8::validate(const value_type* s) {
    return (utf8::validate_string(static_cast<const uint8_t*>(s)) == utf8::UTF8_OK);
}
inline bool charset_utf8::validate(const value_type* s, size_t buflen) {
    return (utf8::validate_string_s(static_cast<const uint8_t*>(s), buflen) == utf8::UTF8_OK);
}

inline const size_t charset_utf8::length(const value_type* s) {
    size_t length = 0;
    return (utf8::str_length(static_cast<const uint8_t*>(s), length) == utf8::UTF8_OK) ? length : 0;
}
inline const size_t charset_utf8::length(const value_type* s, size_t buflen) {
    size_t length = 0;
    return (utf8::str_length_s(static_cast<const uint8_t*>(s), buflen, length) == utf8::UTF8_OK) ? length : 0;
}

} // namespace uni //
} // namespace gea //