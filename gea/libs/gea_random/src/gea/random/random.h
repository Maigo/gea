#ifndef __GEA_RANDOM_H__
#define __GEA_RANDOM_H__

namespace gea {

// ------------------------------------------------------------------------- //
// random_generator: class wrapper                                           //
// ------------------------------------------------------------------------- //
class random_generator {
public:
    static const uint32_t DEFAULT_SEED = 0x00000000u;

    inline explicit random_generator(uint32_t seed = DEFAULT_SEED);

    // (re)seed
    inline void seed(uint32_t seed);
    inline const uint32_t seed() const;
    inline void reseed() const;

    // core random functions
    inline float rfloat() const;
    inline float rfloat(float max);
    inline float rfloat(float min, float max);

    inline double rdouble() const;
    inline double rdouble(double max);
    inline double rdouble(double min, double max);

    inline uint32_t ruint32_t() const;
    inline uint32_t ruint32_t(uint32_t max);
    inline uint32_t ruint32_t(uint32_t min, uint32_t max);

    inline uint64_t ruint64_t() const;
    inline uint64_t ruint64_t(uint64_t max);
    inline uint64_t ruint64_t(uint64_t min, uint64_t max);

    // convenience random functions
    inline bool flip() const;

private:
    uint32_t m_seed;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
extern void           random_init(uint32_t seed);
extern const float    random_float();
extern const double   random_double();
extern const uint32_t random_uint32_t();
extern const uint64_t random_uint64_t();

// ------------------------------------------------------------------------- //
// global instance                                                           //
// ------------------------------------------------------------------------- //
extern random_generator g_random;

} // namespace gea //

#include "random.inl"

#endif // __GEA_RANDOM_H__ //
