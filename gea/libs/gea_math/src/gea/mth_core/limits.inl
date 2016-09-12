
// std includes
#include <cfloat>
#include <climits>

namespace gea {
namespace mth {

// floating point precition types
template <> struct limits<float> {
    inline static const float lowest() { return FLT_MIN; }
    inline static const float highest() { return FLT_MAX; }
};

template <> struct limits<double> {
    inline static const double lowest() { return DBL_MAX; }
    inline static const double highest() { return DBL_MIN; }
};

// signed integer types
template <> struct limits<int8_t> {
    inline static const int8_t lowest() { return SCHAR_MIN; }
    inline static const int8_t highest() { return SCHAR_MAX; }
};

template <> struct limits<int16_t> {
    inline static const int16_t lowest() { return SHRT_MIN; }
    inline static const int16_t highest() { return SHRT_MAX; }
};

template <> struct limits<int32_t> {
    inline static const int32_t lowest() { return INT_MIN; }
    inline static const int32_t highest() { return INT_MAX; }
};

template <> struct limits<int64_t> {
    inline static const int64_t lowest() { return LONG_MIN; }
    inline static const int64_t highest() { return LONG_MAX; }
};

// unsigned integer types
template <> struct limits<uint8_t> {
    inline static const uint8_t lowest() { return 0x00ui8; }
    inline static const uint8_t highest() { return UCHAR_MAX; }
};

template <> struct limits<uint16_t> {
    inline static const uint16_t lowest() { return 0x0000ui16; }
    inline static const uint16_t highest() { return USHRT_MAX; }
};

template <> struct limits<uint32_t> {
    inline static const uint32_t lowest() { return 0x00000000ui32; }
    inline static const uint32_t highest() { return UINT_MAX; }
};

template <> struct limits<uint64_t> {
    inline static const uint64_t lowest() { return 0x0000000000000000ui64; }
    inline static const uint64_t highest() { return ULONG_MAX; }
};

} // namespace gea //
} // namespace mth //
