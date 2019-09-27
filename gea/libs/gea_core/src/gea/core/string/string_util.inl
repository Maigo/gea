#pragma once
#include "string_util.h"

// std includes
#include <stdarg.h>
#include <string.h>

// gea includes
#include <gea/core/bits/bcl.h>
#include <gea/core/bits/bsa.h>
#include <gea/core/math.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //

// variadic arguments
// TODO: move to platform spacific code
inline const int string_util::vsnprintf(char* buffer, const size_t size, const char* format, va_list args) {
    return vsnprintf_s(buffer, size, _TRUNCATE, format, args);
}
inline const int string_util::snprintf(char* buffer, const size_t size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    const int ret = vsnprintf(buffer, size, format, args);
    va_end(args);
    return ret;
}

inline const int string_util::vsscanf(const char* s, const char* format, va_list args) {
    return vsscanf_s(s, format, args);
}
inline const int string_util::sscanf(const char* s, const char* format, ...) {
    va_list args;
    va_start(args, format);
    const int ret = vsscanf(s, format, args);
    va_end(args);
    return ret;
}

// search
inline const char* string_util::first_index_of(const char* s, const char c) {
    return first_index_of(s, s + strlen(s), c);
}
inline const char* string_util::first_index_of(const char* s, const char* end, const char c) {
    const char* safe_end = mth::max(s, end);
    for (const char* it = s, *it_end = safe_end; it != it_end; ++it) {
        if (*it == c) {
            return it;
        }
    }
    return safe_end;
}

inline const char* string_util::last_index_of(const char* s, const char c) {
    return last_index_of(s, s + strlen(s), c);
}
inline const char* string_util::last_index_of(const char* s, const char* end, const char c) {
    const char* safe_end = mth::max(s, end);
    for (const char* it = (safe_end - 1), *it_end = (s - 1); it != it_end; --it) {
        if (*it == c) {
            return it;
        }
    }
    return safe_end;
}

// conversion - hexadecimal to decimal
inline const uint8_t string_util::hex_to_dec(const char hex) {
    return
        bit::bcl::iif('0' <= hex && hex <= '9', uint8_t((hex - '0') + 0x0), uint8_t(0)) +
        bit::bcl::iif('a' <= hex && hex <= 'f', uint8_t((hex - 'a') + 0xA), uint8_t(0)) +
        bit::bcl::iif('A' <= hex && hex <= 'F', uint8_t((hex - 'A') + 0xA), uint8_t(0));
}

inline const size_t string_util::hex_to_dec(const char* hex, const size_t hex_size, uint8_t& out_dec) {
    uint8_t dec = 0; size_t i = 0;
    if (gea_likely(hex && hex_size > i))
        dec = hex_to_dec(hex[i++]) + (dec * 16);
    if (gea_likely(hex && hex_size > i))
        dec = hex_to_dec(hex[i++]) + (dec * 16);
    out_dec = dec;
    return i;
}
inline const size_t string_util::hex_to_dec(const char* hex, const size_t hex_size, uint16_t& out_dec) {
    uint8_t hi, lo;
    const size_t hi_shift = hex_to_dec(hex + 0, hex_size, hi);
    const size_t lo_shift = hex_to_dec(hex + 2, bit::bsa::sub(hex_size, 2), lo);
    out_dec = (static_cast<uint16_t>(hi) << (4 * lo_shift)) | static_cast<uint16_t>(lo);
    return hi_shift + lo_shift;
}
inline const size_t string_util::hex_to_dec(const char* hex, const size_t hex_size, uint32_t& out_dec) {
    uint16_t hi, lo;
    const size_t hi_shift = hex_to_dec(hex + 0, hex_size, hi);
    const size_t lo_shift = hex_to_dec(hex + 4, bit::bsa::sub(hex_size, 4), lo);
    out_dec = (static_cast<uint32_t>(hi) << (4 * lo_shift)) | static_cast<uint32_t>(lo);
    return hi_shift + lo_shift;
}
inline const size_t string_util::hex_to_dec(const char* hex, const size_t hex_size, uint64_t& out_dec) {
    uint32_t hi, lo;
    const size_t hi_shift = hex_to_dec(hex + 0, hex_size, hi);
    const size_t lo_shift = hex_to_dec(hex + 8, bit::bsa::sub(hex_size, 8), lo);
    out_dec = (static_cast<uint64_t>(hi) << (4 * lo_shift)) | static_cast<uint64_t>(lo);
    return hi_shift + lo_shift;
}
inline const size_t string_util::hex_to_dec(const char* hex, const size_t hex_size, uint8_t* out_dec, const size_t dec_size) {
    l_assert_implement;
    return 0;
}

// decimal to hexadecimal
inline const char string_util::dec_to_hex(const uint8_t dec) {
    static const uint8_t map[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    return map[dec & 0x0F];
}
inline const bool string_util::dec_to_hex(const uint8_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    if (gea_likely(size > 0))
        buffer[0] = dec_to_hex((dec >> 4) & 0x0F);
    if (gea_likely(size > 1))
        buffer[1] = dec_to_hex((dec >> 0) & 0x0F);
    return (size >= 2);
}
inline const bool string_util::dec_to_hex(const uint16_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint8_t hi = static_cast<uint8_t>((dec >> 8) & 0x00FF);
    const uint8_t lo = static_cast<uint8_t>((dec >> 0) & 0x00FF);
    dec_to_hex(hi, buffer + 0, size);
    dec_to_hex(lo, buffer + 2, bit::bsa::sub(size, 2));
    return (size >= 4);
}
inline const bool string_util::dec_to_hex(const uint32_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint16_t hi = static_cast<uint16_t>((dec >> 16) & 0x0000FFFF);
    const uint16_t lo = static_cast<uint16_t>((dec >>  0) & 0x0000FFFF);
    dec_to_hex(hi, buffer + 0, size);
    dec_to_hex(lo, buffer + 4, bit::bsa::sub(size, 4));
    return (size >= 8);
}
inline const bool string_util::dec_to_hex(const uint64_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint32_t hi = static_cast<uint32_t>((dec >> 32) & 0x00000000FFFFFFFF);
    const uint32_t lo = static_cast<uint32_t>((dec >>  0) & 0x00000000FFFFFFFF);
    dec_to_hex(hi, buffer + 0, size);
    dec_to_hex(lo, buffer + 8, bit::bsa::sub(size, 8));
    return (size >= 16);
}
inline const bool string_util::dec_to_hex(const uint8_t* dec, const size_t n, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint8_t* it = dec, *end = dec + n;
    char* carot = buffer;
    size_t remain = size;
    while (it && (it < end) && dec_to_hex(*it, carot, remain)) {
        ++it; carot += 2; remain -= 2;
    }
    return (size >= 2 * n);
}

// binary to decimal
inline const uint8_t string_util::bin_to_dec(const char bin) {
    return bit::bcl::iif(bin == '1', uint8_t(1), uint8_t(0));
}

// decimal to binary
inline const char string_util::dec_to_bin(const uint8_t dec) {
    static const uint8_t map[2] = { '0', '1' };
    return map[dec & 0x01];
}
inline const bool string_util::dec_to_bin(const uint8_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    if (gea_likely(size > 0))
        buffer[0] = dec_to_bin((dec >> 7) & 0x01);
    if (gea_likely(size > 1))
        buffer[1] = dec_to_bin((dec >> 6) & 0x01);
    if (gea_likely(size > 2))
        buffer[2] = dec_to_bin((dec >> 5) & 0x01);
    if (gea_likely(size > 3))
        buffer[3] = dec_to_bin((dec >> 4) & 0x01);
    if (gea_likely(size > 4))
        buffer[4] = dec_to_bin((dec >> 3) & 0x01);
    if (gea_likely(size > 5))
        buffer[5] = dec_to_bin((dec >> 2) & 0x01);
    if (gea_likely(size > 6))
        buffer[6] = dec_to_bin((dec >> 1) & 0x01);
    if (gea_likely(size > 7))
        buffer[7] = dec_to_bin((dec >> 0) & 0x01);
    return (size >= 8);
}
inline const bool string_util::dec_to_bin(const uint16_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint8_t hi = static_cast<uint8_t>((dec >> 8) & 0x00FF);
    const uint8_t lo = static_cast<uint8_t>((dec >> 0) & 0x00FF);
    dec_to_bin(hi, buffer + 0, size);
    dec_to_bin(lo, buffer + 8, bit::bsa::sub(size, 8));
    return (size >= 16);
}
inline const bool string_util::dec_to_bin(const uint32_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint16_t hi = static_cast<uint16_t>((dec >> 16) & 0x0000FFFF);
    const uint16_t lo = static_cast<uint16_t>((dec >>  0) & 0x0000FFFF);
    dec_to_bin(hi, buffer +  0, size);
    dec_to_bin(lo, buffer + 16, bit::bsa::sub(size, 16));
    return (size >= 32);
}
inline const bool string_util::dec_to_bin(const uint64_t dec, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint32_t hi = static_cast<uint32_t>((dec >> 32) & 0x00000000FFFFFFFF);
    const uint32_t lo = static_cast<uint32_t>((dec >>  0) & 0x00000000FFFFFFFF);
    dec_to_bin(hi, buffer +  0, size);
    dec_to_bin(lo, buffer + 32, bit::bsa::sub(size, 32));
    return (size >= 64);
}
inline const bool string_util::dec_to_bin(const uint8_t* dec, const size_t n, char* buffer, const size_t size) {
    if (gea_unlikely(!buffer)) return false;

    const uint8_t* it = dec, *end = dec + n;
    char* carot = buffer;
    size_t remain = size;
    while (it && (it < end) && dec_to_bin(*it, carot, remain)) {
        ++it; carot += 8; remain -= 8;
    }
    return (size >= 8 * n);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
