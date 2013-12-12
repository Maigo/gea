#ifndef __GEA_SEMAPHORE_H__
#define __GEA_SEMAPHORE_H__

// gea includes
#include <gea/engine/system/thread/parallel.h>

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// semaphore                                                                 //
// ------------------------------------------------------------------------- //
class semaphore {
public:
    static const uint32_t MAX_COUNT = 99999999;

    // constructors
    inline explicit semaphore(int32_t init = 0, int32_t max_count = MAX_COUNT);
    inline explicit semaphore(const semaphore& o);
    inline ~semaphore();

    // thread functions
    inline bool wait(uint32_t ms = INFINITE);
    inline bool release();
    inline int32_t value() const;
    inline void reset(int32_t init = 0);

    // mutator functions
    inline const semaphore& operator =(const semaphore& o);

private:
    internal::semaphore m_semaphore;
    int32_t             m_max_count;
};

} // namespace prl //
} // namespace gea //

#include "semaphore.inl"

#endif // __GEA_SEMAPHORE_H__ //
