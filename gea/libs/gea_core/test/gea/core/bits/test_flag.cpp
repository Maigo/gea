// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/bits/flag.h>

namespace gea {

// ------------------------------------------------------------------------- //
// endian_swap                                                               //
// ------------------------------------------------------------------------- //

TEST(mth_core_bits_flag, at_index) {
    // bit_at
    {
        struct data_type { uint8_t index; uint32_t bit; };
        const data_type data_set[] = {
            {  0, (1 <<  0) },
            {  7, (1 <<  7) },
            { 14, (1 << 14) },
            { 31, (1 << 31) },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(bit, data.bit);
        }
    }
}

TEST(mth_core_bits_flag, test) {
    // test
    {
        struct data_type { bit::flag32_t flag; uint8_t index; bool exp; };
        const data_type data_set[] = {
            { bit::flag32_t(0xAAAAAAAA), 0, false },
            { bit::flag32_t(0xAAAAAAAA), 7, true },
            { bit::flag32_t(0xAAAAAAAA), 14, false },
            { bit::flag32_t(0xAAAAAAAA), 31, true },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(data.flag.test(bit), data.exp);
        }
    }
}

TEST(mth_core_bits_flag, set) {
    // set
    {
        struct data_type { bit::flag8_t flag; uint8_t index; bool before, after; };
        const data_type data_set[] = {
            { bit::flag8_t(0x00), 0, false, true },
            { bit::flag8_t(0x00), 7, false, true },
            { bit::flag8_t(0xFF), 0, true, true },
            { bit::flag8_t(0xFF), 7, true, true },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(data.flag.test(bit), data.before);
            bit::flag8_t copy = data.flag;
            copy.set(bit);
            EXPECT_EQ(copy.test(bit), data.after);
        }
    }
}

TEST(mth_core_bits_flag, clear) {
    // clear
    {
        struct data_type { bit::flag8_t flag; uint8_t index; bool before, after; };
        const data_type data_set[] = {
            { bit::flag8_t(0x00), 0, false, false },
            { bit::flag8_t(0x00), 7, false, false },
            { bit::flag8_t(0xFF), 0, true, false },
            { bit::flag8_t(0xFF), 7, true, false },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(data.flag.test(bit), data.before);
            bit::flag8_t copy = data.flag;
            copy.clear(bit);
            EXPECT_EQ(copy.test(bit), data.after);
        }
    }
}

TEST(mth_core_bits_flag, toggle) {
    // toggle
    {
        struct data_type { bit::flag8_t flag; uint8_t index; bool before, after; };
        const data_type data_set[] = {
            { bit::flag8_t(0x00), 0, false, true },
            { bit::flag8_t(0x00), 7, false, true },
            { bit::flag8_t(0xFF), 0, true, false },
            { bit::flag8_t(0xFF), 7, true, false },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(data.flag.test(bit), data.before);
            bit::flag8_t copy = data.flag;
            copy.toggle(bit);
            EXPECT_EQ(copy.test(bit), data.after);
        }
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
