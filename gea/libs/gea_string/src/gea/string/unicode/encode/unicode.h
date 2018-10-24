#pragma once

// gea includes
#include <gea/string/unicode/encode/encode.h>

namespace gea {
namespace uni {

// ------------------------------------------------------------------------- //
// Common unicode interface                                                  //
// ------------------------------------------------------------------------- //

// common types
typedef uint32_t codepoint_t;

enum char_type {
    CONTROL,
    PUNCTUATION,
    NUMBER,
    LETTER,
    INVALID,
};

// common functions
// // validation
// error_code_t validate_string  (const uint8_t* s);
// error_code_t validate_string_s(const uint8_t* s, size_t buflen);
// error_code_t validate_char  (const uint8_t* c);
// error_code_t validate_char_s(const uint8_t* c, size_t buflen);
// // traversion
// error_code_t str_next  (const uint8_t*& s);
// error_code_t str_next_s(const uint8_t*& s, size_t buflen);
// error_code_t str_prev  (const uint8_t*& s);
// error_code_t str_prev_s(const uint8_t*& s, size_t buflen);
// // attribute
// error_code_t str_length  (const uint8_t* s,                size_t& length);
// error_code_t str_length_s(const uint8_t* s, size_t buflen, size_t& length);
// // unicode
// error_code_t can_encode(codepoint_t cp);
// error_code_t encode  (codepoint_t cp, const uint8_t* c);
// error_code_t encode_s(codepoint_t cp, const uint8_t* c, size_t buflen);
// error_code_t decode  (const uint8_t* c,                codepoint_t& cp);
// error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp);

// ------------------------------------------------------------------------- //
// Encode scheme independent functions                                       //
// ------------------------------------------------------------------------- //

namespace internal {

} // namespace internal //

} // namespace uni //
} // namespace gea //
