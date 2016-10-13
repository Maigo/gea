
// external includes
#include <gea/random/random.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// polar3                                                                    //
// ------------------------------------------------------------------------- //
inline const polar3 rand_polar3() {
    const float r0 = g_random.rfloat(), r1 = g_random.rfloat();
    return polar3(1.0f, 2.0f * PI * r0, PI * r1);
}

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
inline const quaternion rand_quaternion() {
    const vector3 axis = rand_vector3(1.0f);
    const float angle = g_random.rfloat();
    return quaternion(angle, axis);
}

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
inline const vector3 rand_vector3(const float max_length, const float min_length) {
    const vector3 v(rand_polar3());
    return ((max_length - min_length) * v) + min_length;
}

} // namespace mth //
} // namespace gea //
