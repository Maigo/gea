
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

inline const point2 &line2::operator [](const size_type i) const {
    assert(0 <= i && i < m_container.m_points.size() && "index out of bounds!");
    return m_container.m_points[i];
}

// ------------------------------------------------------------------------- //

inline const line2::points_type &line2::points() const { return m_container.m_points; }

// ------------------------------------------------------------------------- //
// line2::modify_t                                                           //
// ------------------------------------------------------------------------- //

inline void line2::modify_t::reserve(const size_type count)
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
