// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/bits/flag.h>

namespace gea {

// ------------------------------------------------------------------------- //
// bit-flag functions                                                        //
// ------------------------------------------------------------------------- //

TEST(gea_core_bits_flag, at_index) {
    // at_index
    {
        struct data_type { uint8_t index; uint32_t bit; };
        const data_type data_set[] = {
            {  0u, (1u <<  0) },
            {  7u, (1u <<  7) },
            { 14u, (1u << 14) },
            { 31u, (1u << 31) },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(bit, data.bit);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_core_bits_flag, test) {
    // test
    {
        struct data_type { bit::flag32_t flag; uint8_t index; bool exp; };
        const data_type data_set[] = {
            { bit::flag32_t(0xAAAAAAAA),  0u, false },
            { bit::flag32_t(0xAAAAAAAA),  7u, true },
            { bit::flag32_t(0xAAAAAAAA), 14u, false },
            { bit::flag32_t(0xAAAAAAAA), 31u, true },
        };

        for (const data_type &data : data_set) {
            const uint32_t bit = bit::flag32_t::at_index(data.index);
            EXPECT_EQ(data.flag.test(bit), data.exp);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_core_bits_flag, set) {
    // set
    {
        struct data_type { bit::flag8_t flag; uint8_t index; bool before, after; };
        const data_type data_set[] = {
            { bit::flag8_t(0x00), 0u, false, true },
            { bit::flag8_t(0x00), 7u, false, true },
            { bit::flag8_t(0xFF), 0u, true, true },
            { bit::flag8_t(0xFF), 7u, true, true },
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

// ------------------------------------------------------------------------- //

TEST(gea_core_bits_flag, clear) {
    // clear
    {
        struct data_type { bit::flag8_t flag; uint8_t index; bool before, after; };
        const data_type data_set[] = {
            { bit::flag8_t(0x00), 0u, false, false },
            { bit::flag8_t(0x00), 7u, false, false },
            { bit::flag8_t(0xFF), 0u, true, false },
            { bit::flag8_t(0xFF), 7u, true, false },
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

// ------------------------------------------------------------------------- //

TEST(gea_core_bits_flag, toggle) {
    // toggle
    {
        struct data_type { bit::flag8_t flag; uint8_t index; bool before, after; };
        const data_type data_set[] = {
            { bit::flag8_t(0x00), 0u, false, true },
            { bit::flag8_t(0x00), 7u, false, true },
            { bit::flag8_t(0xFF), 0u, true, false },
            { bit::flag8_t(0xFF), 7u, true, false },
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
