#ifndef __GEA_MTH_VECTOR_MATRIX2_H__
#define __GEA_MTH_VECTOR_MATRIX2_H__

// gea includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// matrix2                                                                   //
// ------------------------------------------------------------------------- //
class matrix2 {
public:
    float m[2][2];

    // constructors
    inline matrix2();
    inline matrix2(const float xx, const float yy);
    inline matrix2(const float xx, const float yx,
                   const float xy, const float yy);
    inline explicit matrix2(skip_initialization);
    inline explicit matrix2(identity_initialization);
    inline explicit matrix2(zero_initialization);
    inline matrix2(const matrix2 &o);

    // arithmetic
    inline matrix2 &operator =(const matrix2 &o);
    inline const matrix2 operator+ (const matrix2 &o) const;
    inline const matrix2 operator- (const matrix2 &o) const;
    inline const matrix2 operator* (const matrix2 &o) const;
    inline const matrix2 operator* (const float s) const;
    inline const matrix2 operator/ (const float s) const;
    inline const vector2 operator* (const vector2 &v) const;
    inline const point2  operator* (const point2  &p) const;

    // unary arithmetic
    inline const matrix2 operator+ () const;
    inline const matrix2 operator- () const;

    // compound assignment
    inline matrix2 &operator+= (const matrix2 &o);
    inline matrix2 &operator-= (const matrix2 &o);
    inline matrix2 &operator*= (const matrix2 &o);
    inline matrix2 &operator*= (const float s);
    inline matrix2 &operator/= (const float s);

    // member access
    inline const float operator() (const int32_t i, const int32_t j) const;
    inline const vector2 get_row(const int32_t row) const;
    inline const vector2 get_column(const int32_t col) const;

    // linear algebra
    inline const matrix2 transpose() const;
    inline const float trace() const;
    inline const float determinant() const;
    const matrix2 inverse() const;

    // conversion
    void from_angle(const float angle);
    void to_angle(float &out_angle) const;

    // static constants
    static const matrix2 IDENTITY;
    static const matrix2 ZERO;
};

// ------------------------------------------------------------------------- //

typedef matrix2 mat2;

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix2 operator* (const float s, const matrix2 &m);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const matrix2 &m1, const matrix2 &m2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const matrix2 &m1, const matrix2 &m2, const float e = APPROX_EPSILON);

// nice matrix2
inline const bool nice(const matrix2 &m);

// finite matrix2
inline const bool finite(const matrix2 &m);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
    inline std::ostream &operator<< (std::ostream &lhs, const matrix2 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "matrix2.inl"

#endif // __GEA_MTH_VECTOR_MATRIX2_H__ //
