#pragma once

// header include
#include "charset_ucs.h"

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// UCS2                                                                      //
// ------------------------------------------------------------------------- //
inline bool charset_ucs2::validate(const value_type* s) {
    return (ucs2::validate_string(reinterpret_cast<const uint8_t*>(s)) == ucs2::UCS2_OK);
}
inline bool charset_ucs2::validate(const value_type* s, size_t buflen) {
    return (ucs2::validate_string_s(reinterpret_cast<const uint8_t*>(s), buflen) == ucs2::UCS2_OK);
}

inline const size_t charset_ucs2::length(const value_type* s) {
    size_t length = 0;
    return (ucs2::str_length(reinterpret_cast<const uint8_t*>(s), length) == ucs2::UCS2_OK) ? length : 0;
}
inline const size_t charset_ucs2::length(const value_type* s, size_t buflen) {
    size_t length = 0;
    return (ucs2::str_length_s(reinterpret_cast<const uint8_t*>(s), buflen, length) == ucs2::UCS2_OK) ? length : 0;
}

// ------------------------------------------------------------------------- //
// UCS4                                                                      //
// ------------------------------------------------------------------------- //
inline bool charset_ucs4::validate(const value_type* s) {
    return (ucs4::validate_string(reinterpret_cast<const uint8_t*>(s)) == ucs2::UCS2_OK);
}
inline bool charset_ucs4::validate(const value_type* s, size_t buflen) {
    return (ucs4::validate_string_s(reinterpret_cast<const uint8_t*>(s), buflen) == ucs2::UCS2_OK);
}

inline const size_t charset_ucs4::length(const value_type* s) {
    size_t length = 0;
    return (ucs4::str_length(reinterpret_cast<const uint8_t*>(s), length) == ucs4::UCS4_OK) ? length : 0;
}
inline const size_t charset_ucs4::length(const value_type* s, size_t buflen) {
    size_t length = 0;
    return (ucs4::str_length_s(reinterpret_cast<const uint8_t*>(s), buflen, length) == ucs4::UCS4_OK) ? length : 0;
}

} // namespace uni //
} // namespace gea //
