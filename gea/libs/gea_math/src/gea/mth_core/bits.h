#ifndef __GEA_MTH_CORE_BITS_H__
#define __GEA_MTH_CORE_BITS_H__

namespace gea {
namespace mth {
namespace bit {

// ------------------------------------------------------------------------- //
// bit hacks                                                                 //
// ------------------------------------------------------------------------- //
// count # of ones
inline const uint8_t ones(uint8_t  x);
inline const uint8_t ones(uint16_t x);
inline const uint8_t ones(uint32_t x);
//inline const uint8_t ones(uint64_t x);

// ------------------------------------------------------------------------- //
// count # of zeros
inline const uint8_t zeros(const uint8_t  x);
inline const uint8_t zeros(const uint16_t x);
inline const uint8_t zeros(const uint32_t x);
//inline const uint8_t zeros(const uint64_t x);

// ------------------------------------------------------------------------- //
// count # of leading zeroes
inline const uint8_t lzc(uint8_t  x);
inline const uint8_t lzc(uint16_t x);
inline const uint8_t lzc(uint32_t x);
//inline const uint8_t lzc(uint64_t x);

// ------------------------------------------------------------------------- //
// count # of trailing zeroes
inline const uint8_t tzc(uint8_t  x);
inline const uint8_t tzc(uint16_t x);
inline const uint8_t tzc(uint32_t x);
//inline const uint8_t tzc(uint64_t x);

// ------------------------------------------------------------------------- //
// count # of leading ones
inline const uint8_t loc(uint8_t  x);
inline const uint8_t loc(uint16_t x);
inline const uint8_t loc(uint32_t x);
//inline const uint8_t loc(uint64_t x);

// ------------------------------------------------------------------------- //
// count # of trailing ones
inline const uint8_t toc(uint8_t  x);
inline const uint8_t toc(uint16_t x);
inline const uint8_t toc(uint32_t x);
//inline const uint8_t toc(uint64_t x);

// ------------------------------------------------------------------------- //
// lowest bit set
inline const uint8_t  lbs(const uint8_t  x);
inline const uint16_t lbs(const uint16_t x);
inline const uint32_t lbs(const uint32_t x);
//inline const uint64_t lbs(const uint64_t x);

// ------------------------------------------------------------------------- //
// round up to the next highest power of 2
inline const uint8_t  rpow2(uint8_t  x);
inline const uint16_t rpow2(uint16_t x);
inline const uint32_t rpow2(uint32_t x);
//inline const uint64_t rpow2(uint64_t x);

// ------------------------------------------------------------------------- //
// derive smallest mask to encompass number
inline const uint8_t  mask(uint8_t  x);
inline const uint16_t mask(uint16_t x);
inline const uint32_t mask(uint32_t x);
//inline const uint64_t mask(uint64_t x);

// ------------------------------------------------------------------------- //

} // namespace bit //
} // namespace mth //
} // namespace gea //

#include "bits.inl"

#endif // __GEA_MTH_CORE_BITS_H__ //
