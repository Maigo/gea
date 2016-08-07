#ifndef __GEA_MTH_GRAPH_RDP_H__
#define __GEA_MTH_GRAPH_RDP_H__

// stl includes
#include <assert.h>
#include <vector>

// mth includes
#include <gea/bmth/base.h>
#include <gea/vmth/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point_reduce: rdp (Ramer–Douglas–Peucker)                                 //
// ------------------------------------------------------------------------- //
class point_reduce_rdp
{
public:
    static void point_reduce(const std::vector<point2> &points, const float epsilon, std::vector<point2> &out);
};

} // namespace mth //
} // namespace gea //

#include "point_reduce_rdp.inl"

#endif // __GEA_MTH_GRAPH_RDP_H__ //
