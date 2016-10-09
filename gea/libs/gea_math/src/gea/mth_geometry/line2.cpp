
// header include
#include "line2.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// line2                                                                     //
// ------------------------------------------------------------------------- //

const float line2::length() const
{
    const modify_t::points_type &points = m_container.m_points;

    float length = 0.0f;
    for (int i = 1, e = points.size(); i < e; ++i) {
        length += points[i - 1].to(points[i]).length();
    }
    return length;
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
