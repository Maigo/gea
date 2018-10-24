#pragma once

// gea includes
#include <gea/string/unicode/encode/unicode.h>

namespace gea {
namespace uni {
namespace ucs4 {

// ucs4 constants
const uint32_t    UCS4_NULL         = 0x00000000;
const uint8_t     UCS4_NULL_BYTE    = 0x00;
const size_t      UCS4_CHAR_WIDTH   = 4;
const uint16_t    UCS4_CHAR_UNKNOWN = 0x0000003F; // '?'
// encode
const codepoint_t UCS4_CODEPOINT_MAX  = 0x0010FFFF;

// error codes
enum error_code : error_code_t {
    // inherit error types
    UCS4_OK                  = UNI_OK,
    UCS4_EOF                 = UNI_EOF,
    UCS4_INVALID_CODEPOINT   = UNI_INVALID_CODEPOINT,
    UCS4_RESTRICTED_CODEPOINT= UNI_RESTRICTED_CODEPOINT,
    // ucs4 specific
    UCS4_INCOMPLETE_SEQUENCE = UNI_ERROR_CODE(31),
    UCS4_NO_ENCODING         = UNI_ERROR_CODE(32),
};
inline const char* to_string(const error_code err);

// validation
error_code_t validate_string  (const uint8_t* s);
error_code_t validate_string_s(const uint8_t* s, size_t buflen);
error_code_t validate_char  (const uint8_t* s);
error_code_t validate_char_s(const uint8_t* s, size_t buflen);
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

} // namespace ucs4 //
} // namespace uni //
} // namespace gea //

#include "ucs4.inl"
