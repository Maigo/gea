#ifndef __GEA_MTH_GRAPH_ALGORITHM_H__
#define __GEA_MTH_GRAPH_ALGORITHM_H__

// std includes
#include <vector>

// gea includes
#include <gea/mth_vector/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector<point2>                                                            //
// ------------------------------------------------------------------------- //

inline const point2 bounds_low(const std::vector<point2> &points);
inline const point2 bounds_high(const std::vector<point2> &points);

} // namespace mth //
} // namespace gea //

#include "algorithm.inl"

#endif // __GEA_MTH_GRAPH_ALGORITHM_H__ //
