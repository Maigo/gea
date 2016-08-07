
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// polar3                                                                    //
// ------------------------------------------------------------------------- //
inline const polar3 rand_polar3() {
    const float r1 = gea::g_random.rfloat(), r2 = gea::g_random.rfloat();
    return polar3(1.0f, 2.0f*PI*r1, PI*r2);
}

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
inline const quaternion rand_quaternion() {
    const vector3 axis = rand_vector3(1.0f);
    const float angle = gea::g_random.rfloat();
    return quaternion(angle, axis);
}

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
inline const vector3 rand_vector3(float max, float min) {
    vector3 v(rand_polar3());
    return ((max-min) * v) + min;
}

} // namespace mth //
} // namespace gea //
