#pragma once

// header include
#include "maybe.h"

namespace gea {

// ------------------------------------------------------------------------- //
// maybe                                                                     //
// ------------------------------------------------------------------------- //

template <typename T>
inline maybe<T>::maybe() : m_has_value(false) {}
template <typename T>
inline maybe<T>::maybe(const T& value) : m_value(value), m_has_value(true) {}
template <typename T>
inline maybe<T>::maybe(const maybe<T>& other) : m_value(other.m_value), m_has_value(other.m_has_value) {}

template <typename T>
inline const bool maybe<T>::has_value() const { return m_has_value; }
template <typename T>
inline T maybe<T>::get_value(const T default_value) const {
    return m_has_value ? m_value : default_value;
}

template <typename T>
inline maybe<T>::operator bool() const { return m_has_value; }

// ------------------------------------------------------------------------- //

template <typename T>
inline const bool operator ==(const maybe<T>& lhs, const maybe<T>& rhs) {
    return (!lhs.m_has_value && !rhs.m_has_value) ||
        (lhs.m_has_value && rhs.m_has_value && (lhs.m_value == rhs.m_value));
}
template <typename T>
inline const bool operator !=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(lhs == rhs);
}

inline const bool operator ==(const maybe<void>&, const maybe<void>&) { return true; }
inline const bool operator !=(const maybe<void>&, const maybe<void>&) { return false; }

// ------------------------------------------------------------------------- //

} // namespace gea //
