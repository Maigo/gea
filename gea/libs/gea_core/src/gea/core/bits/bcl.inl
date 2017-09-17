#pragma once
#include "bcl.h"

namespace gea {
namespace bit {
namespace bcl {

// ------------------------------------------------------------------------- //
// branchfree conditional logic                                              //
// ------------------------------------------------------------------------- //

// inline if
inline const uint8_t  iif(const bool c, const uint8_t  a, const uint8_t  b) {
    return b ^ ((a ^ b) & -(!!c));
}
inline const uint16_t iif(const bool c, const uint16_t a, const uint16_t b) {
    return b ^ ((a ^ b) & -(!!c));
}
inline const uint32_t iif(const bool c, const uint32_t a, const uint32_t b) {
    return b ^ ((a ^ b) & -(!!c));
}
inline const uint64_t iif(const bool c, const uint64_t a, const uint64_t b) {
    return b ^ ((a ^ b) & -(!!c));
}

// min - iif(a < b, a, b)
inline const uint8_t  min(const uint8_t  a, const uint8_t  b) {
    return b ^ ((a ^ b) & -(a < b));
}
inline const uint16_t min(const uint16_t a, const uint16_t b) {
    return b ^ ((a ^ b) & -(a < b));
}
inline const uint32_t min(const uint32_t a, const uint32_t b) {
    return b ^ ((a ^ b) & -(a < b));
}
inline const uint64_t min(const uint64_t a, const uint64_t b) {
    return b ^ ((a ^ b) & -(a < b));
}

// max - iif(a < b, b, a)
inline const uint8_t  max(const uint8_t  a, const uint8_t  b) {
    return a ^ ((a ^ b) & -(a < b));
}
inline const uint16_t max(const uint16_t a, const uint16_t b) {
    return a ^ ((a ^ b) & -(a < b));
}
inline const uint32_t max(const uint32_t a, const uint32_t b) {
    return a ^ ((a ^ b) & -(a < b));
}
inline const uint64_t max(const uint64_t a, const uint64_t b) {
    return a ^ ((a ^ b) & -(a < b));
}

} // namespace bcl //
} // namespace bit //
} // namespace gea //
