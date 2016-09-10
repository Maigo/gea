#ifndef __GEA_MTH_GRAPH_SAMPLER_H__
#define __GEA_MTH_GRAPH_SAMPLER_H__

// stl includes
#include <assert.h>
#include <vector>

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/point2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// sampler                                                                   //
// ------------------------------------------------------------------------- //
class sampler
{
public:
    typedef const float(*graph_func)(const float x);

    static void sample(const float min, const float max, const float step, graph_func function, std::vector<point2> &out_points);
};

} // namespace mth //
} // namespace gea //

#include "sampler.inl"

#endif // __GEA_MTH_GRAPH_SAMPLER_H__ //
