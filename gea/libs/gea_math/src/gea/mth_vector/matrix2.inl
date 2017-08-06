// std includes
#include <string.h>

// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //
// constructors
inline matrix2::matrix2() {
    m[0][0] = m[0][1] = 0.0f;
    m[1][0] = m[1][1] = 0.0f;
}
inline matrix2::matrix2(const float xx, const float yy) {
    m[0][0] = xx; m[1][1] = yy;
    m[0][1] = m[1][0] = 0.0f;
}
inline matrix2::matrix2(const float xx, const float yx,
                        const float xy, const float yy) {
    m[0][0] = xx; m[0][1] = yx;
    m[1][0] = xy; m[1][1] = yy;
}
inline matrix2::matrix2(skip_initialization) {}
inline matrix2::matrix2(identity_initialization) {
    m[0][0] = m[1][1] = 1.0f;
    m[0][1] = m[1][0] = 0.0f;
}
inline matrix2::matrix2(zero_initialization) {
    m[0][0] = m[0][1] = 0.0f;
    m[1][0] = m[1][1] = 0.0f;
}
inline matrix2::matrix2(const matrix2 &o) {
    memcpy(&m, &o.m, sizeof(m));
}

// arithmetic
inline matrix2 &matrix2::operator =(const matrix2 &o) {
    memcpy(&m, &o.m, sizeof(m));
    return (*this);
}
inline const matrix2 matrix2::operator+ (const matrix2 &o) const {
    return matrix2(m[0][0] + o.m[0][0], m[0][1] + o.m[0][1],
                   m[1][0] + o.m[1][0], m[1][1] + o.m[1][1]);
}
inline const matrix2 matrix2::operator- (const matrix2 &o) const {
    return matrix2(m[0][0] - o.m[0][0], m[0][1] - o.m[0][1],
                   m[1][0] - o.m[1][0], m[1][1] - o.m[1][1]);
}
inline const matrix2 matrix2::operator* (const matrix2 &o) const {
    return matrix2(m[0][0] * o.m[0][0] + m[0][1] * o.m[1][0], m[0][0] * o.m[0][1] + m[0][1] * o.m[1][1],
                   m[1][0] * o.m[0][0] + m[1][1] * o.m[1][0], m[1][0] * o.m[0][1] + m[1][1] * o.m[1][1]);
}
inline const matrix2 matrix2::operator* (const float s) const {
    return matrix2(m[0][0] * s, m[0][1] * s,
                   m[1][0] * s, m[1][1] * s);
}
inline const matrix2 matrix2::operator/ (const float s) const {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    return matrix2(m[0][0] * s_inv, m[0][1] * s_inv,
                   m[1][0] * s_inv, m[1][1] * s_inv);
}
inline const vector2 matrix2::operator* (const vector2 &v) const {
    return vector2(m[0][0] * v.x + m[0][1] * v.y,
                   m[1][0] * v.x + m[1][1] * v.y);
}
inline const point2 matrix2::operator* (const point2 &p) const {
    return point2(m[0][0] * p.x + m[0][1] * p.y,
                  m[1][0] * p.x + m[1][1] * p.y);
}

// unary arithmetic
inline const matrix2 matrix2::operator+ () const { return (*this); }
inline const matrix2 matrix2::operator- () const {
    return matrix2(-m[0][0], -m[0][1],
                   -m[1][0], -m[1][1]);
}

// compound assignment
inline matrix2 &matrix2::operator+= (const matrix2 &o) {
    m[0][0] += o.m[0][0]; m[0][1] += o.m[0][1];
    m[1][0] += o.m[1][0]; m[1][1] += o.m[1][1];
    return (*this);
}
inline matrix2 &matrix2::operator-= (const matrix2 &o) {
    m[0][0] -= o.m[0][0]; m[0][1] -= o.m[0][1];
    m[1][0] -= o.m[1][0]; m[1][1] -= o.m[1][1];
    return (*this);
}
inline matrix2 &matrix2::operator*= (const matrix2 &o) {
    m[0][0] = m[0][0] * o.m[0][0] + m[0][1] * o.m[1][0]; m[0][1] = m[0][0] * o.m[0][1] + m[0][1] * o.m[1][1];
    m[1][0] = m[1][0] * o.m[0][0] + m[1][1] * o.m[1][0]; m[1][1] = m[1][0] * o.m[0][1] + m[1][1] * o.m[1][1];
    return (*this);
}
inline matrix2 &matrix2::operator*= (const float s) {
    m[0][0] *= s; m[0][1] *= s;
    m[1][0] *= s; m[1][1] *= s;
    return (*this);
}
inline matrix2 &matrix2::operator/= (const float s) {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    m[0][0] *= s_inv; m[0][1] *= s_inv;
    m[1][0] *= s_inv, m[1][1] *= s_inv;
    return (*this);
}

// member access
inline const float matrix2::operator() (const int32_t i, const int32_t j) const {
    l_assert_msg(mth::range(i, 0, 1) && mth::range(j, 0, 1), "index out of bounds!");
    return m[i][j];
}
inline const vector2 matrix2::get_row(const int32_t row) const {
    l_assert_msg(mth::range(row, 0, 1), "index out of bounds!");
    return vector2(m[row][0], m[row][1]);
}
inline const vector2 matrix2::get_column(const int32_t col) const {
    l_assert_msg(mth::range(col, 0, 1), "index out of bounds!");
    return vector2(m[0][col], m[1][col]);
}

// linear algebra
inline const matrix2 matrix2::transpose() const {
    return matrix2(m[0][0], m[1][0],
                   m[0][1], m[1][1]);
}
inline const float matrix2::trace() const {
    return m[0][0] + m[1][1];
}
inline const float matrix2::determinant() const {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix2 operator* (const float s, const matrix2 &m) {
    return (m * s);
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const matrix2 &m1, const matrix2 &m2, const float e) {
    return approx_eq(m1(0, 0), m2(0, 0), e) && approx_eq(m1(0, 1), m2(0, 1), e) &&
           approx_eq(m1(1, 0), m2(1, 0), e) && approx_eq(m1(1, 1), m2(1, 1), e);
}
inline const bool approx_ne(const matrix2 &m1, const matrix2 &m2, const float e) {
    return approx_ne(m1(0, 0), m2(0, 0), e) || approx_ne(m1(0, 1), m2(0, 1), e) ||
           approx_ne(m1(1, 0), m2(1, 0), e) || approx_ne(m1(1, 1), m2(1, 1), e);
}

// nice matrix2
inline const bool nice(const matrix2 &m) {
    return nice(m(0, 0)) && nice(m(0, 1)) &&
           nice(m(1, 0)) && nice(m(1, 1));
}

// finite matrix2
inline const bool finite(const matrix2 &m) {
    return finite(m(0, 0)) && finite(m(0, 1)) &&
           finite(m(1, 0)) && finite(m(1, 1));
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const matrix2 &m) {
    return os << "m:[" <<
        "[" << m.m[0][0] << "," << m.m[0][1] << "]" <<
        "[" << m.m[1][0] << "," << m.m[1][1] << "]" <<
        "]";
}
#endif

} // namespace mth //
} // namespace gea //
