#ifndef __GEA_INTRINSICS_MSVC_H__
#define __GEA_INTRINSICS_MSVC_H__

// ------------------------------------------------------------------------- //
// Compiler Specific Inline Assembly Functions                               //
// ------------------------------------------------------------------------- //

// system information
inline bool ci_has_cpuid() {
    __asm {
        pushfd                          ;// push original EFLAGS
        pop     eax                     ;// get original EFLAGS
        mov     ecx, eax                ;// save original EFLAGS
        xor     eax, 200000h            ;// flip ID bit in EFLAGS
        push    eax                     ;// save new EFLAGS value on stack
        popfd                           ;// replace current EFLAGS value
        pushfd                          ;// get new EFLAGS
        pop     eax                     ;// store new flags in eax
        xor     eax, ecx                ;// can't toggle ID bit
        shr     eax,  21                ;// shift bit 21 to bit 0
        push    ecx                     ;// restore ID bit in EFLAGS
        popfd                           ;//
    }
}
inline void ci_cpuid(void* info, const uint32_t leaf, const uint32_t subleaf = 0) {
    __asm {
        push    edi                     ;
        mov     edi, info               ;
        mov     eax, leaf               ;
        mov     ecx, subleaf            ;
        cpuid                           ;
        mov     dword ptr [edi   ], eax ;
        mov     dword ptr [edi+ 4], ebx ;
        mov     dword ptr [edi+ 8], ecx ;
        mov     dword ptr [edi+12], edx ;
        pop     edi                     ;
    }
}

#endif // __GEA_INTRINSICS_MSVC_H__ //
