#ifndef __GEA_VMTH_QUATERNION_H__
#define __GEA_VMTH_QUATERNION_H__

// mth includes
#include <gea/bmth/base.h>
#include <gea/vmth/vector3.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// forward declarations
class matrix3;

// ------------------------------------------------------------------------- //
// quaternion                                                                //
// ------------------------------------------------------------------------- //
class quaternion {
public:
    float x,y,z,w;

    // constructors
    inline quaternion();
    inline quaternion(float x, float y, float z, float w);
    inline quaternion(float angle, const vector3 &axis);
    inline explicit quaternion(skip_initialization);
    inline quaternion(const quaternion &o);
    inline explicit quaternion(const matrix3 &m);
    inline quaternion(float heading, float attitude, float bank);

    // arithmetic
    inline quaternion &operator =(const quaternion &o);
    inline const quaternion operator+ (const quaternion &o) const;
    inline const quaternion operator- (const quaternion &o) const;
    inline const quaternion operator* (const quaternion &o) const;
    inline const quaternion operator* (float s) const;
    inline const quaternion operator/ (float s) const;
    // unary arithmetic
    inline const quaternion operator+ () const;
    inline const quaternion operator- () const;

    // comparative
    inline bool operator== (const quaternion &o) const;
    inline bool operator!= (const quaternion &o) const;

    // member access
    inline       float &operator[] (int32_t i);
    inline const float &operator[] (int32_t i) const;

    // linear algebra
    inline float length() const;
    inline float length_sq() const;
    inline void normalize();

    inline const float dot_product(const quaternion &o) const;

    inline const quaternion conjugate() const;
    inline const quaternion inverse() const;

    // attributes
    inline bool is_zero() const;

    // conversion
    void from_axis(float angle, const vector3 &axis);
    void to_axis(float &angle, vector3 &axis) const;
    void from_euler(float heading, float attitude, float bank);
    void to_euler(float &heading, float &attitude, float &bank) const;
    void from_matrix(const matrix3 &axis);
    void to_matrix(matrix3 &axis) const;

    // static constants
    static const quaternion ZERO;
    static const quaternion IDENTITY;
};
typedef quaternion quat;

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
inline const quaternion operator* (float s, const quaternion &q);

// linear algebra - convenience functions
inline const float dot_product(const quaternion &q1, const quaternion &q2);

// interpolation
inline const quaternion  lerp(const quaternion &from, const quaternion &to, float t);
inline const quaternion nlerp(const quaternion &from, const quaternion &to, float t);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(const quaternion &q1, const quaternion &q2, float e = APPROX_EPSILON);
inline bool approx_ne(const quaternion &q1, const quaternion &q2, float e = APPROX_EPSILON);
// nice quaternion
inline bool nice(const quaternion &q);
// finite quaternion
inline bool finite(const quaternion &q);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &lhs, const quaternion &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "quaternion.inl"

#endif // __GEA_VMTH_QUATERNION_H__ //
