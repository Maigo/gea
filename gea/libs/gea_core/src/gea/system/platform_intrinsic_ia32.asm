PUBLIC asm_system_break						; void asm_system_break()
PUBLIC asm_cpuid							; void asm_cpuid(void* info, const uint32_t leaf, const uint32_t subleaf)

PUBLIC asm_fsincos							; void asm_fsincos(float angle, float* out_sin, float* out_cos)
PUBLIC asm_fsin								; void asm_fsincos(float angle, float* out_sin)
PUBLIC asm_fcos								; void asm_fsincos(float angle, float* out_cos)

.MODEL FLAT, C								; memory model
.CODE										; code segment

; --------------------------------------------------------------------------- ;
; system functions                                                            ;
; --------------------------------------------------------------------------- ;

asm_system_break PROC
	int		3								; trigger debug exception handler
	ret		0
asm_system_break ENDP

_info$ = 4
_leaf$ = 8
_subleaf$ = 12

asm_cpuid PROC
	mov		eax, DWORD PTR _leaf$[esp]		; move leaf and subleaf to registers used
	mov		ecx, DWORD PTR _subleaf$[esp]	; by cpuid instruction
	cpuid									;
	mov		esi, DWORD PTR _info$[esp]		; load info pointer to register
	mov		DWORD PTR [esi   ], eax			; store cpuid output (eax-edx) to info
	mov		DWORD PTR [esi+ 4], ebx			;
	mov		DWORD PTR [esi+ 8], ecx			;
	mov		DWORD PTR [esi+12], edx			;
	ret		0								;
asm_cpuid ENDP

; --------------------------------------------------------------------------- ;
; math functions                                                              ;
; --------------------------------------------------------------------------- ;

_angle$ = 4
_out_arg0$ = 8
_out_arg1$ = 12

asm_fsincos PROC
	fld		DWORD PTR _angle$[esp]			; push angle onto the FPU stack where we can do FLOPs
	fsincos
	fstp	DWORD PTR _out_arg1$[esp]		; store/pop cosine output argument
	fstp	DWORD PTR _out_arg0$[esp]		; store/pop sine output argument
	ret		0
asm_fsincos ENDP

asm_fsin PROC
	fld		DWORD PTR _angle$[esp]			; push angle onto the FPU stack where we can do FLOPs
	fsin
	fstp	DWORD PTR _out_arg0$[esp]		; store/pop sine output argument
	ret		0
asm_fsin ENDP

asm_fcos PROC
	fld		DWORD PTR _angle$[esp]			; push angle onto the FPU stack where we can do FLOPs
	fcos
	fstp	DWORD PTR _out_arg0$[esp]		; store/pop cosine output argument
	ret		0
asm_fcos ENDP

END
