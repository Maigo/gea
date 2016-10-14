
// header include
#include "convex_hull.h"

// gea includes
#include <gea/mth_vector/algorithm2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// convex_hull: jm (Jarvis march, aka. gift wrapping algorithm)              //
// ------------------------------------------------------------------------- //

void convex_hull_jm::convex_hull(const pointset_type &points, pointset_type &out_points)
{
    assert((points.size() > 2) && "invalid parameters!");

    // find a start point on the hull
    uint32_t index_start = 0;
    find_start_point(points, index_start);

    uint32_t index = index_start, index_next;
    uint32_t size = points.size();
    do {
        // add current point
        out_points.push_back(points[index]);

        // iteratively select a point such that it lies to the right of the
        // segment defined by the current point and the last selected point
        // (starting with any point but the current)
        index_next = (index + 1) % size;
        for (uint32_t i = 0; i < size; ++i) {
            if (winding(points[index], points[index_next], points[i]) == winding_type__clockwise) {
                index_next = i;
            }
        }

        // set for next iteration, until hull is closed
        index = index_next;
    } while (index != index_start);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
