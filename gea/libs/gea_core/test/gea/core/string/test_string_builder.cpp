// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/string/string_builder.h>
#include <gea/core/variable.h>

namespace gea {

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

static void variable_format(const char *format, const variable &var, string_builder &builder) {
    switch (var.type) {
    case variable_type__int8:
        builder.append_format(format, var.get_value<int8_t>());
        break;
    case variable_type__int16:
        builder.append_format(format, var.get_value<int16_t>());
        break;
    case variable_type__int32:
        builder.append_format(format, var.get_value<int32_t>());
        break;
    case variable_type__int64:
        builder.append_format(format, var.get_value<int64_t>());
        break;
    case variable_type__uint8:
        builder.append_format(format, var.get_value<uint8_t>());
        break;
    case variable_type__uint16:
        builder.append_format(format, var.get_value<uint16_t>());
        break;
    case variable_type__uint32:
        builder.append_format(format, var.get_value<uint32_t>());
        break;
    case variable_type__uint64:
        builder.append_format(format, var.get_value<uint64_t>());
        break;
    case variable_type__float32:
        builder.append_format(format, var.get_value<float>());
        break;
    case variable_type__double64:
        builder.append_format(format, var.get_value<double>());
        break;
    default:
        l_error_msg("invalid variable type!");
        break;
    }
}

// ------------------------------------------------------------------------- //
// string_builder                                                            //
// ------------------------------------------------------------------------- //

TEST(mth_core_static_string_builder, append) {
    // append
    {
        struct data_type { const char *a, *b, *c; const char *string; };
        const data_type data_set[] = {
            { "a", "b", "c", "abc" },           // normal
            { "", "", "", "" },                 // empty
            { "abc", "def", "ghf", "abcdefg" }, // overflow
        };

        for (const data_type &data : data_set) {
            static_string_builder<8> builder;
            builder.append(data.a).append(data.b).append(data.c);
            EXPECT_STREQ(builder.data(), data.string);
        }
    }
}

TEST(mth_core_static_string_builder, append_format) {
    // append_format
    {
        struct data_type { const char *format; variable var; const char *string; };
        const data_type data_set[] = {
            { "%i",   variable(int32_t(1234567)), "1234567" },
            { "%.3f", variable(float(1.234f)),    "1.234" },
            { "%04X", variable(uint16_t(0xF00D)), "F00D" },
        };

        for (const data_type &data : data_set) {
            static_string_builder<8> builder;
            variable_format(data.format, data.var, builder);
            EXPECT_STREQ(builder.data(), data.string);
        }
    }
}

TEST(mth_core_static_string_builder, reserve) {
    // reserve
    {
        struct data_type { const size_t size; const bool result; };
        const data_type data_set[] = {
            { 4, true },
            { 8, true },
            { 9, false },
        };

        for (const data_type &data : data_set) {
            static_string_builder<8> builder;
            EXPECT_EQ(builder.reserve(data.size), data.result);
        }
    }
}

TEST(mth_core_static_string_builder, resize) {
    // resize
    {
        struct data_type { const size_t size; const char c; const bool result; const char *string; };
        const data_type data_set[] = {
            { 5, 'a', true, "aaaaa" },
            { 0, '~', true, "" },
            { 7, 'X', true, "XXXXXXX" },
            { 8, 'X', false, "XXXXXXX" },
        };

        for (const data_type &data : data_set) {
            static_string_builder<8> builder;
            EXPECT_EQ(builder.resize(data.size, data.c), data.result);
            EXPECT_STREQ(builder.data(), data.string);
        }
    }
}

TEST(mth_core_static_string_builder, reset) {
    // reset
    {
        static_string_builder<8> builder;
        builder.append("string").reset();
        EXPECT_EQ(builder.size(), 0);
        EXPECT_STREQ(builder.data(), "");
    }
}

TEST(mth_core_static_string_builder, empty) {
    // empty
    {
        static_string_builder<8> builder;
        EXPECT_TRUE(builder.empty());
        EXPECT_FALSE(builder.append("string").empty());
    }
}

TEST(mth_core_static_string_builder, size) {
    // size
    {
        struct data_type { const char *string; const size_t size; };
        const data_type data_set[] = {
            { "string", 6 },
            { "", 0 },
            { "12345678", 7 },
        };

        for (const data_type &data : data_set) {
            static_string_builder<8> builder;
            EXPECT_EQ(builder.append(data.string).size(), data.size);
        }
    }
}

TEST(mth_core_static_string_builder, capacity) {
    // capacity
    {
        static_string_builder<8> builder;
        EXPECT_EQ(builder.capacity(), 8);
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
