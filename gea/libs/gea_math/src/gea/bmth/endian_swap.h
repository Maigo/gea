#ifndef __GEA_BMTH_ENDIAN_SWAP_H__
#define __GEA_BMTH_ENDIAN_SWAP_H__

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// little <-> big endian conversion                                          //
// ------------------------------------------------------------------------- //

// template definition
template <typename T> inline void endian_swap(T &t);

// template specialization of common intrincics
template <> inline void endian_swap<bool>    (bool &t);
template <> inline void endian_swap<int8_t>  (int8_t &t);
template <> inline void endian_swap<uint8_t> (uint8_t &t);
template <> inline void endian_swap<int16_t> (int16_t &t);
template <> inline void endian_swap<uint16_t>(uint16_t &t);
template <> inline void endian_swap<int32_t> (int32_t &t);
template <> inline void endian_swap<uint32_t>(uint32_t &t);
template <> inline void endian_swap<int64_t> (int64_t &t);
template <> inline void endian_swap<uint64_t>(uint64_t &t);

template <> inline void endian_swap<float> (float &t);
template <> inline void endian_swap<double>(double &t);

} // namespace mth //
} // namespace gea //

#include "endian_swap.inl"

#endif // __GEA_BMTH_ENDIAN_SWAP_H__ //
