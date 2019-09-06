// gtest includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// gea includes
#include <gea/system/platform_intrinsic.h>
#include <gea/core/string/string_builder.h>

namespace gea {


// ------------------------------------------------------------------------- //
// system functions                                                          //
// ------------------------------------------------------------------------- //

//TEST(gea_core_platform_intrinsic, i_system_break)
//{
//    // hmm
//}

TEST(gea_core_platform_intrinsic, i_cpuid)
{
    // cpuid
    {
        cpuid_info info = { 0, 0, 0, 0 };
        i_cpuid(info, 0, 0);

        static_string_builder<> string;
        string.append(reinterpret_cast<const char*>(&info.ebx), 4);
        string.append(reinterpret_cast<const char*>(&info.edx), 4);
        string.append(reinterpret_cast<const char*>(&info.ecx), 4);

        // test valid vendor string
        EXPECT_THAT(string.data(), testing::MatchesRegex("\\w*"));
    }
}

// ------------------------------------------------------------------------- //
// math functions                                                            //
// ------------------------------------------------------------------------- //

static const float PI = 3.1415926535897932384626433832795f;
static const float SQRT_2 = 1.4142135623730950488016887242097f;
static const float SQRT_2_INV = 1.0f / SQRT_2;
static const float APPROX_EPSILON = 1.0e-4f;

TEST(gea_core_platform_intrinsic, i_fsincos)
{
    // fsincos
    {
        struct data_type { float angle, sin, cos; };
        const data_type data_set[] = {
            { PI / 1, 0.0f, -1.0f },
            { PI / 2, 1.0f,  0.0f },
            { PI / 4, SQRT_2_INV, SQRT_2_INV },
        };

        float out_sin = 0.0f, out_cos = 0.0f;
        for (const data_type &data : data_set) {
            i_fsincos(data.angle, out_sin, out_cos);
            EXPECT_NEAR(out_sin, data.sin, APPROX_EPSILON);
            EXPECT_NEAR(out_cos, data.cos, APPROX_EPSILON);
        }
    }
}

TEST(mth_core_intrinsic, i_fsin)
{
    // fsin
    {
        struct data_type { float angle, sin; };
        const data_type data_set[] = {
            { PI / 1, 0.0f },
            { PI / 2, 1.0f },
            { PI / 4, SQRT_2_INV },
        };

        float out_sin = 0.0f;
        for (const data_type& data : data_set) {
            i_fsin(data.angle, out_sin);
            EXPECT_NEAR(out_sin, data.sin, APPROX_EPSILON);
        }
    }
}

TEST(mth_core_intrinsic, i_fcos)
{
    // fcos
    {
        struct data_type { float angle, cos; };
        const data_type data_set[] = {
            { PI / 1, -1.0f },
            { PI / 2,  0.0f },
            { PI / 4, SQRT_2_INV },
        };

        float out_cos = 0.0f;
        for (const data_type& data : data_set) {
            i_fcos(data.angle, out_cos);
            EXPECT_NEAR(out_cos, data.cos, APPROX_EPSILON);
        }
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
