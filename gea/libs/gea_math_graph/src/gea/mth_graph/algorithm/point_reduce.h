#ifndef __GEA_MTH_GRAPH_POINT_REDUCE_H__
#define __GEA_MTH_GRAPH_POINT_REDUCE_H__

// stl includes
#include <vector>

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/point2.h>
#include <gea/mth_geometry/line2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point_reduce: rdp (Ramer-Douglas-Peucker)                                 //
// ------------------------------------------------------------------------- //
class point_reduce_rdp {
public:
    typedef line2::pointset_type pointset_type;

    static inline void point_reduce(const line2 &line,           const float epsilon, line2 &out_line);
    static        void point_reduce(const pointset_type &points, const float epsilon, pointset_type &out_points);

private:
    static void find_furthest_point(const pointset_type &points, const uint32_t from, const uint32_t to, float &out_distance, uint32_t &out_index);

    struct stack_item {
        uint32_t from;
        uint32_t to;
    };
    typedef std::vector<stack_item> stack;
};

// ------------------------------------------------------------------------- //

// set default algorithm
typedef point_reduce_rdp point_reduce;

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "point_reduce.inl"

#endif // __GEA_MTH_GRAPH_POINT_REDUCE_H__ //
