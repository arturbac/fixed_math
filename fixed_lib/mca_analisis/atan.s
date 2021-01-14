	.text
	.file	"atan.cc"
	.globl	_Z4atanN9fixedmath7fixed_tE     // -- Begin function _Z4atanN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z4atanN9fixedmath7fixed_tE,@function
_Z4atanN9fixedmath7fixed_tE:            // @_Z4atanN9fixedmath7fixed_tE
	.cfi_startproc
// %bb.0:
	add	x8, x0, #16, lsl #12            // =65536
	cmp	x8, #32, lsl #12                // =131072
	b.hi	.LBB0_2
// %bb.1:
	mul	x8, x0, x0
	lsr	x8, x8, #16
	mul	x12, x8, x0
	mov	x9, #6148914691236517205
	asr	x12, x12, #16
	smulh	x9, x12, x9
	mov	x10, #7378697629483820646
	mov	x11, #46811
	sub	x9, x9, x12
	mul	x12, x12, x8
	movk	x10, #26215
	movk	x11, #56173, lsl #16
	asr	x12, x12, #16
	movk	x11, #28086, lsl #32
	asr	x13, x9, #1
	smulh	x10, x12, x10
	mul	x12, x12, x8
	movk	x11, #46811, lsl #48
	add	x9, x13, x9, lsr #63
	mov	x13, #7282
	asr	x14, x10, #1
	asr	x12, x12, #16
	movk	x13, #29127, lsl #16
	add	x10, x14, x10, lsr #63
	mov	x14, #29789
	smulh	x11, x12, x11
	mul	x12, x12, x8
	movk	x13, #50972, lsl #32
	add	x9, x9, x0
	movk	x14, #17873, lsl #16
	asr	x12, x12, #16
	movk	x13, #7281, lsl #48
	movk	x14, #23831, lsl #32
	add	x9, x9, x10
	asr	x10, x11, #1
	mul	x8, x12, x8
	movk	x14, #53620, lsl #48
	add	x10, x10, x11, lsr #63
	smulh	x11, x12, x13
	asr	x8, x8, #16
	add	x9, x9, x10
	add	x10, x11, x11, lsr #63
	smulh	x8, x8, x14
	add	x9, x9, x10
	asr	x10, x8, #1
	add	x8, x10, x8, lsr #63
	add	x0, x9, x8
	ret
.LBB0_2:
	mov	x0, #9223372036854775807
	ret
.Lfunc_end0:
	.size	_Z4atanN9fixedmath7fixed_tE, .Lfunc_end0-_Z4atanN9fixedmath7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
