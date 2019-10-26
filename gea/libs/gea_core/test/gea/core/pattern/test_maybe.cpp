// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/pattern/maybe.h>

namespace gea {

// ------------------------------------------------------------------------- //
// maybe                                                                     //
// ------------------------------------------------------------------------- //

TEST(gea_core_maybe, maybe) {
    typedef maybe<int8_t> maybe_t;

    struct data_type { int8_t v, d; bool b; };
    const data_type data_set[] = {
        { 1, 0, true },
        { 2, 1, true },
        { 3, 2, false },
        { 4, 3, false },
    };

    const bool test = maybe_t(12) == maybe_t(12);
    for (const data_type& data : data_set) {
        const maybe_t m = (data.b ? maybe_t(data.v) : maybe_t());
        EXPECT_EQ(m.has_value(), data.b);
        EXPECT_EQ(m.get_value(data.d), data.b ? data.v : data.d);
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
