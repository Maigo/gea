
// header include
#include "sampler.h"

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// sampler                                                                   //
// ------------------------------------------------------------------------- //

void sampler::sample(const float min, const float max, const float step, graph_func function, std::vector<point2> &out_points)
{
    assert((min <= max) && (step > 0) && (function != nullptr) && "invalid parameters");

    for (float i = min; approx_leq(i, max); i += step)
    {
        const float x = i;
        const float y = function(x);
        out_points.push_back(point2(x, y));
    }
}

} // namespace mth //
} // namespace gea //
