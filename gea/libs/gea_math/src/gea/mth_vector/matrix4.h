#ifndef __GEA_MTH_VECTOR_MATRIX4_H__
#define __GEA_MTH_VECTOR_MATRIX4_H__

// gea includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/vector4.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix4                                                                   //
// ------------------------------------------------------------------------- //
class matrix4 {
public:
    float m[4][4];

    // constructors
    inline matrix4();
    inline matrix4(const float xx, const float yy, const float zz, float ww);
    inline matrix4(const float xx, const float yx, const float zx, const float wx,
                   const float xy, const float yy, const float zy, const float wy,
                   const float xz, const float yz, const float zz, const float wz,
                   const float xw, const float yw, const float zw, const float ww);
    inline explicit matrix4(skip_initialization);
    inline explicit matrix4(identity_initialization);
    inline explicit matrix4(zero_initialization);
    inline matrix4(const matrix4 &o);

    // arithmetic
    inline matrix4 &operator =(const matrix4 &o);
    inline const matrix4 operator+ (const matrix4 &o) const;
    inline const matrix4 operator- (const matrix4 &o) const;
    inline const matrix4 operator* (const matrix4 &o) const;
    inline const matrix4 operator* (const float s) const;
    inline const matrix4 operator/ (const float s) const;
    inline const vector4 operator* (const vector4 &v) const;
//    inline const point4  operator* (const point4  &p) const;

    // unary arithmetic
    inline const matrix4 operator+ () const;
    inline const matrix4 operator- () const;

    // compound assignment
    inline matrix4 &operator+= (const matrix4 &o);
    inline matrix4 &operator-= (const matrix4 &o);
    inline matrix4 &operator*= (const matrix4 &o);
    inline matrix4 &operator*= (const float s);
    inline matrix4 &operator/= (const float s);

    // member access
    inline const float operator() (const int32_t i, const int32_t j) const;
    inline const vector4 get_row(const int32_t row) const;
    inline const vector4 get_column(const int32_t col) const;

    // linear algebra
    inline const matrix4 transpose() const;
    inline const float trace() const;
    inline const float determinant() const;
    const matrix4 inverse() const;

    // conversion

    // static constants
    static const matrix4 IDENTITY;
    static const matrix4 ZERO;
};

// ------------------------------------------------------------------------- //

typedef matrix4 mat4;

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix4 operator* (const float s, const matrix4 &m);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const matrix4 &m1, const matrix4 &m2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const matrix4 &m1, const matrix4 &m2, const float e = APPROX_EPSILON);

// nice matrix4
inline const bool nice(const matrix4 &m);

// finite matrix4
inline const bool finite(const matrix4 &m);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &lhs, const matrix4 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "matrix4.inl"

#endif // __GEA_MTH_VECTOR_MATRIX4_H__ //
