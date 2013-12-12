#ifndef __GEA_THREAD_H__
#define __GEA_THREAD_H__

#include <gea/engine/system/thread/parallel.h>
#include <gea/engine/utility/state.h>

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// runnable                                                                  //
// ------------------------------------------------------------------------- //
class runnable {
public:
    virtual uint32_t main() = 0;
};

// ------------------------------------------------------------------------- //
// thread                                                                    //
// ------------------------------------------------------------------------- //
class thread : public utl::state_base<uint32_t> {
public:
    enum state {
        EMPTY = 0,
        RUNNING,
        PAUSED
    };

    // constructors
    inline thread(runnable *runnable);
    inline thread(runnable *runnable, const affinity_mask &thread_mask);
    // current thread
    inline static thread get_current_thread();
    // create
    inline thread fork(runnable *r);

    // thread functions
    inline bool construct();

    inline bool start();
    inline bool suspend();
    inline bool wait(uint32_t ms = INFINITE) const;
    inline bool kill();

    // thread affinity mask
    inline void set_thread_mask(const affinity_mask& affinity_mask);
    inline const affinity_mask& get_thread_mask() const;
    inline void inherit_process_mask();

private:
    inline thread();
    inline uint32_t main();

    static uint32_t entry_point(void *param);

    internal::thread m_thread;
    uint32_t         m_tid;
    runnable        *m_runnable;

    affinity_mask    m_thread_mask;
};

} // namespace prl //
} // namespacee gea //

#include "thread.inl"

#endif // __GEA_THREAD_H__ //
