#pragma once

// header include
#include "utf8.h"

namespace gea {
namespace uni {
namespace utf8 {

// error codes
inline const char* to_string(const error_code err) {
    switch (err) {
    case UTF8_OK: return "UTF8_OK";
    case UTF8_EOF: return "UTF8_EOF";
    case UTF8_INVALID_CODEPOINT: return "UTF8_INVALID_CODEPOINT";
    case UTF8_RESTRICTED_CODEPOINT: return "UTF8_RESTRICTED_CODEPOINT";
    case UTF8_OVERFLOW: return "UTF8_OVERFLOW";
    case UTF8_INVALID_HIGH: return "UTF8_INVALID_HIGH";
    case UTF8_INVALID_TRAIL: return "UTF8_INVALID_TRAIL";
    case UTF8_INCOMPLETE_SEQUENCE: return "UTF8_INCOMPLETE_SEQUENCE";
    case UTF8_OVERLONG_SEQUENCE: return "UTF8_OVERLONG_SEQUENCE";
    case UTF8_INVALID_CODE_POINT: return "UTF8_INVALID_CODE_POINT";
    case UTF8_INVALID_BOM: return "UTF8_INVALID_BOM";
    case UTF8_NO_ENCODING: return "UTF8_NO_ENCODING";
    }
    return "";
}

namespace internal {

inline error_code_t char_width(const uint8_t* c, size_t& length) {
    error_code_t err = UTF8_OK;

    uint32_t x = (uint32_t) gea::bit::loc(*c);

    uint32_t x_lt_X = (uint32_t) ((int32_t) (x - (UTF8_MAX_WIDTH + 1)) >> 31);
    uint32_t x_lt_2 = (uint32_t) ((int32_t) (x - 2) >> 31);
    uint32_t x_lt_1 = (uint32_t) ((int32_t) (x - 1) >> 31);

    err = (x_lt_X & UTF8_OK)           | (~x_lt_X & UTF8_INVALID_HIGH);
    err = (x_lt_2 & UTF8_INVALID_HIGH) | (~x_lt_2 & err);
    err = (x_lt_1 & UTF8_OK)           | (~x_lt_1 & err);

    uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);
    x = (x_lt_1   & (1)) | (~x_lt_1   & (x));
    x = (err_mask & (0)) | (~err_mask & (x)); // assure length is 0 on error!

    // return parameters
    length = (size_t) x;
    return err;
}
inline error_code_t char_width(codepoint_t cp, size_t& length) {
    error_code_t err = UTF8_OK;

    uint32_t cp_lt_2 = (uint32_t) ((int32_t) (cp - (0x0000007F + 1)) >> 31);
    uint32_t cp_lt_3 = (uint32_t) ((int32_t) (cp - (0x000007FF + 1)) >> 31);
    uint32_t cp_lt_4 = (uint32_t) ((int32_t) (cp - (0x0000FFFF + 1)) >> 31);

    uint32_t l = 0;
    l = (cp_lt_4 & 3) | (~cp_lt_4 & 4);
    l = (cp_lt_3 & 2) | (~cp_lt_3 & l);
    l = (cp_lt_2 & 1) | (~cp_lt_2 & l);

    // return parameters
    length = (size_t) l;
    return err;
}

inline bool is_trail(const uint8_t* c) { return (*c & 0xC0) == 0x80; }

inline uint8_t mask_cp_hi(size_t char_width) { return ~(0x80 >> char_width); }
inline uint8_t mask_cp_lo() { return 0x3F; }

} // namespace internal //

// unicode
inline error_code_t can_encode(codepoint_t cp) {
    error_code_t err = UTF8_OK;

    uint32_t cp_lt_utf8max = (uint32_t) ((int32_t) (cp - (UTF8_MAX_ENCODE + 1)) >> 31);
    err = (cp_lt_utf8max & UTF8_OK) | (~cp_lt_utf8max & UTF8_NO_ENCODING);

    return err;
}

} // namespace utf8 //
} // namespace uni //
} // namespace gea //
