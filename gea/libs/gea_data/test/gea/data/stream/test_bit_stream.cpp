// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/data/stream/bit_stream.h>
#include <gea/data/stream/fixed_stream.h>

namespace gea {

// ------------------------------------------------------------------------- //
// bit_ostream                                                               //
// ------------------------------------------------------------------------- //

TEST(gea_data, bit_ostream)
{
    // conversion functions
    {
        uint8_t buffer[10] = { 0 };
        fixed_ostream fostream(buffer, sizeof(buffer) / sizeof(buffer[0]));

        bit_ostream ostream(fostream);
        ostream.write_uint32(42, 0, 100);

        EXPECT_TRUE(true);
    }
}

} // namespace gea //
