// gea includes
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //
// constructors
inline point3::point3() : x(0.0f), y(0.0f), z(0.0f) {}
inline point3::point3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
inline point3::point3(skip_initialization) {}
inline point3::point3(zero_initialization) : x(0.0f), y(0.0f), z(0.0f) {}
inline point3::point3(const point3 &o) : x(o.x), y(o.y), z(o.z) {}

// arithmetic
inline point3 &point3::operator= (const point3 &o) {
    x = o.x; y = o.y; z = o.z; return (*this);
}
inline const point3 point3::operator+ (const vector3 &v) const {
    return point3(x + v.x, y + v.y, z + v.z);
}
inline const point3 point3::operator- (const vector3 &v) const {
    return point3(x - v.x, y - v.y, z - v.z);
}

// compound assignment
inline point3 &point3::operator+= (const vector3 &v) {
    x += v.x; y += v.y; z += v.z; return (*this);
}
inline point3 &point3::operator-= (const vector3 &v) {
    x -= v.x; y -= v.y; z -= v.z; return (*this);
}

// comparative
inline bool point3::operator== (const point3 &o) const {
    return (x == o.x && y == o.y && z == o.z);
}
inline bool point3::operator!= (const point3 &o) const {
    return (x != o.x || y != o.y || z != o.z);
}
inline bool point3::operator<  (const point3 &o) const {
    return (x != o.x) ? (x < o.x) : ((y != o.y) ? (y < o.y) : (z < o.z));
}
inline bool point3::operator<= (const point3 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline bool point3::operator>  (const point3 &o) const {
    return (x != o.x) ? (x > o.x) : ((y != o.y) ? (y > o.y) : (z>o.z));
}
inline bool point3::operator>= (const point3 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// member access
inline float &point3::operator[] (int32_t i) {
    l_assert_msg(mth::range(i, 0, 2), "index out of bounds!");
    return (&x)[i];
}
inline const float &point3::operator[] (int32_t i) const {
    l_assert_msg(mth::range(i, 0, 2), "index out of bounds!");
    return (&x)[i];
}

// linear algebra
inline const vector3 point3::to(const point3 &o) const {
    return vector3(o.x - x, o.y - y, o.z - z);
}

// attributes
inline const bool point3::is_zero() const { return (*this) == point3::ORIGIN; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const point3 &p0, const point3 &p1, const float e) {
    return approx_eq(p0.x, p1.x, e) &&
           approx_eq(p0.y, p1.y, e) &&
           approx_eq(p0.z, p1.z, e);
}
inline const bool approx_ne(const point3 &p0, const point3 &p1, const float e) {
    return approx_ne(p0.x, p1.x, e) ||
           approx_ne(p0.y, p1.y, e) ||
           approx_ne(p0.z, p1.z, e);
}
// attributes
inline const bool nice(const point3 &p) {
    return nice(p.x) && nice(p.y) && nice(p.z);
}
inline const bool finite(const point3 &p) {
    return finite(p.x) && finite(p.y) && finite(p.z);
}
// round
inline const point3 round(const point3 &p) {
    return point3(roundf(p.x), roundf(p.y), roundf(p.z));
}
inline const point3 ceil(const point3 &p) {
    return point3(ceilf(p.x), ceilf(p.y), ceilf(p.z));
}
inline const point3 floor(const point3 &p) {
    return point3(floorf(p.x), floorf(p.y), floorf(p.z));
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const point3 &p) {
    return os << "p:[" << p.x << "," << p.y << "," << p.z << "]";
}
#endif

} // namespace mth //
} // namespace gea //
