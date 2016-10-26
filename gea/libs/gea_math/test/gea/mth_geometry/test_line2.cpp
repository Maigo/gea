// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_geometry/line2.h>

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
        line.modify().reserve(sizeof(data_set) / sizeof(point2));

        for (const point2 &point : data_set) {
            line.modify().add_point(point);
        }

        EXPECT_EQ(line.size(), 4);
        EXPECT_FLOAT_EQ(line.length(), 6.0f);
    }
}

} // namespace mth //
} // namespace gea //
