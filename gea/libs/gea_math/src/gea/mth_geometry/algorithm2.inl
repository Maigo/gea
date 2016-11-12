namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// common                                                                    //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// rectangle2                                                                //
// ------------------------------------------------------------------------- //

inline const bool contains(const mth::rectangle2 &a, const mth::rectangle2 &b) {
    return (a.x <= b.x) && (a.y <= b.y) && (b.x + b.width) <= (a.x + a.width) && (b.y + b.height) <= (a.y + a.height);
}

inline const bool contains(const mth::rectangle2 &a, const mth::rectangle2 &b, ignore_position_t) {
    return (a.width >= b.width) && (a.height >= b.height);
}

} // namespace mth //
} // namespace gea //
