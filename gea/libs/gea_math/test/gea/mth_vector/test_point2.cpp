
#include <gtest/gtest.h>

#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //

TEST(gea_math, point2)
{
    // linear algebra functions
    {
        struct data_t {
            point2 from, to;
            vector2 v;
        };
        const data_t data_set[] = {
            { { 0, 0 }, { 2, 0 }, { 2, 0 } },
            { { 1, 1 }, { 2, 0 }, { 1,-1 } },
            { { 1, 2 }, { 2, 2 }, { 1, 0 } },
            { { 2, 2 }, { 0, 0 }, {-2,-2 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.from.to(data.to), data.v));
        }
    }
}

} // namespace mth //
} // namespace gea //
