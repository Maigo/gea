#ifndef __GEA_MTH_VECTOR_ALGORITHM2_H__
#define __GEA_MTH_VECTOR_ALGORITHM2_H__

#include <gea/mth_vector/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //

inline const float distance_to_line(const point2 &line_p0, const point2 &line_p1, const point2 &p);

enum winding_type {
    winding_type__clockwise = -1,
    winding_type__invalid = 0,
    winding_type__counter_clockwise = 1
};
inline const winding_type winding(const point2 &p0, const point2 &p1, const point2 &p2);

} // namespace mth //
} // namespace gea //

#include "algorithm2.inl"

#endif // __GEA_MTH_VECTOR_ALGORITHM2_H__ //
