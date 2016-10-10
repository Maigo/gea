#ifndef __GEA_MATH_GEOMETRY_POLYGON2_h__
#define __GEA_MATH_GEOMETRY_POLYGON2_h__

#include <gea/mth_geometry/internal/modify2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polygon                                                                   //
// ------------------------------------------------------------------------- //

class polygon2 {
public:
    typedef internal::modify2::points_type points_type;
    typedef internal::modify2::size_type   size_type;

    inline polygon2();

    inline       internal::modify2 &modify();
    inline const internal::modify2 &modify() const;

    inline const size_type size() const;
    inline const bool empty() const;

    const float circumference() const;
    const float area() const;

    inline const point2 &operator [](const size_type i) const;
    inline const points_type &points() const;

private:
    internal::modify2 m_container;
};

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "polygon2.inl"

#endif // __GEA_MATH_GEOMETRY_POLYGON2_h__ //
