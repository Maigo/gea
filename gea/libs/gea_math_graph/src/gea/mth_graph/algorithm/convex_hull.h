#ifndef __GEA_MTH_GRAPH_CONVEX_HULL_H__
#define __GEA_MTH_GRAPH_CONVEX_HULL_H__

// stl includes
#include <assert.h>
#include <vector>

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/point2.h>
#include <gea/mth_geometry/polygon2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// convex_hull: jm (Jarvis March, aka. gift wrapping algorithm)              //
// ------------------------------------------------------------------------- //
class convex_hull_jm {
public:
    typedef polygon2::pointset_type pointset_type;

    static inline void convex_hull(const pointset_type &points, polygon2 &out_polygon);
    static        void convex_hull(const pointset_type &points, pointset_type &out_points);

private:
    static inline void find_start_point(const pointset_type &points, uint32_t &out_index);
};

// ------------------------------------------------------------------------- //
// convex_hull: gs (Graham Scan)                                             //
// ------------------------------------------------------------------------- //
class convex_hull_gs {
public:
    typedef polygon2::pointset_type pointset_type;

    static inline void convex_hull(const pointset_type &points, polygon2 &out_polygon);
    static        void convex_hull(const pointset_type &points, pointset_type &out_points);

private:
    static inline void find_start_point(const pointset_type &points, uint32_t &out_index);
};

// ------------------------------------------------------------------------- //

// set default algorithm
typedef convex_hull_jm convex_hull;

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "convex_hull.inl"

#endif // __GEA_MTH_GRAPH_CONVEX_HULL_H__ //
