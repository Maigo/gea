// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/mth_core/bits.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// bit hacks                                                                 //
// ------------------------------------------------------------------------- //

TEST(gea_math, bits_ones)
{
    // count # of ones (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t ones; };
        const data_type data_set[] = {
            { 0x67, 5 },
            { 0xA3, 4 },
            { 0x00, 0 },
            { 0xFF, 8 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::ones(data.bits), data.ones);
        }
    }
    // count # of ones (uint16_t)
    {
        struct data_type { uint16_t bits; uint8_t ones; };
        const data_type data_set[] = {
            { 0x3A65,  8 },
            { 0xC59A,  8 },
            { 0x0000,  0 },
            { 0xFFFF, 16 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::ones(data.bits), data.ones);
        }
    }
    // count # of ones (uint32_t)
    {
        struct data_type { uint32_t bits; uint8_t ones; };
        const data_type data_set[] = {
            { 0x23C863F9, 16 },
            { 0x8F09345C, 14 },
            { 0x00000000,  0 },
            { 0xFFFFFFFF, 32 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::ones(data.bits), data.ones);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_zeros)
{
    // count # of zeros (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t zeros; };
        const data_type data_set[] = {
            { 0x67, 3 },
            { 0xA3, 4 },
            { 0x00, 8 },
            { 0xFF, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::zeros(data.bits), data.zeros);
        }
    }
    // count # of zeros (uint16_t)
    {
        struct data_type { uint16_t bits; uint8_t zeros; };
        const data_type data_set[] = {
            { 0x3A65,  8 },
            { 0xC59A,  8 },
            { 0x0000, 16 },
            { 0xFFFF,  0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::zeros(data.bits), data.zeros);
        }
    }
    // count # of zeros (uint32_t)
    {
        struct data_type { uint32_t bits; uint8_t zeros; };
        const data_type data_set[] = {
            { 0x23C863F9, 16 },
            { 0x8F09345C, 18 },
            { 0x00000000, 32 },
            { 0xFFFFFFFF,  0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::zeros(data.bits), data.zeros);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_lzc)
{
    // count # of leading zeroes (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t lzc; };
        const data_type data_set[] = {
            { 0x3C, 2 },
            { 0x1E, 3 },
            { 0x00, 8 },
            { 0xFF, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::lzc(data.bits), data.lzc);
        }
    }
    // count # of leading zeroes (uint16_t)
    {
        struct data_type { uint16_t bits; uint8_t lzc; };
        const data_type data_set[] = {
            { 0x1CA8,  3 },
            { 0x0E54,  4 },
            { 0x0000, 16 },
            { 0xFFFF,  0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::lzc(data.bits), data.lzc);
        }
    }
    // count # of leading zeroes (uint32_t)
    {
        struct data_type { uint32_t bits; uint8_t lzc; };
        const data_type data_set[] = {
            { 0x07CACAC8,  5 },
            { 0x1F2B2B20,  3 },
            { 0x00000000, 32 },
            { 0xFFFFFFFF,  0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::lzc(data.bits), data.lzc);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_tzc)
{
    // count # of trailing zeroes (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t tzc; };
        const data_type data_set[] = {
            { 0x3C, 2 },
            { 0x1E, 1 },
            { 0x00, 8 },
            { 0xFF, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::tzc(data.bits), data.tzc);
        }
    }
    // count # of trailing zeroes (uint16_t)
    {
        struct data_type { uint16_t bits; uint8_t tzc; };
        const data_type data_set[] = {
            { 0x1CA8,  3 },
            { 0x0E54,  2 },
            { 0x0000, 16 },
            { 0xFFFF,  0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::tzc(data.bits), data.tzc);
        }
    }
    // count # of trailing zeroes (uint32_t)
    {
        struct data_type { uint32_t bits; uint8_t tzc; };
        const data_type data_set[] = {
            { 0x07CACAC8,  3 },
            { 0x1F2B2B20,  5 },
            { 0x00000000, 32 },
            { 0xFFFFFFFF,  0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::tzc(data.bits), data.tzc);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_loc)
{
    // count # of leading ones (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t loc; };
        const data_type data_set[] = {
            { 0xC3, 2 },
            { 0xE1, 3 },
            { 0xFF, 8 },
            { 0x00, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::loc(data.bits), data.loc);
        }
    }
    // count # of leading ones (uint16_t)
    {
        struct data_type { uint16_t bits; uint8_t loc; };
        const data_type data_set[] = {
            { 0xE357, 3 },
            { 0xF1AB, 4 },
            { 0xFFFF, 16 },
            { 0x0000, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::loc(data.bits), data.loc);
        }
    }
    // count # of leading ones (uint32_t)
    {
        struct data_type { uint32_t bits; uint8_t loc; };
        const data_type data_set[] = {
            { 0xF8353537, 5 },
            { 0xE0D4D4DF, 3 },
            { 0xFFFFFFFF, 32 },
            { 0x00000000, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::loc(data.bits), data.loc);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_toc)
{
    // count # of trailing ones (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t toc; };
        const data_type data_set[] = {
            { 0xC3, 2 },
            { 0xE1, 1 },
            { 0xFF, 8 },
            { 0x00, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::toc(data.bits), data.toc);
        }
    }
    // count # of trailing ones (uint16_t)
    {
        struct data_type { uint16_t bits; uint8_t toc; };
        const data_type data_set[] = {
            { 0xE357, 3 },
            { 0xF1AB, 2 },
            { 0xFFFF, 16 },
            { 0x0000, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::toc(data.bits), data.toc);
        }
    }
    // count # of trailing ones (uint32_t)
    {
        struct data_type { uint32_t bits; uint8_t toc; };
        const data_type data_set[] = {
            { 0xF8353537, 3 },
            { 0xE0D4D4DF, 5 },
            { 0xFFFFFFFF, 32 },
            { 0x00000000, 0 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::toc(data.bits), data.toc);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_lbs)
{
    // lowest bit set (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t lbs; };
        const data_type data_set[] = {
            { 0x3C, 0x04 },
            { 0x1E, 0x02 },
            { 0x00, 0x00 },
            { 0xFF, 0x01 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::lbs(data.bits), data.lbs);
        }
    }
    // lowest bit set (uint16_t)
    {
        struct data_type { uint16_t bits; uint16_t lbs; };
        const data_type data_set[] = {
            { 0x1CA8, 0x0008 },
            { 0x0E54, 0x0004 },
            { 0x0000, 0x0000 },
            { 0xFFFF, 0x0001 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::lbs(data.bits), data.lbs);
        }
    }
    // lowest bit set (uint32_t)
    {
        struct data_type { uint32_t bits; uint32_t lbs; };
        const data_type data_set[] = {
            { 0x07CACAC8, 0x00000008 },
            { 0x1F2B2B20, 0x00000020 },
            { 0x00000000, 0x00000000 },
            { 0xFFFFFFFF, 0x00000001 },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::lbs(data.bits), data.lbs);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_rpow2)
{
    // round up to the next highest power of 2 (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t rpow2; };
        const data_type data_set[] = {
            { 0x3C, 0x40 },
            { 0x1E, 0x20 },
            { 0x00, 0x00 },
            { 0xFF, 0x00 }, // overflow
        };

        for (const data_type &data : data_set) {
            const uint8_t rpow2 = bit::rpow2(data.bits);
            EXPECT_EQ(bit::rpow2(data.bits), data.rpow2);
        }
    }
    // round up to the next highest power of 2 (uint16_t)
    {
        struct data_type { uint16_t bits; uint16_t rpow2; };
        const data_type data_set[] = {
            { 0x1CA8, 0x2000 },
            { 0x0E54, 0x1000 },
            { 0x0000, 0x0000 },
            { 0xFFFF, 0x0000 }, // overflow
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::rpow2(data.bits), data.rpow2);
        }
    }
    // round up to the next highest power of 2 (uint32_t)
    {
        struct data_type { uint32_t bits; uint32_t rpow2; };
        const data_type data_set[] = {
            { 0x07CACAC8, 0x08000000 },
            { 0x1F2B2B20, 0x20000000 },
            { 0x00000000, 0x00000000 },
            { 0xFFFFFFFF, 0x00000000 }, // overflow
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::rpow2(data.bits), data.rpow2);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_math, bits_mask)
{
    // derive smallest mask to encompass number (uint8_t)
    {
        struct data_type { uint8_t bits; uint8_t mask; };
        const data_type data_set[] = {
            { 0x3C, 0x3F },
            { 0x1E, 0x1F },
            { 0x00, 0x00 },
            { 0xFF, 0xFF },
        };

        for (const data_type &data : data_set) {
            const uint8_t rpow2 = bit::rpow2(data.bits);
            EXPECT_EQ(bit::mask(data.bits), data.mask);
        }
    }
    // derive smallest mask to encompass number (uint16_t)
    {
        struct data_type { uint16_t bits; uint16_t mask; };
        const data_type data_set[] = {
            { 0x1CA8, 0x1FFF },
            { 0x0E54, 0x0FFF },
            { 0x0000, 0x0000 },
            { 0xFFFF, 0xFFFF },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::mask(data.bits), data.mask);
        }
    }
    // derive smallest mask to encompass number (uint32_t)
    {
        struct data_type { uint32_t bits; uint32_t mask; };
        const data_type data_set[] = {
            { 0x07CACAC8, 0x07FFFFFF },
            { 0x1F2B2B20, 0x1FFFFFFF },
            { 0x00000000, 0x00000000 },
            { 0xFFFFFFFF, 0xFFFFFFFF },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bit::mask(data.bits), data.mask);
        }
    }
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
