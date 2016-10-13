
// external includes
#include <gea/random/random.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// polar2                                                                    //
// ------------------------------------------------------------------------- //
inline const polar2 rand_polar2() {
    const float r0 = g_random.rfloat();
    return polar2(1.0f, 2.0f * PI * r0);
}

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //
inline const point2 rand_point2(const point2 &nw_corner, const point2 &se_corner) {
    const float r0 = g_random.rfloat(), r1 = g_random.rfloat();
    return point2((se_corner.x - nw_corner.x) * r0 + nw_corner.x, (se_corner.y - nw_corner.y) * r1 + nw_corner.y);
}

// ------------------------------------------------------------------------- //
// vector2                                                                   //
// ------------------------------------------------------------------------- //
inline const vector2 rand_vector2(const float max_length, const float min_length) {
    const vector2 v(rand_polar2());
    return ((max_length - min_length) * v) + min_length;
}

} // namespace mth //
} // namespace gea //
