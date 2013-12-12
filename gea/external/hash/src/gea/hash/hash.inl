
namespace gea {

// ------------------------------------------------------------------------- //
// hash_generator                                                            //
// ------------------------------------------------------------------------- //
// constructors
inline hash_generator::hash_generator(uint32_t seed) : m_seed(seed) {}

// (re)seed
inline const uint32_t hash_generator::seed() const { return m_seed; }
inline void hash_generator::seed(uint32_t seed) { m_seed = seed; }
inline void hash_generator::reseed() const {}

// hash functions
const hash32_t hash_generator::h32(const void *data, size_t length) const {
    uint32_t hash;
    gea::hash32(data, length, seed(), &hash);
    return hash;
}
const hash64_t hash_generator::h64(const void *data, size_t length) const {
    uint64_t hash;
    gea::hash64(data, length, seed(), &hash);
    return hash;
}

} // namespace gea //
