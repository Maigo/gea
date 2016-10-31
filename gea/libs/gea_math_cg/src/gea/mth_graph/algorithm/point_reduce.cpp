// header include
#include "point_reduce.h"

// gea includes
#include <gea/mth_vector/algorithm2.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point_reduce: rdp (Ramer-Douglas-Peucker)                                 //
// ------------------------------------------------------------------------- //

void point_reduce_rdp::point_reduce(const std::vector<point2> &points, const float epsilon, std::vector<point2> &out_points)
{
    l_assert_msg((points.size() > 2) && (epsilon > 0), "invalid parameters!");

    stack stack;
    stack.push_back({ 0u, points.size() - 1u });

    // iterative recursion
    while (!stack.empty()) {
        const stack_item args = stack.back();
        stack.pop_back();

        float distance = 0.0f;
        uint32_t index = 0;
        find_furthest_point(points, args.from, args.to, distance, index);

        if (distance > epsilon) {
            stack.push_back({ index, args.to });
            stack.push_back({ args.from, index });
        } else {
            // include start point
            out_points.push_back(points[args.from]);
        }
    }

    // include end point
    out_points.push_back(points[points.size() - 1]);
}

// ------------------------------------------------------------------------- //

void point_reduce_rdp::find_furthest_point(const std::vector<point2> &points, const uint32_t from, const uint32_t to, float &out_distance, uint32_t &out_index)
{
    l_assert_msg((0 <= from && to < points.size()), "invalid parameters");

    float find_distance = 0.0f;
    uint32_t find_index = 0;

    for (uint32_t index = from + 1, end = to - 1; index < end; ++index) {
        const float distance = distance_to_line(points[from], points[to], points[index]);
        if (distance > find_distance) {
            find_distance = distance;
            find_index = index;
        }
    }

    out_distance = find_distance;
    out_index = find_index;
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
