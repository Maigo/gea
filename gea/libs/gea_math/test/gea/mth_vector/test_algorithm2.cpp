// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_vector/algorithm2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// algorithm2                                                                //
// ------------------------------------------------------------------------- //

TEST(gea_math, algorithm2_point2)
{
    // point2 functions
    {
        struct data_t {
            point2 from, to, p;
            float distance;
        };
        const data_t data_set[] = {
            { { 0, 0 }, { 2, 0 }, { 1, 1 }, 1.0f },
            { { 0, 0 }, { 2, 2 }, { 2, 0 }, SQRT_2 },
            { { 1, 1 }, { 2, 2 }, { 0, 0 }, 0.0f },
            { { 0, 0 }, { 1, 1 }, { 0, 0 }, 0.0f },
        };

        for (const data_t &data : data_set) {
            EXPECT_FLOAT_EQ(distance_to_line(data.from, data.to, data.p), data.distance);
        }
    }
}

} // namespace mth //
} // namespace gea //
