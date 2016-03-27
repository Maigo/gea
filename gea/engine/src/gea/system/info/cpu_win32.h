#ifndef __GEA_CPU_WIN32_H__
#define __GEA_CPU_WIN32_H__

#ifdef WIN32

// gea includes
#include <gea/core/memory/allocator.h>
#include <gea/core/pattern/singleton.h>
#include <gea/system/info/cpu/cpu_topology.h>
#include <gea/system/thread/parallel.h>

// gea stl includes
//#include <gea/core/collection/vector.h>

namespace gea {
namespace cpu {

// ------------------------------------------------------------------------- //
// topology                                                                  //
// ------------------------------------------------------------------------- //
class topology_base {
public:
    inline topology_base(const prl::affinity_mask& affinity_mask, uint32_t apic_lvl_id, uint32_t ordnal_number);
    inline void add_affinity_mask(const prl::affinity_mask& affinity_mask);
    inline const prl::affinity_mask& get_affinity_mask() const;
    inline uint32_t get_apic_lvl_id() const;
    inline uint32_t get_ordinal_number() const;

private:
    prl::affinity_mask m_affinity_mask;
    uint32_t           m_apic_lvl_id;
    uint32_t           m_ordnal_number;
};

// smt topology (level-0)
class topology_smt : public topology_base {
public:
    inline topology_smt(const prl::affinity_mask& affinity_mask, uint32_t apic_smt, uint32_t index);
};

// core topology (level-1)
class topology_core : public topology_base {
public:
    inline topology_core(const prl::affinity_mask& affinity_mask, uint32_t apic_core, uint32_t index);
};

// package topology (level-2)
class topology_package : public topology_base {
public:
    inline topology_package(const prl::affinity_mask& affinity_mask, uint32_t apic_pkg, uint32_t index);
};

// ------------------------------------------------------------------------- //
// cpu_manager                                                                //
// ------------------------------------------------------------------------- //
class cpu_manager : public singleton<cpu_manager> {
public:
    inline cpu_manager(gea::allocator *allocator);

    inline const uint32_t get_smt_size() const;
    inline const uint32_t get_core_size() const;
    inline const uint32_t get_pkg_size() const;

    inline const topology_smt&     get_smt(uint32_t index) const;
    inline const topology_core&    get_core(uint32_t index) const;
    inline const topology_package& get_pkg(uint32_t index) const;

    inline const topology_smt&     get_current_smt() const;
    inline const topology_core&    get_current_core() const;
    inline const topology_package& get_current_pkg() const;

    void configure();
    void shutdown();

private:
    void init_cpu();
    void register_lp(const prl::affinity_mask& affinity_mask, const apic& apic);

    inline topology_smt*     find_smt(uint32_t apic_smt) const;
    inline topology_core*    find_core(uint32_t apic_core) const;
    inline topology_package* find_pkg(uint32_t apic_pkg) const;

    // manager members
    gea::allocator *mp_allocator;

    //
    cpu::cpu_interface* m_icpu;

    // topology
    typedef gea::vector<topology_smt*>     smt_list;
    typedef gea::vector<topology_core*>    core_list;
    typedef gea::vector<topology_package*> pkg_list;
    smt_list  m_smts;
    core_list m_cores;
    pkg_list  m_pkgs;
};

} // namespace cpu //
} // namespace gea //

#include "cpu_win32.inl"

#endif // WIN32 //

#endif // __GEA_CPU_WIN32_H__ //
