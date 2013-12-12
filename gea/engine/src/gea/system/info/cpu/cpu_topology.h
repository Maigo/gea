#ifndef __GEA_CPU_TOPOLOGY_H__
#define __GEA_CPU_TOPOLOGY_H__

namespace gea {
namespace cpu {

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
uint32_t get_vendor_id();

// ------------------------------------------------------------------------- //
// cpu interface                                                             //
// ------------------------------------------------------------------------- //
struct apic {
    uint32_t smt, core, pkg;
};

class cpu_interface {
public:
    virtual void configure() = 0;
    virtual apic get_apic() const = 0;
};

} // namespace cpu //
} // namespace gea //

#endif // __GEA_CPU_TOPOLOGY_H__ //
