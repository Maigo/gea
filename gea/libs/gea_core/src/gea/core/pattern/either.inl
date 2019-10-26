#pragma once

// header include
#include "either.h"

namespace gea {

// ------------------------------------------------------------------------- //
// either                                                                    //
// ------------------------------------------------------------------------- //

template <typename L, typename R>
inline either<L, R>::either() : m_has_left_value(false), m_has_right_value(false) {}
template <typename L, typename R>
inline either<L, R>::either(const either<L, R>& other) : m_has_left_value(other.m_has_left_value), m_has_right_value(other.m_has_right_value) {
    if (m_has_left_value)
        m_left_value = other.m_left_value;
    else if (m_has_right_value)
        m_right_value = other.m_right_value;
}
template <typename L, typename R>
inline const either<L, R> either<L, R>::left(const L& l) { return either(either::left_type{ l }); }
template <typename L, typename R>
inline const either<L, R> either<L, R>::right(const R& r) { return either(either::right_type{ r }); }

template <typename L, typename R>
inline const bool either<L, R>::has_left() const { return m_has_left_value; }
template <typename L, typename R>
inline const maybe<L> either<L, R>::get_left() const {
    return m_has_left_value ? maybe<L>(m_left_value) : maybe<L>();
}
template <typename L, typename R>
inline const L either<L, R>::get_left(const L default_value) const {
    return m_has_left_value ? m_left_value : default_value;
}
template <typename L, typename R>
inline const bool either<L, R>::has_right() const { return m_has_right_value; }
template <typename L, typename R>
inline const maybe<R> either<L, R>::get_right() const {
    return m_has_right_value ? maybe<R>(m_right_value) : maybe<R>();
}
template <typename L, typename R>
inline const R either<L, R>::get_right(const R default_value) const {
    return m_has_right_value ? m_right_value : default_value;
}

template <typename L, typename R>
inline either<L, R>::either(const left_type& l) : m_left_value(l.value), m_has_left_value(true), m_has_right_value(false) {}
template <typename L, typename R>
inline either<L, R>::either(const right_type& r) : m_right_value(r.value), m_has_left_value(false), m_has_right_value(true) {}

// ------------------------------------------------------------------------- //

template <typename L, typename R>
inline const bool operator ==(const either<L, R>& lhs, const either<L, R>& rhs) {
    return (lhs.m_has_left_value && rhs.m_has_left_value && (lhs.m_left_value == rhs.m_has_left_value))
        || (rhs.m_has_right_value && rhs.m_has_right_value && (lhs.m_right_value == rhs.m_right_value));
}
template <typename L, typename R>
inline const bool operator !=(const either<L, R>& lhs, const either<L, R>& rhs) {
    return !(lhs == rhs);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
