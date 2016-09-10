#ifndef __GEA_VMTH_QUATERNION_H__
#define __GEA_VMTH_QUATERNION_H__

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/vector3.h>

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
    float x, y, z, w;

    // constructors
    inline quaternion();
    inline quaternion(const float x, const float y, const float z, const float w);
    inline quaternion(const float angle, const vector3 &axis);
    inline explicit quaternion(skip_initialization);
    inline quaternion(const quaternion &o);
    inline explicit quaternion(const matrix3 &m);
    inline quaternion(const float heading, const float attitude, const float bank);

    // arithmetic
    inline quaternion &operator =(const quaternion &o);
    inline const quaternion operator+ (const quaternion &o) const;
    inline const quaternion operator- (const quaternion &o) const;
    inline const quaternion operator* (const quaternion &o) const;
    inline const quaternion operator* (const float s) const;
    inline const quaternion operator/ (const float s) const;
    // unary arithmetic
    inline const quaternion operator+ () const;
    inline const quaternion operator- () const;

    // comparative
    inline const bool operator== (const quaternion &o) const;
    inline const bool operator!= (const quaternion &o) const;

    // member access
    inline       float &operator[] (const int32_t i);
    inline const float &operator[] (const int32_t i) const;

    // linear algebra
    inline const float length() const;
    inline const float length_sq() const;
    inline void normalize();

    inline const float dot_product(const quaternion &o) const;

    inline const quaternion conjugate() const;
    inline const quaternion inverse() const;

    // attributes
    inline const bool is_zero() const;

    // conversion
    void from_axis(const float angle, const vector3 &axis);
    void to_axis(float &out_angle, vector3 &out_axis) const;
    void from_euler(const float heading, const float attitude, const float bank);
    void to_euler(float &out_heading, float &out_attitude, float &out_bank) const;
    void from_matrix(const matrix3 &m);
    void to_matrix(matrix3 &out_m) const;

    // static constants
    static const quaternion ZERO;
    static const quaternion IDENTITY;
};
typedef quaternion quat;

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
inline const quaternion operator* (const float s, const quaternion &q);

// linear algebra - convenience functions
inline const float dot_product(const quaternion &q1, const quaternion &q2);

// interpolation
inline const quaternion  lerp(const quaternion &from, const quaternion &to, const float t);
inline const quaternion nlerp(const quaternion &from, const quaternion &to, const float t);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const quaternion &q1, const quaternion &q2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const quaternion &q1, const quaternion &q2, const float e = APPROX_EPSILON);

// nice quaternion
inline const bool nice(const quaternion &q);

// finite quaternion
inline const bool finite(const quaternion &q);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &lhs, const quaternion &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "quaternion.inl"

#endif // __GEA_VMTH_QUATERNION_H__ //
