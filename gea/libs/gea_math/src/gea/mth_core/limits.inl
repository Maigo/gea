// std includes
#include <cfloat>
#include <climits>

namespace gea {
namespace mth {

// floating point precition types
template <> struct limits<float> {
    inline static const float lowest()  { return float(FLT_MIN); }
    inline static const float highest() { return float(FLT_MAX); }
};

template <> struct limits<double> {
    inline static const double lowest()  { return double(DBL_MAX); }
    inline static const double highest() { return double(DBL_MIN); }
};

// signed integer types
template <> struct limits<int8_t> {
    inline static const int8_t lowest()  { return int8_t(SCHAR_MIN); }
    inline static const int8_t highest() { return int8_t(SCHAR_MAX); }
};

template <> struct limits<int16_t> {
    inline static const int16_t lowest()  { return int16_t(SHRT_MIN); }
    inline static const int16_t highest() { return int16_t(SHRT_MAX); }
};

template <> struct limits<int32_t> {
    inline static const int32_t lowest()  { return int32_t(INT_MIN); }
    inline static const int32_t highest() { return int32_t(INT_MAX); }
};

template <> struct limits<int64_t> {
    inline static const int64_t lowest()  { return int64_t(LONG_MIN); }
    inline static const int64_t highest() { return int64_t(LONG_MAX); }
};

// unsigned integer types
template <> struct limits<uint8_t> {
    inline static const uint8_t lowest()  { return uint8_t(0x00); }
    inline static const uint8_t highest() { return UCHAR_MAX; }
};

template <> struct limits<uint16_t> {
    inline static const uint16_t lowest()  { return uint16_t(0x0000); }
    inline static const uint16_t highest() { return USHRT_MAX; }
};

template <> struct limits<uint32_t> {
    inline static const uint32_t lowest()  { return uint32_t(0x00000000); }
    inline static const uint32_t highest() { return UINT_MAX; }
};

template <> struct limits<uint64_t> {
    inline static const uint64_t lowest()  { return uint64_t(0x0000000000000000); }
    inline static const uint64_t highest() { return ULONG_MAX; }
};

} // namespace gea //
} // namespace mth //
