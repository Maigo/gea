namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// rectangle2                                                                //
// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2() : x(0.0f), y(0.0f), width(0.0f), height(0.0f) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const float x, const float y, const float width, const float height) : x(x), y(y), width(width), height(height) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const point2 &nw_corner, const point2 &se_corner) : x(nw_corner.x), y(nw_corner.y), width(se_corner.x - nw_corner.x), height(se_corner.y - nw_corner.y) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const point2 &nw_corner, const vector2 &size) : x(nw_corner.x), y(nw_corner.y), width(size.x), height(size.y) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(skip_initialization) {}

// ------------------------------------------------------------------------- //

inline rectangle2::rectangle2(const rectangle2 &o) : x(o.x), y(o.y), width(o.width), height(o.height) {}

// ------------------------------------------------------------------------- //

inline const float rectangle2::circumference() const {
    return (2.0f * width + 2.0f * height);
}

// ------------------------------------------------------------------------- //

inline const float rectangle2::area() const {
    return (width * height);
}

// ------------------------------------------------------------------------- //

inline const point2 rectangle2::nw_corner() const {
    return point2(x, y);
}

// ------------------------------------------------------------------------- //

inline const point2 rectangle2::se_corner() const {
    return point2(x + width, y + height);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
