
#include <gtest/gtest.h>

#include <gea/mth_geometry/polygon2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polygon2                                                                  //
// ------------------------------------------------------------------------- //

TEST(gea_math, polygon2)
{
    // conversion functions
    {
        const point2 data_set[] = { { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 } };

        polygon2 polygon;
        polygon.modify().reserve(sizeof(data_set) / sizeof(point2));

        for (const point2 &point : data_set) {
            polygon.modify().add_point(point);
        }

        EXPECT_EQ(polygon.size(), 4);
        EXPECT_FLOAT_EQ(polygon.circumference(), 8.0f);
        EXPECT_FLOAT_EQ(polygon.area(), 4.0f);
    }
}

} // namespace mth //
} // namespace gea //
