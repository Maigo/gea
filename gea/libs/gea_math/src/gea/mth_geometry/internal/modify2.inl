
#include <assert.h>

namespace gea {
namespace mth {
namespace internal {

// ------------------------------------------------------------------------- //
// modify2                                                                   //
// ------------------------------------------------------------------------- //

inline void modify2::reserve(const size_type count)
{
    m_points.reserve(count);
}

// ------------------------------------------------------------------------- //

inline void modify2::add_point(const point2 &p)
{
    m_points.push_back(p);
}

// ------------------------------------------------------------------------- //

inline void modify2::add_point(const vector2 &v)
{
    assert(!m_points.empty() && "trying to line to empty line!");
    m_points.push_back(m_points.back() + v);
}

// ------------------------------------------------------------------------- //

} // namespace internal //
} // namespace mth //
} // namespace gea //
