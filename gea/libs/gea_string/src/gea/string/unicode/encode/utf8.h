#pragma once

// gea includes
#include <gea/core/bits/bits.h>
#include <gea/string/unicode/encode/unicode.h>

// UTF- encoding scheme:
//
// Bits  Last code point  Byte 1    Byte 2    Byte 3    Byte 4    Byte 5    Byte 6
//  7    U+007F         Å  0xxxxxxx
// 11    U+07FF           110xxxxx  10xxxxxx
// 16    U+FFFF           1110xxxx  10xxxxxx  10xxxxxx
// 21    U+1FFFFF         11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
// 26    U+3FFFFFF        111110xx  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx
// 31    U+7FFFFFFF       1111110x  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx

namespace gea {
namespace uni {
namespace utf8 {

// utf8 constants
const uint8_t     UTF8_NULL       = 0x00;
const size_t      UTF8_MAX_WIDTH  = 6;
// encode
const codepoint_t UTF8_MAX_ENCODE     = 0x7FFFFFFF;
const codepoint_t UTF8_CODEPOINT_MAX  = 0x0010FFFF;
const codepoint_t UTF8_RESTRICTED_MIN = 0x0000FFFE;
const codepoint_t UTF8_RESTRICTED_MAX = 0x0000FFFF;
const codepoint_t UTF8_SURROGATE_MIN  = 0x0000D800;
const codepoint_t UTF8_SURROGATE_MAX  = 0x0000DFFF; // DBFF?

// error codes
enum error_code {
    // inherit error types
    UTF8_OK                  = UNI_OK,
    UTF8_EOF                 = UNI_EOF,
    UTF8_INVALID_CODEPOINT   = UNI_INVALID_CODEPOINT,
    UTF8_RESTRICTED_CODEPOINT= UNI_RESTRICTED_CODEPOINT,
    // utf8 specific
    UTF8_OVERFLOW            = UNI_ERROR_CODE(11),
    UTF8_INVALID_HIGH        = UNI_ERROR_CODE(12),
    UTF8_INVALID_TRAIL       = UNI_ERROR_CODE(13),
    UTF8_INCOMPLETE_SEQUENCE = UNI_ERROR_CODE(14),
    UTF8_OVERLONG_SEQUENCE   = UNI_ERROR_CODE(15),
    UTF8_INVALID_CODE_POINT  = UNI_ERROR_CODE(16),
    UTF8_INVALID_BOM         = UNI_ERROR_CODE(17),
    UTF8_NO_ENCODING         = UNI_ERROR_CODE(18),
};
inline const char* to_string(const error_code err);

namespace internal {

error_code_t skip_bom  (const uint8_t* bom);                                 // <-- implement
error_code_t skip_bom_s(const uint8_t* bom, size_t buflen);                  // <-- implement

inline error_code_t char_width(const uint8_t* c, size_t& length);
inline bool is_trail(const uint8_t* c);

// mask operations
inline uint8_t mask_cp_hi(size_t char_width);
inline uint8_t mask_cp_lo();

// test operations
error_code_t test_overlong(codepoint_t cp, size_t length);
error_code_t test_overlong_if(codepoint_t cp, size_t length);

const uint32_t UTF8_VALID_TRAIL_MIN = 0x00000080;
const uint32_t UTF8_VALID_TRAIL_MAX = 0x000000BF;
error_code_t test_invalid_trail(const uint8_t* c);

} // namespace internal //

// ------------------------------------------------------------------------- //
// UTF8 functions                                                            //
// ------------------------------------------------------------------------- //

// validation
error_code_t validate_string  (const uint8_t* s);
error_code_t validate_string_s(const uint8_t* s, size_t buflen);
error_code_t validate_char  (const uint8_t* c);                              // <-- implement
error_code_t validate_char_s(const uint8_t* c, size_t buflen);               // <-- implement
error_code_t validate_codepoint(codepoint_t cp);
// traversion
error_code_t str_next  (const uint8_t*& s);
error_code_t str_next_s(const uint8_t*& s, size_t& buflen);
error_code_t str_prev  (const uint8_t*& s);                                  // <-- implement
error_code_t str_prev_s(const uint8_t*& s, size_t& buflen);                  // <-- implement
// attribute
error_code_t str_length  (const uint8_t* s,                 size_t& length);
error_code_t str_length_s(const uint8_t* s, size_t& buflen, size_t& length);
// unicode
inline error_code_t can_encode(codepoint_t cp);
error_code_t encode  (codepoint_t cp, uint8_t* c);                           // <-- implement
error_code_t encode_s(codepoint_t cp, uint8_t* c, size_t buflen);            // <-- implement
error_code_t decode  (const uint8_t* c,                codepoint_t& cp);     // <-- implement
error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp);     // <-- implement

} // namespace utf8 //
} // namespace uni //
} // namespace gea //

#include "utf8.inl"
