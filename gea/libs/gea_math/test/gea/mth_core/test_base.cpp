// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_core/base.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// trigonometry functions                                                    //
// ------------------------------------------------------------------------- //

TEST(gea_math, trigonometry_functions)
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

TEST(gea_math, helper_functions)
{
    // approximative comparison
    {
        struct data_type { float f0, f1, e; bool eq, ne, leq, geq; };
        const data_type data_set[] = {
            { 1.0f, 1.01f, 0.01f, true, false, true, false },
            { 0.99f, 1.0f, 0.01f, true, false, true, false },
            { 1.01f, 1.0f, 0.01f, true, false, false, true },
            { 1.0f, 0.99f, 0.01f, true, false, false, true },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(approx_eq(data.f0, data.f1, data.e), data.eq);
            EXPECT_EQ(approx_ne(data.f0, data.f1, data.e), data.ne);
            EXPECT_EQ(approx_leq(data.f0, data.f1, data.e), data.leq);
            EXPECT_EQ(approx_geq(data.f0, data.f1, data.e), data.geq);
        }
    }

    // nice scalar

    // finite scalar
}

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //

TEST(gea_math, template_functions)
{
    // max / min

    // smallest / largest

    // clamp
    {
        struct data_type { int i, min, max, ci; };
        const data_type data_set[] = {
            { 10, 1, 5, 5 },
            { 4, 0, 10, 4 },
            { 8, -1, 0, 0 },
            { 3, 0, 0, 0 }
        };
        for (const data_type &data : data_set) {
            EXPECT_EQ(clamp(data.i, data.min, data.max), data.ci);
        }
    }

    // range
    {
        struct data_type { int i, min, max; bool b; };
        const data_type data_set[] = {
            { 10, 1, 5, false },
            { 4, 0, 10, true },
            { 8, -1, 0, false },
            { 3, 0, 0, false }
        };
        for (const data_type &data : data_set) {
            EXPECT_EQ(range(data.i, data.min, data.max), data.b);
        }
    }
}

} // namespace mth //
} // namespace gea //
