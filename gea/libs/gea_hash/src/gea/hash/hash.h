#ifndef __GEA_HASH_H__
#define __GEA_HASH_H__

#include <stdint.h>

namespace gea {

// ------------------------------------------------------------------------- //
// hash type definitions                                                     //
// ------------------------------------------------------------------------- //
typedef uint32_t hash32_t;
typedef uint64_t hash64_t;

// ------------------------------------------------------------------------- //
// hash_generator: class wrapper                                             //
// ------------------------------------------------------------------------- //
class hash_generator {
public:
    static const uint32_t DEFAULT_SEED = 0x00000000u;

    // constructor
    inline explicit hash_generator(uint32_t seed = DEFAULT_SEED);

    // (re)seed
    inline const uint32_t seed() const;
    inline void seed(uint32_t seed);
    inline void reseed() const;

    // hash functions
    inline const hash32_t h32(const void *data, size_t length) const;
    inline const hash64_t h64(const void *data, size_t length) const;

private:
    uint32_t m_seed;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
extern void hash32(const void *data, size_t length, uint32_t seed, void *out);
extern void hash64(const void *data, size_t length, uint32_t seed, void *out);

// ------------------------------------------------------------------------- //
// global instance                                                           //
// ------------------------------------------------------------------------- //
extern hash_generator g_hash;

} // namespace gea //

#include "hash.inl"

#endif // __GEA_HASH_H__ //
