#ifndef __GEA_ASSERT_H__
#define __GEA_ASSERT_H__

// STD includes
#include <stdio.h>

// gea engine includes
#include <gea/system/platform.h>

// defines
#define ASSERT_CONTEXT() gea::context( __LINE__, __FILE__, __FUNC__ )

namespace gea {

// ------------------------------------------------------------------------- //
// context                                                                   //
// ------------------------------------------------------------------------- //
class context {
public:
    inline context();
    inline context(uint32_t line, const char* file, const char* func);

    inline uint32_t    line() const;
    inline const char* file() const;
    inline const char* func() const;

private:
    uint32_t    m_line;
    const char* m_file;
    const char* m_func;
};

// ------------------------------------------------------------------------- //
// run-time light assert                                                     //
// ------------------------------------------------------------------------- //

#define l_error_msg( msg )                                              \
    do {                                                                \
        capture_assertion_error( "error", msg, ASSERT_CONTEXT() );      \
        gea::system_break();                                            \
    } while (0)

#define l_assert( expr )                                                \
    if ( expr ) {}                                                      \
    else {                                                              \
        capture_assertion_error( #expr, ASSERT_CONTEXT() );             \
        gea::system_break();                                            \
    }
#define l_assert_msg( expr, msg )                                       \
    if ( expr ) {}                                                      \
    else {                                                              \
        capture_assertion_error( #expr, msg, ASSERT_CONTEXT() );        \
        gea::system_break();                                            \
    }

//TODO: allow for different types of assertion message handling systems!
inline void capture_assertion_error(const char *expr, const context &cont) {
    printf("%s -- (%s:%i): %s\n", cont.file(), cont.func(), cont.line(), expr);
}
inline void capture_assertion_error(const char *expr, const char *msg, const context &cont) {
    printf("%s -- (%s:%i): %s -- %s\n", cont.file(), cont.func(), cont.line(), expr, msg);
}

// ------------------------------------------------------------------------- //

#define l_assert_implement l_error_msg( "This feature is not implemeneted!" )

// ------------------------------------------------------------------------- //
// compile-time assert                                                       //
// ------------------------------------------------------------------------- //
namespace internal {

// the boost way
template <bool B> struct STATIC_ASSERTION_FAILURE;
template <>       struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

template<int N> struct static_assert_test {};

} // namespace internal //

#define c_assert_msg( expr, msg )                                               \
    typedef ::gea::internal::static_assert_test<                                \
        sizeof(::gea::internal::STATIC_ASSERTION_FAILURE<(expr)==0?false:true>)>\
            msg

#define c_assert( expr ) c_assert_msg( expr, static_assert_typedef_##__LINE__ )

} // namespace gea //

#include "assert.inl"

#endif // __GEA_ASSERT_H__ //
