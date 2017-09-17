#pragma once
#include "bsa.h"

namespace gea {
namespace bit {
namespace bsa {

// ------------------------------------------------------------------------- //
// branchfree saturating arithmetic                                          //
// (from: http://locklessinc.com/articles/sat_arithmetic/)                   //
// ------------------------------------------------------------------------- //

// addition
inline const uint8_t add(const uint8_t a, const uint8_t b) {
    uint8_t res = a + b;
    res |= -(res < a);
    return res;
}
inline const uint16_t add(const uint16_t a, const uint16_t b) {
    uint16_t res = a + b;
    res |= -(res < a);
    return res;
}
inline const uint32_t add(const uint32_t a, const uint32_t b) {
    uint32_t res = a + b;
    res |= -(res < a);
    return res;
}
inline const uint64_t add(const uint64_t a, const uint64_t b) {
    uint64_t res = a + b;
    res |= -(res < a);
    return res;
}

// subtraction
inline const uint8_t sub(const uint8_t a, const uint8_t b) {
    uint8_t res = a - b;
    res &= -(res <= a);
    return res;
}
inline const uint16_t sub(const uint16_t a, const uint16_t b) {
    uint16_t res = a - b;
    res &= -(res <= a);
    return res;
}
inline const uint32_t sub(const uint32_t a, const uint32_t b) {
    uint32_t res = a - b;
    res &= -(res <= a);
    return res;
}
inline const uint64_t sub(const uint64_t a, const uint64_t b) {
    uint64_t res = a - b;
    res &= -(res <= a);
    return res;
}

// division
inline const uint8_t div(const uint8_t a, const uint8_t b) {
    // no overflow possible
    return a / b;
}
inline const uint16_t div(const uint16_t a, const uint16_t b) {
    // no overflow possible
    return a / b;
}
inline const uint32_t div(const uint32_t a, const uint32_t b) {
    // no overflow possible
    return a / b;
}
inline const uint64_t div(const uint64_t a, const uint64_t b) {
    // no overflow possible
    return a / b;
}

// multiplication
inline const uint8_t mul(const uint8_t a, const uint8_t b) {
    const uint16_t res = static_cast<uint16_t>(a)* static_cast<uint16_t>(b);
    const uint8_t hi = (res >> 8);
    const uint8_t lo = (res >> 0);
    return (lo | -!!hi);
}
inline const uint16_t mul(const uint16_t a, const uint16_t b) {
    const uint32_t res = static_cast<uint32_t>(a)* static_cast<uint32_t>(b);
    const uint16_t hi = (res >> 16);
    const uint16_t lo = (res >>  0);
    return (lo | -!!hi);
}
inline const uint32_t mul(const uint32_t a, const uint32_t b) {
    const uint64_t res = static_cast<uint64_t>(a)* static_cast<uint64_t>(b);
    const uint32_t hi = (res >> 32);
    const uint32_t lo = (res >>  0);
    return (lo | -!!hi);
}
//inline const uint64_t mul(const uint64_t a, const uint64_t b) {
//    const uint128_t res = static_cast<uint128_t>(a)* static_cast<uint128_t>(b);
//    const uint64_t hi = (res >> 64);
//    const uint64_t lo = (res >>  0);
//    return (lo | -!!hi);
//}

} // namespace bsa //
} // namespace bit //
} // namespace gea //
