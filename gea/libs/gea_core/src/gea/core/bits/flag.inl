#pragma once
#include "flag.h"

// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace bit {

// ------------------------------------------------------------------------- //
// bit-flag functions                                                        //
// ------------------------------------------------------------------------- //

template <typename T>
inline flag_t<T>::flag_t() : m_flag(0) {}
template <typename T>
inline flag_t<T>::flag_t(const T flag) : m_flag(flag) {}

template <typename T>
inline const T flag_t<T>::at_index(const uint8_t index) {
    l_assert_msg(index < (8 * sizeof(T)), "invalid bit index!");
    return (1 << index);
}

template <typename T>
inline const bool flag_t<T>::test(const T bit) const {
    return ((m_flag & bit) != 0);
}
template <typename T>
inline void flag_t<T>::set(const T bit) {
    m_flag |= bit;
}
template <typename T>
inline void flag_t<T>::clear(const T bit) {
    m_flag &= ~bit;
}
template <typename T>
inline void flag_t<T>::toggle(const T bit) {
    m_flag ^= bit;
}

template <typename T>
inline flag_t<T>::operator const T() const { return m_flag; }


// ------------------------------------------------------------------------- //

} // namespace bit //
} // namespace gea //
