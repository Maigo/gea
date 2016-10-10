
#include <assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// line2                                                                     //
// ------------------------------------------------------------------------- //

inline line2::line2() {}

// ------------------------------------------------------------------------- //

inline internal::modify2 &line2::modify() { return m_container; }

// ------------------------------------------------------------------------- //

inline const internal::modify2 &line2::modify() const { return m_container; }

// ------------------------------------------------------------------------- //

inline const line2::size_type line2::size() const { return m_container.m_points.size(); }

// ------------------------------------------------------------------------- //

inline const bool line2::empty() const { return m_container.m_points.empty(); }

// ------------------------------------------------------------------------- //

inline const point2 &line2::operator [](const size_type i) const {
    assert(0 <= i && i < m_container.m_points.size() && "index out of bounds!");
    return m_container.m_points[i];
}

// ------------------------------------------------------------------------- //

inline const line2::points_type &line2::points() const { return m_container.m_points; }

} // namespace mth //
} // namespace gea //
