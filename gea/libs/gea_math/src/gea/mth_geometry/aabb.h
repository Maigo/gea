#ifndef __GEA_MTH_AABB_H__
#define __GEA_MTH_AABB_H__

#include <gea/mth_core/base.h>

namespace gea {
namespace mth {

class aabb
{
    inline aabb();
    inline aabb(float );
    inline aabb(skip_initialization);
    inline aabb(const aabb &o);

};

} // namespace mth //
} // namespace gea //

#include "aabb.inl"

#endif // __GEA_MTH_AABB_H__ //
