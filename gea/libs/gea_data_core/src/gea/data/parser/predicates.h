#pragma once

// gea includes
#include <gea/core/math.h>

namespace gea {
namespace predicate {

// ------------------------------------------------------------------------- //
// predicates                                                                //
// ------------------------------------------------------------------------- //

template <typename Predicate>
struct not_p {
    static inline const bool test(const char c) { return !Predicate::test(c); }
};

template <char C>
struct is_character_p {
    static inline const bool test(const char c) {
        return (c == C);
    }
};
template <char C>
using is_not_character_p = not_p<is_character_p<C>>;

template <char C0, char C1>
struct is_character_range_p {
    static inline const bool test(const char c) {
        return (C0 <= c) && (c <= C1);
    }
};

struct is_whitespace_p {
    static inline const bool test(const char c) {
        // [\t\r\n ]
        return is_character_p<0x09>::test(c)
            || is_character_p<0x0A>::test(c)
            || is_character_p<0x0D>::test(c)
            || is_character_p<0x20>::test(c);
    }
};
using is_not_whitespace_p = not_p<is_whitespace_p>;

struct is_eol_p {
    static inline const bool test(const char c) {
        // [\r\n]
        return is_character_p<0x0A>::test(c)
            || is_character_p<0x0D>::test(c);
    }
};
using is_not_eol_p = not_p<is_eol_p>;

struct is_alpha_p {
    static inline const bool test(const char c) {
        // [A-Za-z]
        return is_character_range_p<'A', 'Z'>::test(c)
            || is_character_range_p<'a', 'z'>::test(c);
    }
};

typedef is_character_range_p<'0', '9'> is_num_p;

struct is_alpha_num_p {
    // [A-Za-z0-9]
    static inline const bool test(const char c) {
        return is_alpha_p::test(c)
            || is_num_p::test(c);
    }
};


typedef is_num_p is_integer_p;

struct is_float_p {
    static inline const bool test(const char c) {
        // [0-9.]
        return is_num_p::test(c)
            || is_character_p<'.'>::test(c);
    }
};

// ------------------------------------------------------------------------- //
// functions                                                                 //
// ------------------------------------------------------------------------- //

template <int flags, int flag>
struct is_flag {
    static const bool value = (flags & flag) != 0;
};

template <typename Predicate>
struct skip_while {
    static inline const char* test(const char* const begin, const char* const end) {
        const char* it = begin;
        while ((it != end) && Predicate::test(*it)) {
            ++it;
        }
        return it;
    }
};

struct skip_step {
    static inline const char* test(const char* const begin, const size_t step, const char* const end) {
        return begin + mth::min(step, size_t(end - begin));
    }
};

template <bool Condition, typename Predicate>
struct skip_while_if {
    static inline const char* test(const char* const begin, const char* const end);
};
template <typename Predicate>
struct skip_while_if<false, Predicate> {
    static inline const char* test(const char* const begin, const char* const end) { return begin; }
};
template <typename Predicate>
struct skip_while_if<true, Predicate> {
    static inline const char* test(const char* const begin, const char* const end) { return skip_while<Predicate>::test(begin, end); }
};

// ------------------------------------------------------------------------- //

} // namespace pred //
} // namespace gea //

#include "predicates.inl"
