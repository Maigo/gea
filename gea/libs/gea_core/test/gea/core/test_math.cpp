// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/math.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// template functions                                                        //
// ------------------------------------------------------------------------- //

TEST(mth_core_base, template_functions)
{
    // max / min
    {
        struct data_type { int i0, i1, min, max; };
        const data_type data_set[] = {
            { 10,  1,  1, 10 },
            {  4,  0,  0,  4 },
            {  8, -1, -1,  8 },
            { -3,  0, -3,  0 }
        };
        for (const data_type &data : data_set) {
            EXPECT_EQ(min(data.i0, data.i1), data.min);
            EXPECT_EQ(max(data.i0, data.i1), data.max);
        }
    }
    {
        struct data_type { int i0, i1, i2, min, max; };
        const data_type data_set[] = {
            { 10,  1,  5,  1, 10 },
            {  4,  0,  0,  0,  4 },
            {  8, -1, -3, -3,  8 },
            { -3,  0, -4, -4,  0 }
        };
        for (const data_type &data : data_set) {
            EXPECT_EQ(min(data.i0, data.i1, data.i2), data.min);
            EXPECT_EQ(max(data.i0, data.i1, data.i2), data.max);
        }
    }
    {
        struct data_type { int i0, i1, i2, i3, min, max; };
        const data_type data_set[] = {
            { 10,  1,  5,  3,  1, 10 },
            {  4,  0,  0,  1,  0,  4 },
            {  8, -1, -3,  4, -3,  8 },
            { -3,  0, -4, -1, -4,  0 }
        };
        for (const data_type &data : data_set) {
            EXPECT_EQ(min(data.i0, data.i1, data.i2, data.i3), data.min);
            EXPECT_EQ(max(data.i0, data.i1, data.i2, data.i3), data.max);
        }
    }
}

} // namespace mth //
} // namespace gea //
