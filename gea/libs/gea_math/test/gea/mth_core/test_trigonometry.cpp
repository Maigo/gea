// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_core/trigonometry.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //

TEST(mth_core_trigonometry, trigonometry_functions)
{
    // conversion functions
    {
        struct data_type { float rad, deg; };
        const data_type data_set[] = {
            { PI / 4.0f, 45 },
            { PI / 2.0f, 90 },
            { PI / 1.0f, 180 }
        };

        for (const data_type &data : data_set) {
            EXPECT_FLOAT_EQ(degrees_to_radians(data.deg), data.rad);
        }

        for (const data_type &data : data_set) {
            EXPECT_FLOAT_EQ(radians_to_degrees(data.rad), data.deg);
        }
    }

//    // optimized sin & cos method
//    {
//        struct data_type { float rad, sin, cos; };
//        const data_type data_set[] = {
//            { PI / 4.0f, SQRT_2 / 2.0f, SQRT_2 / 2.0f },
//            { PI / 2.0f, 1.0f, 0.0f },
//            { PI / 1.0f, 0.0f, -1.0f }
//        };
//
//        float sin, cos;
//        for (const data_type &data : data_set) {
//            fsincos(data.rad, sin, cos);
//            EXPECT_FLOAT_EQ(sin, data.sin);
//            EXPECT_FLOAT_EQ(cos, data.cos);
//        }
//    }
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

TEST(mth_core_trigonometry, helper_functions)
{
    // approximative comparison
    {
        struct data_type { float f0, f1; bool eq, ne; };
        const data_type data_set[] = {
            { float(M_PI), -1.0f * float(M_PI), true, false },
            { float(M_PI) / 2.0f, -(3.0f / 2.0f) * float(M_PI), true, false },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(approx_angle_eq(data.f0, data.f1), data.eq);
            EXPECT_EQ(approx_angle_ne(data.f0, data.f1), data.ne);
        }
    }
}

} // namespace mth //
} // namespace gea //
