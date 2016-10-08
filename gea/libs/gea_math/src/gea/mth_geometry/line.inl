
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// line2                                                                     //
// ------------------------------------------------------------------------- //

inline line2::line2() {}

// ------------------------------------------------------------------------- //

inline line2::modify_t &line2::modify() { return m_container; }

// ------------------------------------------------------------------------- //

inline const line2::modify_t &line2::modify() const { return m_container; }

// ------------------------------------------------------------------------- //

inline const line2::size_type line2::size() const { return m_container.m_points.size(); }

// ------------------------------------------------------------------------- //

inline const bool line2::empty() const { return m_container.m_points.empty(); }

// ------------------------------------------------------------------------- //

inline const float line2::length() const
{
    const modify_t::points_type &points = m_container.m_points;

    float length = 0.0f;
    for (int i = 1, e = points.size(); i < e; ++i) {
        length += points[i - 1].to(points[i]).length();
    }
    return length;
}

// ------------------------------------------------------------------------- //

inline const line2::points_type &line2::points() const { return m_container.m_points; }

// ------------------------------------------------------------------------- //
// line2::modify_t                                                           //
// ------------------------------------------------------------------------- //

inline void line2::modify_t::reserve(const line2::size_type count)
{
    m_points.reserve(count);
}

// ------------------------------------------------------------------------- //

inline void line2::modify_t::add_point(const point2 &p)
{
    m_points.push_back(p);
}

// ------------------------------------------------------------------------- //

inline void line2::modify_t::add_point(const vector2 &v)
{
    assert(!m_points.empty() && "trying to line to empty line!");
    m_points.push_back(m_points.back() + v);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
