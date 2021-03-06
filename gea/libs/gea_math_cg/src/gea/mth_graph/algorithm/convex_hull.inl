// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// convex_hull: jm (Jarvis march, aka. gift wrapping algorithm)              //
// ------------------------------------------------------------------------- //

inline void convex_hull_jm::convex_hull(const pointset_type &points, polygon2 &out_polygon)
{
    convex_hull(points, out_polygon.modify().points());
}

// ------------------------------------------------------------------------- //

inline void convex_hull_jm::find_start_point(const pointset_type &points, size_t &out_index)
{
    l_assert_msg(points.size() > 0,"invalid parameters!");

    size_t index = 0;
    for (size_t i = 1, e = points.size(); i < e; ++i) {
        if ((points[i].y < points[index].y) || ((points[i].y == points[index].y) && (points[i].x < points[index].x))) {
            index = i;
        }
    }
    out_index = index;
}

// ------------------------------------------------------------------------- //
// convex_hull: gs (Graham Scan)                                             //
// ------------------------------------------------------------------------- //

inline void convex_hull_gs::convex_hull(const pointset_type &points, polygon2 &out_polygon)
{
    convex_hull(points, out_polygon.modify().points());
}

// ------------------------------------------------------------------------- //

inline void convex_hull_gs::find_start_point(const pointset_type &points, size_t &out_index)
{
    l_assert_msg(points.size() > 0, "invalid parameters!");

    size_t index = 0;
    for (size_t i = 1, e = points.size(); i < e; ++i) {
        if ((points[i].y < points[index].y) || ((points[i].y == points[index].y) && (points[i].x < points[index].x))) {
            index = i;
        }
    }
    out_index = index;
}

// ------------------------------------------------------------------------- //
// convex_hull: mc (Monotone Chain)                                          //
// ------------------------------------------------------------------------- //

inline void convex_hull_mc::convex_hull(const pointset_type &points, polygon2 &out_polygon)
{
    convex_hull(points, out_polygon.modify().points());
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
