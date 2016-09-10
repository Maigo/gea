#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //
inline const float distance_to_line(const point2 &line_p0, const point2 &line_p1, const point2 &p)
{
    const vector2 v0 = line_p0.to(line_p1);
    const vector2 v1 = line_p0.to(p);

    const float dot = v1.dot_product(v0);
    const vector2 v2 = v1 - dot * v0;

    return v2.length();
}

} // namespace mth //
} // namespace gea //
