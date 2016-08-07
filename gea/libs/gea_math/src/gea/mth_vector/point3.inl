
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //
// constructors
inline point3::point3() : x(0.0f), y(0.0f), z(0.0f) {}
inline point3::point3(float x, float y, float z) : x(x), y(y), z(z) {}
inline point3::point3(skip_initialization) {}
inline point3::point3(const point3 &o) : x(o.x), y(o.y), z(o.z) {}

// arithmetic
inline point3 &point3::operator= (const point3 &o) {
	x=o.x; y=o.y; z=o.z; return (*this);
}
inline const point3 point3::operator+ (const vector3 &v) const {
	return point3(x+v.x, y+v.y, z+v.z);
}
inline const point3 point3::operator- (const vector3 &v) const {
	return point3(x-v.x, y-v.y, z-v.z);
}

// compound assignment
inline point3 &point3::operator+= (const vector3 &v) {
	x+=v.x; y+=v.y; z+=v.z; return (*this);
}
inline point3 &point3::operator-= (const vector3 &v) {
	x-=v.x; y-=v.y; z-=v.z; return (*this);
}

// comparative
inline bool point3::operator== (const point3 &o) const {
	return (x==o.x && y==o.y && z==o.z);
}
inline bool point3::operator!= (const point3 &o) const {
	return (x!=o.x || y!=o.y || z!=o.z);
}
inline bool point3::operator<  (const point3 &o) const {
    return (x != o.x) ? (x<o.x) : ((y != o.y) ? (y<o.y) : (z<o.z));
}
inline bool point3::operator<= (const point3 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline bool point3::operator>  (const point3 &o) const {
    return (x != o.x) ? (x>o.x) : ((y != o.y) ? (y>o.y) : (z>o.z));
}
inline bool point3::operator>= (const point3 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// member access
inline float &point3::operator[] (int32_t i) {
    assert(mth::range(i,0,2) && "index out of bounds!");
    return (&x)[i];
}
inline const float &point3::operator[] (int32_t i) const {
    assert(mth::range(i,0,2) && "index out of bounds!");
    return (&x)[i];
}

// attributes
inline bool point3::is_zero() const { return (*this) == point3::ORIGIN; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(const point3 &p0, const point3 &p1, float e) {
    return approx_eq(p0.x, p1.x, e) &&
           approx_eq(p0.y, p1.y, e) &&
           approx_eq(p0.z, p1.z, e);
}
inline bool approx_ne(const point3 &p0, const point3 &p1, float e) {
    return approx_ne(p0.x, p1.x, e) ||
           approx_ne(p0.y, p1.y, e) ||
           approx_ne(p0.z, p1.z, e);
}
// nice point3
inline bool nice(const point3 &p) {
    return nice(p.x) && nice(p.y) && nice(p.z);
}
// finite point3
inline bool finite(const point3 &p) {
    return finite(p.x) && finite(p.y) && finite(p.z);
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &os, const point3 &p) {
    return os << "p:[" << p.x << "," << p.y << "," << p.z << "]";
}
#endif

} // namespace mth //
} // namespace gea //
