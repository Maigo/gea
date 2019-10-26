#pragma once

// gea includes
#include <gea/core/pattern/maybe.h>

namespace gea {

// ------------------------------------------------------------------------- //
// either                                                                    //
// ------------------------------------------------------------------------- //

template <typename L, typename R>
class either {
public:
    inline either();
    inline either(const either<L, R>& other);
    static inline const either left(const L& l);
    static inline const either right(const R& r);

    inline const bool has_left() const;
    inline const maybe<L> get_left() const;
    inline const L get_left(const L default_value) const;
    inline const bool has_right() const;
    inline const maybe<R> get_right() const;
    inline const R get_right(const R default_value) const;

private:
    struct left_type { L value; };
    struct right_type { R value; };
    inline either(const left_type& l);
    inline either(const right_type& r);

    template <typename L2, typename R2>
    friend const bool operator ==(const either<L2, R2>& lhs, const either<L2, R2>& rhs);

    union {
        L m_left_value;
        R m_right_value;
    };
    const bool m_has_left_value : 1;
    const bool m_has_right_value : 1;
};

// ------------------------------------------------------------------------- //

template <typename L, typename R>
inline const bool operator ==(const either<L, R>& lhs, const either<L, R>& rhs);
template <typename L, typename R>
inline const bool operator !=(const either<L, R>& lhs, const either<L, R>& rhs);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "either.inl"
