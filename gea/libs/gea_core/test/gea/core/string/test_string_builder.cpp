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
    }
}

// ------------------------------------------------------------------------- //
// string_builder                                                            //
// ------------------------------------------------------------------------- //

TEST(mth_core_string_builder, append) {
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

TEST(mth_core_string_builder, append_format) {
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

// ------------------------------------------------------------------------- //

} // namespace gea //
