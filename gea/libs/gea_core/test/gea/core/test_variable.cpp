// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/variable.h>

namespace gea {

// ------------------------------------------------------------------------- //
// variable                                                                  //
// ------------------------------------------------------------------------- //

TEST(mth_core_variable, variable) {
    // get_value
    {
        EXPECT_EQ(variable(1.234f).get_value<float>(), 1.234f);
        EXPECT_EQ(variable(float(1.234f)).get_value<float>(), 1.234f);
        EXPECT_EQ(variable(uint16_t(123)).get_value<uint16_t>(), 123);
//      EXPECT_EQ(variable().get_value<float>(), 0.0f);
//      EXPECT_EQ(variable().get_value<uint16_t>(), 0);
    }
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

TEST(mth_core_variable, to_string) {
    // to_string
    {
        struct data_type { variable var; const char *string; };
        const data_type data_set[] = {
            { variable(int8_t(0)), "variable_type__int8" },
            { variable(float(0.f)), "variable_type__float32" },
        };

        for (const data_type &data : data_set) {
            EXPECT_STREQ(to_string(data.var.type), data.string);
        }
    }
}

TEST(mth_core_variable, get_variable_type) {
    // get_variable_type
    {
        EXPECT_EQ(get_variable_type<int32_t>(), variable_type__int32);
//      EXPECT_EQ(get_variable_type<const int32_t>(), variable_type__int32);
//      EXPECT_EQ(get_variable_type<volatile int32_t>(), variable_type__int32);
        EXPECT_EQ(get_variable_type<uint8_t>(), variable_type__uint8);
        EXPECT_EQ(get_variable_type<float>(), variable_type__float32);
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
