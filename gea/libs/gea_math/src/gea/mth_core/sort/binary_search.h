#ifndef __GEA_MTH_CORE_BINARY_SEARCH_H__
#define __GEA_MTH_CORE_BINARY_SEARCH_H__

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// binary_search                                                             //
// ------------------------------------------------------------------------- //

template <class T>
bool less(const T& lhs, const T& rhs) { return lhs < rhs; }

template <class FwdIt, class T, class Pred>
void binary_search(FwdIt begin, FwdIt end, Pred compare);

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "binary_search.inl"

#endif // __GEA_MTH_CORE_BINARY_SEARCH_H__ //
