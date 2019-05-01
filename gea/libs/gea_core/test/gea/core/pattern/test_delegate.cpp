// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/core/pattern/delegate.h>

namespace gea {

template <typename T>
struct test_struct {
    test_struct(const T& offset) : offset(offset) {}
    const T add_offset(const T& lhs, const T& rhs) const { return offset + lhs + rhs; }
    static const T add(const T& lhs, const T& rhs) { return lhs + rhs; }
    T offset;
};

// ------------------------------------------------------------------------- //
// delegate                                                                  //
// ------------------------------------------------------------------------- //

TEST(gea_core_delegate, delegate_member_function)
{
    // non-const member function
    {
        typedef delegate<const int8_t(const int8_t&, const int8_t&)> delegate_t;
        typedef test_struct<int8_t> test_struct_t;

        struct data_type { int8_t a, b, init, ab; };
        const data_type data_set[] = {
            {  1,  2, 1,  4 },
            { -3,  4, 2,  3 },
            {  5, -6, 4,  3 },
            { -7, -8, 8, -7 },
        };

        for (const data_type &data : data_set) {
            test_struct_t add(data.init);
            delegate_t delegate = delegate_t::create<test_struct_t, &test_struct_t::add_offset>(&add);

            EXPECT_EQ(delegate(data.a, data.b), data.ab);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_core_delegate, delegate_const_member_function)
{
    // const member function
    {
        typedef delegate<const int32_t(const int32_t&, const int32_t&)> delegate_t;
        typedef test_struct<int32_t> add_t;

        struct data_type { int8_t a, b, init, ab; };
        const data_type data_set[] = {
            {  1,  2, 1,  4 },
            { -3,  4, 2,  3 },
            {  5, -6, 4,  3 },
            { -7, -8, 8, -7 },
        };

        for (const data_type &data : data_set) {
            add_t add(data.init);
            delegate_t delegate = delegate_t::create<add_t, &add_t::add_offset>(&add);

            EXPECT_EQ(delegate(data.a, data.b), data.ab);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_core_delegate, delegate_function)
{
    // function
    {
        typedef delegate<const float(const float&, const float&)> delegate_t;
        typedef test_struct<float> test_struct_t;

        struct data_type { float a, b, ab; };
        const data_type data_set[] = {
            {  1.f,  2.f,  3.f },
            { -3.f,  4.f,  1.f },
            {  5.f, -6.f, -1.f },
            { -7.f, -8.f,-15.f },
        };

        for (const data_type &data : data_set) {
            delegate_t delegate = delegate_t::create<&test_struct_t::add>();

            EXPECT_FLOAT_EQ(delegate(data.a, data.b), data.ab);
        }
    }
}

// ------------------------------------------------------------------------- //

TEST(gea_core_delegate, delegate_lambda)
{
    // function
    {
        typedef delegate<const bool(const bool other)> delegate_t;

        struct data_type { bool a, not_a; };
        const data_type data_set[] = {
            { true, false },
            { false, true },
        };

        for (const data_type &data : data_set) {
            delegate_t delegate = [](const bool other)->const bool { return !other; };
            EXPECT_EQ(delegate(data.a), data.not_a);

            delegate = [](const bool other)->const bool { return !other; };
            EXPECT_EQ(delegate(data.a), data.not_a);
        }
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //
