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
    float x, y, width, height;

    inline rectangle2();
    inline rectangle2(const float x, const float y, const float width, const float height);
    inline rectangle2(const point2 &nw_corner, const point2 &se_corner);
    inline rectangle2(const point2 &nw_corner, const vector2 &size);
    inline explicit rectangle2(skip_initialization);
    inline rectangle2(const rectangle2 &o);

    inline const float circumference() const;
    inline const float area() const;

    inline const point2 nw_corner() const;
    inline const point2 se_corner() const;
};

// ------------------------------------------------------------------------- //

typedef rectangle2 rect2;

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "rectangle2.inl"

#endif // __GEA_MTH_GEOMETRY_RECTANGLE2_H__ //
