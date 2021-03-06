#ifndef __GEA_MTH_VECTOR_MATRIX3_H__
#define __GEA_MTH_VECTOR_MATRIX3_H__

// gea includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/point3.h>
#include <gea/mth_vector/vector3.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// forward declarations
class quaternion;

// ------------------------------------------------------------------------- //
// matrix3                                                                   //
// ------------------------------------------------------------------------- //
class matrix3 {
public:
    float m[3][3];

    // constructors
    inline matrix3();
    inline matrix3(const float xx, const float yy, const float zz);
    inline matrix3(const float xx, const float yx, const float zx,
                   const float xy, const float yy, const float zy,
                   const float xz, const float yz, const float zz);
    inline explicit matrix3(skip_initialization);
    inline explicit matrix3(identity_initialization);
    inline explicit matrix3(zero_initialization);
    inline matrix3(const matrix3 &o);
    inline explicit matrix3(const quaternion &q);
//    inline matrix3(const float heading, const float attitude, const float bank);

    // arithmetic
    inline matrix3 &operator =(const matrix3 &o);
    inline const matrix3 operator+ (const matrix3 &o) const;
    inline const matrix3 operator- (const matrix3 &o) const;
    inline const matrix3 operator* (const matrix3 &o) const;
    inline const matrix3 operator* (const float s) const;
    inline const matrix3 operator/ (const float s) const;
    inline const vector3 operator* (const vector3 &v) const;
    inline const point3  operator* (const point3  &p) const;

    // unary arithmetic
    inline const matrix3 operator+ () const;
    inline const matrix3 operator- () const;

    // compound assignment
    inline matrix3 &operator+= (const matrix3 &o);
    inline matrix3 &operator-= (const matrix3 &o);
    inline matrix3 &operator*= (const matrix3 &o);
    inline matrix3 &operator*= (const float s);
    inline matrix3 &operator/= (const float s);

    // member access
    inline const float operator() (const int32_t i, const int32_t j) const;
    inline const vector3 get_row(const int32_t row) const;
    inline const vector3 get_column(const int32_t col) const;

    // linear algebra
    inline const matrix3 transpose() const;
    inline const float trace() const;
    inline const float determinant() const;
    const matrix3 inverse() const;

    // conversion
    void from_quaternion(const quaternion &q);
    void to_quaternion(quaternion &out_q) const;
    void from_euler(const float heading, const float attitude, const float bank); // yzx
    void to_euler(float &out_heading, float &out_attitude, float &out_bank) const;
    void from_rotation(const float angle, const vector3& axis);

    // static constants
    static const matrix3 IDENTITY;
    static const matrix3 ZERO;
};

// ------------------------------------------------------------------------- //

typedef matrix3 mat3;

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix3 operator* (const float s, const matrix3 &m);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const matrix3 &m1, const matrix3 &m2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const matrix3 &m1, const matrix3 &m2, const float e = APPROX_EPSILON);

// nice matrix3
inline const bool nice(const matrix3 &m);

// finite matrix3
inline const bool finite(const matrix3 &m);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &lhs, const matrix3 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "matrix3.inl"

#endif // __GEA_MTH_VECTOR_MATRIX3_H__ //
