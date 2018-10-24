#pragma once

// gea includes
#include <gea/string/unicode/encode/unicode.h>

namespace gea {
namespace uni {
namespace ucs2 {

// utf8 constants
const uint16_t    UCS2_NULL         = 0x0000;
const uint8_t     UCS2_NULL_BYTE    = 0x00;
const size_t      UCS2_CHAR_WIDTH   = 2;
const uint16_t    UCS2_CHAR_UNKNOWN = 0x003F; // '?'
// encode
const codepoint_t UCS2_MAX_ENCODE     = 0x0000FFFF;

// error codes
enum error_code : error_code_t {
    // inherit error types
    UCS2_OK                  = UNI_OK,
    UCS2_EOF                 = UNI_EOF,
    UCS2_INVALID_CODEPOINT   = UNI_INVALID_CODEPOINT,
    UCS2_RESTRICTED_CODEPOINT= UNI_RESTRICTED_CODEPOINT,
    // ucs2 specific
    UCS2_INCOMPLETE_SEQUENCE = UNI_ERROR_CODE(21),
    UCS2_NO_ENCODING         = UNI_ERROR_CODE(22),
};
inline const char* to_string(const error_code err);

// validation
error_code_t validate_string  (const uint8_t* s);
error_code_t validate_string_s(const uint8_t* s, size_t buflen);
error_code_t validate_char  (const uint8_t* c);
error_code_t validate_char_s(const uint8_t* c, size_t buflen);
error_code_t validate_codepoint(codepoint_t cp);
// traversion
error_code_t str_next  (const uint8_t*& s);
error_code_t str_next_s(const uint8_t*& s, size_t& buflen);
error_code_t str_prev  (const uint8_t*& s);
error_code_t str_prev_s(const uint8_t*& s, size_t& buflen);
// attribute
error_code_t str_length  (const uint8_t* s,                size_t& length);
error_code_t str_length_s(const uint8_t* s, size_t buflen, size_t& length);
// unicode
inline error_code_t can_encode(codepoint_t cp);
error_code_t encode  (codepoint_t cp, uint8_t* c);
error_code_t encode_s(codepoint_t cp, uint8_t* c, size_t buflen);
error_code_t decode  (const uint8_t* c,                codepoint_t& cp);
error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp);

} // namespace ucs2 //
} // namespace uni //
} // namespace gea //

#include "ucs2.inl"
