// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/data/core/guid.h>

namespace gea {
namespace data {

// ------------------------------------------------------------------------- //
// guid                                                                      //
// ------------------------------------------------------------------------- //

TEST(gea_data_core_guid, compare)
{
    // compare
    {
        EXPECT_TRUE(true);
    }
}

TEST(gea_data_core_guid, to_string)
{
    // to_string
    {
        struct data_type { const uint8_t data[16]; const char *string; };
        const data_type data_set[] = {
            //  |> little-endian                                |> big-endian.
            { { 0x33, 0x22, 0x11, 0x00, 0x55, 0x44, 0x77, 0x66, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff }, "00112233-4455-6677-8899-AABBCCDDEEFF" }
        };

        for (const data_type &data : data_set) {
            static_string_builder<37> builder;
            EXPECT_STREQ(to_string(guid(data.data), builder), data.string);
        }
    }
}

TEST(gea_data_core_guid, from_string)
{
    // from_string
    {
        struct data_type { const uint8_t data[16]; const char *string; };
        const data_type data_set[] = {
            //  |> little-endian                                |> big-endian.
            { { 0x33, 0x22, 0x11, 0x00, 0x55, 0x44, 0x77, 0x66, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff }, "00112233-4455-6677-8899-AABBCCDDEEFF" }
        };

        for (const data_type &data : data_set) {
            EXPECT_EQ(from_string(data.string), guid(data.data));
        }
    }
}

} // namespace data //
} // namespace gea //
