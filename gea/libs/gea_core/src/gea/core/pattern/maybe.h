#pragma once

// gea include
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// maybe                                                                     //
// ------------------------------------------------------------------------- //

template <typename T>
class maybe {
public:
    inline maybe();
    inline explicit maybe(const T& value);
    inline maybe(const maybe<T>& other);

    inline const bool has_value() const;
    inline T get_value(const T default_value) const;

    inline operator bool() const;

private:
    template <typename T2>
    friend const bool operator ==(const maybe<T2>& lhs, const maybe<T2>& rhs);

    union {
        const T m_value;
    };
    const bool m_has_value;
};

// empty template specialization
template <> struct maybe<void> {};

// ------------------------------------------------------------------------- //

template <typename T>
inline const bool operator ==(const maybe<T>& lhs, const maybe<T>& rhs);
template <typename T>
inline const bool operator !=(const maybe<T>& lhs, const maybe<T>& rhs);

inline const bool operator ==(const maybe<void>&, const maybe<void>&);
inline const bool operator !=(const maybe<void>&, const maybe<void>&);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "maybe.inl"
