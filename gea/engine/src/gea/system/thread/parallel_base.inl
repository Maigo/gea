
// gea mth includes
#include <gea/bmth/bits.h>

// gea engine includes
#include <gea/system/memory.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// base_affinity_mask                                                        //
// ------------------------------------------------------------------------- //
// constructors
inline base_affinity_mask::base_affinity_mask() : m_affinity_mask(0) {}
inline base_affinity_mask::~base_affinity_mask() {}
// modifiers
inline void base_affinity_mask::bit_set(uint32_t i) {
    l_assert_msg(i < 32, "Index out of bounds!");
    m_affinity_mask |= 1 << i;
}
inline void base_affinity_mask::bit_clear(uint32_t i) {
    l_assert_msg(i < 32, "Index out of bounds!");
    m_affinity_mask ^=  1 << i;
}
inline void base_affinity_mask::clear() {
    m_affinity_mask = 0x0;
}
// test
inline bool base_affinity_mask::test_bit(uint32_t i) const {
    l_assert_msg(i < 32, "Index out of bounds!");
    return (m_affinity_mask & (1 << i)) != 0;
}
inline bool base_affinity_mask::test_subset(const base_affinity_mask& subset) const {
    return (subset.m_affinity_mask & m_affinity_mask) == subset.m_affinity_mask;
}
inline bool base_affinity_mask::operator ==(const base_affinity_mask& o) const {
    return m_affinity_mask == o.m_affinity_mask;
}
// attributes
inline uint32_t base_affinity_mask::num_bits_set() const {
	return gea::mth::bit::ones(m_affinity_mask);
}
inline uint32_t base_affinity_mask::size() const {
    return 8 * sizeof(m_affinity_mask); // = 32
}

// internal constructors
inline void base_affinity_mask::extend(const base_affinity_mask& affinity_mask) {
    m_affinity_mask |= affinity_mask.m_affinity_mask;
}
// internal mutators
inline base_affinity_mask::base_affinity_mask(uint32_t raw_affinity_mask)
    : m_affinity_mask(raw_affinity_mask) {}
inline void base_affinity_mask::set_raw_affinity_mask(uint32_t raw_affinity_mask) {
    m_affinity_mask = raw_affinity_mask;
}
inline uint32_t base_affinity_mask::get_raw_affinity_mask() const {
    return m_affinity_mask;
}

// ------------------------------------------------------------------------- //
// base_affinity_mask_cutter                                                 //
// ------------------------------------------------------------------------- //
template <class T>
inline base_affinity_mask_cutter<T>::base_affinity_mask_cutter(const T& affinity_mask)
    : m_affinity_mask(affinity_mask.m_affinity_mask) {}

template <class T>
inline bool base_affinity_mask_cutter<T>::has_next() const {
    return m_affinity_mask != 0;
}
template <class T>
inline T base_affinity_mask_cutter<T>::next() {
    uint32_t lbs = bit::lbs(m_affinity_mask);
    // remove lsb (at index)
    m_affinity_mask &= ~lbs;

    T affinity_mask;
    affinity_mask.set_raw_affinity_mask(lbs);
    return affinity_mask;
}

} // namespace gea //