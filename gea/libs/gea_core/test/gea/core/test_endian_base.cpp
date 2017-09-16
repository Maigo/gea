// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/endian_base.h>

namespace gea {

// ------------------------------------------------------------------------- //
// endian_swap                                                               //
// ------------------------------------------------------------------------- //

TEST(mth_core_endian_swap, endian_swap) {
    // endian_swap - 8 bits
    {
        struct data_type { uint8_t before, after; };
        const data_type data_set[] = {
            { 0xF0, 0xF0 },
        };

        for (const data_type &data : data_set) {
            uint8_t before = data.before;
            endian_swap(before);
            EXPECT_EQ(before, data.after);
        }
    }

    // endian_swap - 16 bits
    {
        struct data_type { uint16_t before, after; };
        const data_type data_set[] = {
            { 0xFF00, 0x00FF },
        };

        for (const data_type &data : data_set) {
            uint16_t before = data.before;
            endian_swap(before);
            EXPECT_EQ(before, data.after);
        }
    }

    // endian_swap - 32 bits
    {
        struct data_type { uint32_t before, after; };
        const data_type data_set[] = {
            { 0xFFFF0000, 0x0000FFFF },
        };

        for (const data_type &data : data_set) {
            uint32_t before = data.before;
            endian_swap(before);
            EXPECT_EQ(before, data.after);
        }
    }

    // endian_swap - 64 bits
    {
        struct data_type { uint64_t before, after; };
        const data_type data_set[] = {
            { 0xFFFFFFFF00000000, 0x00000000FFFFFFFF },
        };

        for (const data_type &data : data_set) {
            uint64_t before = data.before;
            endian_swap(before);
            EXPECT_EQ(before, data.after);
        }
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
