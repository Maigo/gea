#ifndef __GEA_TASK_MANAGER_H__
#define __GEA_TASK_MANAGER_H__

// gea includes
#include <core/parallel/task.h>
#include <core/pattern/singleton.h>

#include <gea/system/thread/parallel.h>
#include <gea/system/thread/thread.h>

namespace gea {
namespace prl {

typedef uint32_t taskid_t;

//DEGUG
template <class T>
class list {
public:
    list();
    inline void allocator(void *a) {}
    inline void reserve(const uint32_t &num) {}

    inline void add(const T &t);
};

template <class T>
class vector {
public:
    vector();
    inline void allocator(void *a) {}
    inline void reserve(const uint32_t &num) {}
    inline void push_back(const T &t) {}

    inline T operator[] (int i);
    inline const T operator[] (int i) const;
};

// ------------------------------------------------------------------------- //
// task                                                                      //
// ------------------------------------------------------------------------- //
struct task {
    taskid_t m_taskid;     // 0x00
    uint32_t m_priority;   // 0x

    void    *m_work;       // 0x

    // pad to 16 byte border
    uint8_t  m_pad[
        16 - sizeof(taskid_t)
           - sizeof(uint32_t)
           - sizeof(void *)];
};

// ------------------------------------------------------------------------- //
// task_thread                                                               //
// ------------------------------------------------------------------------- //
class task_thread : public runnable {
public:
    task_thread(const affinity_mask &affinity_mask);
    ~task_thread();

    // thread functions
    inline void start();
    inline void stop();

    // runnable interface
    virtual uint32_t main();
private:
    thread  m_thread;
};

// ------------------------------------------------------------------------- //
// task_manager                                                              //
// ------------------------------------------------------------------------- //
class task_manager : public singleton<task_manager> {
public:
    static const size_t TASK_QUEUE_SIZE = 200;

    task_manager();
    ~task_manager();

    void init();
    void finalize();

    void add_task(const task &t);

private:
    void fork_consumers() const;
    void quit_consumers() const;


    list<task>            m_task_queue;
    list<taskid_t>        m_open_taskids;
    vector<task_thread *> m_consumers;
};

} // namespace prl //
} // namespace gea //

#include "task_manager.inl"

#endif // __GEA_TASK_MANAGER_H__ //
