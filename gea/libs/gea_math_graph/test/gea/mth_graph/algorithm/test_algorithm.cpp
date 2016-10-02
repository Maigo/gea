
#include <gtest/gtest.h>

#include <gea/mth_graph/algorithm/algorithm.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// algorithm                                                                 //
// ------------------------------------------------------------------------- //

template <int N>
static void fill(const point2 (&points)[N], std::vector<point2> &out_points)
{
    for (const point2 &point : points) {
        out_points.push_back(point);
    }
}

TEST(gea_math_graph, algorithm_min)
{
    std::vector<point2> points = {
        point2(0, 0), point2(4, 4), point2(-2, 2), point2(-1, -1), point2(2, 6)
    };

    const point2 min_point = bounds_low(points);
    EXPECT_EQ(min_point, point2(-2, -1));

    const point2 max_point = bounds_low(points);
    EXPECT_EQ(max_point, point2(4, 6));
}

} // namespace mth //
} // namespace gea //
