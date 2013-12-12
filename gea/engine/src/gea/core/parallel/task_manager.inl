
namespace gea {
namespace prl {

// ------------------------------------------------------------------------- //
// task_thread                                                               //
// ------------------------------------------------------------------------- //
// thread functions
inline void task_thread::start() { m_thread.start(); }
inline void task_thread::stop() { m_thread.suspend(); }

} // namespace prl //
} // namespace gea //
