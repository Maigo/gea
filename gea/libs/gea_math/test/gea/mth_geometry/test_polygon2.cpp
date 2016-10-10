
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
        struct point_t {
            point_t() : p(), valid(false) {}
            point_t(const float x, const float y) : p(x, y), valid(true) {}
            point2 p;
            bool valid;
        };
        struct data_t {
            point_t point_set[5];
            int size;
            float circumference;
            float area;
        };
        const data_t data_set[] = {
            //  point_set,                                                 size,       circumference, area
            { { point_t(1, 1), point_t(3, 1) },                               2,                4.0f, 0.0f },
            { { point_t(1, 1), point_t(3, 1), point_t(3, 3) },                3, (2 * SQRT_2 + 4.0f), 2.0f },
            { { point_t(0, 0), point_t(2, 0), point_t(2, 2), point_t(0, 2) }, 4,                8.0f, 4.0f },
            { { point_t(0, 0), point_t(2, 0), point_t(4, 2), point_t(2, 2) }, 4, (4 * SQRT_2 + 4.0f), 4.0f }
        };

        for (const data_t &data : data_set) {

            polygon2 polygon;
            polygon.modify().reserve(sizeof(data_set) / sizeof(point2));

            for (const point_t &point : data.point_set) {
                if (point.valid) {
                    polygon.modify().add_point(point.p);
                }
            }

            EXPECT_EQ(polygon.size(), data.size);
            EXPECT_FLOAT_EQ(polygon.circumference(), data.circumference);
            EXPECT_FLOAT_EQ(polygon.area(), data.area);
        }
    }
}

} // namespace mth //
} // namespace gea //
