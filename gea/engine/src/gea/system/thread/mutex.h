#ifndef __GEA_MUTEX_H__
#define __GEA_MUTEX_H__

// gea includes
#include <gea/engine/system/thread/parallel.h>

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// mutex                                                                     //
// ------------------------------------------------------------------------- //
class mutex {
public:
    static const uint32_t DEFAULT_SPIN_COUNT = 4000;

    // constructors
    inline mutex();
    inline explicit mutex(uint32_t spin_count);
    inline explicit mutex(const mutex& o);
    inline ~mutex();

    // thread functions
    inline bool lock();
    inline bool try_lock();
    inline bool unlock();
    inline bool is_locked() const;

    // mutator functions
    inline const mutex& operator =(const mutex& o);
    inline void set_spin_count(uint32_t spin_count);
    inline uint32_t get_spin_count() const;

private:
    inline void init();

    internal::critical_section m_mutex;
    uint32_t                   m_spin_count;
    bool                       m_locked;
};

// ------------------------------------------------------------------------- //
// mutex_holder                                                              //
// ------------------------------------------------------------------------- //
class mutex_holder {
public:
    // constructors
    inline mutex_holder( mutex& m );
    inline ~mutex_holder();

    // early release
    inline void release();

private:
    DISALLOW_COPY_AND_ASSIGN(mutex_holder);

    mutex* m_mutex_ptr;
};

} // namespace prl //
} // namespace gea //

#include "mutex.inl"

#endif // __GEA_MUTEX_H__ //
