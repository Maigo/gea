// std includes
#include <string.h>

// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix4                                                                   //
// ------------------------------------------------------------------------- //
// constructors
inline matrix4::matrix4() {
    m[0][0] = m[0][1] = m[0][2] = m[0][3] = 0.0f;
    m[1][0] = m[1][1] = m[1][2] = m[1][3] = 0.0f;
    m[2][0] = m[2][1] = m[2][2] = m[2][3] = 0.0f;
}
inline matrix4::matrix4(const float xx, const float yy, const float zz, const float ww) {
    m[0][0] = xx; m[1][1] = yy; m[2][2] = zz; m[3][3] = ww;
    m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
}
inline matrix4::matrix4(const float xx, const float yx, const float zx, const float wx,
                        const float xy, const float yy, const float zy, const float wy,
                        const float xz, const float yz, const float zz, const float wz,
                        const float xw, const float yw, const float zw, const float ww) {
    m[0][0] = xx; m[0][1] = yx; m[0][2] = zx; m[0][3] = wx;
    m[1][0] = xy; m[1][1] = yy; m[1][2] = zy; m[1][3] = wy;
    m[2][0] = xz; m[2][1] = yz; m[2][2] = zz; m[2][3] = wz;
    m[3][0] = xw; m[3][1] = yw; m[3][2] = zw; m[3][3] = ww;
}
inline matrix4::matrix4(skip_initialization) {}
inline matrix4::matrix4(identity_initialization) {
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
}
inline matrix4::matrix4(zero_initialization) {
    m[0][0] = m[0][1] = m[0][2] = m[0][3] = 0.0f;
    m[1][0] = m[1][1] = m[1][2] = m[1][3] = 0.0f;
    m[2][0] = m[2][1] = m[2][2] = m[2][3] = 0.0f;
    m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0.0f;
}
inline matrix4::matrix4(const matrix4 &o) {
    memcpy(&m, &o.m, sizeof(m));
}

// arithmetic
inline matrix4 &matrix4::operator =(const matrix4 &o) {
    memcpy(&m, &o.m, sizeof(m));
    return (*this);
}
inline const matrix4 matrix4::operator- (const matrix4 &o) const {
    return matrix4(m[0][0] - o.m[0][0], m[0][1] - o.m[0][1], m[0][2] - o.m[0][2], m[0][3] - o.m[0][3],
                   m[1][0] - o.m[1][0], m[1][1] - o.m[1][1], m[1][2] - o.m[1][2], m[1][3] - o.m[1][3],
                   m[2][0] - o.m[2][0], m[2][1] - o.m[2][1], m[2][2] - o.m[2][2], m[2][3] - o.m[2][3],
                   m[3][0] - o.m[3][0], m[3][1] - o.m[3][1], m[3][2] - o.m[3][2], m[3][3] - o.m[3][3]);
}
inline const matrix4 matrix4::operator+ (const matrix4 &o) const {
    return matrix4(m[0][0] + o.m[0][0], m[0][1] + o.m[0][1], m[0][2] + o.m[0][2], m[0][3] + o.m[0][3],
                   m[1][0] + o.m[1][0], m[1][1] + o.m[1][1], m[1][2] + o.m[1][2], m[1][3] + o.m[1][3],
                   m[2][0] + o.m[2][0], m[2][1] + o.m[2][1], m[2][2] + o.m[2][2], m[2][3] + o.m[2][3],
                   m[3][0] + o.m[3][0], m[3][1] + o.m[3][1], m[3][2] + o.m[3][2], m[3][3] + o.m[3][3]);
}
inline const matrix4 matrix4::operator* (const matrix4 &o) const {
    return matrix4(m[0][0] * o.m[0][0] + m[0][1] * o.m[1][0] + m[0][2] * o.m[2][0] + m[0][3] * o.m[3][0], m[0][0] * o.m[0][1] + m[0][1] * o.m[1][1] + m[0][2] * o.m[2][1] + m[0][3] * o.m[3][1], m[0][0] * o.m[0][2] + m[0][1] * o.m[1][2] + m[0][2] * o.m[2][2] + m[0][3] * o.m[3][2], m[0][0] * o.m[0][3] + m[0][1] * o.m[1][3] + m[0][2] * o.m[2][3] + m[0][3] * o.m[3][3],
                   m[1][0] * o.m[0][0] + m[1][1] * o.m[1][0] + m[1][2] * o.m[2][0] + m[1][3] * o.m[3][0], m[1][0] * o.m[0][1] + m[1][1] * o.m[1][1] + m[1][2] * o.m[2][1] + m[1][3] * o.m[3][1], m[1][0] * o.m[0][2] + m[1][1] * o.m[1][2] + m[1][2] * o.m[2][2] + m[1][3] * o.m[3][2], m[1][0] * o.m[0][3] + m[1][1] * o.m[1][3] + m[1][2] * o.m[2][3] + m[1][3] * o.m[3][3],
                   m[2][0] * o.m[0][0] + m[2][1] * o.m[1][0] + m[2][2] * o.m[2][0] + m[2][3] * o.m[3][0], m[2][0] * o.m[0][1] + m[2][1] * o.m[1][1] + m[2][2] * o.m[2][1] + m[2][3] * o.m[3][1], m[2][0] * o.m[0][2] + m[2][1] * o.m[1][2] + m[2][2] * o.m[2][2] + m[2][3] * o.m[3][2], m[2][0] * o.m[0][3] + m[2][1] * o.m[1][3] + m[2][2] * o.m[2][3] + m[2][3] * o.m[3][3],
                   m[3][0] * o.m[0][0] + m[3][1] * o.m[1][0] + m[3][2] * o.m[2][0] + m[3][3] * o.m[3][0], m[3][0] * o.m[0][1] + m[3][1] * o.m[1][1] + m[3][2] * o.m[2][1] + m[3][3] * o.m[3][1], m[3][0] * o.m[0][2] + m[3][1] * o.m[1][2] + m[3][2] * o.m[2][2] + m[3][3] * o.m[3][2], m[3][0] * o.m[0][3] + m[3][1] * o.m[1][3] + m[3][2] * o.m[2][3] + m[3][3] * o.m[3][3]);
}
inline const matrix4 matrix4::operator* (const float s) const {
    return matrix4(m[0][0] * s, m[0][1] * s, m[0][2] * s, m[0][3] * s,
                   m[1][0] * s, m[1][1] * s, m[1][2] * s, m[1][3] * s,
                   m[2][0] * s, m[2][1] * s, m[2][2] * s, m[2][3] * s,
                   m[3][0] * s, m[3][1] * s, m[3][2] * s, m[3][3] * s);
}
inline const matrix4 matrix4::operator/ (const float s) const {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    return matrix4(m[0][0] * s_inv, m[0][1] * s_inv, m[0][2] * s_inv, m[0][3] * s_inv,
                   m[1][0] * s_inv, m[1][1] * s_inv, m[1][2] * s_inv, m[1][3] * s_inv,
                   m[2][0] * s_inv, m[2][1] * s_inv, m[2][2] * s_inv, m[2][3] * s_inv,
                   m[3][0] * s_inv, m[3][1] * s_inv, m[3][2] * s_inv, m[3][3] * s_inv);
}
inline const vector4 matrix4::operator* (const vector4 &v) const {
    return vector4(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
                   m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
                   m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
                   m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
}
// unary arithmetic
inline const matrix4 matrix4::operator+ () const { return (*this); }
inline const matrix4 matrix4::operator- () const {
    return matrix4(-m[0][0], -m[0][1], -m[0][2], -m[0][3],
                   -m[1][0], -m[1][1], -m[1][2], -m[1][3],
                   -m[2][0], -m[2][1], -m[2][2], -m[2][3],
                   -m[3][0], -m[3][1], -m[3][2], -m[3][3]);
}

// member access
inline const float matrix4::operator() (const int32_t i, const int32_t j) const {
    l_assert_msg(mth::range(i, 0, 3) && mth::range(j, 0, 3), "index out of bounds!");
    return m[i][j];
}
inline const vector4 matrix4::get_row(const int32_t row) const {
    l_assert_msg(mth::range(row, 0, 3), "index out of bounds!");
    return vector4(m[row][0], m[row][1], m[row][2], m[row][3]);
}
inline const vector4 matrix4::get_column(const int32_t col) const {
    l_assert_msg(mth::range(col, 0, 3), "index out of bounds!");
    return vector4(m[0][col], m[1][col], m[2][col], m[3][col]);
}

// linear algebra
inline const matrix4 matrix4::transpose() const {
    return matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
                   m[0][1], m[1][1], m[2][1], m[3][1],
                   m[0][2], m[1][2], m[2][2], m[3][2],
                   m[0][3], m[1][3], m[2][3], m[3][3]);
}
inline const float matrix4::trace() const {
    return m[0][0] + m[1][1] + m[2][2] + m[3][3];
}
inline const float matrix4::determinant() const {
    return m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] -
           m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
           m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] -
           m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
           m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] -
           m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
           m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
           m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
           m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] -
           m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
           m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
           m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
           m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] -
           m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
           m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] -
           m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
           m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] -
           m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
           m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
           m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
           m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] -
           m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
           m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
           m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
}


// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix4 operator* (const float s, const matrix4 &m) {
    return (m * s);
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const matrix4 &m1, const matrix4 &m2, const float e) {
    return approx_eq(m1(0, 0), m2(0, 0), e) && approx_eq(m1(0, 1), m2(0, 1), e) && approx_eq(m1(0, 2), m2(0, 2), e) && approx_eq(m1(0, 3), m2(0, 3), e) &&
           approx_eq(m1(1, 0), m2(1, 0), e) && approx_eq(m1(1, 1), m2(1, 1), e) && approx_eq(m1(1, 2), m2(1, 2), e) && approx_eq(m1(1, 3), m2(1, 3), e) &&
           approx_eq(m1(2, 0), m2(2, 0), e) && approx_eq(m1(2, 1), m2(2, 1), e) && approx_eq(m1(2, 2), m2(2, 2), e) && approx_eq(m1(2, 3), m2(2, 3), e) &&
           approx_eq(m1(3, 0), m2(3, 0), e) && approx_eq(m1(3, 1), m2(3, 1), e) && approx_eq(m1(3, 2), m2(3, 2), e) && approx_eq(m1(3, 3), m2(3, 3), e);
}
inline const bool approx_ne(const matrix4 &m1, const matrix4 &m2, const float e) {
    return approx_ne(m1(0, 0), m2(0, 0), e) || approx_ne(m1(0, 1), m2(0, 1), e) || approx_ne(m1(0, 2), m2(0, 2), e) || approx_ne(m1(0, 3), m2(0, 3), e) ||
           approx_ne(m1(1, 0), m2(1, 0), e) || approx_ne(m1(1, 1), m2(1, 1), e) || approx_ne(m1(1, 2), m2(1, 2), e) || approx_ne(m1(1, 3), m2(1, 3), e) ||
           approx_ne(m1(2, 0), m2(2, 0), e) || approx_ne(m1(2, 1), m2(2, 1), e) || approx_ne(m1(2, 2), m2(2, 2), e) || approx_ne(m1(2, 3), m2(2, 3), e) ||
           approx_ne(m1(3, 0), m2(3, 0), e) || approx_ne(m1(3, 1), m2(3, 1), e) || approx_ne(m1(3, 2), m2(3, 2), e) || approx_ne(m1(3, 3), m2(3, 3), e);
}
// nice matrix4
inline const bool nice(const matrix4 &m) {
    return nice(m(0, 0)) && nice(m(0, 1)) && nice(m(0, 2)) && nice(m(0, 3)) &&
           nice(m(1, 0)) && nice(m(1, 1)) && nice(m(1, 2)) && nice(m(1, 3)) &&
           nice(m(2, 0)) && nice(m(2, 1)) && nice(m(2, 2)) && nice(m(2, 3)) &&
           nice(m(3, 0)) && nice(m(3, 1)) && nice(m(3, 2)) && nice(m(3, 3));
}

// finite matrix4
inline const bool finite(const matrix4 &m) {
    return finite(m(0, 0)) && finite(m(0, 1)) && finite(m(0, 2)) && finite(m(0, 3)) &&
           finite(m(1, 0)) && finite(m(1, 1)) && finite(m(1, 2)) && finite(m(1, 3)) &&
           finite(m(2, 0)) && finite(m(2, 1)) && finite(m(2, 2)) && finite(m(2, 3)) &&
           finite(m(3, 0)) && finite(m(3, 1)) && finite(m(3, 2)) && finite(m(3, 3));
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const matrix4 &m) {
    return os << "m:[" <<
        "[" << m.m[0][0] << "," << m.m[0][1] << "," << m.m[0][2] << "," << m.m[0][3] << "]" <<
        "[" << m.m[1][0] << "," << m.m[1][1] << "," << m.m[1][2] << "," << m.m[1][3] << "]" <<
        "[" << m.m[2][0] << "," << m.m[2][1] << "," << m.m[2][2] << "," << m.m[2][3] << "]" <<
        "[" << m.m[3][0] << "," << m.m[3][1] << "," << m.m[3][2] << "," << m.m[3][3] << "]" <<
        "]";
}
#endif

} // namespace mth //
} // namespace gea //
