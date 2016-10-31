// gea includes
#include <gea/mth_core/limits.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// vector<point2>                                                            //
// ------------------------------------------------------------------------- //

inline const point2 bounds_low(const std::vector<point2> &points)
{
    float x = limits<float>::highest(), y = limits<float>::highest();
    for (const point2 &point : points) {
        x = min(point.x, x);
        y = min(point.y, y);
    }

    return point2(x, y);
}
inline const point2 bounds_high(const std::vector<point2> &points)
{
    float x = limits<float>::lowest(), y = limits<float>::lowest();
    for (const point2 &point : points) {
        x = max(point.x, x);
        y = max(point.y, y);
    }

    return point2(x, y);
}

} // namespace mth //
} // namespace gea //