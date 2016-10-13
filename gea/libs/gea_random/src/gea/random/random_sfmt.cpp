
// header include
#include "random.h"

// sfmt includes
#include "SFMT.h"

namespace gea {

// internal data
sfmt_t g_sfmt;

// global functions
void           random_init(uint32_t seed) { sfmt_init_gen_rand(&g_sfmt, seed); }
const float    random_float() { return random_uint32_t() * (1.0f / float(4294967296)); }
const double   random_double(){ return random_uint32_t() * (1.0 / double(4294967296)); }
const uint32_t random_uint32_t() { return sfmt_genrand_uint32(&g_sfmt); }
const uint64_t random_uint64_t() { return sfmt_genrand_uint64(&g_sfmt); }

} // namespace gea //
