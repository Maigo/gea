#ifndef __GEA_CPUID_INTEL_H__
#define __GEA_CPUID_INTEL_H__

#include "cpuid_general.h"

namespace gea {
namespace cpuid {

namespace internal {
// ------------------------------------------------------------------------- //
// CPUID intel leaf structs                                                  //
// ------------------------------------------------------------------------- //

// eax == 1
struct intel_feature_ecx {
    uint32_t sse3         : 1; // 0
    uint32_t pclmuldq     : 1; // 1
    uint32_t dtes64       : 1; // 2
    uint32_t monitor      : 1; // 3
    uint32_t ds_cpl       : 1; // 4
    uint32_t vmx          : 1; // 5
    uint32_t smx          : 1; // 6
    uint32_t eist         : 1; // 7
    uint32_t tm2          : 1; // 8
    uint32_t ssse3        : 1; // 9
    uint32_t cnxt_id      : 1; // 10
    uint32_t res0         : 1; // 11
    uint32_t fma          : 1; // 12
    uint32_t cx16         : 1; // 13
    uint32_t xtpr         : 1; // 14
    uint32_t pdcm         : 1; // 15
    uint32_t res1         : 1; // 16
    uint32_t pcid         : 1; // 17
    uint32_t dca          : 1; // 18
    uint32_t sse4_1       : 1; // 19
    uint32_t sse4_2       : 1; // 20
    uint32_t x2apic       : 1; // 21
    uint32_t movbe        : 1; // 22
    uint32_t popcnt       : 1; // 23
    uint32_t tsc_deadline : 1; // 24
    uint32_t aes          : 1; // 25
    uint32_t xsave        : 1; // 26
    uint32_t osxsave      : 1; // 27
    uint32_t avx          : 1; // 28
    uint32_t res2         : 3; // 31:29
};
struct intel_feature_edx {
    uint32_t fpu    : 1; // 0
    uint32_t vme    : 1; // 1
    uint32_t de     : 1; // 2
    uint32_t pse    : 1; // 3
    uint32_t tsc    : 1; // 4
    uint32_t msr    : 1; // 5
    uint32_t pae    : 1; // 6
    uint32_t mce    : 1; // 7
    uint32_t cx8    : 1; // 8
    uint32_t apic   : 1; // 9
    uint32_t res0   : 1; // 10
    uint32_t sep    : 1; // 11
    uint32_t mtrr   : 1; // 12
    uint32_t pge    : 1; // 13
    uint32_t mca    : 1; // 14
    uint32_t cmov   : 1; // 15
    uint32_t pat    : 1; // 16
    uint32_t pse_36 : 1; // 17
    uint32_t psn    : 1; // 18
    uint32_t clfsh  : 1; // 19
    uint32_t res1   : 1; // 20
    uint32_t ds     : 1; // 21
    uint32_t acpi   : 1; // 22
    uint32_t mmx    : 1; // 23
    uint32_t fxsr   : 1; // 24
    uint32_t sse    : 1; // 25
    uint32_t sse2   : 1; // 26
    uint32_t ss     : 1; // 27
    uint32_t htt    : 1; // 28
    uint32_t tm     : 1; // 29
    uint32_t res2   : 1; // 30
    uint32_t pbe    : 1; // 31
};
    
struct leaf_s1 {
    uint32_t reserved0;
    uint32_t reserved1;
    union { intel_feature_ecx feature0;
            uint32_t          feature0_all;
    };
    union { intel_feature_edx feature1;
            uint32_t          feature1_all;
    };
};

// eax == 6
struct intel_thermal_power_eax {
    uint32_t dts  :  1; // 0
    uint32_t itbt :  1; // 1
    uint32_t arat :  1; // 2
    uint32_t res0 :  1; // 3
    uint32_t pln  :  1; // 4
    uint32_t ecmd :  1; // 5
    uint32_t ptm  :  1; // 6
    uint32_t res1 : 25; // 31:7
};
struct intel_thermal_power_ebx {
    uint32_t nit  :  4; // 4:0
    uint32_t res0 : 28; // 31:5
};
struct intel_thermal_power_ecx {
    uint32_t hcf  :  1; // 0
    uint32_t res0 :  2; // 2:1
    uint32_t peb  :  1; // 3
    uint32_t res1 : 28; // 31:4
};

struct leaf_s6 {
    union { intel_thermal_power_eax eax;
            uint32_t                eax_all;
    };
    union { intel_thermal_power_ebx ebx;
            uint32_t                ebx_all;
    };
    union { intel_thermal_power_ecx ecx;
            uint32_t                ecx_all;
    };
    uint32_t reserved0;
};
// eax == 7
struct leaf_s7 {
    uint32_t reserved0, reserved1, reserved2, reserved3;
};
// eax == 8
struct leaf_s8 {
    uint32_t reserved0, reserved1, reserved2, reserved3;
};
// eax == 9
struct leaf_s9 {
    uint32_t plt_dca_cap, reserved0, reserved1, reserved2;
};
// eax == 11
// x2APIC Features / Processor Topology (Function 0Bh)
struct leaf_sB_eax {
    uint32_t apic_shr :  5; // 4:0
    uint32_t res0     : 27; // 31:5
};
struct leaf_sB_ebx {
    uint32_t lp_cnt : 16; // 15:0
    uint32_t res0   : 16; // 31:16
};
struct leaf_sB_ecx {
    uint32_t lvl_nr   :  8; // 7:0
    uint32_t lvl_type :  8; // 15:8
    uint32_t res0     : 16; // 31:16
};
struct leaf_sB {
    union { leaf_sB_eax eax; uint32_t eax_all; };
    union { leaf_sB_ebx ebx; uint32_t ebx_all; };
    union { leaf_sB_ecx ecx; uint32_t ecx_all; };
    uint32_t x2apic_id;
};

// eax == extension 1
// extended feature bits
struct leaf_e1_ecx {
    uint32_t lahf :  1; // 0
    uint32_t res0 : 31; // 31:1
};
struct leaf_e1_edx {
    uint32_t res0    : 11; // 10:0
    uint32_t syscall :  1; // 11
    uint32_t res1    :  8; // 19:12
    uint32_t xd_bit  :  1; // 20
    uint32_t res2    :  5; // 25:21
    uint32_t gb_page :  1; // 26
    uint32_t rdtscp  :  1; // 27
    uint32_t res3    :  1; // 28
    uint32_t ia_64   :  1; // 29
    uint32_t res4    :  2; // 31:30
};
struct leaf_e1 {
    uint32_t reserved0, reserved1;
    union { leaf_e1_ecx ecx; uint32_t ecx_all; };
    union { leaf_e1_edx edx; uint32_t edx_all; };
};
// eax == extension 2-3-4
// processor brand string
struct leaf_e2 {
    char name[16];
};

// eax == extended 6
struct leaf_e6_ecx {
    uint32_t l2c_line_size :  8; // 7:0
    uint32_t res1          :  4; // 11:8
    uint32_t l2c_assoc     :  4; // 15:12
    uint32_t l2c_size_x1kb : 16; // 31:16
};

struct leaf_e6 {
    uint32_t reserved0, reserved1;
    union { leaf_e6_ecx ecx; uint32_t ecx_all; };
    uint32_t reserved2;
};

} // namespace internal //

// ------------------------------------------------------------------------- //
// CPUID intel leaf composite struct                                         //
// ------------------------------------------------------------------------- //

struct intel_leaf {
    union {
        internal::leaf    rx;

        internal::leaf_s0 s0;
        internal::leaf_s1 s1;
        internal::leaf_s6 s6;
        internal::leaf_s7 s7;
        internal::leaf_s8 s8;
        internal::leaf_s9 s9;
        internal::leaf_sB sB;

        internal::leaf_e0 e0;
        internal::leaf_e1 e1;
        internal::leaf_e2 e2;
        internal::leaf_e2 e3;
        internal::leaf_e2 e4;
        internal::leaf_e6 e6;
    };
};


} // namespace cpuid //
} // namespace gea //

#endif // __GEA_CPUID_INTEL_H__ //
