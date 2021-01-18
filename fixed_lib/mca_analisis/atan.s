	.text
	.file	"atan.cc"
	.globl	_Z4atanN9fixedmath7fixed_tE     // -- Begin function _Z4atanN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z4atanN9fixedmath7fixed_tE,@function
_Z4atanN9fixedmath7fixed_tE:            // @_Z4atanN9fixedmath7fixed_tE
// %bb.0:
	b	_ZN9fixedmath4atanENS_7fixed_tE
.Lfunc_end0:
	.size	_Z4atanN9fixedmath7fixed_tE, .Lfunc_end0-_Z4atanN9fixedmath7fixed_tE
                                        // -- End function
	.section	.text._ZN9fixedmath4atanENS_7fixed_tE,"axG",@progbits,_ZN9fixedmath4atanENS_7fixed_tE,comdat
	.weak	_ZN9fixedmath4atanENS_7fixed_tE // -- Begin function _ZN9fixedmath4atanENS_7fixed_tE
	.p2align	2
	.type	_ZN9fixedmath4atanENS_7fixed_tE,@function
_ZN9fixedmath4atanENS_7fixed_tE:        // @_ZN9fixedmath4atanENS_7fixed_tE
	.cfi_startproc
// %bb.0:
	cmp	x0, #0                          // =0
	cneg	x8, x0, mi
	cmp	x8, #16, lsl #12                // =65536
	b.gt	.LBB1_4
// %bb.1:
	mov	w9, #39318
	cmp	x8, x9
	b.gt	.LBB1_3
// %bb.2:
	mul	x9, x0, x0
	lsr	x9, x9, #16
	mul	x13, x9, x8
	mov	x10, #6148914691236517205
	lsr	x13, x13, #16
	mov	x11, #-3689348814741910324
	smulh	x10, x13, x10
	movk	x11, #52429
	mov	x12, #46811
	sub	x10, x10, x13
	mul	x13, x13, x9
	movk	x12, #56173, lsl #16
	umulh	x11, x13, x11
	lsr	x13, x13, #16
	movk	x12, #28086, lsl #32
	asr	x14, x10, #1
	mul	x13, x13, x9
	movk	x12, #46811, lsl #48
	add	x10, x14, x10, lsr #63
	mov	x14, #58255
	lsr	x13, x13, #16
	movk	x14, #36408, lsl #16
	add	x8, x10, x8
	mov	x10, #29789
	smulh	x12, x13, x12
	mul	x13, x13, x9
	movk	x14, #14563, lsl #32
	movk	x10, #17873, lsl #16
	add	x8, x8, x11, lsr #18
	lsr	x11, x13, #16
	movk	x14, #58254, lsl #48
	movk	x10, #23831, lsl #32
	mul	x9, x11, x9
	movk	x10, #53620, lsl #48
	umulh	x13, x13, x14
	asr	x14, x12, #1
	lsr	x9, x9, #16
	add	x11, x14, x12, lsr #63
	smulh	x9, x9, x10
	add	x8, x8, x11
	asr	x10, x9, #1
	add	x8, x8, x13, lsr #19
	add	x9, x10, x9, lsr #63
	add	x8, x8, x9
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_3:
	mov	w9, #39319
	mov	x10, #-65536
	mul	x9, x8, x9
	movk	x10, #26217, lsl #16
	lsr	x9, x9, #16
	add	x8, x10, x8, lsl #16
	add	x9, x9, #16, lsl #12            // =65536
	sdiv	x8, x8, x9
	mul	x9, x8, x8
	lsr	x9, x9, #16
	mul	x10, x9, x8
	mov	x11, #6148914691236517205
	asr	x10, x10, #16
	mov	x12, #7378697629483820646
	mov	x13, #46811
	mul	x14, x10, x9
	smulh	x11, x10, x11
	movk	x12, #26215
	movk	x13, #56173, lsl #16
	asr	x14, x14, #16
	sub	x10, x11, x10
	movk	x13, #28086, lsl #32
	asr	x11, x10, #1
	smulh	x12, x14, x12
	mul	x14, x14, x9
	movk	x13, #46811, lsl #48
	add	x10, x11, x10, lsr #63
	asr	x11, x12, #1
	asr	x14, x14, #16
	add	x11, x11, x12, lsr #63
	mov	x12, #7282
	add	x8, x8, x10
	mov	x10, #29789
	smulh	x13, x14, x13
	mul	x14, x14, x9
	movk	x12, #29127, lsl #16
	movk	x10, #17873, lsl #16
	asr	x14, x14, #16
	movk	x12, #50972, lsl #32
	movk	x10, #23831, lsl #32
	mul	x9, x14, x9
	movk	x12, #7281, lsl #48
	movk	x10, #53620, lsl #48
	add	x8, x8, x11
	asr	x11, x13, #1
	asr	x9, x9, #16
	add	x11, x11, x13, lsr #63
	smulh	x12, x14, x12
	smulh	x9, x9, x10
	add	x12, x12, x12, lsr #63
	add	x8, x8, x11
	asr	x10, x9, #1
	add	x8, x8, x12
	add	x9, x10, x9, lsr #63
	add	x8, x8, x9
	mov	w9, #35415
	add	x8, x8, x9
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_4:
	mov	x0, #9223372036854775807
	ret
.Lfunc_end1:
	.size	_ZN9fixedmath4atanENS_7fixed_tE, .Lfunc_end1-_ZN9fixedmath4atanENS_7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
