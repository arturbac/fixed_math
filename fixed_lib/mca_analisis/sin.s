	.text
	.file	"sin.cc"
	.globl	_Z3sinN9fixedmath7fixed_tE      // -- Begin function _Z3sinN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z3sinN9fixedmath7fixed_tE,@function
_Z3sinN9fixedmath7fixed_tE:             // @_Z3sinN9fixedmath7fixed_tE
	.cfi_startproc
// %bb.0:
	mov	w8, #37407
	mov	w9, #18558
	movk	w8, #1, lsl #16
	movk	w9, #6, lsl #16
	add	x10, x0, x8
	cmp	x10, x9
	b.hs	.LBB0_2
.LBB0_1:
	mov	w9, #9279
	movk	w9, #3, lsl #16
	cmp	x0, x8
	sub	x9, x9, x0
	csel	x9, x9, x0, gt
	mul	x11, x9, x9
	lsr	x11, x11, #16
	mul	x12, x11, x9
	mov	w8, #10922
	asr	x12, x12, #16
	mul	x8, x12, x8
	mul	x12, x12, x11
	asr	x12, x12, #16
	mov	w10, #546
	mul	x11, x12, x11
	mul	x10, x12, x10
	mov	w12, #13
	asr	x11, x11, #16
	asr	x8, x8, #16
	mul	x11, x11, x12
	add	x9, x9, x10, asr #16
	add	x8, x8, x11, asr #16
	sub	x0, x9, x8
	ret
.LBB0_2:
	sdiv	x11, x10, x9
	mov	w12, #46687
	msub	x9, x11, x9, x10
	mov	x10, #-37407
	movk	w12, #4, lsl #16
	cmp	x9, #0                          // =0
	movk	x10, #65534, lsl #16
	csel	x10, x12, x10, lt
	add	x0, x10, x9
	b	.LBB0_1
.Lfunc_end0:
	.size	_Z3sinN9fixedmath7fixed_tE, .Lfunc_end0-_Z3sinN9fixedmath7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
