
// sfmt includes
extern "C" {
    #include "SFMT.h"
}

// header include
#include "random.h"

namespace gea {

// global functions
void     random_init(uint32_t seed) { init_gen_rand(seed); }
float    random_float() { return gen_rand32() * (1.0f/4294967295.0f); }
double   random_double(){ return gen_rand32() * (1.0 /4294967295.0 ); }
uint32_t random_uint32_t() { return gen_rand32(); }
uint64_t random_uint64_t() { return gen_rand64(); }

} // namespace gea //
