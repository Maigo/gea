
// header include
#include "thread.h"

namespace gea {
namespace prl {

uint32_t thread::entry_point(void *param) {
    thread *t = static_cast<thread *>(param);
    l_assert_msg( t->is_state(EMPTY), "Invalid state transition");

    // execute associated runnable
    return t->main();
}

} // namespace prl //
} // namespace gea //
