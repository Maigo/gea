// std includes
#include <string.h>

// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
// constructors
inline matrix3::matrix3() {
    m[0][0] = m[0][1] = m[0][2] = 0.0f;
    m[1][0] = m[1][1] = m[1][2] = 0.0f;
    m[2][0] = m[2][1] = m[2][2] = 0.0f;
}
inline matrix3::matrix3(const float xx, const float yy, const float zz) {
    m[0][0] = xx; m[1][1] = yy; m[2][2] = zz;
    m[0][1] = m[0][2] = m[1][0] = m[1][2] = m[2][0] = m[2][1] = 0.0f;
}
inline matrix3::matrix3(const float xx, const float yx, const float zx,
                        const float xy, const float yy, const float zy,
                        const float xz, const float yz, const float zz) {
    m[0][0] = xx; m[0][1] = yx; m[0][2] = zx;
    m[1][0] = xy; m[1][1] = yy; m[1][2] = zy;
    m[2][0] = xz; m[2][1] = yz; m[2][2] = zz;
}
inline matrix3::matrix3(skip_initialization) {}
inline matrix3::matrix3(identity_initialization) {
    m[0][0] = m[1][1] = m[2][2] = 1.0f;
    m[0][1] = m[0][2] = m[1][0] = m[1][2] = m[2][0] = m[2][1] = 0.0f;
}
inline matrix3::matrix3(zero_initialization) {
    m[0][0] = m[0][1] = m[0][2] = 0.0f;
    m[1][0] = m[1][1] = m[1][2] = 0.0f;
    m[2][0] = m[2][1] = m[2][2] = 0.0f;
}
inline matrix3::matrix3(const matrix3 &o) {
    memcpy(&m, &o.m, sizeof(m));
}
inline matrix3::matrix3(const quaternion &q) { from_quaternion(q); }

// arithmetic
inline matrix3 &matrix3::operator =(const matrix3 &o) {
    memcpy(&m, &o.m, sizeof(m));
    return (*this);
}
inline const matrix3 matrix3::operator- (const matrix3 &o) const {
    return matrix3(m[0][0] - o.m[0][0], m[0][1] - o.m[0][1], m[0][2] - o.m[0][2],
                   m[1][0] - o.m[1][0], m[1][1] - o.m[1][1], m[1][2] - o.m[1][2],
                   m[2][0] - o.m[2][0], m[2][1] - o.m[2][1], m[2][2] - o.m[2][2]);
}
inline const matrix3 matrix3::operator+ (const matrix3 &o) const {
    return matrix3(m[0][0] + o.m[0][0], m[0][1] + o.m[0][1], m[0][2] + o.m[0][2],
                   m[1][0] + o.m[1][0], m[1][1] + o.m[1][1], m[1][2] + o.m[1][2],
                   m[2][0] + o.m[2][0], m[2][1] + o.m[2][1], m[2][2] + o.m[2][2]);
}
inline const matrix3 matrix3::operator* (const matrix3 &o) const {
    return matrix3(m[0][0] * o.m[0][0] + m[0][1] * o.m[1][0] + m[0][2] * o.m[2][0], m[0][0] * o.m[0][1] + m[0][1] * o.m[1][1] + m[0][2] * o.m[2][1], m[0][0] * o.m[0][2] + m[0][1] * o.m[1][2] + m[0][2] * o.m[2][2],
                   m[1][0] * o.m[0][0] + m[1][1] * o.m[1][0] + m[1][2] * o.m[2][0], m[1][0] * o.m[0][1] + m[1][1] * o.m[1][1] + m[1][2] * o.m[2][1], m[1][0] * o.m[0][2] + m[1][1] * o.m[1][2] + m[1][2] * o.m[2][2],
                   m[2][0] * o.m[0][0] + m[2][1] * o.m[1][0] + m[2][2] * o.m[2][0], m[2][0] * o.m[0][1] + m[2][1] * o.m[1][1] + m[2][2] * o.m[2][1], m[2][0] * o.m[0][2] + m[2][1] * o.m[1][2] + m[2][2] * o.m[2][2]);
}
inline const matrix3 matrix3::operator* (const float s) const {
    return matrix3(m[0][0] * s, m[0][1] * s, m[0][2] * s,
                   m[1][0] * s, m[1][1] * s, m[1][2] * s,
                   m[2][0] * s, m[2][1] * s, m[2][2] * s);
}
inline const matrix3 matrix3::operator/ (const float s) const {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    return matrix3(m[0][0] * s_inv, m[0][1] * s_inv, m[0][2] * s_inv,
                   m[1][0] * s_inv, m[1][1] * s_inv, m[1][2] * s_inv,
                   m[2][0] * s_inv, m[2][1] * s_inv, m[2][2] * s_inv);
}
inline const vector3 matrix3::operator* (const vector3 &v) const {
    return vector3(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                   m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                   m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
}
inline const point3 matrix3::operator* (const point3 &p) const {
    return point3(m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z,
        m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z,
        m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z);
}
// unary arithmetic
inline const matrix3 matrix3::operator+ () const { return (*this); }
inline const matrix3 matrix3::operator- () const {
    return matrix3(-m[0][0], -m[0][1], -m[0][2],
                   -m[1][0], -m[1][1], -m[1][2],
                   -m[2][0], -m[2][1], -m[2][2]);
}

// member access
inline const float matrix3::operator() (const int32_t i, const int32_t j) const {
    l_assert_msg(mth::range(i, 0, 2) && mth::range(j, 0, 2), "index out of bounds!");
    return m[i][j];
}
inline const vector3 matrix3::get_row(const int32_t row) const {
    l_assert_msg(mth::range(row, 0, 2), "index out of bounds!");
    return vector3(m[row][0], m[row][1], m[row][2]);
}
inline const vector3 matrix3::get_column(const int32_t col) const {
    l_assert_msg(mth::range(col, 0, 2), "index out of bounds!");
    return vector3(m[0][col], m[1][col], m[2][col]);
}

// linear algebra
inline const matrix3 matrix3::transpose() const {
    return matrix3(m[0][0], m[1][0], m[2][0],
                   m[0][1], m[1][1], m[2][1],
                   m[0][2], m[1][2], m[2][2]);
}
inline const float matrix3::trace() const {
    return m[0][0] + m[1][1] + m[2][2];
}
inline const float matrix3::determinant() const {
    return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] -
           m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];
}


// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix3 operator* (const float s, const matrix3 &m) {
    return (m * s);
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const matrix3 &m1, const matrix3 &m2, const float e) {
    return approx_eq(m1(0, 0), m2(0, 0), e) && approx_eq(m1(0, 1), m2(0, 1), e) && approx_eq(m1(0, 2), m2(0, 2), e) &&
           approx_eq(m1(1, 0), m2(1, 0), e) && approx_eq(m1(1, 1), m2(1, 1), e) && approx_eq(m1(1, 2), m2(1, 2), e) &&
           approx_eq(m1(2, 0), m2(2, 0), e) && approx_eq(m1(2, 1), m2(2, 1), e) && approx_eq(m1(2, 2), m2(2, 2), e);
}
inline const bool approx_ne(const matrix3 &m1, const matrix3 &m2, const float e) {
    return approx_ne(m1(0, 0), m2(0, 0), e) || approx_ne(m1(0, 1), m2(0, 1), e) || approx_ne(m1(0, 2), m2(0, 2), e) ||
           approx_ne(m1(1, 0), m2(1, 0), e) || approx_ne(m1(1, 1), m2(1, 1), e) || approx_ne(m1(1, 2), m2(1, 2), e) ||
           approx_ne(m1(2, 0), m2(2, 0), e) || approx_ne(m1(2, 1), m2(2, 1), e) || approx_ne(m1(2, 2), m2(2, 2), e);
}
// nice matrix3
inline const bool nice(const matrix3 &m) {
    return nice(m(0, 0)) && nice(m(0, 1)) && nice(m(0, 2)) &&
           nice(m(1, 0)) && nice(m(1, 1)) && nice(m(1, 2)) &&
           nice(m(2, 0)) && nice(m(2, 1)) && nice(m(2, 2));
}

// finite matrix3
inline const bool finite(const matrix3 &m) {
    return finite(m(0, 0)) && finite(m(0, 1)) && finite(m(0, 2)) &&
           finite(m(1, 0)) && finite(m(1, 1)) && finite(m(1, 2)) &&
           finite(m(2, 0)) && finite(m(2, 1)) && finite(m(2, 2));
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const matrix3 &m) {
    return os << "m:[" <<
        "[" << m.m[0][0] << "," << m.m[0][1] << "," << m.m[0][2] << "]" <<
        "[" << m.m[1][0] << "," << m.m[1][1] << "," << m.m[1][2] << "]" <<
        "[" << m.m[2][0] << "," << m.m[2][1] << "," << m.m[2][2] << "]" <<
        "]";
}
#endif

} // namespace mth //
} // namespace gea //
