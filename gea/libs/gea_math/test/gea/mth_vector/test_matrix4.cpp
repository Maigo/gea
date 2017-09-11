// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_vector/matrix4.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix4                                                                   //
// ------------------------------------------------------------------------- //

namespace static_data {
    static matrix4 m1to16 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    static matrix4 m16x1 = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
} // static_data //

TEST(mth_vector_matrix4, arithmetic)
{
    // addition
    {
        struct data_t {
            matrix4 matrix0, matrix1, sum;
        };
        const data_t data_set[] = {
            { static_data::m1to16, static_data::m16x1, { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 + data.matrix1), data.sum));
        }
    }

        // subtraction
    {
        struct data_t {
            matrix4 matrix0, matrix1, difference;
        };
        const data_t data_set[] = {
            { static_data::m1to16, static_data::m16x1, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 - data.matrix1), data.difference));
        }
    }
    // multiplication
    {
        struct data_t {
            matrix4 matrix0, matrix1, product;
        };
        const data_t data_set[] = {
            { static_data::m1to16, static_data::m16x1, { 10, 10, 10, 10, 26, 26, 26, 26, 42, 42, 42, 42, 58, 58, 58, 58 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix0 * data.matrix1), data.product));
        }
    }
    // multiplication (scalar)
    {
        struct data_t {
            matrix4 matrix;
            float scalar;
            matrix4 product;
        };
        const data_t data_set[] = {
            { static_data::m1to16, 2, { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.scalar), data.product));
        }
    }
    // division (scalar)
    {
        struct data_t {
            matrix4 matrix;
            float scalar;
            matrix4 quotient;
        };
        const data_t data_set[] = {
            { { 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48 }, 3, static_data::m1to16 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix / data.scalar), data.quotient));
        }
    }
    // multiplication (vector)
    {
        struct data_t {
            matrix4 matrix;
            vector4 vector;
            vector4 product;
        };
        const data_t data_set[] = {
            { static_data::m1to16, { 2, 2, 2, 2 }, { 20, 52, 84, 116 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq((data.matrix * data.vector), data.product));
        }
    }
//    // multiplication (point)
//    {
//        struct data_t {
//            matrix4 matrix;
//            point4 point;
//            point4 product;
//        };
//        const data_t data_set[] = {
//            { static_data::m1to16, { 2, 2, 2, 2 }, { 20, 52, 84, 116 } },
//        };
//
//        for (const data_t &data : data_set) {
//            EXPECT_TRUE(approx_eq((data.matrix * data.point), data.product));
//        }
//    }
}

TEST(mth_vector_matrix4, linear_algebra)
{
    // transpose
    {
        struct data_t {
            matrix4 matrix, transpose;
        };
        const data_t data_set[] = {
            { static_data::m1to16, { 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16 } },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.transpose(), data.transpose));
        }
    }

        // trace
    {
        struct data_t {
            matrix4 matrix;
            float trace;
        };
        const data_t data_set[] = {
            { static_data::m1to16, 34 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.trace(), data.trace));
        }
    }

    // determinant
    {
        struct data_t {
            matrix4 matrix;
            float determinant;
        };
        const data_t data_set[] = {
            { { 1, 0, 2, 0, 2, 0, 1, 0, 1, 1, 1, 1, 2, 0, 0, 2 }, 6 },
        };

        for (const data_t &data : data_set) {
            EXPECT_TRUE(approx_eq(data.matrix.determinant(), data.determinant));
        }
    }

    // inverse
    {
        struct data_t {
            matrix4 matrix, inverse;
        };
        const data_t data_set[] = {
            { { 1, 0, 2, 0, 2, 0, 1, 0, 1, 1, 1, 1, 2, 0, 0, 2 }, { -1 / 3.f, 2 / 3.f, 0, 0, -2 / 3.f, 1 / 3.f, 1, -1 / 2.f, 2 / 3.f, -1 / 3.f, 0, 0, 1 / 3.f, -2 / 3.f, 0, 1 / 2.f } },
            { { 1, 2, 1, 2, 0, 0, 1, 0, 2, 1, 1, 0, 0, 0, 1, 2 }, { -1 / 3.f, -2 / 3.f, 2 / 3.f, 1 / 3.f, 2 / 3.f, 1 / 3.f, -1 / 3.f, -2 / 3.f, 0, 1, 0, 0, 0, -1 / 2.f, 0, 1 / 2.f } }
        };

        for (const data_t &data : data_set) {
            const matrix4 m_inv = data.matrix.inverse();
            EXPECT_TRUE(approx_eq(m_inv, data.inverse));
        }
    }
}

} // namespace mth //
} // namespace gea //
