#pragma once

// header include
#include "ascii.h"

namespace gea {
namespace uni {
namespace ascii {

// error codes
inline const char* to_string(const error_code err) {
    switch (err) {
    case ASCII_OK:                   return "ASCII_OK";
    case ASCII_EOF:                  return "ASCII_EOF";
    case ASCII_INVALID_CODEPOINT:    return "ASCII_INVALID_CODEPOINT";
    case ASCII_RESTRICTED_CODEPOINT: return "ASCII_RESTRICTED_CODEPOINT";
    }
    return "";
}

// validation
inline error_code_t validate_string(const uint8_t* s) {
    error_code_t err = ASCII_OK;

    while ((err == ASCII_OK) && (s[0] != ASCII_NULL)) {
        err = validate_char(s);
        str_next(s);
    }

    return err;
}
inline error_code_t validate_string_s(const uint8_t* s, size_t buflen) {
    error_code_t err0 = ASCII_OK, err1 = ASCII_OK;

    while ((err0 == ASCII_OK) && (s[0] != ASCII_NULL)) {
        err0 = validate_char_s(s, buflen);
        err1 = str_next_s(s, buflen);

        uint32_t err0_mask = (uint32_t) ((int32_t) (err0 - 0) >> 31);
        err0 = (err0_mask & err0) | (~err0_mask & err1);
    }
    return err0;
}
inline error_code_t validate_char(const uint8_t* c) {
    error_code_t err = ASCII_OK;

    uint32_t asciimax_lt_c = (uint32_t) ((int32_t) (ASCII_CODEPOINT_MAX - (*c)) >> 31);
    err = (asciimax_lt_c & ASCII_INVALID_CODEPOINT) | (~asciimax_lt_c & err);

    return err;
}
inline error_code_t validate_char_s(const uint8_t* c, size_t buflen) {
    error_code_t err = ASCII_OK;

    uint32_t asciimax_lt_c = (uint32_t) ((int32_t) (ASCII_CODEPOINT_MAX - (*c)) >> 31);
    uint32_t buflen_lt_1 = (uint32_t) ((int32_t) (buflen - 1) >> 31);
    err = (asciimax_lt_c & ASCII_INVALID_CODEPOINT) | (~asciimax_lt_c & err);
    err = (buflen_lt_1   & ASCII_EOF)               | (~buflen_lt_1 & err);

    return err;
}
// traversion
inline error_code_t str_next(const uint8_t*& s) {
    error_code_t err = ASCII_OK;

    ++s;

    return err;
}
inline error_code_t str_next_s(const uint8_t*& s, size_t& buflen) {
    error_code_t err = ASCII_OK;

    uint32_t buflen_lt_1 = (uint32_t) ((int32_t) (buflen - 1) >> 31);
    err = (buflen_lt_1 & ASCII_EOF) | (~buflen_lt_1 & err);
    uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);

    uintptr_t p = (uintptr_t) s;
    p      = (err_mask & (p)) | (~err_mask & (p + 1));
    buflen = (err_mask & (0)) | (~err_mask & (buflen - 1));

    // return parameters
    s = (const uint8_t*) p;
    return err;
}
inline error_code_t str_prev(const uint8_t*& s) {
    error_code_t err = ASCII_OK;

    --s;

    return err;
}
inline error_code_t str_prev_s(const uint8_t*& s, size_t& buflen) {
    error_code_t err = ASCII_OK;

    uint32_t buflen_lt_1 = (uint32_t) ((int32_t) (buflen - 1) >> 31);
    err = (buflen_lt_1 & ASCII_EOF) | (~buflen_lt_1 & err);
    uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);

    uintptr_t p = (uintptr_t) s;
    p      = (err_mask & (p)) | (~err_mask & (p - 1));
    buflen = (err_mask & (0)) | (~err_mask & (buflen - 1));

    // return parameters
    s = (const uint8_t*) p;
    return err;
}
// attribute
inline error_code_t str_length(const uint8_t* s, size_t& length) {
    error_code_t err = ASCII_OK;

    size_t l = 0;
    while ((err == ASCII_OK) && (s[0] != ASCII_NULL)) {
        err = str_next(s);
        ++l;
    }

    // return parameters
    length = l;
    return err;
}

inline error_code_t str_length_s(const uint8_t* s, size_t buflen, size_t& length) {
    error_code_t err = ASCII_OK;

    size_t l = 0;
    while ((err == ASCII_OK) && (s[0] != ASCII_NULL)) {
        err = str_next_s(s, buflen);
        uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);
        l = (err_mask & (l)) | (~err_mask & (l + 1));
    }

    // return parameters
    length = l;
    return err;
}
// unicode
//inline error_code_t can_encode(codepoint_t cp);
//error_code_t encode  (codepoint_t cp, uint8_t* c);
//error_code_t encode_s(codepoint_t cp, uint8_t* c, size_t buflen);
//error_code_t decode  (const uint8_t* c,                codepoint_t& cp);
//error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp);

} // namespace ascii //
} // namespace uni //
} // namespace gea //
