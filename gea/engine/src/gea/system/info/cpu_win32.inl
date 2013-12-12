
namespace gea {
namespace cpu {

// ------------------------------------------------------------------------- //
// topology                                                                  //
// ------------------------------------------------------------------------- //
inline topology_base::topology_base(const prl::affinity_mask& affinity_mask, uint32_t apic_lvl_id, uint32_t ordnal_number)
    : m_affinity_mask(affinity_mask), m_apic_lvl_id(apic_lvl_id), m_ordnal_number(ordnal_number) {}
inline void topology_base::add_affinity_mask(const prl::affinity_mask& affinity_mask) { m_affinity_mask.extend(affinity_mask); }
inline const prl::affinity_mask& topology_base::get_affinity_mask() const { return m_affinity_mask; }
inline uint32_t topology_base::get_apic_lvl_id() const { return m_apic_lvl_id; }
inline uint32_t topology_base::get_ordinal_number() const { return m_ordnal_number; }

// smt topology (level-0)
topology_smt::topology_smt(const prl::affinity_mask& affinity_mask, uint32_t apic_smt, uint32_t index) : topology_base(affinity_mask, apic_smt, index) {}

// core topology (level-1)
topology_core::topology_core(const prl::affinity_mask& affinity_mask, uint32_t apic_core, uint32_t index) : topology_base(affinity_mask, apic_core, index) {}

// package topology (level-2)
topology_package::topology_package(const prl::affinity_mask& affinity_mask, uint32_t apic_pkg, uint32_t index) : topology_base(affinity_mask, apic_pkg, index) {}

// ------------------------------------------------------------------------- //
// cpu_manager                                                               //
// ------------------------------------------------------------------------- //

inline cpu_manager::cpu_manager(gea::allocator *allocator)
    : mp_allocator(allocator), m_icpu(NULL)
{
    // set internal vector members to use same allocator
    m_smts.set_allocator(allocator);
    m_cores.set_allocator(allocator);
    m_pkgs.set_allocator(allocator);
}

inline const uint32_t cpu_manager::get_smt_size() const  { return m_smts.size(); }
inline const uint32_t cpu_manager::get_core_size() const { return m_cores.size(); }
inline const uint32_t cpu_manager::get_pkg_size() const  { return m_pkgs.size(); }

inline const topology_smt& cpu_manager::get_smt(uint32_t index) const {
    l_assert_msg(index < m_smts.size(), "Index out of bounds!");
    return *m_smts[index];
}
inline const topology_core& cpu_manager::get_core(uint32_t index) const {
    l_assert_msg(index < m_cores.size(), "Index out of bounds!");
    return *m_cores[index];
}
inline const topology_package& cpu_manager::get_pkg(uint32_t index) const {
    l_assert_msg(index < m_pkgs.size(), "Index out of bounds!");
    return *m_pkgs[index];
}

inline const topology_smt& cpu_manager::get_current_smt() const {
    apic apic = m_icpu->get_apic();
    return *find_smt(apic.smt);
}
inline const topology_core& cpu_manager::get_current_core() const {
    apic apic = m_icpu->get_apic();
    return *find_core(apic.core);
}
inline const topology_package& cpu_manager::get_current_pkg() const {
    apic apic = m_icpu->get_apic();
    return *find_pkg(apic.pkg);
}

inline topology_smt* cpu_manager::find_smt(uint32_t apic_smt) const {
    smt_list::const_iterator it = m_smts.begin(), end = m_smts.end();
    for (; it != end; ++it) {
        if ( (*it)->get_apic_lvl_id() == apic_smt )
            return *it;
    }
    return NULL;
}
inline topology_core* cpu_manager::find_core(uint32_t apic_core) const {
    core_list::const_iterator it = m_cores.begin(), end = m_cores.end();
    for (; it != end; ++it) {
        if ( (*it)->get_apic_lvl_id() == apic_core )
            return *it;
    }
    return NULL;
}
inline topology_package* cpu_manager::find_pkg(uint32_t apic_pkg) const {
    pkg_list::const_iterator it = m_pkgs.begin(), end = m_pkgs.end();
    for (; it != end; ++it) {
        if ( (*it)->get_apic_lvl_id() == apic_pkg )
            return *it;
    }
    return NULL;
}

} // namespace cpu //
} // namespace gea //