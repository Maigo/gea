
// external gea includes
#include <external/static_hash/static_hash.h>
// gea includes
#include <gea/engine/system/thread/thread.h>
#include <gea/engine/system/info/cpu/cpu_topology_amd.h>
#include <gea/engine/system/info/cpu/cpu_topology_intel.h>

// header include
#include "cpu_win32.h"

namespace gea {
namespace cpu {

// ------------------------------------------------------------------------- //
// cpu_manager                                                               //
// ------------------------------------------------------------------------- //
void cpu_manager::configure() {
    // init cpu interface if unknown
    if (m_icpu == NULL)
        init_cpu();

    // get current thread and thread mask
    prl::thread current_thread = prl::thread::get_current_thread();
    prl::affinity_mask pam = current_thread.get_thread_mask();

    // affinity mask cutter
    prl::affinity_mask_cutter cutter(pam);

    // determin max topology layer size
    //TODO: optimize
    uint32_t max = pam.num_bits_set();
    m_smts.reserve( max );
    m_cores.reserve( max );
    m_pkgs.reserve( max );

    // split process affinity mask into multiple masks
    prl::affinity_mask single_lp;
    while (cutter.has_next()) {
        single_lp = cutter.next();
        current_thread.set_thread_mask(single_lp);

        apic apic = m_icpu->get_apic();
        register_lp(single_lp, apic);
    }
    // reset thread affinity
    current_thread.set_thread_mask(pam);
}

void cpu_manager::shutdown() {
    // destroy cpu interface
    if (m_icpu != NULL)
        mp_allocator->make_delete<cpu_interface>(m_icpu);

    // destroy logical processor
    smt_list::iterator smt_it, smt_end = m_smts.end();
    for (smt_it = m_smts.begin(); smt_it != smt_end; ++smt_it)
        mp_allocator->make_delete<topology_smt>(*smt_it);
    // destroy processor core
    core_list::iterator core_it, core_end = m_cores.end();
    for (core_it = m_cores.begin(); core_it != core_end; ++core_it)
        mp_allocator->make_delete<topology_core>(*core_it);
    // destroy processor package
    pkg_list::iterator pkg_it, pkg_end = m_pkgs.end();
    for (pkg_it = m_pkgs.begin(); pkg_it != pkg_end; ++pkg_it)
        mp_allocator->make_delete<topology_package>(*pkg_it);
}


void cpu_manager::init_cpu() {
    uint32_t vendor_id  = cpu::get_vendor_id();

    switch (vendor_id) {
    case static_hash("GenuineIntel", 0xd3abe2b3):
        m_icpu = mp_allocator->make_new<cpu::intel::cpu_interface_intel>();
        m_icpu->configure();
        break;
    case static_hash("AuthenticAMD", 0x87875052):
        // do something
        //m_icpu = new cpu::amd::cpu_interface_amd();
        //m_icpu->configure();
        break;
    default:
        // do something
        //m_icpu = new cpu::cpu_interface_stub();
        break;
    }
}

void cpu_manager::register_lp(const prl::affinity_mask& affinity_mask, const apic& apic) {
    // register processor package
    topology_package* pkg = find_pkg(apic.pkg);
    if (pkg == NULL)  m_pkgs.push_back(pkg = mp_allocator->make_new<topology_package>(affinity_mask, apic.pkg, m_pkgs.size()));

    // register processor core
    topology_core* core = find_core(apic.core);
    if (core == NULL) m_cores.push_back(core = mp_allocator->make_new<topology_core>(affinity_mask, apic.core, m_cores.size()));

    // register logical processor
    topology_smt* smt = find_smt(apic.smt);
    if (smt == NULL)  m_smts.push_back(smt = mp_allocator->make_new<topology_smt>(affinity_mask, apic.smt, m_smts.size()));

    // propagate affinity mask through layers
    pkg->add_affinity_mask(affinity_mask);
    core->add_affinity_mask(affinity_mask);

    // construct hierarchy
    //TODO: add
}

} // namespace cpu //
} // namespace gea //