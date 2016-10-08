#ifndef __GEA_VMTH_LINEAR_TRANSFORM2_H__
#define __GEA_VMTH_LINEAR_TRANSFORM2_H__

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/matrix2.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// linear_transform2                                                         //
// ------------------------------------------------------------------------- //
class linear_transform2 {
public:
    // constructors
    inline linear_transform2();
    inline explicit linear_transform2(skip_initialization);
    inline linear_transform2(const matrix2 &transform, const vector2 &translation);

    // arithmetic
    inline linear_transform2 &operator =(const linear_transform2 &o);
    inline const vector2 operator* (const vector2 &v) const;
    inline const point2  operator* (const point2  &p) const;

//    static linear_transform2 from_translation(const vector2 &translation);

    // member access
    inline const matrix2 &get_transform() const;
    inline const vector2 &get_translation() const;

private:
    matrix2 m_transform;
    vector2 m_translation;

};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const linear_transform2 &m1, const linear_transform2 &m2, const float e = APPROX_EPSILON);
inline const bool approx_ne(const linear_transform2 &m1, const linear_transform2 &m2, const float e = APPROX_EPSILON);

// nice matrix2
inline const bool nice(const linear_transform2 &m);

// finite matrix2
inline const bool finite(const linear_transform2 &m);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
    inline std::ostream &operator<< (std::ostream &lhs, const linear_transform2 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "linear_transform2.inl"

#endif // __GEA_VMTH_LINEAR_TRANSFORM2_H__ //
