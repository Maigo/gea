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
    // ------------------------------------------------------------------------- //

    class modify_t {
    public:
        typedef std::vector<point2> points_type;
        typedef points_type::size_type size_type;

        inline void reserve(const size_type count);

        inline void add_point(const point2 &p);
        inline void add_point(const vector2 &v);

    private:
        friend class line2;
        inline modify_t() {}

        points_type m_points;
    };

    // ------------------------------------------------------------------------- //

    typedef modify_t::points_type points_type;
    typedef modify_t::size_type size_type;

    inline line2();

    inline modify_t &modify();
    inline const modify_t &modify() const;

    inline const size_type size() const;
    inline const bool empty() const;

    inline const float length() const;

    inline const points_type &points() const;

private:
    modify_t m_container;
};

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "line.inl"

#endif // __GEA_MTH_GEOMETRY_LINE2_H__ //
