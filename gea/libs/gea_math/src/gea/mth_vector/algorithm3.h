#ifndef __GEA_VMTH_ALGORITHM3_H__
#define __GEA_VMTH_ALGORITHM3_H__

#include <gea/mth_vector/point3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //

inline const float distance_to_line(const point3 &line_p0, const point3 &line_p1, const point3 &p);

} // namespace mth //
} // namespace gea //

#include "algorithm3.inl"

#endif // __GEA_VMTH_ALGORITHM3_H__ //
