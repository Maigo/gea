#ifndef __GEA_MTH_GEOMETRY_LINE2_H__
#define __GEA_MTH_GEOMETRY_LINE2_H__

#include <vector>

#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// line2                                                                     //
// ------------------------------------------------------------------------- //

class line2 {
public:
    typedef std::vector<point2> points_type;
    typedef points_type::size_type size_type;

    inline line2();

    inline const size_type size() const;
    inline const float length() const;

    inline const points_type &points() const;

private:
    friend class line2_builder;
    points_type m_points;
};

// ------------------------------------------------------------------------- //
// line2_builder                                                             //
// ------------------------------------------------------------------------- //

class line2_builder
{
public:
    inline line2_builder(line2 &line);

    inline line2_builder &reserve(const line2::size_type count);

    inline line2_builder &at_point(const point2 &p);
    inline line2_builder &to_point(const vector2 &v);
private:
    line2 &m_line;
};

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "line.inl"

#endif // __GEA_MTH_GEOMETRY_LINE2_H__ //
