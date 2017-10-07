// header include 
#include "bit_stream.h"

// gea includes
#include <gea/core/bits/bsa.h>
#include <gea/mth_core/base.h>
#include <gea/mth_core/bits.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// bit_ostream                                                               //
// ------------------------------------------------------------------------- //
// interface functions
void bit_ostream::flush() {}

// floating point numbers
void bit_ostream::write_float(const float f) {}
void bit_ostream::write_double(const double d) {}

// signed integers
void bit_ostream::write_int8(const int8_t s, const int8_t min, const int8_t max) {
    l_assert_msg(mth::range(s, min, max) && (min <= max), "invalid arguments!");
    const uint8_t span = uint8_t(max - min);
    const uint8_t mask = mth::bit::mask(span);
    const uint8_t size = mth::bit::toc(mask);
    write_internal(uint32_t(s - min), mask, size);
}
void bit_ostream::write_int16(const int16_t s, const int16_t min, const int16_t max) {
    l_assert_msg(mth::range(s, min, max) && (min <= max), "invalid arguments!");
    uint16_t span = uint16_t(max - min);
    uint16_t mask = mth::bit::mask(span);
    uint8_t  size = mth::bit::toc(mask);
    write_internal(uint32_t(s - min), mask, size);
}
void bit_ostream::write_int32(const int32_t s, const int32_t min, const int32_t max) {
    l_assert_msg(mth::range(s, min, max) && (min <= max), "invalid arguments!");
    uint32_t span = uint32_t(max - min);
    uint32_t mask = mth::bit::mask(span);
    uint8_t  size = mth::bit::toc(mask);
    write_internal(uint32_t(s - min), mask, size);
}
void bit_ostream::write_int64(const int64_t s, const int64_t min, const int64_t max) {
    l_assert_msg(mth::range(s, min, max) && (min <= max), "invalid arguments!");
    uint64_t span = uint64_t(max - min);
    uint64_t mask = mth::bit::mask(span);
    uint8_t  size = mth::bit::toc(mask);
    write_internal(uint32_t((s - min) >> 32), uint32_t(mask >> 32), mth::clamp(bit::bsa::sub(size, 32), uint8_t(0), uint8_t(32)));
    write_internal(uint32_t((s - min) >>  0), uint32_t(mask >>  0), mth::clamp(bit::bsa::sub(size,  0), uint8_t(0), uint8_t(32)));
}

// unsigned integers
void bit_ostream::write_uint8(const uint8_t u, const uint8_t min, const uint8_t max) {
    l_assert_msg(mth::range(u, min, max) && (min <= max), "invalid arguments!");
    uint8_t span = uint8_t(max - min);
    uint8_t mask = mth::bit::mask(span);
    uint8_t size = mth::bit::toc(mask);
    write_internal(uint32_t(u - min), mask, size);
}
void bit_ostream::write_uint16(const uint16_t u, const uint16_t min, const uint16_t max) {
    l_assert_msg(mth::range(u, min, max) && (min <= max), "invalid arguments!");
    uint16_t span = uint16_t(max - min);
    uint16_t mask = mth::bit::mask(span);
    uint8_t  size = mth::bit::toc(mask);
    write_internal(uint32_t(u - min), mask, size);
}
void bit_ostream::write_uint32(const uint32_t u, const uint32_t min, const uint32_t max) {
    l_assert_msg(mth::range(u, min, max) && (min <= max), "invalid arguments!");
    uint32_t span = uint32_t(max - min);
    uint32_t mask = mth::bit::mask(span);
    uint8_t  size = mth::bit::toc(mask);
    write_internal(uint32_t(u - min), mask, size);
}
void bit_ostream::write_uint64(const uint64_t u, const uint64_t min, const uint64_t max) {
    l_assert_msg(mth::range(u, min, max) && (min <= max), "invalid arguments!");
    uint64_t span = uint64_t(max - min);
    uint64_t mask = mth::bit::mask(span);
    uint8_t  size = mth::bit::toc(mask);
    write_internal(uint32_t((u - min) >> 32), uint32_t(mask >> 32), mth::clamp(bit::bsa::sub(size, 32), uint8_t(0), uint8_t(32)));
    write_internal(uint32_t((u - min) >>  0), uint32_t(mask >>  0), mth::clamp(bit::bsa::sub(size,  0), uint8_t(0), uint8_t(32)));
}

// boolean
void bit_ostream::write_bool(const bool b) {
    write_internal(uint32_t(b), 0x00000001, 1);
}

void bit_ostream::write_internal(const uint32_t bits, const uint32_t mask, const uint8_t size) {
    l_assert_implement;
}

// ------------------------------------------------------------------------- //
// bit_istream                                                               //
// ------------------------------------------------------------------------- //
// floating point numbers
const float bit_istream::read_float() {
    l_assert_implement;
    return 0.0f;
}
const double bit_istream::read_double() {
    l_assert_implement;
    return 0.0;
}
// signed integers
const int8_t bit_istream::read_int8(const int8_t  min, const int8_t  max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0;
}
const int16_t bit_istream::read_int16(const int16_t min, const int16_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0;
}
const int32_t bit_istream::read_int32(const int32_t min, const int32_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0;
}
const int64_t bit_istream::read_int64(const int64_t min, const int64_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0;
}
// unsigned integers
const uint8_t bit_istream::read_uint8(const uint8_t  min, const uint8_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0u;
}
const uint16_t bit_istream::read_uint16(const uint16_t min, const uint16_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0u;
}
const uint32_t bit_istream::read_uint32(const uint32_t min, const uint32_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0u;
}
const uint64_t bit_istream::read_uint64(const uint64_t min, const uint64_t max) {
    l_assert_msg((min <= max), "invalid arguments!");
    l_assert_implement;
    return 0u;
}
// boolean
const bool bit_istream::read_bool() {
    l_assert_implement;
    return false;
}

} // namespace gea //
