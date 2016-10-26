// header include
#include "polygon2.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

namespace {

static const float determinant(const point2 &c0, const point2 &c1) {
    return (c0.x * c1.y - c1.x * c0.y);
}

} // namespace //

// ------------------------------------------------------------------------- //
// polygon2                                                                  //
// ------------------------------------------------------------------------- //

const float polygon2::circumference() const
{
    const pointset_type &points = m_container.m_points;

    float circumference = 0.0f;
    for (int i = 0, e = points.size(); i < e; ++i) {
        circumference += points[i].to(points[(i + 1) % e]).length();
    }
    return circumference;
}

// ------------------------------------------------------------------------- //

const float polygon2::area() const
{
    const pointset_type &points = m_container.m_points;

    float area = 0.0f;
    for (int i = 0, e = points.size(); i < e; ++i) {
        area += determinant(points[i], points[(i + 1) % e]);
    }
    return fabs(area * 0.5f);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
