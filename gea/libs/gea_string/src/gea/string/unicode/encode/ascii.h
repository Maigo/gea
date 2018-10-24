#pragma once

// gea includes
#include <gea/string/unicode/encode/encode.h>

namespace gea {
namespace uni {
namespace ascii {

// ascii constants
const uint8_t ASCII_NULL          = 0x00;
// encode
const uint8_t ASCII_CODEPOINT_MAX = 0x7F;

// error codes
enum error_code : error_code_t {
    // inherit error types
    ASCII_OK                  = UNI_OK,
    ASCII_EOF                 = UNI_EOF,
    ASCII_INVALID_CODEPOINT   = UNI_INVALID_CODEPOINT,
    ASCII_RESTRICTED_CODEPOINT= UNI_RESTRICTED_CODEPOINT,
    // ascii specific
//  ASCII_OVERFLOW            = UNI_ERROR_CODE(21),
//  ASCII_INVALID_HIGH        = UNI_ERROR_CODE(22),
//  ASCII_INCOMPLETE_SEQUENCE = UNI_ERROR_CODE(23),
//  ASCII_OVERLONG_SEQUENCE   = UNI_ERROR_CODE(24),
//  ASCII_INVALID_CODE_POINT  = UNI_ERROR_CODE(25),
//  ASCII_INVALID_BOM         = UNI_ERROR_CODE(26),
//  ASCII_NO_ENCODING         = UNI_ERROR_CODE(27),
};
inline const char* to_string(const error_code err);

// validation
inline error_code_t validate_string  (const uint8_t* s);
inline error_code_t validate_string_s(const uint8_t* s, size_t buflen);
inline error_code_t validate_char  (const uint8_t* c);
inline error_code_t validate_char_s(const uint8_t* c, size_t buflen);
//error_code_t validate_codepoint(codepoint_t cp);
// traversion
inline error_code_t str_next  (const uint8_t*& s);
inline error_code_t str_next_s(const uint8_t*& s, size_t& buflen);
inline error_code_t str_prev  (const uint8_t*& s);
inline error_code_t str_prev_s(const uint8_t*& s, size_t& buflen);
// attribute
inline error_code_t str_length  (const uint8_t* s,                size_t& length);
inline error_code_t str_length_s(const uint8_t* s, size_t buflen, size_t& length);
// unicode
//inline error_code_t can_encode(codepoint_t cp);
//error_code_t encode  (codepoint_t cp, uint8_t* c);
//error_code_t encode_s(codepoint_t cp, uint8_t* c, size_t buflen);
//error_code_t decode  (const uint8_t* c,                codepoint_t& cp);
//error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp);

} // namespace ascii //
} // namespace uni //
} // namespace gea //

#include "ascii.inl"
