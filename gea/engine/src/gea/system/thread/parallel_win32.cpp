
#include "parallel_win32.h"

namespace gea {
namespace prl {

namespace internal {

// ------------------------------------------------------------------------- //
// Global Functions                                                          //
// ------------------------------------------------------------------------- //
err_code_t get_process_affinity_mask(affinity_mask* process_affinity_mask, affinity_mask* system_affinity_mask) {
    err_code_t ret = GEA_OK;

    DWORD win_pam, win_sam;
    if (GetProcessAffinityMask(GetCurrentProcess(), &win_pam, &win_sam) != 0) {
        if (process_affinity_mask != NULL) process_affinity_mask->set_affinity_mask(win_pam);
        if (system_affinity_mask  != NULL) system_affinity_mask->set_affinity_mask(win_sam);
    } else {
        ret = GEA_THREAD_ERROR;
    }

    // return error code
    return ret;
}

err_code_t thread_bind_context(thread &t, const affinity_mask& affinity_mask) {
    err_code_t ret = GEA_OK;
    
    if ( SetThreadAffinityMask(t.m_handle,  affinity_mask.get_affinity_mask()) != 0 ) {
    } else {
	    ret = GEA_THREAD_ERROR;
    }

    // return error code
    return ret;
}

} // namespace internal //

} // namespace prl //
} // namespace gea //
