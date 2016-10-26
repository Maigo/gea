
// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
// constructors
inline quaternion::quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
inline quaternion::quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
inline quaternion::quaternion(const float angle, const vector3 &axis) { from_axis(angle, axis); }
inline quaternion::quaternion(skip_initialization) {}
inline quaternion::quaternion(identity_initialization) : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
inline quaternion::quaternion(zero_initialization) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
inline quaternion::quaternion(const quaternion &o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
inline quaternion::quaternion(const matrix3 &m) { from_matrix(m); }
inline quaternion::quaternion(const float heading, const float attitude, const float bank) { from_euler(heading, attitude, bank); }

// arithmetic
inline quaternion &quaternion::operator =(const quaternion &o) {
    x = o.x; y = o.y; z = o.z; w = o.w; return (*this);
}
inline const quaternion quaternion::operator+ (const quaternion &o) const {
    return quaternion(x + o.x, y + o.y, z + o.z, w + o.w);
}
inline const quaternion quaternion::operator- (const quaternion &o) const {
    return quaternion(x - o.x, y - o.y, z - o.z, w - o.w);
}
inline const quaternion quaternion::operator* (const quaternion &o) const {
    return quaternion(w * o.x + x * o.w + y * o.z - z * o.y,
                      w * o.y - x * o.z + y * o.w + z * o.x,
                      w * o.z + x * o.y - y * o.x + z * o.w,
                      w * o.w - x * o.w - y * o.y - z * o.z);
}
inline const quaternion quaternion::operator* (const float s) const {
    return quaternion(x * s, y * s, z * s, w * s);
}
inline const quaternion quaternion::operator/ (const float s) const {
    l_assert_msg(s != 0.0f, "divide by zero!");
    const float s_inv = 1.0f / s;
    return quaternion(x * s_inv, y * s_inv, z * s_inv, w * s_inv);
}
// unary arithmetic
inline const quaternion quaternion::operator+ () const { return (*this); }
inline const quaternion quaternion::operator- () const {
    return quaternion(-x, -y, -z, -w);
}

// comparative
inline const bool quaternion::operator== (const quaternion &o) const {
    return (x == o.x && y == o.y && z == o.z && w == o.w);
}
inline const bool quaternion::operator!= (const quaternion &o) const {
    return (x != o.x || y != o.y || z != o.z || w != o.w);
}

// member access
inline float &quaternion::operator[] (const int32_t i) {
    l_assert_msg(mth::range(i, 0, 3), "index out of bounds!");
    return (&x)[i];
}
inline const float &quaternion::operator[] (const int32_t i) const {
    l_assert_msg(mth::range(i, 0, 3), "index out of bounds!");
    return (&x)[i];
}

// linear algebra
inline const float quaternion::length()    const { return sqrtf(x * x + y * y + z * z + w * w); }
inline const float quaternion::length_sq() const { return      (x * x + y * y + z * z + w * w); }
inline void quaternion::normalize() {
    const float len_sq = length_sq();
	if (len_sq != 0.0) {
        const float scale = (1.0f / sqrtf(len_sq));
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
    }
}

inline const float quaternion::dot_product(const quaternion &o) const {
    return x * o.x + y * o.y + z * o.z + w * o.w;
}

inline const quaternion quaternion::conjugate() const {
    return quaternion(-x, -y, -z, w);
}
inline const quaternion quaternion::inverse() const {
    return conjugate() / length_sq();
}

// attributes
inline const bool quaternion::is_zero() const { return (*this) == quaternion::ZERO; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
inline const quaternion operator* (const float s, const quaternion &q) {
    return (q * s);
}

// linear algebra - convenience functions
inline const float dot_product(const quaternion &q1, const quaternion &q2) {
    return q1.dot_product(q2);
}

// interpolation
inline const quaternion lerp(const quaternion &from, const quaternion &to, const float t) {
    l_assert_msg(mth::range(t, 0.0f, 1.0f), "out of range!");
    if (from.dot_product(to) < 0.0f) {
        return from + (((-to) - from) * t);
    } else {
        return from + (((to) - from) * t);
    }
}
inline const quaternion nlerp(const quaternion &from, const quaternion &to, const float t) {
    quaternion q = lerp(from, to, t);
    q.normalize();
    return q;
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const quaternion &q1, const quaternion &q2, const float e) {
    if (q1.dot_product(q2) > 0) {
        return approx_eq(q1.x, q2.x, e) && approx_eq(q1.y, q2.y, e) &&
               approx_eq(q1.z, q2.z, e) && approx_eq(q1.w, q2.w, e);
    } else {
        return approx_eq(q1.x, -q2.x, e) && approx_eq(q1.y, -q2.y, e) &&
               approx_eq(q1.z, -q2.z, e) && approx_eq(q1.w, -q2.w, e);
    }
}
inline const bool approx_ne(const quaternion &q1, const quaternion &q2, const float e) {
    if (q1.dot_product(q2) > 0) {
        return approx_ne(q1.x, q2.x, e) || approx_ne(q1.y, q2.y, e) ||
               approx_ne(q1.z, q2.z, e) || approx_ne(q1.w, q2.w, e);
    } else {
        return approx_ne(q1.x, -q2.x, e) || approx_ne(q1.y, -q2.y, e) ||
               approx_ne(q1.z, -q2.z, e) || approx_ne(q1.w, -q2.w, e);
    }
}
// nice quaternion
inline const bool nice(const quaternion &q) {
    return nice(q.x) && nice(q.y) && nice(q.z) && nice(q.w);
}
// finite quaternion
inline const bool finite(const quaternion &q) {
    return finite(q.x) && finite(q.y) && finite(q.z) && finite(q.w);
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const quaternion &q) {
    return os << "q:[" << q.x << "," << q.y << "," << q.z << "," << q.w << "]";
}
#endif

} // namespace mth //
} // namespace gea //
