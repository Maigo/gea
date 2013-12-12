
// gea includes
#include <gea/system/info/cpu.h>

#include "task_manager.h"

namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// task_thread                                                               //
// ------------------------------------------------------------------------- //
task_thread::task_thread(const affinity_mask &affinity_mask)
    : m_thread(this, affinity_mask)
{
    // construct new thread (in suspended state)
    m_thread.construct();
}
task_thread::~task_thread() {}

uint32_t task_thread::main() {
    //TODO:: add something here

    return 0;
}

// ------------------------------------------------------------------------- //
// task_manager                                                              //
// ------------------------------------------------------------------------- //
task_manager::task_manager() {
    //
}
task_manager::~task_manager() {}

void task_manager::init() {
    
    //TODO* get allocator
    // pool_allocator<sizeof(task)>
    m_task_queue.allocator( NULL );
    m_task_queue.reserve( TASK_QUEUE_SIZE );

    //TODO* get allocator
    // pool_allocator<sizeof(taskid_t)>
    m_open_taskids.allocator( NULL );
    m_open_taskids.reserve( TASK_QUEUE_SIZE );

    // get hardware thread count
    cpu::cpu_manager &cpu = cpu::cpu_manager::get();
    uint32_t hwt = cpu.get_smt_size();

    // allocate task consumers
    m_consumers.allocator( NULL );
    m_consumers.reserve(hwt);

    // initialize consumers based on SMT
    for (uint32_t i=0; i<hwt; ++i) {
        const affinity_mask &affinity_mask = cpu.get_smt(i).get_affinity_mask();
        task_thread *tt = new task_thread(affinity_mask);
        m_consumers.push_back(tt);
    }

    // start new threads
    for (uint32_t i=0; i<hwt; ++i)
        m_consumers[i]->start();
}
void task_manager::finalize() {
    //TODO: delete pool_allocator(s)
}

void task_manager::add_task(const task &t) {
    m_task_queue.add(t);
}

void task_manager::fork_consumers() const {

}
void task_manager::quit_consumers() const {

}

} // namespace prl //
} // namespace gea //
