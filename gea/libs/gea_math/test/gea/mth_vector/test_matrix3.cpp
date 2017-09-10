// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_core/trigonometry.h>
#include <gea/mth_vector/matrix3.h>
#include <gea/mth_vector/quaternion.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //

TEST(mth_vector_matrix3, arithmetic)
{
    // addition
    {
        struct data_t {
            matrix3 m0, m1, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1}, { 2, 3, 4, 5, 6, 7, 8, 9, 10 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m0 + data.m1), data.res));
        }
    }

    // subtraction
    {
        struct data_t {
            matrix3 m0, m1, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 0, 1, 2, 3, 4, 5, 6, 7, 8 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m0 - data.m1), data.res));
        }
    }
    // multiplication
    {
        struct data_t {
            matrix3 m0, m1, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 6, 6, 6, 15, 15, 15, 24, 24, 24 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m0 * data.m1), data.res));
        }
    }
    // multiplication (scalar)
    {
        struct data_t {
            matrix3 m;
            float s;
            matrix3 res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 2, { 2, 4, 6, 8, 10, 12, 14, 16, 18 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m * data.s), data.res));
        }
    }
    // division (scalar)
    {
        struct data_t {
            matrix3 m;
            float s;
            matrix3 res;
        };
        const data_t data_set[] = {
            { { 3, 6, 9, 12, 15, 18, 21, 24, 27 }, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m / data.s), data.res));
        }
    }
    // multiplication (vector)
    {
        struct data_t {
            matrix3 m;
            vector3 v;
            vector3 res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 2, 2, 2 }, { 12, 30, 48 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m * data.v), data.res));
        }
    }
    // multiplication (point)
    {
        struct data_t {
            matrix3 m;
            point3 v;
            point3 res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 2, 2, 2 }, { 12, 30, 48 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m * data.v), data.res));
        }
    }
}

TEST(mth_vector_matrix3, linear_algebra)
{
    // transpose
    {
        struct data_t {
            matrix3 m, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 1, 4, 7, 2, 5, 8, 3, 6, 9 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.m.transpose(), data.res));
        }
    }

    // trace
    {
        struct data_t {
            matrix3 m;
            float res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 15 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.m.trace(), data.res));
        }
    }

    // determinant
    {
        struct data_t {
            matrix3 m;
            float res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 2, 6, 2, 8, 9 }, 6 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.m.determinant(), data.res));
        }
    }

    // inverse
    {
        struct data_t {
            matrix3 m, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 2, 6, 2, 8, 9 }, { -5, 1, 1, -4, .5f, 1, 14/3.f, -2/3.f, -1 } },
        };

        for (const data_t &data : data_set) {
            const matrix3 m_inv = data.m.inverse();
            EXPECT_TRUE(approx_eq(m_inv, data.res));
        }
    }
}

TEST(mth_vector_matrix3, conversion)
{
    // from_quaternion / to_quaternion
    {
        struct data_t {
            quaternion q;
            matrix3 m;
        };
        const data_t data_set[] = {
            { { 0, 0, float(M_SQRT1_2), float(M_SQRT1_2) }, { 0, -1, 0, 1, 0, 0, 0, 0, 1 } },
            { { 0, 0, float(M_SQRT1_2), -float(M_SQRT1_2) }, { 0, 1, 0, -1, 0, 0, 0, 0, 1 } },
        };

        for (const data_t &data : data_set) {
            matrix3 m(mth::SKIP_INITIALIZATION);
            m.from_quaternion(data.q);
            EXPECT_TRUE(approx_eq(m, data.m));
        }

        for (const data_t &data : data_set) {
            quaternion q;
            data.m.to_quaternion(q);
            EXPECT_TRUE(approx_eq(q, data.q));
        }
    }

    // from_euler / to_euler
    {
        struct data_t {
            float a0, a1, a2;
            matrix3 m;
        };
        const data_t data_set[] = {
            { 0, 0, float(M_PI) / 2.f, { 0, -1, 0, 1, 0, 0, 0, 0, 1 } },
            { 0, 0, -float(M_PI) / 2.f, { 0, 1, 0, -1, 0, 0, 0, 0, 1 } },
        };

        for (const data_t &data : data_set) {
            matrix3 m(mth::SKIP_INITIALIZATION);
            m.from_euler(data.a1, data.a2, data.a0);
            EXPECT_TRUE(approx_eq(m, data.m));
        }

        for (const data_t &data : data_set) {
            float a0, a1, a2;
            data.m.to_euler(a1, a2, a0);
            EXPECT_TRUE(approx_angle_eq(a0, data.a0) && approx_angle_eq(a1, data.a1) && approx_angle_eq(a2, data.a2));
        }
    }
}

} // namespace mth //
} // namespace gea //
