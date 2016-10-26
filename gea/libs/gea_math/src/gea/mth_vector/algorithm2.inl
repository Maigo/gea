
// gea includes
#include <gea/mth_vector/vector2.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //
inline const float distance_to_line(const point2 &line_p0, const point2 &line_p1, const point2 &p)
{
    const vector2 v0 = line_p0.to(line_p1);
    const vector2 v1 = line_p0.to(p);
    l_assert_msg(approx_ne(v0, vector2::ZERO), "invalid line!");

    const float dot = v1.dot_product(v0);
    const vector2 v2 = v1 - (dot * v0) / v0.length_sq();

    return v2.length();
}

// ------------------------------------------------------------------------- //

inline const winding_type winding(const point2 &p0, const point2 &p1, const point2 &p2)
{
    const float value = (p2.y - p0.y) * (p1.x - p2.x) - (p2.x - p0.x) * (p1.y - p2.y);
    return static_cast<winding_type>(sign(value));
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
