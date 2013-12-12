
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polar3                                                                     //
// ------------------------------------------------------------------------- //

// constructors
inline polar3::polar3() : r(0.0f), theta(0.0f), phi(0.0f) {}
inline polar3::polar3(float r, float theta, float phi) 
    : r(r), theta(theta), phi(phi) {}
inline polar3::polar3(skip_initialization) {}
inline polar3::polar3(const polar3 &o)
    : r(o.r), theta(o.theta), phi(o.phi) {}
inline polar3::polar3(const vector3 &v) { from_vector(v); }

// arithmetic
inline polar3 &polar3::operator= (const polar3 &o) {
    r=o.r; theta=o.theta; phi=o.phi; return (*this);
}
inline const polar3 polar3::operator+ (const polar3 &o) const {
    return polar3(r+o.r, theta+o.theta, phi+o.phi);
}
inline const polar3 polar3::operator- (const polar3 &o) const {
    return polar3(r-o.r, theta-o.theta, phi-o.phi);
}
inline const polar3 polar3::operator* (float s) const {
    return polar3(r*s, theta*s, phi*s);
}
inline const polar3 polar3::operator/ (float s) const {
    assert((s!=0.0f) && "divide by zero!");
    float s_inv = 1.0f/s;
    return polar3(r*s_inv, theta*s_inv, phi*s_inv);
}

// compound assignment
inline polar3 &polar3::operator+= (const polar3 &o) {
    r+=o.r; theta+=o.theta; phi+=o.phi; return (*this);
}
inline polar3 &polar3::operator-= (const polar3 &o) {
    r-=o.r; theta-=o.theta; phi-=o.phi; return (*this);
}
inline polar3 &polar3::operator*= (float s) {
    r*=s; theta*=s; phi*=s; return (*this);
}
inline polar3 &polar3::operator/= (float s) {
    assert((s!=0.0f) && "divide by zero!");
    float s_inv = 1.0f/s;
    r*=s_inv; theta*=s_inv; phi*=s_inv; return (*this);
}

// comparative
inline bool polar3::operator== (const polar3 &o) const {
    return ((r == o.r) && (theta == o.theta) && (phi == o.phi));
}
inline bool polar3::operator< (const polar3 &o) const {
    return (r != o.r) ? (r < o.r) : (
        (theta != o.theta) ? (theta < o.theta) : (phi < o.phi));
}
inline bool polar3::operator<= (const polar3 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline bool polar3::operator> (const polar3 &o) const {
    return (r != o.r) ? (r > o.r) : (
        (theta != o.theta) ? (theta > o.theta) : (phi > o.phi));
}
inline bool polar3::operator>= (const polar3 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &os, const polar3 &p) {
    return os << "p:[" << p.r << "," << p.theta << "," << p.phi << "]";
}
#endif

} // namespace mth //
} // namespace gea //