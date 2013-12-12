
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
// constructors
inline vector3::vector3() : x(0.0f), y(0.0f), z(0.0f) {}
inline vector3::vector3(float x, float y, float z) : x(x), y(y), z(z) {}
inline vector3::vector3(skip_initialization) {}
inline vector3::vector3(const vector3 &o) : x(o.x), y(o.y), z(o.z) {}
inline vector3::vector3(const polar3 &p) { from_polar(p); }

// arithmetic
inline vector3 &vector3::operator= (const vector3 &o) {
    x=o.x; y=o.y; z=o.z; return (*this);
}
inline const vector3 vector3::operator+ (const vector3 &o) const {
    return vector3(x+o.x, y+o.y, z+o.z);
}
inline const vector3 vector3::operator- (const vector3 &o) const {
    return vector3(x-o.x, y-o.y, z-o.z);
}
inline const vector3 vector3::operator* (const vector3 &o) const {
    return vector3(x*o.x, y*o.y, z*o.z);
}
inline const vector3 vector3::operator/ (const vector3 &o) const {
    assert((o.x!=0.0f) && (o.y!=0.0f) && (o.z!=0.0f) && "divide by zero!");
    return vector3(x/o.x, y/o.y, z/o.z);
}
inline const vector3 vector3::operator+ (float s) const {
    return vector3(x+s, y+s, z+s);
}
inline const vector3 vector3::operator- (float s) const {
    return vector3(x-s, y-s, z-s);
}
inline const vector3 vector3::operator* (float s) const {
    return vector3(x*s, y*s, z*s);
}
inline const vector3 vector3::operator/ (float s) const {
    assert((s!=0.0f) && "divide by zero!");
    float s_inv = 1.0f/s;
    return vector3(x*s_inv, y*s_inv, z*s_inv);
}
// unary arithmetic
inline const vector3 vector3::operator+ () const { return (*this); }
inline const vector3 vector3::operator- () const {
    return vector3(-x, -y, -z);
}

// compound assignment
inline vector3 &vector3::operator+= (const vector3 &o) {
    x+=o.x; y+=o.y; z+=o.z; return (*this);
}
inline vector3 &vector3::operator-= (const vector3 &o) {
    x-=o.x; y-=o.y; z-=o.z; return (*this);
}
inline vector3 &vector3::operator+= (float s) {
    x+=s; y+=s; z+=s; return (*this);
}
inline vector3 &vector3::operator-= (float s) {
    x-=s; y-=s; z-=s; return (*this);
}
inline vector3 &vector3::operator*= (float s) {
    x*=s; y*=s; z*=s; return (*this);
}
inline vector3 &vector3::operator/= (float s) {
    assert((s!=0.0f) && "divide by zero!");
    float s_inv = 1.0f / s;
    x*=s_inv; y*=s_inv; z*=s_inv; return (*this);
}

// comparative
inline bool vector3::operator== (const vector3 &o) const {
    return (x==o.x && y==o.y && z==o.z);
}
inline bool vector3::operator!= (const vector3 &o) const {
    return (x!=o.x || y!=o.y || z!=o.z);
}
inline bool vector3::operator<  (const vector3 &o) const {
    return (x != o.x) ? (x<o.x) : ((y != o.y) ? (y<o.y) : (z<o.z));
}
inline bool vector3::operator<= (const vector3 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline bool vector3::operator>  (const vector3 &o) const {
    return (x != o.x) ? (x>o.x) : ((y != o.y) ? (y>o.y) : (z>o.z));
}
inline bool vector3::operator>= (const vector3 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// member access
inline float &vector3::operator[] (int32_t i) {
    assert(mth::range(i,0,2) && "index out of bounds!");
    return (&x)[i];
}
inline const float &vector3::operator[] (int32_t i) const {
    assert(mth::range(i,0,2) && "index out of bounds!");
    return (&x)[i];
}

// linear algebra
inline const float vector3::length()    const { return sqrtf(x*x + y*y + z*z); }
inline const float vector3::length_sq() const { return      (x*x + y*y + z*z); }
inline void vector3::normalize() {
    float len_sq = length_sq();
	if (len_sq != 0.0 ) {
		const float scale = ( 1.0f / sqrtf( len_sq ) );
		x *= scale;
		y *= scale;
		z *= scale;
    }
}

inline const float vector3::dot_product(const vector3 &o) const {
    return (x*o.x + y*o.y + z*o.z);
}
inline const vector3 vector3::cross_product(const vector3 &o) const {
    return vector3(x*o.y - y*o.x, y*o.z - z*o.y, z*o.x - x*o.z);
}

inline const float vector3::angle(const vector3 &o) const {
    // theta = arccos( a dot b / |a||b| )
    float len = length() * o.length();
    return (len != 0.0f) ? acos(dot_product(o)/len) : 0.0f;
}

// attributes
inline bool vector3::is_zero() const { return (*this) == vector3::ZERO; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const vector3 operator* (float s, const vector3 &v) {
    return (v*s);
}

// linear algebra - convenience functions
inline const float dot_product(const vector3 &v0, const vector3 &v1) {
    return v0.dot_product(v1);
}
inline const vector3 cross_product(const vector3 &v0, const vector3 &v1) {
    return v0.cross_product(v1);
}
inline const float angle(const vector3 &v0, const vector3 &v1) {
    return v0.angle(v1);
}

// interpolation
inline const vector3 lerp(const vector3 &from, const vector3 &to, float t) {
    assert(mth::range(t, 0.0f, 1.0f) && "out of range!");
    return from + (to - from) * t;
}
inline const vector3 nlerp(const vector3 &from, const vector3 &to, float t) {
    vector3 v = lerp(from, to, t);
    v.normalize();
    return v;
}

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(const vector3 &v0, const vector3 &v1, float e) {
    return approx_eq(v0.x, v1.x, e) &&
           approx_eq(v0.y, v1.y, e) &&
           approx_eq(v0.z, v1.z, e);
}
inline bool approx_ne(const vector3 &v0, const vector3 &v1, float e) {
    return approx_ne(v0.x, v1.x, e) ||
           approx_ne(v0.y, v1.y, e) ||
           approx_ne(v0.z, v1.z, e);
}
// nice vector3
inline bool nice(const vector3 &v) {
    return nice(v.x) && nice(v.y) && nice(v.z);
}
// finite vector3
inline bool finite(const vector3 &v) {
    return finite(v.x) && finite(v.y) && finite(v.z);
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &os, const vector3 &v) {
    return os << "v:[" << v.x << "," << v.y << "," << v.z << "]";
}
#endif

} // namespace mth //
} // namespace gea //
