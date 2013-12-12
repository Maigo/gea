
// external gea includes
#include <external/hash/hash.h>
#include <external/static_hash/static_hash.h>

// local gea includes
#include "cpu_cpuid.h"
#include "cpu_topology.h"

namespace gea {
namespace cpu {

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
uint32_t get_vendor_id() {
    // cpu id struct
    cpuid_info leaf0;

    // fetch standard 0
    ci_cpuid(&leaf0, STANDARD_0);
//    uint32_t s_leaf_size = leaf0.eax;

    // detect vendor
    char vendor_id[16] = {0};
    uint32_t* vendor_id_u32 = reinterpret_cast<uint32_t*>(vendor_id);
    vendor_id_u32[0] = leaf0.ebx;
    vendor_id_u32[1] = leaf0.edx;
    vendor_id_u32[2] = leaf0.ecx;
    vendor_id_u32[3] = 0;

    // convert to hash value
    return gea::g_hash32(vendor_id_u32, 12);
}

} // namespace cpu //
} // namespace gea //
