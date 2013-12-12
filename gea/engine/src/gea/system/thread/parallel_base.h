#ifndef __GEA_PARALLEL_BASE_H__
#define __GEA_PARALLEL_BASE_H__

namespace gea {

// ------------------------------------------------------------------------- //
// base_affinity_mask                                                        //
// ------------------------------------------------------------------------- //
class base_affinity_mask {
public:
    static const base_affinity_mask EMPTY;

    // constructors
    inline base_affinity_mask();
    inline ~base_affinity_mask();

    // modifiers
    inline void bit_set(uint32_t i);
    inline void bit_clear(uint32_t i);
    inline void clear();

    inline void extend(const base_affinity_mask& mask);

    // test
    inline bool test_bit(uint32_t i) const;
    inline bool test_subset(const base_affinity_mask& subset) const;

    inline bool operator ==(const base_affinity_mask& o) const;

    // attributes
    inline uint32_t num_bits_set() const;
    inline uint32_t size() const;

protected:
    // internal constructors
    inline base_affinity_mask(uint32_t raw_affinity_mask);
    // internal mutators
    inline void set_raw_affinity_mask(uint32_t raw_affinity_mask);
    inline uint32_t get_raw_affinity_mask() const;

private:
    template <class T> friend class base_affinity_mask_cutter;
    uint32_t m_affinity_mask;
};

// ------------------------------------------------------------------------- //
// affinity_mask_cutter                                                      //
// ------------------------------------------------------------------------- //
template <class T>
class base_affinity_mask_cutter {
public:
    base_affinity_mask_cutter(const T& affinity_mask);

    inline bool has_next() const;
    inline T next();

private:
    uint32_t m_affinity_mask;
};

} // namespace gea //

#include "parallel_base.inl"

#endif // __GEA_PARALLEL_BASE_H__ //
