namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// rectangle2                                                                //
// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2()
    : m_nw_corner()
    , m_se_corner() {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const point2 &nw_corner, const point2 &se_corner)
    : m_nw_corner(nw_corner)
    , m_se_corner(se_corner) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const point2 &nw_corner, const vector2 &size)
    : m_nw_corner(nw_corner)
    , m_se_corner(nw_corner.x + size.x, nw_corner.y + size.y) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(skip_initialization)
    : m_nw_corner(SKIP_INITIALIZATION)
    , m_se_corner(SKIP_INITIALIZATION) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const rectangle2 &o)
    : m_nw_corner(o.m_nw_corner)
    , m_se_corner(o.m_se_corner) {}

// ------------------------------------------------------------------------- //

inline const float rectangle2::x() const {
    return m_nw_corner.x;
}

// ------------------------------------------------------------------------- //

inline const float rectangle2::y() const {
    return m_nw_corner.y;
}

// ------------------------------------------------------------------------- //

inline const float rectangle2::width() const {
    return (m_se_corner.x - m_nw_corner.x);
}

// ------------------------------------------------------------------------- //

inline const float rectangle2::height() const {
    return (m_se_corner.y - m_nw_corner.y);
}

// ------------------------------------------------------------------------- //

inline const point2 &rectangle2::nw_corner() const {
    return m_nw_corner;
}

// ------------------------------------------------------------------------- //

inline const point2 &rectangle2::se_corner() const {
    return m_se_corner;
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
