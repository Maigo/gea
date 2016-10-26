#ifndef __GEA_MTH_VECTOR_VECTOR3_H__
#define __GEA_MTH_VECTOR_VECTOR3_H__

// gea includes
#include <gea/mth_core/base.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// forward declarations
class polar3;

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
class vector3 {
public:
    float x, y, z;

    // constructors
    inline vector3();
    inline vector3(const float x, const float y, const float z);
    inline explicit vector3(skip_initialization);
    inline explicit vector3(zero_initialization);
    inline vector3(const vector3 &o);
    inline explicit vector3(const polar3 &p);

    // arithmetic
    inline vector3 &operator= (const vector3 &o);
    inline const vector3 operator+ (const vector3 &o) const;
    inline const vector3 operator- (const vector3 &o) const;
    inline const vector3 operator* (const vector3 &o) const;
    inline const vector3 operator/ (const vector3 &o) const;
    inline const vector3 operator* (const float s) const;
    inline const vector3 operator+ (const float s) const;
    inline const vector3 operator- (const float s) const;
    inline const vector3 operator/ (const float s) const;

    // unary arithmetic
    inline const vector3 operator+ () const;
    inline const vector3 operator- () const;

    // compound assignment
    inline vector3 &operator+= (const vector3 &o);
    inline vector3 &operator-= (const vector3 &o);
    inline vector3 &operator+= (const float s);
    inline vector3 &operator-= (const float s);
    inline vector3 &operator*= (const float s);
    inline vector3 &operator/= (const float s);

    // comparative
    inline const bool operator== (const vector3 &o) const;
    inline const bool operator!= (const vector3 &o) const;
    inline const bool operator<  (const vector3 &o) const;
    inline const bool operator<= (const vector3 &o) const;
    inline const bool operator>  (const vector3 &o) const;
    inline const bool operator>= (const vector3 &o) const;

    // member access
    inline       float &operator[] (const int32_t i);
    inline const float &operator[] (const int32_t i) const;

    // linear algebra
    inline const float length()    const;
    inline const float length_sq() const;
    inline void normalize();

    inline const float dot_product(const vector3 &o) const;
    inline const vector3 cross_product(const vector3 &o) const;

    inline const float angle(const vector3 &o) const;

    // attributes
    inline const bool is_zero() const;

    // conversion
    void from_polar(const polar3 &p); //note: should be called spherical
    void to_polar(polar3 &out_p) const;

    // static constants
    static const vector3 ZERO;
    static const vector3 X_AXIS;
    static const vector3 Y_AXIS;
    static const vector3 Z_AXIS;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const vector3 operator* (const float s, const vector3 &v);

// linear algebra - convenience functions
inline const float dot_product(const vector3 &v1, const vector3 &v2);
inline const vector3 cross_product(const vector3 &v1, const vector3 &v2);
inline const float angle(const vector3 &v1, const vector3 &v2);

// interpolation
inline const vector3  lerp(const vector3 &from, const vector3 &to, const float t);
inline const vector3 nlerp(const vector3 &from, const vector3 &to, const float t);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const vector3 &v1, const vector3 &v2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const vector3 &v1, const vector3 &v2, const float e = APPROX_EPSILON);

// attributes
inline const bool nice(const vector3 &v);
inline const bool finite(const vector3 &v);

// round
inline const vector3 round(const vector3 &v);
inline const vector3 ceil(const vector3 &v);
inline const vector3 floor(const vector3 &v);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const vector3 &v);
#endif

} // namespace mth //
} // namespace gea //

#include "vector3.inl"

#endif // __GEA_MTH_VECTOR_VECTOR3_H__ //
