#ifndef __GEA_CPU_TOPOLOGY_AMD_H__
#define __GEA_CPU_TOPOLOGY_AMD_H__

// local gea includes
#include "cpu_topology.h"

namespace gea {
namespace cpu {
namespace amd {

// ------------------------------------------------------------------------- //
// amd topology configuration functions                                      //
// ------------------------------------------------------------------------- //
// error codes
typedef int32_t err_code_t;
static const err_code_t AMD_OK                =  0;
static const err_code_t AMD_HARDWARE_ERROR    = -1;

// ------------------------------------------------------------------------- //
// amd cpu interface                                                         //
// ------------------------------------------------------------------------- //
class cpu_interface_amd : public cpu_interface {
public:
    virtual ~cpu_interface_amd() {}

    virtual void configure();
    virtual apic get_apic() const;

private:
};

} // namespace amd //
} // namespace cpu //
} // namespace gea //

#include "cpu_topology_amd.inl"

#endif // __GEA_CPU_TOPOLOGY_AMD_H__ //
