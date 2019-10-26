// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/pattern/either.h>

namespace gea {

// ------------------------------------------------------------------------- //
// either                                                                    //
// ------------------------------------------------------------------------- //

TEST(gea_core_either, either) {
    typedef either<uint32_t, float_t> either_t;
    typedef maybe<uint32_t> maybe_l_t;
    typedef maybe<float_t> maybe_r_t;

    struct data_type { uint32_t i; float_t f; bool b; };
    const data_type data_set[] = {
        { 1, 1.1f, true },
        { 2, 2.2f, true },
        { 3, 3.3f, false },
        { 4, 4.4f, false },
    };

    for (const data_type& data : data_set) {
        const either_t e = (data.b ? either_t::left(data.i) : either_t::right(data.f));
        EXPECT_EQ(e.has_left(), data.b);
        EXPECT_EQ(e.get_left(0), data.b ? data.i : 0);
        EXPECT_EQ(e.get_left(), data.b ? maybe_l_t(data.i) : maybe_l_t());

        EXPECT_EQ(e.has_right(), !data.b);
        EXPECT_EQ(e.get_right(0.0f), !data.b ? data.f : 0.0f);
        EXPECT_EQ(e.get_right(), !data.b ? maybe_r_t(data.f) : maybe_r_t());
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
