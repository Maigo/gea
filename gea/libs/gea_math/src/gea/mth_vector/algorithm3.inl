#include <gea/mth_vector/vector3.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //
inline const float distance_to_line(const point3 &line_p0, const point3 &line_p1, const point3 &p)
{
    const vector3 v0 = line_p0.to(line_p1);
    const vector3 v1 = line_p0.to(p);

    const float dot = v1.dot_product(v0);
    const vector3 v2 = v1 - dot * v0;

    return v2.length();
}

} // namespace mth //
} // namespace gea //
