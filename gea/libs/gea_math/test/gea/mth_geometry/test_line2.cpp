
#include <gtest/gtest.h>

#include <gea/mth_geometry/line.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// line2                                                                     //
// ------------------------------------------------------------------------- //

TEST(gea_math, line2)
{
    // conversion functions
    {
        const point2 data_set[] = { { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 } };

        line2 line;
        line2_builder(line).at_point(data_set[0]).at_point(data_set[1]).at_point(data_set[2]).at_point(data_set[3]);

        EXPECT_EQ(line.points().size(), 4);
        EXPECT_FLOAT_EQ(line.length(), 6.0f);
    }
}

} // namespace mth //
} // namespace gea //
