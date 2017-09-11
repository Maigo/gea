#ifndef __GEA_MTH_VECTOR_VECTOR4_H__
#define __GEA_MTH_VECTOR_VECTOR4_H__

// gea includes
#include <gea/mth_core/base.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector4                                                                   //
// ------------------------------------------------------------------------- //
class vector4 {
public:
    float x, y, z, w;

    // constructors
    inline vector4();
    inline vector4(const float x, const float y, const float z, const float w);
    inline explicit vector4(skip_initialization);
    inline explicit vector4(zero_initialization);
    inline vector4(const vector4 &o);

    // arithmetic
    inline vector4 &operator= (const vector4 &o);
    inline const vector4 operator+ (const vector4 &o) const;
    inline const vector4 operator- (const vector4 &o) const;
    inline const vector4 operator* (const vector4 &o) const;
    inline const vector4 operator/ (const vector4 &o) const;
    inline const vector4 operator* (const float s) const;
    inline const vector4 operator+ (const float s) const;
    inline const vector4 operator- (const float s) const;
    inline const vector4 operator/ (const float s) const;

    // unary arithmetic
    inline const vector4 operator+ () const;
    inline const vector4 operator- () const;

    // compound assignment
    inline vector4 &operator+= (const vector4 &o);
    inline vector4 &operator-= (const vector4 &o);
    inline vector4 &operator+= (const float s);
    inline vector4 &operator-= (const float s);
    inline vector4 &operator*= (const float s);
    inline vector4 &operator/= (const float s);

    // comparative
    inline const bool operator== (const vector4 &o) const;
    inline const bool operator!= (const vector4 &o) const;
    inline const bool operator<  (const vector4 &o) const;
    inline const bool operator<= (const vector4 &o) const;
    inline const bool operator>  (const vector4 &o) const;
    inline const bool operator>= (const vector4 &o) const;

    // member access
    inline       float &operator[] (const int32_t i);
    inline const float &operator[] (const int32_t i) const;

    // linear algebra
    inline const float length()    const;
    inline const float length_sq() const;
    inline void normalize();

    // attributes
    inline const bool is_zero() const;

    // conversion

    // static constants
    static const vector4 ZERO;
    static const vector4 X_AXIS;
    static const vector4 Y_AXIS;
    static const vector4 Z_AXIS;
    static const vector4 W_AXIS;
};

// ------------------------------------------------------------------------- //

typedef vector4 vec4;

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const vector4 operator* (const float s, const vector4 &v);

// interpolation
inline const vector4  lerp(const vector4 &from, const vector4 &to, const float t);
inline const vector4 nlerp(const vector4 &from, const vector4 &to, const float t);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const vector4 &v1, const vector4 &v2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const vector4 &v1, const vector4 &v2, const float e = APPROX_EPSILON);

// attributes
inline const bool nice(const vector4 &v);
inline const bool finite(const vector4 &v);

// round
inline const vector4 round(const vector4 &v);
inline const vector4 ceil(const vector4 &v);
inline const vector4 floor(const vector4 &v);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const vector4 &v);
#endif

} // namespace mth //
} // namespace gea //

#include "vector4.inl"

#endif // __GEA_MTH_VECTOR_VECTOR4_H__ //
