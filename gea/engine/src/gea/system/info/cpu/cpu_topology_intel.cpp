
// local gea includes
#include "cpu_cpuid.h"
// header include
#include "cpu_topology_intel.h"

namespace gea {
namespace cpu {
namespace intel {

// ------------------------------------------------------------------------- //
// intel topology configuration functions                                    //
// ------------------------------------------------------------------------- //

uint32_t cpu_apicid(const topology_params& params) {
    cpuid_info  data;

    if (params.apic_mode == INTEL_X2APIC_MODE) {
        ci_cpuid(&data, STANDARD_B);
        return data.edx;
    }
    ci_cpuid(&data, STANDARD_1);
    return bits(data.ebx, 24,31);
}

err_code_t cpu_topology_params_0Bh(topology_params& params) {
    // initial error code
    err_code_t err = INTEL_OK;

    cpuid_info data;

    // test support
    if (params.max_st_leaf >= 0xB) {
        ci_cpuid(&data, STANDARD_B, 0);
        if (data.ebx == 0) return INTEL_0BH_NOT_SUPPORTED;
    }

    uint32_t subleaf = 0;
    uint32_t level_type, level_shift;
    bool has_smt = false, has_core = false;

    // temp param
    uint32_t core_smt_mask;

    do {
        ci_cpuid(&data, STANDARD_B, subleaf);
        // if EBX == 0 subleaf is invalid
        if (data.ebx == 0)
            break;

        level_type  = bits(data.ecx, 8,15);
        level_shift = bits(data.eax, 0, 4);

        switch(level_type) {
        case 1: // SMT level type: level_shift is the smt mask width
            params.apic_smt_mask   = ~((~0u) << level_shift);
            params.apic_core_shift = level_shift;
            has_smt = true;
            break;
        case 2: // core level type: level_shift is the core and smt mask width combined
            core_smt_mask         = ~((~0u) << level_shift);
            params.apic_pkg_mask  = ~(core_smt_mask);
            params.apic_pkg_shift = level_shift;
            has_core = true;
            break;
        default:
            break;
        }
        ++subleaf;
    } while(1);

    if (has_smt && has_core) {
        params.apic_core_mask  = core_smt_mask ^ params.apic_smt_mask;
    } else if (has_smt && !has_core) {
        params.apic_core_mask  = 0;
        params.apic_pkg_mask  = ~(params.apic_smt_mask);
        params.apic_pkg_shift = params.apic_core_shift;
    } else {
        err = INTEL_HARDWARE_ERROR;
    }

    // set x2apic mode
    params.apic_mode = INTEL_X2APIC_MODE;

    // return error code
    return err;
}

err_code_t cpu_topology_params_04h(topology_params& params) {
    // initial error code
    err_code_t err = INTEL_OK;

    cpuid_info  data;
    ci_cpuid(&data, STANDARD_1);

    uint32_t coreid_max_count = 1;
    uint32_t smtid_per_core_max_count = 1;

    uint32_t core_smt_max_count = bits(data.ebx, 16,23);

    // case 1: leaf 04h sets max # CoreIDs that's allocated in a package
    if (params.max_st_leaf >= 0x4) {
        ci_cpuid(&data, STANDARD_4);

        coreid_max_count = bits(data.eax, 26,31) + 1;
        smtid_per_core_max_count = core_smt_max_count / coreid_max_count;
    // case 2: no support for leaf 04h revert to 1 core per package
    } else {
        coreid_max_count = 1;
        smtid_per_core_max_count = core_smt_max_count / coreid_max_count;
    }

    params.apic_smt_mask   = mask(smtid_per_core_max_count, &params.apic_core_shift);
    params.apic_core_mask  = mask(coreid_max_count, &params.apic_pkg_shift) << params.apic_core_shift;
    params.apic_pkg_mask   = ~(params.apic_smt_mask | params.apic_core_mask);
    params.apic_pkg_shift += params.apic_core_shift;

    // set legacy apic mode
    params.apic_mode = INTEL_LEGACY_APIC_MODE;

    // return error code
    return err;
}

err_code_t cpu_topology_params(topology_params& params) {
    // initial error code
    err_code_t err = INTEL_OK;

    cpuid_info  data;

    // get standard and extended leaf numbers
    ci_cpuid(&data, STANDARD_0);
    params.max_st_leaf = data.eax;
    ci_cpuid(&data, EXTENDED_0);
    params.max_ex_leaf = data.eax;

    ci_cpuid(&data, STANDARD_1);
    bool htt = bits(data.edx, 28,28) != 0;
    // case 1-2: smt compliant processor
    if (htt) {
        // case 1: try derive using x2APIC
        if (cpu_topology_params_0Bh(params) != INTEL_OK)
            // case 2: else rever to legacy APIC
            if (cpu_topology_params_04h(params) != INTEL_OK)
                err = INTEL_HARDWARE_ERROR;
    } else { // case 3: before smt, one logical processor in one physical package
        params.apic_smt_mask   = 0;
        params.apic_core_mask  = 0;
        params.apic_core_shift = 0;
        params.apic_pkg_mask   = (~0u);
        params.apic_pkg_shift  = 0;
        params.apic_mode = INTEL_EMULATED_APIC_MODE;
    }

    // return error code
    return err;
}

// ------------------------------------------------------------------------- //
// intel cpu interface                                                       //
// ------------------------------------------------------------------------- //
void cpu_interface_intel::configure() {
    if (cpu_topology_params(m_params) == INTEL_OK) {
        // do nothing
    } else {
        //TODO: handle error
    }
}

apic cpu_interface_intel::get_apic() const {
    uint32_t raw_apic = cpu_apicid(m_params);

    apic a;
    a.smt  = raw_apic >> (0);
    a.core = raw_apic >> (m_params.apic_core_shift);
    a.pkg  = raw_apic >> (m_params.apic_core_shift + m_params.apic_pkg_shift);
    return a;
}

} // namespace intel //
} // namespace cpu //
} // namespace gea //
