#pragma once

namespace gea {
namespace bit {

// ------------------------------------------------------------------------- //
// bit-flag functions                                                        //
// ------------------------------------------------------------------------- //

template <typename T>
class flag_t {
public:
    typedef T value_type;

    inline flag_t();
    inline explicit flag_t(const T flag);

    static inline const T at_index(const uint8_t index);

    inline const bool test(const T bit) const;
    inline void set(const T bit);
    inline void clear(const T bit);
    inline void toggle(const T bit);

    inline operator const T() const;

private:
    T m_flag;
};

// typedefs for common flag types
typedef flag_t<uint8_t>  flag8_t;
typedef flag_t<uint16_t> flag16_t;
typedef flag_t<uint32_t> flag32_t;
typedef flag_t<uint64_t> flag64_t;

// ------------------------------------------------------------------------- //

} // namespace bit //
} // namespace gea //

#include "flag.inl"
