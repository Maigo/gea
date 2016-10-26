namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// polygon2                                                                  //
// ------------------------------------------------------------------------- //

inline polygon2::polygon2() {}

// ------------------------------------------------------------------------- //

inline internal::modify2 &polygon2::modify() { return m_container; }

// ------------------------------------------------------------------------- //

inline const internal::modify2 &polygon2::modify() const { return m_container; }

// ------------------------------------------------------------------------- //

inline const polygon2::size_type polygon2::size() const { return m_container.m_points.size(); }

// ------------------------------------------------------------------------- //

inline const bool polygon2::empty() const { return m_container.m_points.empty(); }

// ------------------------------------------------------------------------- //

inline const point2 &polygon2::operator [](const size_type i) const {
    l_assert_msg(0 <= i && i < m_container.m_points.size(), "index out of bounds!");
    return m_container.m_points[i];
}

// ------------------------------------------------------------------------- //

inline const polygon2::pointset_type &polygon2::points() const { return m_container.m_points; }

} // namespace mth //
} // namespace gea //
