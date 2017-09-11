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

namespace static_data {
    static matrix2 m1to4 = { 1, 2, 3, 4 };
    static matrix2 m4x1 = { 1, 1, 1, 1 };
} // static_data //

TEST(mth_vector_matrix2, arithmetic)
{
    // addition
    {
        struct data_t {
            matrix2 matrix0, matrix1, sum;
        };
        const data_t data_set[] = {
            { static_data::m1to4, static_data::m4x1, { 2, 3, 4, 5 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 + data.matrix1), data.sum));
        }
    }

    // subtraction
    {
        struct data_t {
            matrix2 matrix0, matrix1, difference;
        };
        const data_t data_set[] = {
            { static_data::m1to4, static_data::m4x1, { 0, 1, 2, 3 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 - data.matrix1), data.difference));
        }
    }
    // multiplication
    {
        struct data_t {
            matrix2 matrix0, matrix1, product;
        };
        const data_t data_set[] = {
            { static_data::m1to4, static_data::m4x1, { 3, 3, 7, 7 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 * data.matrix1), data.product));
        }
    }
    // multiplication (scalar)
    {
        struct data_t {
            matrix2 matrix;
            float scalar;
            matrix2 product;
        };
        const data_t data_set[] = {
            { static_data::m1to4, 2, { 2, 4, 6, 8 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.scalar), data.product));
        }
    }
    // division (scalar)
    {
        struct data_t {
            matrix2 matrix;
            float scalar;
            matrix2 quotient;
        };
        const data_t data_set[] = {
            { { 3, 6, 9, 12 }, 3, static_data::m1to4 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix / data.scalar), data.quotient));
        }
    }
    // multiplication (vector)
    {
        struct data_t {
            matrix2 matrix;
            vector2 vector;
            vector2 product;
        };
        const data_t data_set[] = {
            { static_data::m1to4, { 2, 2 }, { 6, 14 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.vector), data.product));
        }
    }
    // multiplication (point)
    {
        struct data_t {
            matrix2 matrix;
            point2 point;
            point2 product;
        };
        const data_t data_set[] = {
            { static_data::m1to4, { 2, 2 }, { 6, 14 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.point), data.product));
        }
    }
}

TEST(mth_vector_matrix2, linear_algebra)
{
    // transpose
    {
        struct data_t {
            matrix2 matrix, transpose;
        };
        const data_t data_set[] = {
            { static_data::m1to4, { 1, 3, 2, 4 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.transpose(), data.transpose));
        }
    }

    // trace
    {
        struct data_t {
            matrix2 matrix;
            float trace;
        };
        const data_t data_set[] = {
            { static_data::m1to4, 5 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.trace(), data.trace));
        }
    }

    // determinant
    {
        struct data_t {
            matrix2 matrix;
            float determinant;
        };
        const data_t data_set[] = {
            { static_data::m1to4, -2 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.determinant(), data.determinant));
        }
    }

    // inverse
    {
        struct data_t {
            matrix2 matrix, inverse;
        };
        const data_t data_set[] = {
            { static_data::m1to4, { -2, 1, 3 / 2.f, -1 / 2.f } },
        };

        for (const data_t &data : data_set) {
            const matrix2 m_inv = data.matrix.inverse();
            EXPECT_TRUE(approx_eq(m_inv, data.inverse));
        }
    }
}

TEST(mth_vector_matrix2, conversion)
{
    // from_angle / to angle
    {
        struct data_t {
            float angle;
            matrix2 matrix;
        };
        const data_t data_set[] = {
            { float(M_PI) / 2.f, { 0, -1, 1, 0 } },
            { float(M_PI) / 1.f, { -1, 0, 0, -1 } },
        };

        for (const data_t &data : data_set) {
            matrix2 m_rot(mth::SKIP_INITIALIZATION);
            m_rot.from_angle(data.angle);
            EXPECT_TRUE(approx_eq(m_rot, data.matrix));
        }

        for (const data_t &data : data_set) {
            float angle;
            data.matrix.to_angle(angle);
            EXPECT_TRUE(approx_angle_eq(angle, data.angle));
        }
    }
}

} // namespace mth //
} // namespace gea //
