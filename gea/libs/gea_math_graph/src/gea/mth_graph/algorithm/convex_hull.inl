
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

inline void convex_hull_jm::find_start_point(const pointset_type &points, uint32_t &out_index)
{
    assert((points.size() > 0) && "invalid parameters!");

    uint32_t index = 0;
    for (uint32_t i = 1, e = points.size(); i < e; ++i) {
        if (points[i].x < points[index].x) {
            index = i;
        }
    }
    out_index = index;
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //