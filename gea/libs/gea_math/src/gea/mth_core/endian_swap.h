#ifndef __GEA_BMTH_ENDIAN_SWAP_H__
#define __GEA_BMTH_ENDIAN_SWAP_H__

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// little <-> big endian conversion                                          //
// ------------------------------------------------------------------------- //

// template definition
template <typename T> inline void endian_swap(T &out_t);

// template specialization of common intrincics
template <> inline void endian_swap<bool>    (bool     &out_t);
template <> inline void endian_swap<int8_t>  (int8_t   &out_t);
template <> inline void endian_swap<uint8_t> (uint8_t  &out_t);
template <> inline void endian_swap<int16_t> (int16_t  &out_t);
template <> inline void endian_swap<uint16_t>(uint16_t &out_t);
template <> inline void endian_swap<int32_t> (int32_t  &out_t);
template <> inline void endian_swap<uint32_t>(uint32_t &out_t);
template <> inline void endian_swap<int64_t> (int64_t  &out_t);
template <> inline void endian_swap<uint64_t>(uint64_t &out_t);

template <> inline void endian_swap<float>   (float    &out_t);
template <> inline void endian_swap<double>  (double   &out_t);

} // namespace mth //
} // namespace gea //

#include "endian_swap.inl"

#endif // __GEA_BMTH_ENDIAN_SWAP_H__ //
