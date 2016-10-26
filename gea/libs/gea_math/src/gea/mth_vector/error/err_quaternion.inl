
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm_one(const quaternion &q) { return fabs(q.x) + fabs(q.y) + fabs(q.z) + fabs(q.w); }
inline const float norm_two(const quaternion &q) { return sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w); }
inline const float norm_inf(const quaternion &q) { return mth::max(fabs(q.x), fabs(q.y), fabs(q.z), fabs(q.w)); }

// error fucntions
inline const float error_absolute(const quaternion &q, const quaternion &qh) {
    return norm_two(q - qh);
}
inline const float error_relative(const quaternion &q, const quaternion &qh) {
    l_assert_msg(!q.is_zero(), "divide by zero!");
    return error_absolute(q,qh) / norm_two(q);
}

} // namespace mth //
} // namespace gea //
