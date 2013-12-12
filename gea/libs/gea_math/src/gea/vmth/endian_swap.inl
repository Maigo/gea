
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<matrix3>(matrix3 &m) {
    endian_swap(m.m[0][0]); endian_swap(m.m[0][1]); endian_swap(m.m[0][2]);
    endian_swap(m.m[1][0]); endian_swap(m.m[1][1]); endian_swap(m.m[1][2]);
    endian_swap(m.m[2][0]); endian_swap(m.m[2][1]); endian_swap(m.m[2][2]);
}

// ------------------------------------------------------------------------- //
// polar3                                                                     //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<polar3>(polar3 &p) {
    endian_swap(p.r); endian_swap(p.theta); endian_swap(p.phi);
}

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<quaternion>(quaternion &q) {
    endian_swap(q.x); endian_swap(q.y); endian_swap(q.z); endian_swap(q.w);
}

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
template <> inline void endian_swap<vector3>(vector3 &v) {
    endian_swap(v.x); endian_swap(v.y); endian_swap(v.z);
}

} // namespace mth //
} // namespace gea //
