#ifndef __GEA_MTH_VECTOR_RANDOM2_H__
#define __GEA_MTH_VECTOR_RANDOM2_H__

// gea includes
#include <gea/mth_vector/matrix2.h>
#include <gea/mth_vector/polar2.h>
#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// polar2                                                                    //
// ------------------------------------------------------------------------- //
inline const polar2 rand_polar2();

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //
inline const point2 rand_point2(const point2 &nw_corner, const point2 &se_corner);

// ------------------------------------------------------------------------- //
// vector2                                                                   //
// ------------------------------------------------------------------------- //
inline const vector2 rand_vector2(const float max_length, const float min_length = 0.0f);

} // namespace mth //
} // namespace gea //

#include "random2.inl"

#endif // __GEA_MTH_VECTOR_RANDOM2_H__ //
