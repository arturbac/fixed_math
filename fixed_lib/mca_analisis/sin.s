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
	mov	x8, #15603
	sub	x9, x9, x0
	movk	x8, #62415, lsl #16
	csel	x9, x9, x0, gt
	movk	x8, #53052, lsl #32
	mul	x10, x9, x9
	movk	x8, #15603, lsl #48
	lsr	x10, x10, #16
	smulh	x8, x10, x8
	sub	x8, x8, x10
	asr	x11, x8, #5
	add	x8, x11, x8, lsr #63
	add	x8, x8, #16, lsl #12            // =65536
	mul	x8, x8, x10
	mov	x11, #-7378697629483820647
	asr	x8, x8, #16
	smulh	x8, x8, x11
	asr	x11, x8, #3
	add	x8, x11, x8, lsr #63
	add	x8, x8, #16, lsl #12            // =65536
	mul	x8, x8, x10
	mov	x10, #6148914691236517205
	asr	x8, x8, #16
	movk	x10, #54613, lsl #48
	smulh	x8, x8, x10
	add	x8, x8, x8, lsr #63
	add	x8, x8, #16, lsl #12            // =65536
	mul	x8, x8, x9
	asr	x0, x8, #16
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
