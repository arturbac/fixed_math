	.text
	.file	"tan.cc"
	.globl	_Z3tanN9fixedmath7fixed_tE      // -- Begin function _Z3tanN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z3tanN9fixedmath7fixed_tE,@function
_Z3tanN9fixedmath7fixed_tE:             // @_Z3tanN9fixedmath7fixed_tE
	.cfi_startproc
// %bb.0:
	mov	w8, #37406
	movk	w8, #1, lsl #16
	mov	w9, #9276
	add	x8, x0, x8
	movk	w9, #3, lsl #16
	cmp	x8, x9
	b.hi	.LBB0_2
// %bb.1:
	mul	x8, x0, x0
	lsr	x8, x8, #16
	mov	x9, #6148914691236517205
	mul	x13, x8, x0
	movk	x9, #21846
	asr	x13, x13, #16
	smulh	x9, x13, x9
	mul	x13, x13, x8
	mov	x12, #13663
	asr	x13, x13, #16
	movk	x12, #2219, lsl #16
	lsl	x14, x13, #1
	mul	x13, x13, x8
	mov	x10, #-8608480567731124088
	mov	w11, #51
	movk	x12, #21984, lsl #32
	asr	x13, x13, #16
	movk	x10, #34953
	movk	x12, #35507, lsl #48
	mul	x11, x13, x11
	smulh	x10, x14, x10
	smulh	x12, x11, x12
	add	x10, x10, x14
	add	x11, x12, x11
	mov	x12, #52799
	asr	x14, x10, #3
	movk	x12, #23324, lsl #16
	mul	x13, x13, x8
	add	x10, x14, x10, lsr #63
	mov	w14, #62
	movk	x12, #36501, lsl #32
	asr	x13, x13, #16
	movk	x12, #23671, lsl #48
	mul	x8, x13, x8
	mul	x13, x13, x14
	smulh	x12, x13, x12
	mov	x13, #20025
	add	x9, x9, x9, lsr #63
	movk	x13, #32596, lsl #16
	add	x9, x9, x0
	mov	w14, #1382
	movk	x13, #25686, lsl #32
	asr	x8, x8, #16
	movk	x13, #430, lsl #48
	add	x9, x9, x10
	asr	x10, x11, #9
	mul	x8, x8, x14
	add	x10, x10, x11, lsr #63
	asr	x11, x12, #10
	smulh	x8, x8, x13
	add	x11, x11, x12, lsr #63
	add	x9, x9, x10
	asr	x10, x8, #10
	add	x8, x10, x8, lsr #63
	add	x9, x9, x11
	add	x0, x9, x8
	ret
.LBB0_2:
	mov	x0, #9223372036854775807
	ret
.Lfunc_end0:
	.size	_Z3tanN9fixedmath7fixed_tE, .Lfunc_end0-_Z3tanN9fixedmath7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
