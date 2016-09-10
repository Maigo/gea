
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
// norm functions
inline const float norm_one(const matrix3 &m) {
    return mth::max(m.get_column(0).norm_one(), m.get_column(1).norm_one(), m.get_column(2).norm_one());
}
inline const float norm_two(const matrix3 &m) {
    return 1.0f;
}
inline const float norm_inf(const matrix3 &m) {
    return mth::max(m.get_row(0).norm_one(), m.get_row(1).norm_one(), m.get_row(2).norm_one());
}

inline const float norm_1(const matrix3 &m) {
    return mth::max(fabs(m.m[0][0]) + fabs(m.m[1][0]) + fabs(m.m[2][0]),
                    fabs(m.m[0][1]) + fabs(m.m[1][1]) + fabs(m.m[2][1]),
                    fabs(m.m[0][2]) + fabs(m.m[1][2]) + fabs(m.m[2][2]));
}
inline const float norm_inf(const matrix3 &m) {
    return mth::max(fabs(m.m[0][0]) + fabs(m.m[0][1]) + fabs(m.m[0][2]),
                    fabs(m.m[1][0]) + fabs(m.m[1][1]) + fabs(m.m[1][2]),
                    fabs(m.m[2][0]) + fabs(m.m[2][1]) + fabs(m.m[2][2]));
}

// error fucntions

} // namespace mth //
} // namespace gea //
