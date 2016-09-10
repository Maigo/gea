#ifndef __GEA_VMTH_ALGORITHM2_H__
#define __GEA_VMTH_ALGORITHM2_H__

#include <gea/mth_vector/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //

inline const float distance_to_line(const point2 &line_p0, const point2 &line_p1, const point2 &p);

} // namespace mth //
} // namespace gea //

#include "algorithm2.inl"

#endif // __GEA_VMTH_ALGORITHM2_H__ //
