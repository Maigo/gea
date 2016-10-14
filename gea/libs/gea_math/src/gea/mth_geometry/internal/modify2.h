#ifndef __GEA_MATH_GEOMETRY_MODIFY2_H__
#define __GEA_MATH_GEOMETRY_MODIFY2_H__

#include <vector>

#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

class line2;
class polygon2;

namespace internal {

// ------------------------------------------------------------------------- //
// modify2                                                                   //
// ------------------------------------------------------------------------- //

class modify2 {
public:
    typedef std::vector<point2>         pointset_type;
    typedef pointset_type::size_type    size_type;

    inline void reserve(const size_type count);

    inline void add_point(const point2 &p);
    inline void add_point(const vector2 &v);

    inline       pointset_type &points();
    inline const pointset_type &points() const;

private:
    friend class ::gea::mth::line2;
    friend class ::gea::mth::polygon2;

    inline modify2() {}

    pointset_type m_points;
};

// ------------------------------------------------------------------------- //

} // namespace internal //
} // namespace mth //
} // namespace gea //

#include "modify2.inl"

#endif // __GEA_MATH_GEOMETRY_MODIFY2_H__ //
