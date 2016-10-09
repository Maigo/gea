#ifndef __GEA_MATH_GEOMETRY_POLYGON2_h__
#define __GEA_MATH_GEOMETRY_POLYGON2_h__

#include <vector>

#include <gea/mth_vector/point2.h>
#include <gea/mth_vector/vector2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polygon                                                                   //
// ------------------------------------------------------------------------- //

class polygon2 {
public:
// ------------------------------------------------------------------------- //
    class modify_t {
    public:
        typedef std::vector<point2> points_type;
        typedef points_type::size_type size_type;

        inline void reserve(const size_type count);

        inline void add_point(const point2 &p);
        inline void add_point(const vector2 &v);

    private:
        friend class polygon2;
        inline modify_t() {}

        points_type m_points;
    };
// ------------------------------------------------------------------------- //

    typedef modify_t::points_type points_type;
    typedef modify_t::size_type size_type;

    inline polygon2();

    inline modify_t &modify();
    inline const modify_t &modify() const;

    inline const size_type size() const;
    inline const bool empty() const;

    const float circumference() const;
    const float area() const;

    inline const point2 &operator [](const size_type i) const;
    inline const points_type &points() const;

private:
    modify_t m_container;
};

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "polygon2.inl"

#endif // __GEA_MATH_GEOMETRY_POLYGON2_h__ //
