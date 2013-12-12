namespace gea {

// ------------------------------------------------------------------------- //
// random_generator                                                          //
// ------------------------------------------------------------------------- //
inline random_generator::random_generator(uint32_t seed) : m_seed(seed) {
    random_init(m_seed);
}

// reseed
inline void random_generator::seed(uint32_t seed) {
    m_seed = seed;
    random_init(m_seed);
}
inline const uint32_t random_generator::seed() const { return m_seed; }
inline void random_generator::reseed() const { random_init(m_seed); }

// core random functions
inline float random_generator::rfloat() const    { reseed(); return random_float(); }
inline float random_generator::rfloat(float max) { reseed(); return max * random_float(); }
inline float random_generator::rfloat(float min, float max) {
    reseed(); return min + (max - min) * random_float();
}

inline double random_generator::rdouble() const { reseed(); return random_double(); }
inline double random_generator::rdouble(double max) { reseed(); return max * random_double(); }
inline double random_generator::rdouble(double min, double max) {
    reseed(); return min + (max - min) * random_double();
}

inline uint32_t random_generator::ruint32_t() const { reseed(); return random_uint32_t(); }
inline uint32_t random_generator::ruint32_t(uint32_t max) {
    reseed(); return (uint32_t)((float) max * random_float());
}
inline uint32_t random_generator::ruint32_t(uint32_t min, uint32_t max) {
    reseed(); return (uint32_t) ((float) max + (float) (max - min) * random_float());
}

inline uint64_t random_generator::ruint64_t() const { reseed(); return random_uint64_t(); }
inline uint64_t random_generator::ruint64_t(uint64_t max) {
    reseed(); return (uint64_t) ((double) max * random_double());
}
inline uint64_t random_generator::ruint64_t(uint64_t min, uint64_t max) {
    reseed(); return (uint64_t) ((double) max + (double) (max - min) * random_double());
}

// convenience random functions
inline bool random_generator::flip() const {
    reseed(); return (0.5f < random_float());
}

} // namespace gea //
