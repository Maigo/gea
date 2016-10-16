
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //
// constructors
inline point2::point2() : x(0.0f), y(0.0f) {}
inline point2::point2(const float x, const float y) : x(x), y(y) {}
inline point2::point2(skip_initialization) {}
inline point2::point2(zero_initialization) : x(0.0f), y(0.0f) {}
inline point2::point2(const point2 &o) : x(o.x), y(o.y) {}

// arithmetic
inline point2 &point2::operator= (const point2 &o) {
    x = o.x; y = o.y; return (*this);
}
inline const point2 point2::operator+ (const vector2 &v) const {
    return point2(x + v.x, y + v.y);
}
inline const point2 point2::operator- (const vector2 &v) const {
    return point2(x - v.x, y - v.y);
}

// compound assignment
inline point2 &point2::operator+= (const vector2 &v) {
    x += v.x; y += v.y; return (*this);
}
inline point2 &point2::operator-= (const vector2 &v) {
    x -= v.x; y -= v.y; return (*this);
}

// comparative
inline bool point2::operator== (const point2 &o) const {
    return (x == o.x && y == o.y);
}
inline bool point2::operator!= (const point2 &o) const {
    return (x != o.x || y != o.y);
}
inline bool point2::operator<  (const point2 &o) const {
    return (x != o.x) ? (x < o.x) : (y < o.y);
}
inline bool point2::operator<= (const point2 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline bool point2::operator>  (const point2 &o) const {
    return (x != o.x) ? (x > o.x) : (y>o.y);
}
inline bool point2::operator>= (const point2 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// member access
inline float &point2::operator[] (int32_t i) {
    assert(mth::range(i, 0, 1) && "index out of bounds!");
    return (&x)[i];
}
inline const float &point2::operator[] (int32_t i) const {
    assert(mth::range(i, 0, 1) && "index out of bounds!");
    return (&x)[i];
}

// linear algebra
inline const vector2 point2::to(const point2 &o) const {
    return vector2(o.x - x, o.y - y);
}

// attributes
inline const bool point2::is_zero() const { return (*this) == point2::ORIGIN; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

inline const float distance(const point2 &p0, const point2 &p1) {
    return p0.to(p1).length();
}
inline const float distance_sq(const point2 &p0, const point2 &p1) {
    return p0.to(p1).length_sq();
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const point2 &p0, const point2 &p1, const float e) {
    return approx_eq(p0.x, p1.x, e) &&
           approx_eq(p0.y, p1.y, e);
}
inline const bool approx_ne(const point2 &p0, const point2 &p1, const float e) {
    return approx_ne(p0.x, p1.x, e) ||
           approx_ne(p0.y, p1.y, e);
}
// attributes
inline const bool nice(const point2 &p) {
    return nice(p.x) && nice(p.y);
}
inline const bool finite(const point2 &p) {
    return finite(p.x) && finite(p.y);
}
// round
inline const point2 round(const point2 &p) {
    return point2(roundf(p.x), roundf(p.y));
}
inline const point2 ceil(const point2 &p) {
    return point2(ceilf(p.x), ceilf(p.y));
}
inline const point2 floor(const point2 &p) {
    return point2(floorf(p.x), floorf(p.y));
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const point2 &p) {
    return os << "p:[" << p.x << "," << p.y << "]";
}
#endif

} // namespace mth //
} // namespace gea //
