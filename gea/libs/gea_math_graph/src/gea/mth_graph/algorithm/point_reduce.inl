namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point_reduce: rdp (Ramer-Douglas-Peucker)                                 //
// ------------------------------------------------------------------------- //

inline void point_reduce_rdp::point_reduce(const line2 &line, const float epsilon, line2 &out_line)
{
    assert((epsilon > 0) && "invalid parameters!");
    point_reduce(line.points(), epsilon, out_line.modify().points());
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
