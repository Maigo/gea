
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm_one(const vector3 &v) { return fabs(v.x) + fabs(v.y) + fabs(v.z); }
inline const float norm_two(const vector3 &v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
inline const float norm_inf(const vector3 &v) { return mth::max(fabs(v.x), fabs(v.y), fabs(v.z)); }

// error fucntions
inline const float error_absolute(const vector3 &v, const vector3 &vh) {
    return norm_two(v - vh);
}
inline const float error_relative(const vector3 &v, const vector3 &vh) {
    assert(!v.is_zero() && "divide by zero!");
    return error_absolute(v, vh) / norm_two(v);
}

} // namespace mth //
} // namespace gea //
