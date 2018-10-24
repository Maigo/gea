// header include
#include "utf8.h"

namespace gea {
namespace uni {
namespace utf8 {

namespace internal {

error_code_t skip_bom(const uint8_t* bom) {
    error_code_t err = UTF8_OK;
    return err;
}
error_code_t skip_bom_s(const uint8_t* bom, size_t buflen) {
    error_code_t err = UTF8_OK;
    return err;
}

error_code_t test_overlong(codepoint_t cp, size_t length) {
    error_code_t err0 = UTF8_OK, err1 = UTF8_OK;

    uint32_t cp_lt_0x00080 = (uint32_t) ((int32_t) (cp - 0x00080) >> 31);
    uint32_t cp_lt_0x00800 = (uint32_t) ((int32_t) (cp - 0x00800) >> 31);
    uint32_t cp_lt_0x10000 = (uint32_t) ((int32_t) (cp - 0x10000) >> 31);

    uint32_t l_lt_2 = (uint32_t) ((int32_t) (length - 2) >> 31);
    uint32_t l_lt_3 = (uint32_t) ((int32_t) (length - 3) >> 31);
    uint32_t l_lt_4 = (uint32_t) ((int32_t) (length - 4) >> 31);

    err1 = (l_lt_4 & UTF8_OK)     | (~l_lt_4 & UTF8_OVERLONG_SEQUENCE);
    err0 = (cp_lt_0x10000 & err1) | (~cp_lt_0x10000 & err0);

    err1 = (l_lt_3 & UTF8_OK)     | (~l_lt_3 & UTF8_OVERLONG_SEQUENCE);
    err0 = (cp_lt_0x00800 & err1) | (~cp_lt_0x00800 & err0);

    err1 = (l_lt_2 & UTF8_OK)     | (~l_lt_2 & UTF8_OVERLONG_SEQUENCE);
    err0 = (cp_lt_0x00080 & err1) | (~cp_lt_0x00080 & err0);

    return err0;
}
//error_code_t test_overlong_if(codepoint_t cp, size_t length) {
//        if      (cp < 0x00080) {
//            if (length != 1)
//                return UTF8_OVERLONG_SEQUENCE;
//        }
//        else if (cp < 0x00800) {
//            if (length != 2)
//                return UTF8_OVERLONG_SEQUENCE;
//        }
//        else if (cp < 0x10000) {
//            if (length != 3)
//                return UTF8_OVERLONG_SEQUENCE;
//        }
//
//        return UTF8_OK;
//}

error_code_t test_invalid_trail(const uint8_t* c) {
    error_code_t err = UTF8_OK;

    uint32_t trail = (uint32_t)* c;
    uint32_t ma_lt_c = (uint32_t) ((int32_t) (UTF8_VALID_TRAIL_MAX - trail) >> 31);
    uint32_t c_lt_mi = (uint32_t) ((int32_t) (trail - UTF8_VALID_TRAIL_MIN) >> 31);
    err = (c_lt_mi & UTF8_INVALID_TRAIL) | (~c_lt_mi & UTF8_OK);
    err = (ma_lt_c & UTF8_INVALID_TRAIL) | (~ma_lt_c & err);

    return err;
}

} // namespace internal //

// ------------------------------------------------------------------------- //
// UTF8 functions                                                            //
// ------------------------------------------------------------------------- //

// validation
error_code_t validate_string(const uint8_t* s) {
    error_code_t err0 = UTF8_OK, err1 = UTF8_OK;

    // skip bom if present
    err0 = internal::skip_bom(s);

    while ((err0 == UTF8_OK) && (*s != UTF8_NULL)) {
        err0 = validate_char(s);
        err1 = str_next(s);

        uint32_t err0_mask = (uint32_t) ((int32_t) (err0 - 0) >> 31);
        err0 = (err0_mask & err0) | (~err0_mask & err1);
    }
    return err0;
}
error_code_t validate_string_s(const uint8_t* s, size_t buflen) {
    error_code_t err0 = UTF8_OK, err1 = UTF8_OK;

    // skip bom if present
    err0 = internal::skip_bom_s(s, buflen);

    while ((err0 == UTF8_OK) && (*s != UTF8_NULL)) {
        err0 = validate_char_s(s, buflen);
        err1 = str_next_s(s, buflen);

        uint32_t err0_mask = (uint32_t) ((int32_t) (err0 - 0) >> 31);
        err0 = (err0_mask & err0) | (~err0_mask & err1);
    }
    return err0;
}
error_code_t validate_char(const uint8_t* c) {
    error_code_t err = UTF8_OK;

    size_t char_width;
    err = internal::char_width(c, char_width);

    // validate high and trail

    codepoint_t cp = 0x00000000;
    err = decode(c, cp);
    err = validate_codepoint(cp);
    err = internal::test_overlong(cp, char_width);

    return err;
}
error_code_t validate_char_s(const uint8_t* c, size_t buflen) {
    error_code_t err = UTF8_OK;
    return err;
}
error_code_t validate_codepoint(codepoint_t cp) {
    error_code_t err = UTF8_OK;

    uint32_t cp_lt_cpmax = (uint32_t) ((int32_t) (cp -  (UTF8_CODEPOINT_MAX + 1)) >> 31);
    uint32_t cp_lt_rmax  = (uint32_t) ((int32_t) (cp - (UTF8_RESTRICTED_MAX + 1)) >> 31);
    uint32_t cp_lt_rmin  = (uint32_t) ((int32_t) (cp - (UTF8_RESTRICTED_MIN + 0)) >> 31);
    uint32_t cp_lt_smax  = (uint32_t) ((int32_t) (cp -  (UTF8_SURROGATE_MAX + 1)) >> 31);
    uint32_t cp_lt_smin  = (uint32_t) ((int32_t) (cp -  (UTF8_SURROGATE_MIN + 0)) >> 31);

    err = (cp_lt_cpmax & UTF8_OK)                   | (~cp_lt_cpmax & UTF8_INVALID_CODEPOINT);
    err = (cp_lt_rmax  & UTF8_RESTRICTED_CODEPOINT) | (~cp_lt_rmax  & err);
    err = (cp_lt_rmin  & UTF8_OK)                   | (~cp_lt_rmin  & err);
    err = (cp_lt_smax  & UTF8_RESTRICTED_CODEPOINT) | (~cp_lt_smax  & err);
    err = (cp_lt_rmin  & UTF8_OK)                   | (~cp_lt_smin  & err);

    return err;
}

// traversion
error_code_t str_next(const uint8_t*& s) {
    error_code_t err = UTF8_OK;

    size_t char_width;
    err = internal::char_width(s, char_width);
    s  += char_width;

    return err;
}
error_code_t str_next_s(const uint8_t*& s, size_t& buflen) {
    error_code_t err0 = UTF8_OK, err1 = UTF8_OK;

    size_t char_width;
    err0 = internal::char_width(s, char_width);

    uint32_t buflen_lt_width = (uint32_t) ((int32_t) (buflen - char_width) >> 31);
    uint32_t buflen_lt_1     = (uint32_t) ((int32_t) (buflen - 1) >> 31);

    // check if char_width > remaining buffer length
    err1 = (buflen_lt_width & UTF8_INCOMPLETE_SEQUENCE) | (~buflen_lt_width & err0);
    uint32_t err0_mask       = (uint32_t) ((int32_t) (err0 - 0) >> 31);
    uint32_t err1_mask       = (uint32_t) ((int32_t) (err1 - 0) >> 31);
    // but prioritize invalid char width error
    err0   = (err0_mask & err0) | (~err0_mask & err1);

    uintptr_t p = (uintptr_t) s;
    p      = (err1_mask & (p)) | (~err1_mask & (p - char_width));
    buflen = (err1_mask & (0)) | (~err1_mask & (buflen - char_width));

    // return parameters
    s = (const uint8_t*) p;
    return err0;
}
error_code_t str_prev(const uint8_t*& s) {
//    size_t i = UTF8_MAX_WIDTH;
//    do {
//        --c; --i;
//    } while((i > 0) && internal::is_trail(c));
//
//    return internal::char_width(c, i);
return UTF8_OK;
}
error_code_t str_prev_s(const uint8_t*& s, size_t& buflen) {
//    size_t i = UTF8_MAX_WIDTH;
//    do {
//        --c; --i;
//    } while((i > 0) && internal::is_trail(c));
//
//    return internal::char_width(c, i);
return UTF8_OK;
}
// attribute
error_code_t str_length(const uint8_t* s, size_t& length) {
    error_code_t err = UTF8_OK;

    // skip bom if present
    err = internal::skip_bom(s);

    size_t l = 0; // length acc
    while ((err == UTF8_OK) && (s[0] != UTF8_NULL)) {
        err = str_next(s);
        ++l; // increment length
    }

    // return parameters
    length = l;
    return err;
}
error_code_t str_length_s(const uint8_t* s, size_t& buflen, size_t& length) {
    error_code_t err = UTF8_OK;

    // skip bom if present
    err = internal::skip_bom_s(s, buflen);

    size_t l = 0; // length acc
    while ((err == UTF8_OK) && (buflen > 0) && (s[0] != UTF8_NULL)) {
        err = str_next_s(s, buflen);
        ++l; // increment length
    }

    // return parameters
    length = l;
    return err;
}

// unicode
error_code_t encode(codepoint_t cp, uint8_t* c) {
    error_code_t err = UTF8_OK;

    size_t char_width;
    err = internal::char_width(cp, char_width); // always UTF8_OK


    return err;
}
error_code_t encode_s(codepoint_t cp, uint8_t* c, size_t buflen) {
    error_code_t err = UTF8_OK;
    return err;
}
error_code_t decode(const uint8_t* c, codepoint_t& cp) {
    error_code_t err = UTF8_OK;

    size_t char_width;
    err = internal::char_width(c, char_width);

    codepoint_t acc = ((codepoint_t) (internal::mask_cp_hi(char_width) & *c++));
    while ((err == UTF8_OK) && (char_width > 1)) {
        err = internal::test_invalid_trail(c);
        acc = (acc << 6) | ((codepoint_t) (internal::mask_cp_lo() & *c++));
        --char_width;
    }

    // return parameters
    cp = acc;
    return err;
}
error_code_t decode_s(const uint8_t* c, size_t buflen, codepoint_t& cp) {
    error_code_t err0 = UTF8_OK, err1 = UTF8_OK;

    size_t char_width;
    err0 = internal::char_width(c, char_width);

    uint32_t buflen_lt_width = (uint32_t) ((int32_t) (buflen - char_width) >> 31);
    // check if char_width > remaining buffer length
    err1 = (buflen_lt_width & UTF8_INCOMPLETE_SEQUENCE) | (~buflen_lt_width & err0);
    uint32_t err0_mask       = (uint32_t) ((int32_t) (err0 - 0) >> 31);
    // but prioritize invalid char width error
    err0   = (err0_mask & err0) | (~err0_mask & err1);

    codepoint_t acc = ((codepoint_t) (internal::mask_cp_hi(char_width) & *c++));
    while ((err0 == UTF8_OK) && (char_width > 1)) {
        err0 = internal::test_invalid_trail(c);
        acc = (acc << 6) | ((codepoint_t) (internal::mask_cp_lo() & *c++));
        --char_width;
    }

    // return parameters
    cp = acc;
    return err0;
}

} // namespace utf8 //
} // namespace uni //
} // namespace gea //
