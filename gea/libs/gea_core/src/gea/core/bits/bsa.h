#pragma once

namespace gea {
namespace bit {
namespace bsa {

// ------------------------------------------------------------------------- //
// branchfree saturating arithmetic                                          //
// (from: http://locklessinc.com/articles/sat_arithmetic/)                   //
// ------------------------------------------------------------------------- //

// addition
inline const uint8_t  add(const uint8_t  a, const uint8_t  b);
inline const uint16_t add(const uint16_t a, const uint16_t b);
inline const uint32_t add(const uint32_t a, const uint32_t b);
inline const uint64_t add(const uint64_t a, const uint64_t b);

// subtraction
inline const uint8_t  sub(const uint8_t  a, const uint8_t  b);
inline const uint16_t sub(const uint16_t a, const uint16_t b);
inline const uint32_t sub(const uint32_t a, const uint32_t b);
inline const uint64_t sub(const uint64_t a, const uint64_t b);

// division
inline const uint8_t  div(const uint8_t  a, const uint8_t  b);
inline const uint16_t div(const uint16_t a, const uint16_t b);
inline const uint32_t div(const uint32_t a, const uint32_t b);
inline const uint64_t div(const uint64_t a, const uint64_t b);

// multiplication
inline const uint8_t  mul(const uint8_t  a, const uint8_t  b);
inline const uint16_t mul(const uint16_t a, const uint16_t b);
inline const uint32_t mul(const uint32_t a, const uint32_t b);
//inline const uint64_t mul(const uint64_t a, const uint64_t b);

} // namespace bsa //
} // namespace bit //
} // namespace gea //

#include "bsa.inl"
