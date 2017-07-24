// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector4                                                                   //
// ------------------------------------------------------------------------- //
// constructors
inline vector4::vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
inline vector4::vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
inline vector4::vector4(skip_initialization) {}
inline vector4::vector4(zero_initialization) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
inline vector4::vector4(const vector4 &o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
//inline vector4::vector4(const polar3 &p) { from_polar(p); }

// arithmetic
inline vector4 &vector4::operator= (const vector4 &o) {
    x = o.x; y = o.y; z = o.z; w = o.w;  return (*this);
}
inline const vector4 vector4::operator+ (const vector4 &o) const {
    return vector4(x + o.x, y + o.y, z + o.z, w + o.w);
}
inline const vector4 vector4::operator- (const vector4 &o) const {
    return vector4(x - o.x, y - o.y, z - o.z, w - o.w);
}
inline const vector4 vector4::operator* (const vector4 &o) const {
    return vector4(x * o.x, y * o.y, z * o.z, w * o.w);
}
inline const vector4 vector4::operator/ (const vector4 &o) const {
    l_assert_msg((o.x != 0.0f) && (o.y != 0.0f) && (o.z != 0.0f) && (o.w != 0.0f), "divide by zero!");
    return vector4(x / o.x, y / o.y, z / o.z, w / o.w);
}
inline const vector4 vector4::operator+ (const float s) const {
    return vector4(x + s, y + s, z + s, w + s);
}
inline const vector4 vector4::operator- (const float s) const {
    return vector4(x - s, y - s, z - s, w - s);
}
inline const vector4 vector4::operator* (const float s) const {
    return vector4(x * s, y * s, z * s, w * s);
}
inline const vector4 vector4::operator/ (const float s) const {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    return vector4(x * s_inv, y * s_inv, z * s_inv, w * s_inv);
}
// unary arithmetic
inline const vector4 vector4::operator+ () const { return (*this); }
inline const vector4 vector4::operator- () const {
    return vector4(-x, -y, -z, -w);
}

// compound assignment
inline vector4 &vector4::operator+= (const vector4 &o) {
    x += o.x; y += o.y; z += o.z; w += o.w; return (*this);
}
inline vector4 &vector4::operator-= (const vector4 &o) {
    x -= o.x; y -= o.y; z -= o.z; w -= o.w; return (*this);
}
inline vector4 &vector4::operator+= (const float s) {
    x += s; y += s; z += s; w += s;  return (*this);
}
inline vector4 &vector4::operator-= (const float s) {
    x -= s; y -= s; z -= s; w -= s; return (*this);
}
inline vector4 &vector4::operator*= (const float s) {
    x *= s; y *= s; z *= s; w *= s;  return (*this);
}
inline vector4 &vector4::operator/= (const float s) {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    x *= s_inv; y *= s_inv; z *= s_inv; w *= s_inv; return (*this);
}

// comparative
inline const bool vector4::operator== (const vector4 &o) const {
    return (x == o.x && y == o.y && z == o.z && w == o.w);
}
inline const bool vector4::operator!= (const vector4 &o) const {
    return (x != o.x || y != o.y || z != o.z || w != o.w);
}
inline const bool vector4::operator<  (const vector4 &o) const {
    return (x != o.x) ? (x < o.x) : ((y != o.y) ? (y < o.y) : ((z != o.z) ? (z < o.z) : (w < o.w)));
}
inline const bool vector4::operator<= (const vector4 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline const bool vector4::operator>  (const vector4 &o) const {
    return (x != o.x) ? (x > o.x) : ((y != o.y) ? (y > o.y) : ((z != o.z) ? (z > o.z) : (w > o.w)));
}
inline const bool vector4::operator>= (const vector4 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// member access
inline float &vector4::operator[] (const int32_t i) {
    l_assert_msg(mth::range(i, 0, 3), "index out of bounds!");
    return (&x)[i];
}
inline const float &vector4::operator[] (const int32_t i) const {
    l_assert_msg(mth::range(i, 0, 3), "index out of bounds!");
    return (&x)[i];
}

// linear algebra
inline const float vector4::length()    const { return sqrtf(x * x + y * y + z * z + w * w); }
inline const float vector4::length_sq() const { return      (x * x + y * y + z * z + w * w); }
inline void vector4::normalize() {
    const float len_sq = length_sq();
    if (len_sq != 0.0) {
        const float scale = (1.0f / sqrtf(len_sq));
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
    }
}

// attributes
inline const bool vector4::is_zero() const { return (*this) == vector4::ZERO; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const vector4 operator* (const float s, const vector4 &v) {
    return (v * s);
}

// interpolation
inline const vector4 lerp(const vector4 &from, const vector4 &to, const float t) {
    l_assert_msg(mth::range(t, 0.0f, 1.0f), "out of range!");
    return from + (to - from) * t;
}
inline const vector4 nlerp(const vector4 &from, const vector4 &to, const float t) {
    vector4 v = lerp(from, to, t);
    v.normalize();
    return v;
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const vector4 &v0, const vector4 &v1, const float e) {
    return approx_eq(v0.x, v1.x, e) &&
           approx_eq(v0.y, v1.y, e) &&
           approx_eq(v0.z, v1.z, e) &&
           approx_eq(v0.w, v1.w, e);
}
inline const bool approx_ne(const vector4 &v0, const vector4 &v1, const float e) {
    return approx_ne(v0.x, v1.x, e) ||
           approx_ne(v0.y, v1.y, e) ||
           approx_ne(v0.z, v1.z, e) ||
           approx_ne(v0.w, v1.w, e);
}

// attributes
inline const bool nice(const vector4 &v) {
    return nice(v.x) && nice(v.y) && nice(v.z) && nice(v.w);
}
inline const bool finite(const vector4 &v) {
    return finite(v.x) && finite(v.y) && finite(v.z) && finite(v.w);
}

// round
inline const vector4 round(const vector4 &v) {
    return vector4(roundf(v.x), roundf(v.y), roundf(v.z), round(v.w));
}
inline const vector4 ceil(const vector4 &v) {
    return vector4(ceilf(v.x), ceilf(v.y), ceilf(v.z), ceilf(v.w));
}
inline const vector4 floor(const vector4 &v) {
    return vector4(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w));
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const vector4 &v) {
    return os << "v:[" << v.x << "," << v.y << "," << v.z << "," << v.w << "]";
}
#endif

} // namespace mth //
} // namespace gea //
