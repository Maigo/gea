#ifndef __GEA_MTH_GRAPH_RDP_H__
#define __GEA_MTH_GRAPH_RDP_H__

// stl includes
#include <assert.h>
#include <vector>

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point_reduce: rdp (Ramer-Douglas-Peucker)                                 //
// ------------------------------------------------------------------------- //
class point_reduce_rdp {
public:
    static void point_reduce(const std::vector<point2> &points, const float epsilon, std::vector<point2> &out_points);
    static void point_reduce(const std::vector<point2> &points, const float epsilon, std::vector<uint32_t> &out_indicies);

private:
    static void find_furthest_point(const std::vector<point2> &points, const uint32_t from, const uint32_t to, float &out_distance, uint32_t &out_index);

    struct point_reduce_arg {
        uint32_t from;
        uint32_t to;
    };
    typedef std::vector<point_reduce_arg> point_reduce_stack;
};

} // namespace mth //
} // namespace gea //

#include "point_reduce_rdp.inl"

#endif // __GEA_MTH_GRAPH_RDP_H__ //
