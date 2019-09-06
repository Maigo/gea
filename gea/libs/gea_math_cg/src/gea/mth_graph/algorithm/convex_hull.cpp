// header include
#include "convex_hull.h"

// std includes
#include <algorithm>

// gea includes
#include <gea/mth_vector/algorithm2.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// convex_hull: jm (Jarvis march, aka. gift wrapping algorithm)              //
// ------------------------------------------------------------------------- //

void convex_hull_jm::convex_hull(const pointset_type &points, pointset_type &out_points)
{
    l_assert_msg(points.size() > 2, "invalid parameters!");
    if (points.size() < 3) {
        out_points.assign(points.begin(), points.end());
        return;
    }

    // find a start point on the hull
    size_t index_start = 0;
    find_start_point(points, index_start);

    size_t index = index_start, index_next;
    size_t size = points.size();
    do {
        // add current point
        out_points.push_back(points[index]);

        // iteratively select a point such that it lies to the right of the
        // segment defined by the current point and the last selected point
        // (starting with any point but the current)
        index_next = (index + 1) % size;
        for (size_t i = 0; i < size; ++i) {
            const point2 &p0 = points[index];
            const point2 &p1 = points[index_next];
            const point2 &p2 = points[i];

            // note: in case of colinearity (3 points in a line), select the
            // point furthest away.
            const winding_type w = winding(p0, p1, p2);
            if ((w == winding_type__clockwise) || ((w == winding_type__invalid) && distance_sq(p0, p2) > distance_sq(p0, p1))) {
                index_next = i;
            }
        }

        // set for next iteration, until hull is closed
        index = index_next;
    } while (index != index_start);
}

// ------------------------------------------------------------------------- //
// convex_hull: gs (Graham Scan)                                             //
// ------------------------------------------------------------------------- //

void convex_hull_gs::convex_hull(const pointset_type &points, pointset_type &out_points)
{
    l_assert_msg(points.size() > 2, "invalid parameters!");
    if (points.size() < 3) {
        out_points.assign(points.begin(), points.end());
        return;
    }

    // find a start point on the hull
    size_t index_start = 0;
    find_start_point(points, index_start);

    // allocate array for sorting, move start point to the end (avoid degenerate end point edge case)
    pointset_type sort_points(points);
    std::swap(sort_points[index_start], sort_points.back());

    // sort array, excluding start point
    const point2 &p0 = sort_points.back();
    std::sort(sort_points.begin(), sort_points.end() - 1, [p0](const point2 &p1, const point2 &p2)->bool {
        const winding_type w = winding(p0, p1, p2);
        return (w == winding_type__counter_clockwise) || ((w == winding_type__invalid) && (distance_sq(p0, p1) < distance(p0, p2)));
    });

    out_points.push_back(sort_points.back()); // start point
    out_points.push_back(sort_points.front());

    for (size_t i = 1, e = sort_points.size(); i < e; ++i) {
        while ((out_points.size() > 1u) && winding(*(out_points.rbegin() + 1), *(out_points.rbegin()), sort_points[i]) != winding_type__counter_clockwise) {
            out_points.pop_back();
        }

        out_points.push_back(sort_points[i]);
    }

    // remove the duplicate end points, same as start point
    l_assert(out_points.front() == out_points.back());
    out_points.pop_back();
}

// ------------------------------------------------------------------------- //
// convex_hull: mc (Monotone Chain)                                          //
// ------------------------------------------------------------------------- //
void convex_hull_mc::convex_hull(const pointset_type &points, pointset_type &out_points) {
    l_assert_implement;
};

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
