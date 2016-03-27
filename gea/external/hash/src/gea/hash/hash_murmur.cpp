
// murmur includes
#include "MurmurHash3.h"

// header include
#include "hash.h"

namespace gea {

// global functions
void hash32(const void *data, int len, uint32_t seed, void *out) {
    MurmurHash3_x86_32(data, len, seed, out);
}
void hash64(const void *data, int len, uint32_t seed, void *out) {
    hash32_t gea_alignment(16) _hash[4];
    MurmurHash3_x86_128(data, len, seed, _hash);

    ( (hash32_t*) out)[0] = _hash[0];
    ( (hash32_t*) out)[1] = _hash[1];
}

} // namespace gea //
