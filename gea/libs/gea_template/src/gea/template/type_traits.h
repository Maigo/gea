#ifndef __GEA_TEMPLATE_TYPE_TRAITS_H__
#define __GEA_TEMPLATE_TYPE_TRAITS_H__

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// type_traits                                                               //
// ------------------------------------------------------------------------- //

// value types
template <class T, T v>
struct integral_constant;

typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true>  true_type;

// primary type categories
// is_void
template <class T> struct is_void;

// is_same
template <class T0, class T1> struct is_same;

// type properties
// is_const
template <class T> struct is_const;

// ------------------------------------------------------------------------- //

} // namespace gea //
} // namespace mth //

#include "type_traits.inl"

#endif // __GEA_TEMPLATE_TYPE_TRAITS_H__ //
