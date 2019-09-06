#pragma once
#include "bits.h"

namespace gea {
namespace bit {

// ------------------------------------------------------------------------- //
// bit hacks                                                                 //
// ------------------------------------------------------------------------- //
// implemented using the SWAR population count algorithm
inline const uint8_t ones(uint8_t x)  {
    static const uint8_t S[] = {1u, 2u, 4u};
    static const uint8_t B[] = {0x55u, 0x33u, 0x0Fu};
    static const uint8_t M = 0x3Fu;

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    return static_cast<uint8_t>(x & M);
}
inline const uint8_t ones(uint16_t x)  {
    static const uint16_t S[] = {1u, 2u, 4u, 8u};
    static const uint16_t B[] = {0x5555u, 0x3333u, 0x0F0Fu, 0x00FFu};
    static const uint16_t M = 0x003Fu;

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    x = ((x >> S[3]) + x) & B[3];
    return static_cast<uint8_t>(x & M);
}
inline const uint8_t ones(uint32_t x)  {
    static const uint32_t S[] = {1u, 2u, 4u, 8u, 16u};
    static const uint32_t B[] = {0x55555555u, 0x33333333u, 0x0F0F0F0Fu, 0x00FF00FFu, 0x0000FFFFu};
    static const uint32_t M = 0x0000003Fu;

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    x = ((x >> S[3]) + x) & B[3];
    x = ((x >> S[4]) + x) & B[4];
    return static_cast<uint8_t>(x & M);
}
inline const uint8_t ones(uint64_t x)  {
    static const uint64_t S[] = {1u, 2u, 4u, 8u, 16u, 32u};
    static const uint64_t B[] = {0x5555555555555555u, 0x3333333333333333u, 0x0F0F0F0F0F0F0F0Fu,
                                 0x00FF00FF00FF00FFu, 0x0000FFFF0000FFFFu, 0x00000000FFFFFFFFu};
    static const uint64_t M = 0x000000000000003Fu;

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    x = ((x >> S[3]) + x) & B[3];
    x = ((x >> S[4]) + x) & B[4];
    x = ((x >> S[5]) + x) & B[5];
    return static_cast<uint8_t>(x & M);
}

// ------------------------------------------------------------------------- //
inline const uint8_t zeros(const uint8_t  x) { return (8  - ones(x)); }
inline const uint8_t zeros(const uint16_t x) { return (16 - ones(x)); }
inline const uint8_t zeros(const uint32_t x) { return (32 - ones(x)); }
inline const uint8_t zeros(const uint64_t x) { return (64 - ones(x)); }

// ------------------------------------------------------------------------- //
inline const uint8_t lzc(uint8_t x) {
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    return zeros(x);
}
inline const uint8_t lzc(uint16_t x) {
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    return zeros(x);
}
inline const uint8_t lzc(uint32_t x) {
    x |= (x >>  1u);
    x |= (x >>  2u);
    x |= (x >>  4u);
    x |= (x >>  8u);
    x |= (x >> 16u);
    return zeros(x);
}
inline const uint8_t lzc(uint64_t x) {
    x |= (x >>  1u);
    x |= (x >>  2u);
    x |= (x >>  4u);
    x |= (x >>  8u);
    x |= (x >> 16u);
    x |= (x >> 32u);
    return zeros(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t tzc(uint8_t  x) {
    x |= (x << 1u);
    x |= (x << 2u);
    x |= (x << 4u);
    return zeros(x);
}
inline const uint8_t tzc(uint16_t x) {
    x |= (x << 1u);
    x |= (x << 2u);
    x |= (x << 4u);
    x |= (x << 8u);
    return zeros(x);
}
inline const uint8_t tzc(uint32_t x) {
    x |= (x << 1u);
    x |= (x << 2u);
    x |= (x << 4u);
    x |= (x << 8u);
    x |= (x << 16u);
    return zeros(x);
}
inline const uint8_t tzc(uint64_t x) {
    x |= (x << 1u);
    x |= (x << 2u);
    x |= (x << 4u);
    x |= (x << 8u);
    x |= (x << 16u);
    x |= (x << 32u);
    return zeros(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t loc(uint8_t x) {
    x &= (x >> 1u) | 0x80u;
    x &= (x >> 2u) | 0xC0u;
    x &= (x >> 4u) | 0xF0u;
    return ones(x);
}
inline const uint8_t loc(uint16_t x) {
    x &= (x >> 1u) | 0x8000u;
    x &= (x >> 2u) | 0xC000u;
    x &= (x >> 4u) | 0xF000u;
    x &= (x >> 8u) | 0xFF00u;
    return ones(x);
}
inline const uint8_t loc(uint32_t x) {
    x &= (x >> 1u)  | 0x80000000u;
    x &= (x >> 2u)  | 0xC0000000u;
    x &= (x >> 4u)  | 0xF0000000u;
    x &= (x >> 8u)  | 0xFF000000u;
    x &= (x >> 16u) | 0xFFFF0000u;
    return ones(x);
}
inline const uint8_t loc(uint64_t x) {
    x &= (x >> 1u)  | 0x8000000000000000u;
    x &= (x >> 2u)  | 0xC000000000000000u;
    x &= (x >> 4u)  | 0xF000000000000000u;
    x &= (x >> 8u)  | 0xFF00000000000000u;
    x &= (x >> 16u) | 0xFFFF000000000000u;
    x &= (x >> 32u) | 0xFFFFFFFF00000000u;
    return ones(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t toc(uint8_t  x) {
    x &= (x << 1u) | 0x01u;
    x &= (x << 2u) | 0x03u;
    x &= (x << 4u) | 0x0Fu;
    return ones(x);
}
inline const uint8_t toc(uint16_t x) {
    x &= (x << 1u) | 0x0001u;
    x &= (x << 2u) | 0x0003u;
    x &= (x << 4u) | 0x000Fu;
    x &= (x << 8u) | 0x00FFu;
    return ones(x);
}
inline const uint8_t toc(uint32_t x) {
    x &= (x << 1u)  | 0x00000001u;
    x &= (x << 2u)  | 0x00000003u;
    x &= (x << 4u)  | 0x0000000Fu;
    x &= (x << 8u)  | 0x000000FFu;
    x &= (x << 16u) | 0x0000FFFFu;
    return ones(x);
}
inline const uint8_t toc(uint64_t x) {
    x &= (x << 1u)  | 0x0000000000000001u;
    x &= (x << 2u)  | 0x0000000000000003u;
    x &= (x << 4u)  | 0x000000000000000Fu;
    x &= (x << 8u)  | 0x00000000000000FFu;
    x &= (x << 16u) | 0x000000000000FFFFu;
    x &= (x << 32u) | 0x00000000FFFFFFFFu;
    return ones(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t  lbs(const uint8_t  x) { return x & (~x + 1u); }
inline const uint16_t lbs(const uint16_t x) { return x & (~x + 1u); }
inline const uint32_t lbs(const uint32_t x) { return x & (~x + 1u); }
inline const uint64_t lbs(const uint64_t x) { return x & (~x + 1u); }

// ------------------------------------------------------------------------- //
inline const uint8_t rpow2(uint8_t x) {
    --x;
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    return ++x;
}
inline const uint16_t rpow2(uint16_t x) {
    --x;
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    return ++x;
}
inline const uint32_t rpow2(uint32_t x) {
    --x;
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    x |= (x >> 16u);
    return ++x;
}
inline const uint64_t rpow2(uint64_t x) {
    --x;
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    x |= (x >> 16u);
    x |= (x >> 32u);
    return ++x;
}

// ------------------------------------------------------------------------- //
inline const uint8_t mask(uint8_t x) {
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    return x;
}
inline const uint16_t mask(uint16_t x) {
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    return x;
}
inline const uint32_t mask(uint32_t x) {
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    x |= (x >> 16u);
    return x;
}
inline const uint64_t mask(uint64_t x) {
    x |= (x >> 1u);
    x |= (x >> 2u);
    x |= (x >> 4u);
    x |= (x >> 8u);
    x |= (x >> 16u);
    x |= (x >> 32u);
    return x;
}

// ------------------------------------------------------------------------- //
inline const bool is_pow2(const uint8_t x) {
    return x && !(x & (x - 1));
}
inline const bool is_pow2(const uint16_t x) {
    return x && !(x & (x - 1));
}
inline const bool is_pow2(const uint32_t x) {
    return x && !(x & (x - 1));
}
inline const bool is_pow2(const uint64_t x) {
    return x && !(x & (x - 1));
}

// ------------------------------------------------------------------------- //

} // namespace bit //
} // namespace gea //
