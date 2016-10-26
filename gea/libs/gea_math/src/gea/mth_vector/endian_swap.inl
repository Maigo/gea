namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<matrix3>(matrix3 &out_m) {
    endian_swap(out_m.m[0][0]); endian_swap(out_m.m[0][1]); endian_swap(out_m.m[0][2]);
    endian_swap(out_m.m[1][0]); endian_swap(out_m.m[1][1]); endian_swap(out_m.m[1][2]);
    endian_swap(out_m.m[2][0]); endian_swap(out_m.m[2][1]); endian_swap(out_m.m[2][2]);
}

// ------------------------------------------------------------------------- //
// polar3                                                                     //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<polar3>(polar3 &out_p) {
    endian_swap(out_p.r); endian_swap(out_p.theta); endian_swap(out_p.phi);
}

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<quaternion>(quaternion &out_q) {
    endian_swap(out_q.x); endian_swap(out_q.y); endian_swap(out_q.z); endian_swap(out_q.w);
}

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<vector3>(vector3 &out_v) {
    endian_swap(out_v.x); endian_swap(out_v.y); endian_swap(out_v.z);
}

} // namespace mth //
} // namespace gea //
