#ifndef __GEA_VMTH_MATRIX3_H__
#define __GEA_VMTH_MATRIX3_H__

// mth includes
#include <gea/bmth/base.h>
#include <gea/vmth/vector3.h>

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
    inline matrix3(float xx, float yy, float zz);
    inline matrix3(float xx, float yx, float zx,
                   float xy, float yy, float zy,
                   float xz, float yz, float zz);
    inline matrix3(skip_initialization);
    inline matrix3(const matrix3 &o);
    inline explicit matrix3(const quaternion &q);
//    inline matrix3(float heading, float attitude, float bank);

    // arithmetic
    inline matrix3 &operator =(const matrix3 &o);
    inline const matrix3 operator+ (const matrix3 &o) const;
    inline const matrix3 operator- (const matrix3 &o) const;
    inline const matrix3 operator* (const matrix3 &o) const;
    inline const matrix3 operator* (float s) const;
    inline const matrix3 operator/ (float s) const;
    inline const vector3 operator* (const vector3 &v) const;
    // unary arithmetic
    inline const matrix3 operator+ () const;
    inline const matrix3 operator- () const;

    // member access
    inline const float operator() (int32_t i, int32_t j) const;
    inline const vector3 get_row(int32_t row) const;
    inline const vector3 get_column(int32_t col) const;

    // linear algebra
    inline const matrix3 transpose() const;
    inline const float trace() const;
    inline const float determinant() const;
    const matrix3 inverse() const;

    // conversion
    void from_quaternion(const quaternion &q);
    void to_quaternion(quaternion &q) const;
    void from_euler(float heading, float attitude, float bank);
    void to_euler(float &heading, float &attitude, float &bank);

    // static constants
    static const matrix3 IDENTITY;
    static const matrix3 ZERO;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic
inline const matrix3 operator* (float s, const matrix3 &m);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(const matrix3 &m1, const matrix3 &m2, float e = APPROX_EPSILON);
inline bool approx_ne(const matrix3 &m1, const matrix3 &m2, float e = APPROX_EPSILON);
// nice matrix3
inline bool nice(const matrix3 &m);
// finite matrix3
inline bool finite(const matrix3 &m);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &lhs, const matrix3 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "matrix3.inl"

#endif // __GEA_VMTH_MATRIX3_H__ //
