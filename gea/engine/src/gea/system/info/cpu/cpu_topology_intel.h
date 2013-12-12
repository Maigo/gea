#ifndef __GEA_CPU_TOPOLOGY_INTEL_H__
#define __GEA_CPU_TOPOLOGY_INTEL_H__

#include "cpu_topology.h"

namespace gea {
namespace cpu {
namespace intel {

// ------------------------------------------------------------------------- //
// intel topology configuration functions                                    //
// ------------------------------------------------------------------------- //
// error codes
typedef int32_t err_code_t;
static const err_code_t INTEL_OK                =  0;
static const err_code_t INTEL_HARDWARE_ERROR    = -1;
static const err_code_t INTEL_0BH_NOT_SUPPORTED = -2;

// topology constants
static const uint32_t INTEL_EMULATED_APIC_MODE = 0;
static const uint32_t INTEL_LEGACY_APIC_MODE   = 1;
static const uint32_t INTEL_X2APIC_MODE        = 2;

// topopogy constants structure
struct topology_params {
    uint32_t max_st_leaf;
    uint32_t max_ex_leaf;

    uint32_t apic_smt_mask;
    uint32_t apic_core_shift;
    uint32_t apic_core_mask;
    uint32_t apic_pkg_shift;
    uint32_t apic_pkg_mask;

    uint32_t apic_mode;
};

uint32_t cpu_apicid(const topology_params& params);
err_code_t cpu_topology_params(topology_params& params);

// ------------------------------------------------------------------------- //
// intel cpu interface                                                       //
// ------------------------------------------------------------------------- //
class cpu_interface_intel : public cpu_interface {
public:
    virtual ~cpu_interface_intel() {}

    virtual void configure();
    virtual apic get_apic() const;

private:
    topology_params m_params;
};

} // namespace intel //
} // namespace cpu //
} // namespace gea //

#include "cpu_topology_intel.inl"

#endif // __GEA_CPU_TOPOLOGY_INTEL_H__ //
