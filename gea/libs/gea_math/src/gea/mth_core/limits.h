#ifndef __GEA_MTH_CORE_LIMITS_H__
#define __GEA_MTH_CORE_LIMITS_H__

#include <limits>       // std::numeric_limits

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// limits                                                                    //
// ------------------------------------------------------------------------- //

template <typename T>
struct limits {
    inline static const T lowest();
    inline static const T highest();
};

// ------------------------------------------------------------------------- //

// floating point precition types
template <> struct limits<float>;
template <> struct limits<double>;

// signed integer types
template <> struct limits<int8_t>;
template <> struct limits<int16_t>;
template <> struct limits<int32_t>;
template <> struct limits<int64_t>;

// unsigned integer types
template <> struct limits<uint8_t>;
template <> struct limits<uint16_t>;
template <> struct limits<uint32_t>;
template <> struct limits<uint64_t>;

// ------------------------------------------------------------------------- //

} // namespace gea //
} // namespace mth //

#include "limits.inl"

#endif // __GEA_MTH_CORE_LIMITS_H__ //
