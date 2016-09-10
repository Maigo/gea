
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polar2                                                                    //
// ------------------------------------------------------------------------- //

// constructors
inline polar2::polar2() : r(0.0f), theta(0.0f) {}
inline polar2::polar2(const float r, const float theta) : r(r), theta(theta) {}
inline polar2::polar2(skip_initialization) {}
inline polar2::polar2(const polar2 &o) : r(o.r), theta(o.theta) {}
inline polar2::polar2(const vector2 &v) { from_vector(v); }

// arithmetic
inline polar2 &polar2::operator= (const polar2 &o) {
    r = o.r; theta = o.theta; return (*this);
}
inline const polar2 polar2::operator+ (const polar2 &o) const {
    return polar2(r + o.r, theta + o.theta);
}
inline const polar2 polar2::operator- (const polar2 &o) const {
    return polar2(r - o.r, theta - o.theta);
}
inline const polar2 polar2::operator* (float s) const {
    return polar2(r * s, theta * s);
}
inline const polar2 polar2::operator/ (float s) const {
    assert((s != 0.0f) && "divide by zero!");
    const float s_inv = 1.0f / s;
    return polar2(r * s_inv, theta * s_inv);
}

// compound assignment
inline polar2 &polar2::operator+= (const polar2 &o) {
    r += o.r; theta += o.theta; return (*this);
}
inline polar2 &polar2::operator-= (const polar2 &o) {
    r -= o.r; theta -= o.theta; return (*this);
}
inline polar2 &polar2::operator*= (float s) {
    r *= s; theta *= s; return (*this);
}
inline polar2 &polar2::operator/= (float s) {
    assert((s != 0.0f) && "divide by zero!");
    const float s_inv = 1.0f / s;
    r *= s_inv; theta *= s_inv; return (*this);
}

// comparative
inline const bool polar2::operator== (const polar2 &o) const {
    return ((r == o.r) && (theta == o.theta));
}
inline const bool polar2::operator< (const polar2 &o) const {
    return (r != o.r) ? (r < o.r) : (theta < o.theta);
}
inline const bool polar2::operator<= (const polar2 &o) const {
    return ((*this) == o) || ((*this) < o);
}
inline const bool polar2::operator> (const polar2 &o) const {
    return (r != o.r) ? (r > o.r) : (theta > o.theta);
}
inline const bool polar2::operator>= (const polar2 &o) const {
    return ((*this) == o) || ((*this) > o);
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const polar2 &p) {
    return os << "p:[" << p.r << "," << p.theta << "]";
}
#endif

} // namespace mth //
} // namespace gea //
