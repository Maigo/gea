
#include <gtest/gtest.h>

#include <gea/template/type_traits.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// type_traits                                                               //
// ------------------------------------------------------------------------- //

TEST(gea_template, primary_type_categories)
{
    // is_void
    {
        EXPECT_EQ((is_void<void>::value), true);
        EXPECT_EQ((is_void<char>::value), false);
        EXPECT_EQ((is_void<bool>::value), false);

        struct pod_t {};
        EXPECT_EQ((is_void<pod_t>::value), false);
    }

    // is_same
    {
        EXPECT_EQ((is_same<void, void>::value), true);
        EXPECT_EQ((is_same<char, bool>::value), false);
        EXPECT_EQ((is_same<bool, char>::value), false);

        struct pod_t {};
        EXPECT_EQ((is_same<pod_t, pod_t>::value), true);
    }
}

TEST(gea_template, type_properties)
{
    // is_const
    {
        EXPECT_EQ((is_const<      int>::value), false);
        EXPECT_EQ((is_const<const int>::value), true);

        struct pod_t {};
        EXPECT_EQ((is_const<      pod_t>::value), false);
        EXPECT_EQ((is_const<const pod_t>::value), true);
    }
}

} // namespace mth //
} // namespace gea //
