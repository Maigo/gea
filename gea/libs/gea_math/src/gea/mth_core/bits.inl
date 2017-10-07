#pragma once
#include "bits.h"

namespace gea {
namespace mth {
namespace bit {

// ------------------------------------------------------------------------- //
// bit hacks                                                                 //
// ------------------------------------------------------------------------- //
// implemented using the SWAR population count algorithm
inline const uint8_t ones(uint8_t x)  {
    static const uint8_t S[] = {1, 2, 4};
    static const uint8_t B[] = {0x55, 0x33, 0x0F};

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    return static_cast<uint8_t>(x & 0x3F);
}
inline const uint8_t ones(uint16_t x)  {
    static const uint16_t S[] = {1, 2, 4, 8};
    static const uint16_t B[] = {0x5555, 0x3333, 0x0F0F, 0x00FF};

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    x = ((x >> S[3]) + x) & B[3];
    return static_cast<uint8_t>(x & 0x003F);
}
inline const uint8_t ones(uint32_t x)  {
    static const uint32_t S[] = {1, 2, 4, 8, 16};
    static const uint32_t B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    x = ((x >> S[3]) + x) & B[3];
    x = ((x >> S[4]) + x) & B[4];
    return static_cast<uint8_t>(x & 0x0000003F);
}
inline const uint8_t ones(uint64_t x)  {
    static const uint64_t S[] = {1, 2, 4, 8, 16, 32};
    static const uint64_t B[] = {0x5555555555555555, 0x3333333333333333, 0x0F0F0F0F0F0F0F0F,
                                 0x00FF00FF00FF00FF, 0x0000FFFF0000FFFF, 0x00000000FFFFFFFF};

    x = x - ((x >> 1) & B[0]);
    x = ((x >> S[1]) & B[1]) + (x & B[1]);
    x = ((x >> S[2]) + x) & B[2];
    x = ((x >> S[3]) + x) & B[3];
    x = ((x >> S[4]) + x) & B[4];
    x = ((x >> S[5]) + x) & B[5];
    return static_cast<uint8_t>(x & 0x000000000000003F);
}

// ------------------------------------------------------------------------- //
inline const uint8_t zeros(const uint8_t  x) { return (8  - ones(x)); }
inline const uint8_t zeros(const uint16_t x) { return (16 - ones(x)); }
inline const uint8_t zeros(const uint32_t x) { return (32 - ones(x)); }
inline const uint8_t zeros(const uint64_t x) { return (64 - ones(x)); }

// ------------------------------------------------------------------------- //
inline const uint8_t lzc(uint8_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    return zeros(x);
}
inline const uint8_t lzc(uint16_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    return zeros(x);
}
inline const uint8_t lzc(uint32_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return zeros(x);
}
inline const uint8_t lzc(uint64_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    return zeros(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t tzc(uint8_t  x) {
    x |= (x << 1);
    x |= (x << 2);
    x |= (x << 4);
    return zeros(x);
}
inline const uint8_t tzc(uint16_t x) {
    x |= (x << 1);
    x |= (x << 2);
    x |= (x << 4);
    x |= (x << 8);
    return zeros(x);
}
inline const uint8_t tzc(uint32_t x) {
    x |= (x << 1);
    x |= (x << 2);
    x |= (x << 4);
    x |= (x << 8);
    x |= (x << 16);
    return zeros(x);
}
inline const uint8_t tzc(uint64_t x) {
    x |= (x << 1);
    x |= (x << 2);
    x |= (x << 4);
    x |= (x << 8);
    x |= (x << 16);
    x |= (x << 32);
    return zeros(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t loc(uint8_t x) {
    x &= (x >> 1) | 0x80u;
    x &= (x >> 2) | 0xC0u;
    x &= (x >> 4) | 0xF0u;
    return ones(x);
}
inline const uint8_t loc(uint16_t x) {
    x &= (x >> 1) | 0x8000u;
    x &= (x >> 2) | 0xC000u;
    x &= (x >> 4) | 0xF000u;
    x &= (x >> 8) | 0xFF00u;
    return ones(x);
}
inline const uint8_t loc(uint32_t x) {
    x &= (x >> 1)  | 0x80000000u;
    x &= (x >> 2)  | 0xC0000000u;
    x &= (x >> 4)  | 0xF0000000u;
    x &= (x >> 8)  | 0xFF000000u;
    x &= (x >> 16) | 0xFFFF0000u;
    return ones(x);
}
inline const uint8_t loc(uint64_t x) {
    x &= (x >> 1)  | 0x8000000000000000;
    x &= (x >> 2)  | 0xC000000000000000;
    x &= (x >> 4)  | 0xF000000000000000;
    x &= (x >> 8)  | 0xFF00000000000000;
    x &= (x >> 16) | 0xFFFF000000000000;
    x &= (x >> 32) | 0xFFFFFFFF00000000;
    return ones(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t toc(uint8_t  x) {
    x &= (x << 1) | 0x01u;
    x &= (x << 2) | 0x03u;
    x &= (x << 4) | 0x0Fu;
    return ones(x);
}
inline const uint8_t toc(uint16_t x) {
    x &= (x << 1) | 0x0001u;
    x &= (x << 2) | 0x0003u;
    x &= (x << 4) | 0x000Fu;
    x &= (x << 8) | 0x00FFu;
    return ones(x);
}
inline const uint8_t toc(uint32_t x) {
    x &= (x << 1)  | 0x00000001u;
    x &= (x << 2)  | 0x00000003u;
    x &= (x << 4)  | 0x0000000Fu;
    x &= (x << 8)  | 0x000000FFu;
    x &= (x << 16) | 0x0000FFFFu;
    return ones(x);
}
inline const uint8_t toc(uint64_t x) {
    x &= (x << 1)  | 0x0000000000000001;
    x &= (x << 2)  | 0x0000000000000003;
    x &= (x << 4)  | 0x000000000000000F;
    x &= (x << 8)  | 0x00000000000000FF;
    x &= (x << 16) | 0x000000000000FFFF;
    x &= (x << 32) | 0x00000000FFFFFFFF;
    return ones(x);
}

// ------------------------------------------------------------------------- //
inline const uint8_t  lbs(const uint8_t  x) { return x & (~x + 1); }
inline const uint16_t lbs(const uint16_t x) { return x & (~x + 1); }
inline const uint32_t lbs(const uint32_t x) { return x & (~x + 1); }
inline const uint64_t lbs(const uint64_t x) { return x & (~x + 1); }

// ------------------------------------------------------------------------- //
inline const uint8_t rpow2(uint8_t x) {
    --x;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    return ++x;
}
inline const uint16_t rpow2(uint16_t x) {
    --x;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    return ++x;
}
inline const uint32_t rpow2(uint32_t x) {
    --x;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return ++x;
}
inline const uint64_t rpow2(uint64_t x) {
    --x;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    return ++x;
}

// ------------------------------------------------------------------------- //
inline const uint8_t mask(uint8_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    return x;
}
inline const uint16_t mask(uint16_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    return x;
}
inline const uint32_t mask(uint32_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return x;
}
inline const uint64_t mask(uint64_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    return x;
}

// ------------------------------------------------------------------------- //

} // namespace bit //
} // namespace mth //
} // namespace gea //
