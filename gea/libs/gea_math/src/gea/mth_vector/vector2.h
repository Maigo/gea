#ifndef __GEA_VMTH_VECTOR3_H__
#define __GEA_VMTH_VECTOR3_H__

// stl includes
#include <assert.h>

// mth includes
#include <gea/mth_core/base.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// forward declarations
class polar2;

// ------------------------------------------------------------------------- //
// vector2                                                                   //
// ------------------------------------------------------------------------- //
class vector2 {
public:
    float x, y, z;

    // constructors
    inline vector2();
    inline vector2(const float x, const float y);
    inline explicit vector2(skip_initialization);
    inline vector2(const vector2 &o);
    inline explicit vector2(const polar2 &p);

    // arithmetic
    inline vector2 &operator= (const vector2 &o);
    inline const vector2 operator+ (const vector2 &o) const;
    inline const vector2 operator- (const vector2 &o) const;
    inline const vector2 operator* (const vector2 &o) const;
    inline const vector2 operator/ (const vector2 &o) const;
    inline const vector2 operator* (const float s) const;
    inline const vector2 operator+ (const float s) const;
    inline const vector2 operator- (const float s) const;
    inline const vector2 operator/ (const float s) const;

    // unary arithmetic
    inline const vector2 operator+ () const;
    inline const vector2 operator- () const;

    // compound assignment
    inline vector2 &operator+= (const vector2 &o);
    inline vector2 &operator-= (const vector2 &o);
    inline vector2 &operator+= (const float s);
    inline vector2 &operator-= (const float s);
    inline vector2 &operator*= (const float s);
    inline vector2 &operator/= (const float s);

    // comparative
    inline const bool operator== (const vector2 &o) const;
    inline const bool operator!= (const vector2 &o) const;
    inline const bool operator<  (const vector2 &o) const;
    inline const bool operator<= (const vector2 &o) const;
    inline const bool operator>  (const vector2 &o) const;
    inline const bool operator>= (const vector2 &o) const;

    // member access
    inline       float &operator[] (const int32_t i);
    inline const float &operator[] (const int32_t i) const;

    // linear algebra
    inline const float length()    const;
    inline const float length_sq() const;
    inline void normalize();

    inline const float dot_product(const vector2 &o) const;

    inline const float angle(const vector2 &o) const;

    // attributes
    inline const bool is_zero() const;

    // conversion
    void from_polar(const polar2 &p); //note: should be called spherical
    void to_polar(polar2 &out_p) const;

    // static constants
    static const vector2 ZERO;
    static const vector2 X_AXIS;
    static const vector2 Y_AXIS;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const vector2 operator* (const float s, const vector2 &v);

// linear algebra - convenience functions
inline const float dot_product(const vector2 &v0, const vector2 &v1);
inline const float angle(const vector2 &v0, const vector2 &v1);

// interpolation
inline const vector2  lerp(const vector2 &from, const vector2 &to, const float t);
inline const vector2 nlerp(const vector2 &from, const vector2 &to, const float t);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const vector2 &v0, const vector2 &v1, const float e = APPROX_EPSILON);
inline const bool approx_ne(const vector2 &v0, const vector2 &v1, const float e = APPROX_EPSILON);
// nice vector2
inline const bool nice(const vector2 &v);
// finite vector2
inline const bool finite(const vector2 &v);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const vector2 &v);
#endif

} // namespace mth //
} // namespace gea //

#include "vector2.inl"

#endif // __GEA_VMTH_VECTOR3_H__ //
