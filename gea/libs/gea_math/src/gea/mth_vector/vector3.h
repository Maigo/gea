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
class polar3;

// ------------------------------------------------------------------------- //
// vector3                                                                   //
// ------------------------------------------------------------------------- //
class vector3 {
public:
    float x,y,z;

    // constructors
    inline vector3();
    inline vector3(float x, float y, float z);
    inline explicit vector3(skip_initialization);
    inline vector3(const vector3 &o);
    inline explicit vector3(const polar3 &p);

    // arithmetic
    inline vector3 &operator= (const vector3 &o);
    inline const vector3 operator+ (const vector3 &o) const;
    inline const vector3 operator- (const vector3 &o) const;
    inline const vector3 operator* (const vector3 &o) const;
    inline const vector3 operator/ (const vector3 &o) const;
    inline const vector3 operator* (float s) const;
    inline const vector3 operator+ (float s) const;
    inline const vector3 operator- (float s) const;
    inline const vector3 operator/ (float s) const;

    // unary arithmetic
    inline const vector3 operator+ () const;
    inline const vector3 operator- () const;

    // compound assignment
    inline vector3 &operator+= (const vector3 &o);
    inline vector3 &operator-= (const vector3 &o);
    inline vector3 &operator+= (float s);
    inline vector3 &operator-= (float s);
    inline vector3 &operator*= (float s);
    inline vector3 &operator/= (float s);

    // comparative
    inline bool operator== (const vector3 &o) const;
    inline bool operator!= (const vector3 &o) const;
    inline bool operator<  (const vector3 &o) const;
    inline bool operator<= (const vector3 &o) const;
    inline bool operator>  (const vector3 &o) const;
    inline bool operator>= (const vector3 &o) const;

    // member access
    inline       float &operator[] (int32_t i);
    inline const float &operator[] (int32_t i) const;

    // linear algebra
    inline const float length()    const;
    inline const float length_sq() const;
    inline void normalize();

    inline const float dot_product(const vector3 &o) const;
    inline const vector3 cross_product(const vector3 &o) const;

    inline const float angle(const vector3 &o) const;

    // attributes
    inline bool is_zero() const;

    // conversion
    void from_polar(const polar3 &p); //note: should be called spherical
    void to_polar(polar3 &p) const;

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
inline const vector3 operator* (float s, const vector3 &v);

// linear algebra - convenience functions
inline const float dot_product(const vector3 &v1, const vector3 &v2);
inline const vector3 cross_product(const vector3 &v1, const vector3 &v2);
inline const float angle(const vector3 &v1, const vector3 &v2);

// interpolation
inline const vector3  lerp(const vector3 &from, const vector3 &to, float t);
inline const vector3 nlerp(const vector3 &from, const vector3 &to, float t);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(const vector3 &v1, const vector3 &v2, float e = APPROX_EPSILON);
inline bool approx_ne(const vector3 &v1, const vector3 &v2, float e = APPROX_EPSILON);
// nice vector3
inline bool nice(const vector3 &v);
// finite vector3
inline bool finite(const vector3 &v);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &os, const vector3 &v);
#endif

} // namespace mth //
} // namespace gea //

#include "vector3.inl"

#endif // __GEA_VMTH_VECTOR3_H__ //
