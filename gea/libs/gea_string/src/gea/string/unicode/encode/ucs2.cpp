// header include
#include "ucs2.h"

namespace gea {
namespace uni {
namespace ucs2 {

// validation
error_code_t validate_string(const uint8_t* s) {
    error_code_t err0 = UCS2_OK, err1 = UCS2_OK;

    while ((err0 == UCS2_OK) && (((const uint16_t*)s)[0] != UCS2_NULL)) {
        err0 = validate_char(s);
        err1 = str_next(s);

        uint32_t err0_mask = (uint32_t) ((int32_t) (err0 - 0) >> 31);
        err0 = (err0_mask & err0) | (~err0_mask & err1);
    }

    return err0;
}
error_code_t validate_string_s(const uint8_t* s, size_t buflen) {
    error_code_t err0 = UCS2_OK, err1 = UCS2_OK;

    while ((err0 == UCS2_OK) && (((const uint16_t*)s)[0] != UCS2_NULL)) {
        err0 = validate_char_s(s, buflen);
        err1 = str_next_s(s, buflen);

        uint32_t err0_mask = (uint32_t) ((int32_t) (err0 - 0) >> 31);
        err0 = (err0_mask & err0) | (~err0_mask & err1);
    }
    return err0;
}
error_code_t validate_char(const uint8_t* c) {
    error_code_t err = UCS2_OK;
    return err;
}
error_code_t validate_char_s(const uint8_t* c, size_t buflen) {
    error_code_t err = UCS2_OK;
    return err;
}
error_code_t validate_codepoint(codepoint_t cp) {
    error_code_t err = UCS2_OK;
    return err;
}

// traversion
error_code_t str_next(const uint8_t*& s) {
    error_code_t err = UCS2_OK;

    s += UCS2_CHAR_WIDTH;

    return err;
}
error_code_t str_next_s(const uint8_t*& s, size_t& buflen) {
    error_code_t err = UCS2_OK;

    uint32_t buflen_lt_width = (uint32_t) ((int32_t) (buflen - UCS2_CHAR_WIDTH) >> 31);
    uint32_t buflen_lt_1     = (uint32_t) ((int32_t) (buflen - 1) >> 31);
    // check if char_width > remaining buffer length
    err = (buflen_lt_width & UCS2_INCOMPLETE_SEQUENCE) | (~buflen_lt_width & err);
    err = (buflen_lt_1     & UCS2_EOF)                 | (~buflen_lt_1 & err);

    uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);

    uintptr_t p = (uintptr_t) s;
    p      = (err_mask & (p)) | (~err_mask & (p + UCS2_CHAR_WIDTH));
    buflen = (err_mask & (0)) | (~err_mask & (buflen - UCS2_CHAR_WIDTH));

    // return parameters
    s = (const uint8_t*) p;
    return err;
}
error_code_t str_prev(const uint8_t*& s) {
    error_code_t err = UCS2_OK;

    s -= UCS2_CHAR_WIDTH;

    return err;
}
error_code_t str_prev_s(const uint8_t*& s, size_t& buflen) {
    error_code_t err = UCS2_OK;

    uint32_t buflen_lt_width = (uint32_t) ((int32_t) (buflen - UCS2_CHAR_WIDTH) >> 31);
    uint32_t buflen_lt_1     = (uint32_t) ((int32_t) (buflen - 1) >> 31);
    // check if char_width > remaining buffer length
    err = (buflen_lt_width & UCS2_INCOMPLETE_SEQUENCE) | (~buflen_lt_width & err);
    err = (buflen_lt_1     & UCS2_EOF)                 | (~buflen_lt_1 & err);

    uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);

    uintptr_t p = (uintptr_t) s;
    p      = (err_mask & (p)) | (~err_mask & (p - UCS2_CHAR_WIDTH));
    buflen = (err_mask & (0)) | (~err_mask & (buflen - UCS2_CHAR_WIDTH));

    // return parameters
    s = (const uint8_t*) p;
    return err;
}
// attribute
error_code_t str_length(const uint8_t* s, size_t& length) {
    error_code_t err = UCS2_OK;

    size_t l = 0; // length acc
    while ((err == UCS2_OK) && (((const uint16_t*)s)[0] != UCS2_NULL)) {
        err = str_next(s);
        ++l; // increment length
    }

    // return parameters
    length = l;
    return err;
}
error_code_t str_length_s(const uint8_t* s, size_t buflen, size_t& length) {
    error_code_t err = UCS2_OK;

    size_t l = 0; // length acc
    while ((err == UCS2_OK) && (((const uint16_t*)s)[0] != UCS2_NULL)) {
        err = str_next_s(s, buflen);
        uint32_t err_mask = (uint32_t) ((int32_t) (err - 0) >> 31);
        l = (err_mask & (l)) | (~err_mask & (l + 1));
    }

    // return parameters
    length = l;
    return err;
}
// unicode
error_code_t encode(codepoint_t cp, uint8_t* c) {
    error_code_t err = UCS2_OK;

    uint32_t ucs2max_lt_cp = (uint32_t) ((int32_t) (UCS2_MAX_ENCODE - cp) >> 31);
    ((uint16_t*) c)[0] = (uint16_t) ((ucs2max_lt_cp & UCS2_CHAR_UNKNOWN) | (~ucs2max_lt_cp & cp));
    err = (ucs2max_lt_cp & UCS2_NO_ENCODING) | (~ucs2max_lt_cp & err);

    return err;
}
error_code_t encode_s(codepoint_t cp, const uint8_t* c, size_t buflen) {
    error_code_t err = UCS2_OK;

    if (buflen >= 2) {
        uint32_t ucs2max_lt_cp = (uint32_t) ((int32_t) (UCS2_MAX_ENCODE - cp) >> 31);
        ((uint16_t*) c)[0] = (uint16_t) ((ucs2max_lt_cp & UCS2_CHAR_UNKNOWN) | (~ucs2max_lt_cp & cp));
        err = (ucs2max_lt_cp & UCS2_NO_ENCODING) | (~ucs2max_lt_cp & err);
    } else {
        uint32_t buflen_lt_1 = (uint32_t) ((int32_t) (buflen - 1) >> 31);
        err = (buflen_lt_1 & UCS2_EOF) | (~buflen_lt_1 & UCS2_INCOMPLETE_SEQUENCE);
    }

    return err;
}
error_code_t decode(const uint8_t* c, codepoint_t& cp) {
    error_code_t err = UCS2_OK;

    cp = (codepoint_t) ((const uint16_t*) c)[0];

    return err;
}
error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp) {
    error_code_t err = UCS2_OK;

    if (buflen >= 2) {
        cp = (codepoint_t) ((const uint16_t*) c)[0];
    } else {
        uint32_t buflen_lt_1 = (uint32_t) ((int32_t) (buflen - 1) >> 31);
        err = (buflen_lt_1 & UCS2_EOF) | (~buflen_lt_1 & UCS2_INCOMPLETE_SEQUENCE);
    }

    return err;
}

} // namespace ucs2 //
} // namespace uni //
} // namespace gea //
