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

namespace static_data {
    static matrix3 m1to9 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    static matrix3 m9x1 = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
} // static_data //

TEST(mth_vector_matrix3, arithmetic)
{
    // addition
    {
        struct data_t {
            matrix3 matrix0, matrix1, sum;
        };
        const data_t data_set[] = {
            { static_data::m1to9, static_data::m9x1, { 2, 3, 4, 5, 6, 7, 8, 9, 10 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 + data.matrix1), data.sum));
        }
    }

    // subtraction
    {
        struct data_t {
            matrix3 matrix0, matrix1, difference;
        };
        const data_t data_set[] = {
            { static_data::m1to9, static_data::m9x1, { 0, 1, 2, 3, 4, 5, 6, 7, 8 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 - data.matrix1), data.difference));
        }
    }
    // multiplication
    {
        struct data_t {
            matrix3 matrix0, matrix1, product;
        };
        const data_t data_set[] = {
            { static_data::m1to9, static_data::m9x1, { 6, 6, 6, 15, 15, 15, 24, 24, 24 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 * data.matrix1), data.product));
        }
    }
    // multiplication (scalar)
    {
        struct data_t {
            matrix3 matrix;
            float scalar;
            matrix3 product;
        };
        const data_t data_set[] = {
            { static_data::m1to9, 2, { 2, 4, 6, 8, 10, 12, 14, 16, 18 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.scalar), data.product));
        }
    }
    // division (scalar)
    {
        struct data_t {
            matrix3 matrix;
            float scalar;
            matrix3 quotient;
        };
        const data_t data_set[] = {
            { { 3, 6, 9, 12, 15, 18, 21, 24, 27 }, 3, static_data::m1to9 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix / data.scalar), data.quotient));
        }
    }
    // multiplication (vector)
    {
        struct data_t {
            matrix3 matrix;
            vector3 vector;
            vector3 product;
        };
        const data_t data_set[] = {
            { static_data::m1to9, { 2, 2, 2 }, { 12, 30, 48 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.vector), data.product));
        }
    }
    // multiplication (point)
    {
        struct data_t {
            matrix3 matrix;
            point3 point;
            point3 product;
        };
        const data_t data_set[] = {
            { static_data::m1to9, { 2, 2, 2 }, { 12, 30, 48 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.point), data.product));
        }
    }
}

TEST(mth_vector_matrix3, linear_algebra)
{
    // transpose
    {
        struct data_t {
            matrix3 matrix, transpose;
        };
        const data_t data_set[] = {
            { static_data::m1to9, { 1, 4, 7, 2, 5, 8, 3, 6, 9 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.transpose(), data.transpose));
        }
    }

    // trace
    {
        struct data_t {
            matrix3 matrix;
            float trace;
        };
        const data_t data_set[] = {
            { static_data::m1to9, 15 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.trace(), data.trace));
        }
    }

    // determinant
    {
        struct data_t {
            matrix3 matrix;
            float determinant;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 2, 6, 2, 8, 9 }, 6 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.determinant(), data.determinant));
        }
    }

    // inverse
    {
        struct data_t {
            matrix3 matrix, inverse;
        };
        const data_t data_set[] = {
            { { 1, 2, 3, 4, 2, 6, 2, 8, 9 }, { -5, 1, 1, -4, .5f, 1, 14/3.f, -2/3.f, -1 } },
        };

        for (const data_t &data : data_set) {
            const matrix3 m_inv = data.matrix.inverse();
            EXPECT_TRUE(approx_eq(m_inv, data.inverse));
        }
    }
}

TEST(mth_vector_matrix3, conversion)
{
    // from_quaternion / to_quaternion
    {
        struct data_t {
            quaternion quaternion;
            matrix3 matrix;
        };
        const data_t data_set[] = {
            { { 0, 0, float(M_SQRT1_2), float(M_SQRT1_2) }, { 0, -1, 0, 1, 0, 0, 0, 0, 1 } },
            { { 0, 0, float(M_SQRT1_2), -float(M_SQRT1_2) }, { 0, 1, 0, -1, 0, 0, 0, 0, 1 } },
        };

        for (const data_t &data : data_set) {
            matrix3 matrix(mth::SKIP_INITIALIZATION);
            matrix.from_quaternion(data.quaternion);
            EXPECT_TRUE(approx_eq(matrix, data.matrix));
        }

        for (const data_t &data : data_set) {
            quaternion quaternion;
            data.matrix.to_quaternion(quaternion);
            EXPECT_TRUE(approx_eq(quaternion, data.quaternion));
        }
    }

    // from_euler / to_euler
    {
        struct data_t {
            float angle0, angle1, angle2;
            matrix3 matrix;
        };
        const data_t data_set[] = {
            { 0, 0, float(M_PI) / 2.f, { 0, -1, 0, 1, 0, 0, 0, 0, 1 } },
            { 0, 0, -float(M_PI) / 2.f, { 0, 1, 0, -1, 0, 0, 0, 0, 1 } },
        };

        for (const data_t &data : data_set) {
            matrix3 matrix(mth::SKIP_INITIALIZATION);
            matrix.from_euler(data.angle1, data.angle2, data.angle0);
            EXPECT_TRUE(approx_eq(matrix, data.matrix));
        }

        for (const data_t &data : data_set) {
            float angle0, angle1, angle2;
            data.matrix.to_euler(angle1, angle2, angle0);
            EXPECT_TRUE(approx_angle_eq(angle0, data.angle0) && approx_angle_eq(angle1, data.angle1) && approx_angle_eq(angle2, data.angle2));
        }
    }

    // from_rotation
    {
        struct data_t {
            float angle;
            vector3 axis;
            matrix3 matrix;
        };
        const data_t data_set[] = {
            { float(M_PI) / 2.f, { 1, 1, 0 }, { 0.5, 0.5, float(M_SQRT1_2), 0.5, 0.5, -float(M_SQRT1_2), -float(M_SQRT1_2), float(M_SQRT1_2), 0 } },
        };

        for (const data_t &data : data_set) {
            matrix3 matrix(mth::SKIP_INITIALIZATION);
            matrix.from_rotation(data.angle, data.axis);
            EXPECT_TRUE(approx_eq(matrix, data.matrix));
        }
    }
}

} // namespace mth //
} // namespace gea //
