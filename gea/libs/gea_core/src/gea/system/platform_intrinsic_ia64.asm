PUBLIC asm_system_break						; void asm_system_break()
PUBLIC asm_cpuid							; void asm_cpuid(void* info, const uint32_t leaf, const uint32_t subleaf)

PUBLIC asm_fsincos							; void asm_fsincos(float angle, float* out_sin, float* out_cos)
PUBLIC asm_fsin								; void asm_fsincos(float angle, float* out_sin)
PUBLIC asm_fcos								; void asm_fsincos(float angle, float* out_cos)

.CODE										; code segment

; --------------------------------------------------------------------------- ;
; system functions                                                            ;
; --------------------------------------------------------------------------- ;

asm_system_break PROC
	int		3								; trigger debug exception handler
	ret		0
asm_system_break ENDP

_info$ = 8
_leaf$ = 16
_subleaf$ = 24

asm_cpuid PROC
	mov		QWORD PTR _info$[rsp], rcx		; move arguments to stack
	mov		DWORD PTR _leaf$[rsp], edx		;
	mov		DWORD PTR _subleaf$[rsp], r8d	;

	mov		eax, DWORD PTR _leaf$[rsp]		; move leaf and subleaf to registers used
	mov		ecx, DWORD PTR _subleaf$[rsp]	; by cpuid instruction
	cpuid									;
	mov		r8, QWORD PTR _info$[rsp]		; load info pointer to register
	mov		DWORD PTR [r8+ 0], eax			; store cpuid output (eax-edx) to info
	mov		DWORD PTR [r8+ 4], ebx			;
	mov		DWORD PTR [r8+ 8], ecx			;
	mov		DWORD PTR [r8+12], edx			;
	ret		0								;
asm_cpuid ENDP

; --------------------------------------------------------------------------- ;
; math functions                                                              ;
; --------------------------------------------------------------------------- ;

_angle$ = 8

asm_fsincos PROC
	movss	DWORD PTR _angle$[rsp], xmm0	; argument angle is in xmm0, move it to the stack
	fld		DWORD PTR _angle$[rsp]			; push angle onto the FPU stack where we can do FLOPs
	fsincos
	fstp	DWORD PTR [r8]					; store/pop cosine output argument
	fstp	DWORD PTR [rdx]					; store/pop sine output argument
	ret		0
asm_fsincos ENDP

asm_fsin PROC
	movss	DWORD PTR _angle$[rsp], xmm0	; argument angle is in xmm0, move it to the stack
	fld		DWORD PTR _angle$[rsp]			; push angle onto the FPU stack where we can do FLOPs
	fsin
	fstp	DWORD PTR [rdx]					; store/pop sine output argument
	ret		0
asm_fsin ENDP

asm_fcos PROC
	movss	DWORD PTR _angle$[rsp], xmm0	; argument angle is in xmm0, move it to the stack
	fld		DWORD PTR _angle$[rsp]			; push angle onto the FPU stack where we can do FLOPs
	fcos
	fstp	DWORD PTR [rdx]					; store/pop cosine output argument
	ret		0
asm_fcos ENDP

END
