#ifndef __GEA_MTH_GEOMETRY_RECTANGLE2_H__
#define __GEA_MTH_GEOMETRY_RECTANGLE2_H__

#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// rectangle2                                                                //
// ------------------------------------------------------------------------- //

class rectangle2 {
public:
    inline rectangle2();
    inline rectangle2(const point2 &nw_corner, const point2 &se_corner);
    inline rectangle2(const point2 &nw_corner, const vector2 &size);
    inline explicit rectangle2(skip_initialization);
    inline rectangle2(const rectangle2 &o);

    inline const float x() const;
    inline const float y() const;
    inline const float width() const;
    inline const float height() const;

    inline const point2 &nw_corner() const;
    inline const point2 &se_corner() const;

private:
    point2 m_nw_corner;
    point2 m_se_corner;
};

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "rectangle2.inl"

#endif // __GEA_MTH_GEOMETRY_RECTANGLE2_H__ //
