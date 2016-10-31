// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_graph/algorithm/sampler.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// sampler                                                                   //
// ------------------------------------------------------------------------- //

TEST(gea_math_graph, sampler_sample)
{
    std::vector<point2> points;

    auto sample_func = [](const float x) -> const float { return sin(2.0f * PI * x); };
    sampler::sample(0.0f, 1.0f, 0.01f, sample_func, points);

    EXPECT_EQ(points.size(), 101);
}

} // namespace mth //
} // namespace gea //
