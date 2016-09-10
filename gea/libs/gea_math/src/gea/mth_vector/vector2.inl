
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector2                                                                   //
// ------------------------------------------------------------------------- //
// constructors
inline vector2::vector2() : x(0.0f), y(0.0f) {}
inline vector2::vector2(const float x, const float y) : x(x), y(y) {}
inline vector2::vector2(skip_initialization) {}
inline vector2::vector2(const vector2 &o) : x(o.x), y(o.y) {}
inline vector2::vector2(const polar2 &p) { from_polar(p); }

// arithmetic
inline vector2 &vector2::operator= (const vector2 &o) {
    x = o.x; y = o.y; return (*this);
}
inline const vector2 vector2::operator+ (const vector2 &o) const {
    return vector2(x + o.x, y + o.y);
}
inline const vector2 vector2::operator- (const vector2 &o) const {
    return vector2(x - o.x, y - o.y);
}
inline const vector2 vector2::operator* (const vector2 &o) const {
    return vector2(x * o.x, y * o.y);
}
inline const vector2 vector2::operator/ (const vector2 &o) const {
    assert((o.x != 0.0f) && (o.y != 0.0f) && "divide by zero!");
    return vector2(x / o.x, y / o.y);
}
inline const vector2 vector2::operator+ (const float s) const {
    return vector2(x + s, y + s);
}
inline const vector2 vector2::operator- (const float s) const {
    return vector2(x - s, y - s);
}
inline const vector2 vector2::operator* (const float s) const {
    return vector2(x * s, y * s);
}
inline const vector2 vector2::operator/ (const float s) const {
    assert((s != 0.0f) && "divide by zero!");
    const float s_inv = 1.0f / s;
    return vector2(x * s_inv, y * s_inv);
}
// unary arithmetic
inline const vector2 vector2::operator+ () const { return (*this); }
inline const vector2 vector2::operator- () const {
    return vector2(-x, -y);
}

// compound assignment
inline vector2 &vector2::operator+= (const vector2 &o) {
    x += o.x; y += o.y; return (*this);
}
inline vector2 &vector2::operator-= (const vector2 &o) {
    x -= o.x; y -= o.y; return (*this);
}
inline vector2 &vector2::operator+= (const float s) {
    x += s; y += s; return (*this);
}
inline vector2 &vector2::operator-= (const float s) {
    x -= s; y -= s; return (*this);
}
inline vector2 &vector2::operator*= (const float s) {
    x *= s; y *= s; return (*this);
}
inline vector2 &vector2::operator/= (const float s) {
    assert((s != 0.0f) && "divide by zero!");
    float s_inv = 1.0f / s;
    x *= s_inv; y *= s_inv; return (*this);
}

// comparative
inline const bool vector2::operator== (const vector2 &o) const {
    return (x == o.x && y == o.y);
}
inline const bool vector2::operator!= (const vector2 &o) const {
    return (x != o.x || y != o.y);
}
inline const bool vector2::operator<  (const vector2 &o) const {
    return (x != o.x) ? (x < o.x) : (y < o.y);
}
inline const bool vector2::operator<= (const vector2 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline const bool vector2::operator>  (const vector2 &o) const {
    return (x != o.x) ? (x > o.x) : (y>o.y);
}
inline const bool vector2::operator>= (const vector2 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// member access
inline float &vector2::operator[] (const int32_t i) {
    assert(mth::range(i, 0, 1) && "index out of bounds!");
    return (&x)[i];
}
inline const float &vector2::operator[] (const int32_t i) const {
    assert(mth::range(i, 0, 1) && "index out of bounds!");
    return (&x)[i];
}

// linear algebra
inline const float vector2::length()    const { return sqrtf(x * x + y * y); }
inline const float vector2::length_sq() const { return      (x * x + y * y); }
inline void vector2::normalize() {
    const float len_sq = length_sq();
    if (len_sq != 0.0) {
        const float scale = (1.0f / sqrtf(len_sq));
        x *= scale;
        y *= scale;
    }
}

inline const float vector2::dot_product(const vector2 &o) const {
    return (x * o.x + y * o.y);
}

inline const float vector2::angle(const vector2 &o) const {
    // theta = arccos( a dot b / |a||b| )
    const float len = length() * o.length();
    return (len != 0.0f) ? acos(dot_product(o) / len) : 0.0f;
}

// attributes
inline const bool vector2::is_zero() const { return (*this) == vector2::ZERO; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const vector2 operator* (const float s, const vector2 &v) {
    return (v * s);
}

// linear algebra - convenience functions
inline const float dot_product(const vector2 &v0, const vector2 &v1) {
    return v0.dot_product(v1);
}
inline const float angle(const vector2 &v0, const vector2 &v1) {
    return v0.angle(v1);
}

// interpolation
inline const vector2 lerp(const vector2 &from, const vector2 &to, const float t) {
    assert(mth::range(t, 0.0f, 1.0f) && "out of range!");
    return from + (to - from) * t;
}
inline const vector2 nlerp(const vector2 &from, const vector2 &to, const float t) {
    vector2 v = lerp(from, to, t);
    v.normalize();
    return v;
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const vector2 &v0, const vector2 &v1, const float e) {
    return approx_eq(v0.x, v1.x, e) &&
           approx_eq(v0.y, v1.y, e);
}
inline const bool approx_ne(const vector2 &v0, const vector2 &v1, const float e) {
    return approx_ne(v0.x, v1.x, e) ||
           approx_ne(v0.y, v1.y, e);
}
// nice vector2
inline const bool nice(const vector2 &v) {
    return nice(v.x) && nice(v.y);
}
// finite vector2
inline const bool finite(const vector2 &v) {
    return finite(v.x) && finite(v.y);
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const vector2 &v) {
    return os << "v:[" << v.x << "," << v.y << "]";
}
#endif

} // namespace mth //
} // namespace gea //
