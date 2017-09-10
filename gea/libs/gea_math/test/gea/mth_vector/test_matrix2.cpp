// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_core/trigonometry.h>
#include <gea/mth_vector/matrix2.h>
#include <gea/mth_vector/vector2.h>
#include <gea/mth_vector/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //

TEST(gea_math, matrix2)
{
    // arithmetic - addition
    {
        struct data_t {
            matrix2 m0, m1, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, { 1, 1, 1, 1 }, { 2, 3, 4, 5 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m0 + data.m1), data.res));
        }
    }
    // arithmetic - subtraction
    {
        struct data_t {
            matrix2 m0, m1, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, { 1, 1, 1, 1 }, { 0, 1, 2, 3 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m0 - data.m1), data.res));
        }
    }
    // arithmetic - multiplication
    {
        struct data_t {
            matrix2 m0, m1, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, { 1, 1, 1, 1 }, { 3, 3, 7, 7 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m0 * data.m1), data.res));
        }
    }
    // arithmetic - multiplication (scalar)
    {
        struct data_t {
            matrix2 m;
            float s;
            matrix2 res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, 2, { 2, 4, 6, 8 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m * data.s), data.res));
        }
    }
    // arithmetic - division (scalar)
    {
        struct data_t {
            matrix2 m;
            float s;
            matrix2 res;
        };
        const data_t data_set[] = {
            { { 3, 6, 9, 12 }, 3, { 1, 2, 3, 4 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m / data.s), data.res));
        }
    }
    // arithmetic - multiplication (vector)
    {
        struct data_t {
            matrix2 m;
            vector2 v;
            vector2 res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, {2, 2}, { 6, 14 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m * data.v), data.res));
        }
    }
    // arithmetic - multiplication (point)
    {
        struct data_t {
            matrix2 m;
            point2 v;
            point2 res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, { 2, 2 }, { 6, 14 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.m * data.v), data.res));
        }
    }

    // linear algebra - transpose
    {
        struct data_t {
            matrix2 m, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, {1, 3, 2, 4} },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.m.transpose(), data.res));
        }
    }

    // linear algebra - trace
    {
        struct data_t {
            matrix2 m;
            float res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, 5 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.m.trace(), data.res));
        }
    }

    // linear algebra - determinant
    {
        struct data_t {
            matrix2 m;
            float res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, -2 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.m.determinant(), data.res));
        }
    }

    // linear algebra - inverse
    {
        struct data_t {
            matrix2 m, res;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4 }, { -2, 1, 3/2.f, -1/2.f } },
        };

        for (const data_t &data : data_set) {
            const matrix2 m_inv = data.m.inverse();
            EXPECT_TRUE(approx_eq(m_inv, data.res));
        }
    }

    // conversion - from_angle / to angle
    {
        struct data_t {
            float angle;
            matrix2 m;
        };
        const data_t data_set[] = {
            { float(M_PI) / 2.f, { 0, -1, 1, 0 } },
            { float(M_PI) / 1.f, { -1, 0, 0, -1 } },
        };

        for (const data_t &data : data_set) {
            matrix2 m_rot(mth::SKIP_INITIALIZATION);
            m_rot.from_angle(data.angle);
            EXPECT_TRUE(approx_eq(m_rot, data.m));
        }

        for (const data_t &data : data_set) {
            float m_angle;
            data.m.to_angle(m_angle);
            EXPECT_TRUE(approx_angle_eq(m_angle, data.angle));
        }
    }
}

} // namespace mth //
} // namespace gea //
