// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/string/string_util.h>

#include <gea/core/bits/bcl.h>

template <typename T>
inline const T min(const T lhs, const T rhs) { return (lhs < rhs) ? lhs : rhs; }

template <typename T0, size_t S0, typename T1, size_t S1>
::testing::AssertionResult CmpHelperARREQ(
    const char* a0_expression, const char* s0_expression, const char* a1_expression, const char* s1_expression,
    const T0(&a0)[S0], const size_t s0, const T1(&a1)[S1], const size_t s1){
    for (size_t i = 0, e = min(s0, s1); i < e; ++i) {
        if ((i >= S0) || (i >= S1) || (a0[i] != a1[i])) {
            return ::testing::AssertionFailure();// << "array[" << i << "] (" << (i >= S1) ? -1 : a1[i] << ") != expected[" << i << "] (" << (i >= S0) ? -1 : a0[i] << ")";
        }
    }

    return ::testing::AssertionSuccess();
}

#define EXPECT_ARREQ(a1, s1, a2, s2) \
  EXPECT_PRED_FORMAT4(CmpHelperARREQ, a1, s1, a2, s2)

namespace gea {

// ------------------------------------------------------------------------- //
// string_util                                                               //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// conversion functions                                                      //
// ------------------------------------------------------------------------- //

TEST(mth_core_string_util, hex_to_dec) {
    // hex_to_dec - single char
    {
        struct data_type { const uint8_t dec; const char hex; };
        const data_type data_set[] = {
            { 0x00, '0' },
            { 0x0A, 'A' },
            { 0x00, 'X' },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(hex_to_dec(data.hex), data.dec);
        }
    }

    // hex_to_dec - uint8_t
    {
        struct data_type { const uint8_t dec; const char hex[3]; const size_t size; };
        const data_type data_set[] = {
            { 0x00, "00", 2 }, { 0x0, "00", 1 }, { 0x0, "00", 0 },
            { 0x12, "12", 2 }, { 0x1, "12", 1 }, { 0x0, "12", 0 },
            { 0x91, "91", 2 }, { 0x9, "91", 1 }, { 0x0, "91", 0 },
            { 0xFA, "FA", 2 }, { 0xF, "FA", 1 }, { 0x0, "FA", 0 },
        };

        for (const data_type &data : data_set) {
            uint8_t dec = 0;
            EXPECT_EQ(hex_to_dec(data.hex, data.size, dec), data.size);
            EXPECT_EQ(data.dec, dec);
        }
    }

    // hex_to_dec - uint16_t
    {
        struct data_type { const uint16_t dec; const char hex[5]; const size_t size; };
        const data_type data_set[] = {
            { 0x0000, "0000", 4 }, { 0x00, "0000", 2 }, { 0x0, "0000", 0 },
            { 0x1234, "1234", 4 }, { 0x12, "1234", 2 }, { 0x0, "1234", 0 },
            { 0x9191, "9191", 4 }, { 0x91, "9191", 2 }, { 0x0, "9191", 0 },
            { 0xFAAF, "FAAF", 4 }, { 0xFA, "FAAF", 2 }, { 0x0, "FAAF", 0 },
        };

        for (const data_type &data : data_set) {
            uint16_t dec = 0;
            EXPECT_EQ(hex_to_dec(data.hex, data.size, dec), data.size);
            EXPECT_EQ(data.dec, dec);
        }
    }

    // hex_to_dec - uint32_t
    {
        struct data_type { const uint32_t dec; const char *hex; const size_t size; };
        const data_type data_set[] = {
            { 0x00000000, "00000000", 8 }, { 0x0000, "00000000", 4 }, { 0x0, "00000000", 0 },
            { 0x12345678, "12345678", 8 }, { 0x1234, "12345678", 4 }, { 0x0, "12345678", 0 },
            { 0x91919191, "91919191", 8 }, { 0x9191, "91919191", 4 }, { 0x0, "91919191", 0 },
            { 0xFAAFFAAF, "FAAFFAAF", 8 }, { 0xFAAF, "FAAFFAAF", 4 }, { 0x0, "FAAFFAAF", 0 },
        };

        for (const data_type &data : data_set) {
            uint32_t dec = 0;
            EXPECT_EQ(hex_to_dec(data.hex, data.size, dec), data.size);
            EXPECT_EQ(data.dec, dec);
        }
    }

    // hex_to_dec - uint64_t
    {
        struct data_type { const uint64_t dec; const char *hex; const size_t size; };
        const data_type data_set[] = {
            { 0x0000000000000000, "0000000000000000", 16 }, { 0x00000000, "0000000000000000", 8 }, { 0x0, "0000000000000000", 0 },
            { 0x123456789ABCDEF0, "123456789ABCDEF0", 16 }, { 0x12345678, "123456789ABCDEF0", 8 }, { 0x0, "123456789ABCDEF0", 0 },
            { 0x9191919191919191, "9191919191919191", 16 }, { 0x91919191, "9191919191919191", 8 }, { 0x0, "9191919191919191", 0 },
            { 0xFAAFFAAFFAAFFAAF, "FAAFFAAFFAAFFAAF", 16 }, { 0xFAAFFAAF, "FAAFFAAFFAAFFAAF", 8 }, { 0x0, "FAAFFAAFFAAFFAAF", 0 },
        };

        for (const data_type &data : data_set) {
            uint64_t dec = 0;
            EXPECT_EQ(hex_to_dec(data.hex, data.size, dec), data.size);
            EXPECT_EQ(data.dec, dec);
        }
    }

    // hex_to_dec - uint8_t *
    {
//        struct data_type { const uint8_t dec[8]; const size_t dec_size; const char hex[17]; const size_t hex_size; };
//        const data_type data_set[] = {
//            { { 0x00, 0x00 }, 2, "0000", 4 },
//            { { 0x12, 0x34, 0x56, 0x78 }, 4, "12345678", 8 },
//            { { 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91 }, 8, "9191919191919191", 16 },
//            { { }, 0, "", 0 },
//        };
//
//        for (const data_type &data : data_set) {
//            uint8_t dec[8] = { 0x00 };
//            EXPECT_EQ(hex_to_dec(data.hex, data.hex_size, dec, data.dec_size), data.dec_size);
//            EXPECT_ARREQ(dec, sizeof(dec), data.dec, data.dec_size);
//        }
        FAIL();
    }
}

TEST(mth_core_string_util, dec_to_hex) {
    // dec_to_hex - single char
    {
        struct data_type { const uint8_t dec; const char hex; };
        const data_type data_set[] = {
            { 0x00, '0' },
            { 0x0A, 'A' },
            { 0x10, '0' },
            { 0x1A, 'A' },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(dec_to_hex(data.dec), data.hex);
        }
    }

    // dec_to_hex - uint8_t
    {
        struct data_type { const uint8_t dec; const char *hex; };
        const data_type data_set[] = {
            { 0x00, "00" },
            { 0x12, "12" },
            { 0x91, "91" },
            { 0xFA, "FA" },
        };

        for (const data_type &data : data_set) {
            char buffer[3] = { 0 };
            EXPECT_TRUE(dec_to_hex(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.hex);
        }
    }

    // dec_to_hex - uint16_t
    {
        struct data_type { const uint16_t dec; const char *hex; };
        const data_type data_set[] = {
            { 0x0000, "0000" },
            { 0x1234, "1234" },
            { 0x9191, "9191" },
            { 0xFAAF, "FAAF" },
        };

        for (const data_type &data : data_set) {
            char buffer[5] = { 0 };
            EXPECT_TRUE(dec_to_hex(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.hex);
        }
    }

    // dec_to_hex - uint32_t
    {
        struct data_type { const uint32_t dec; const char *hex; };
        const data_type data_set[] = {
            { 0x00000000, "00000000" },
            { 0x12345678, "12345678" },
            { 0x91919191, "91919191" },
            { 0xFAAFFAAF, "FAAFFAAF" },
        };

        for (const data_type &data : data_set) {
            char buffer[9] = { 0 };
            EXPECT_TRUE(dec_to_hex(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.hex);
        }
    }

    // dec_to_hex - uint64_t
    {
        struct data_type { const uint64_t dec; const char *hex; };
        const data_type data_set[] = {
            { 0x0000000000000000, "0000000000000000" },
            { 0x123456789ABCDEF0, "123456789ABCDEF0" },
            { 0x9191919191919191, "9191919191919191" },
            { 0xFAAFFAAFFAAFFAAF, "FAAFFAAFFAAFFAAF" },
        };

        for (const data_type &data : data_set) {
            char buffer[17] = { 0 };
            EXPECT_TRUE(dec_to_hex(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.hex);
        }
    }

    // dec_to_hex - uint8_t *
    {
        struct data_type { const uint8_t dec[8]; const size_t n; const char *hex; };
        const data_type data_set[] = {
            { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 2, "0000" },
            { { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 }, 4, "12345678" },
            { { 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91 }, 8, "9191919191919191" },
            { { 0xFA, 0xAF, 0xFA, 0xAF, 0xFA, 0xAF, 0xFA, 0xAF }, 0, "" },
        };

        for (const data_type &data : data_set) {
            char buffer[17] = { 0 };
            EXPECT_TRUE(dec_to_hex(data.dec, data.n, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.hex);
        }
    }
}

TEST(mth_core_string_util, bin_to_dec) {
    // bin_to_dec - single char
    {
        struct data_type { const uint8_t dec;  const char bin; };
        const data_type data_set[] = {
            { 0x0, '0' },
            { 0x1, '1' },
            { 0x0, 'X' },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(bin_to_dec(data.bin), data.dec);
        }
    }
}

TEST(mth_core_string_util, dec_to_bin) {
    // dec_to_bin - single char
    {
        struct data_type { const uint8_t dec;  const char bin; };
        const data_type data_set[] = {
            { 0x0, '0' },
            { 0x1, '1' },
            { 0x2, '0' },
            { 0x3, '1' },
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(dec_to_bin(data.dec), data.bin);
        }
    }

    // dec_to_bin - uint8_t
    {
        struct data_type { const uint8_t dec; const char *bin; };
        const data_type data_set[] = {
            { 0x00, "00000000" },
            { 0x12, "00010010" },
            { 0x91, "10010001" },
            { 0xFA, "11111010" },
        };

        for (const data_type &data : data_set) {
            char buffer[9] = { 0 };
            EXPECT_TRUE(dec_to_bin(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.bin);
        }
    }

    // dec_to_bin - uint16_t
    {
        struct data_type { const uint16_t dec; const char *bin; };
        const data_type data_set[] = {
            { 0x0000, "0000000000000000" },
            { 0x1234, "0001001000110100" },
            { 0x9191, "1001000110010001" },
            { 0xFAAF, "1111101010101111" },
        };

        for (const data_type &data : data_set) {
            char buffer[17] = { 0 };
            EXPECT_TRUE(dec_to_bin(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.bin);
        }
    }

    // dec_to_bin - uint32_t
    {
        struct data_type { const uint32_t dec; const char *bin; };
        const data_type data_set[] = {
            { 0x00000000, "00000000000000000000000000000000" },
            { 0x12345678, "00010010001101000101011001111000" },
            { 0x91919191, "10010001100100011001000110010001" },
            { 0xFAAFFAAF, "11111010101011111111101010101111" },
        };

        for (const data_type &data : data_set) {
            char buffer[33] = { 0 };
            EXPECT_TRUE(dec_to_bin(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.bin);
        }
    }

    // dec_to_bin - uint64_t
    {
        struct data_type { const uint64_t dec; const char *bin; };
        const data_type data_set[] = {
            { 0x0000000000000000, "0000000000000000000000000000000000000000000000000000000000000000" },
            { 0x123456789ABCDEF0, "0001001000110100010101100111100010011010101111001101111011110000" },
            { 0x9191919191919191, "1001000110010001100100011001000110010001100100011001000110010001" },
            { 0xFAAFFAAFFAAFFAAF, "1111101010101111111110101010111111111010101011111111101010101111" },
        };

        for (const data_type &data : data_set) {
            char buffer[65] = { 0 };
            EXPECT_TRUE(dec_to_bin(data.dec, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.bin);
        }
    }

    // dec_to_bin - uint8_t *
    {
        struct data_type { const uint8_t dec[8]; const size_t n; const char *bin; };
        const data_type data_set[] = {
            { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 2, "0000000000000000" },
            { { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 }, 4, "00010010001101000101011001111000" },
            { { 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91 }, 8, "1001000110010001100100011001000110010001100100011001000110010001" },
            { { 0xFA, 0xAF, 0xFA, 0xAF, 0xFA, 0xAF, 0xFA, 0xAF }, 0, "" },
        };

        for (const data_type &data : data_set) {
            char buffer[65] = { 0 };
            EXPECT_TRUE(dec_to_bin(data.dec, data.n, buffer, sizeof(buffer) - 1));
            EXPECT_STREQ(buffer, data.bin);
        }
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
