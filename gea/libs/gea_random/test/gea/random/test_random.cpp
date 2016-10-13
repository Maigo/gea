
#include <gtest/gtest.h>

#include <gea/random/random.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// helper traits                                                             //
// ------------------------------------------------------------------------- //

template <typename T>
struct trait {
    static inline const bool lower(const T v0, const T v1) { return (v0 <= v1); }
    static inline const bool upper(const T v0, const T v1) { return (v0 <= v1); }
};

template <>
struct trait<float>
{
    static inline const bool lower(const float v0, const float v1) { return (v0 <= v1); }
    static inline const bool upper(const float v0, const float v1) { return (v0 <  v1); }
};

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

template <typename T>
static const bool in_range(const T v, const T min, const T max) {
    return trait<T>::lower(min, v) && trait<T>::upper(v, max);
}

// ------------------------------------------------------------------------- //
// random                                                                    //
// ------------------------------------------------------------------------- //

TEST(gea_random, random_enclosure)
{
    for (int i = 0, e = 1000; i < e; ++i) {
        EXPECT_TRUE(in_range(g_random.rfloat(), 0.0f, 1.0f)); // 0.0 <= v < 1.0
    }
}

} // namespace mth //
} // namespace gea //
