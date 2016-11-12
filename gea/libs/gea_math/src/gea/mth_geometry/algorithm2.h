#ifndef __GEA_MTH_GEOMETRY_ALGORITHM2_H__
#define __GEA_MTH_GEOMETRY_ALGORITHM2_H__

// gea includes
#include <gea/mth_geometry/rectangle2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// common                                                                    //
// ------------------------------------------------------------------------- //

enum ignore_position_t { ignore_position };

// ------------------------------------------------------------------------- //
// rectangle2                                                                //
// ------------------------------------------------------------------------- //

inline const bool contains(const mth::rectangle2 &a, const mth::rectangle2 &b);
inline const bool contains(const mth::rectangle2 &a, const mth::rectangle2 &b, ignore_position_t);

} // namespace mth //
} // namespace gea //

#include "algorithm2.inl"

#endif // __GEA_MTH_GEOMETRY_ALGORITHM2_H__ //
