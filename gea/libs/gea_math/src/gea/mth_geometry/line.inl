
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// line2                                                                     //
// ------------------------------------------------------------------------- //

inline line2::line2() {}

inline const line2::size_type line2::size() const { return m_points.size(); }
inline const float line2::length() const
{
    float length = 0.0f;
    for (int i = 1, e = m_points.size(); i < e;  ++i) {
        length += m_points[i - 1].to(m_points[i]).length();
    }
    return length;
}

inline const line2::points_type &line2::points() const { return m_points; }

// ------------------------------------------------------------------------- //
// line2_builder                                                             //
// ------------------------------------------------------------------------- //

inline line2_builder::line2_builder(line2 &line)
    : m_line(line)
{}

// ------------------------------------------------------------------------- //

inline line2_builder &line2_builder::reserve(const line2::size_type count)
{
    m_line.m_points.reserve(count);
    return (*this);
}

// ------------------------------------------------------------------------- //

inline line2_builder &line2_builder::at_point(const point2 &p)
{
    m_line.m_points.push_back(p);
    return (*this);
}

// ------------------------------------------------------------------------- //

inline line2_builder &line2_builder::to_point(const vector2 &v)
{
    assert(!m_line.m_points.empty() && "trying to line to empty line!");
    m_line.m_points.push_back(m_line.m_points.back() + v);
    return (*this);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
