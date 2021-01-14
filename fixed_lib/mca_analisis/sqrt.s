	.text
	.file	"sqrt.cc"
	.globl	_Z4sqrtN9fixedmath7fixed_tE     // -- Begin function _Z4sqrtN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z4sqrtN9fixedmath7fixed_tE,@function
_Z4sqrtN9fixedmath7fixed_tE:            // @_Z4sqrtN9fixedmath7fixed_tE
	.cfi_startproc
// %bb.0:
	lsr	x9, x0, #48
	cbnz	x9, .LBB0_5
// %bb.1:
	mov	x8, x0
	cbz	x0, .LBB0_6
// %bb.2:
	lsl	x8, x8, #16
	mov	w9, #64
	clz	x10, x8
	sub	w9, w9, w10
	eor	w10, w10, #0x3f
	tst	w9, #0x1
	csel	w9, w10, w9, eq
	sub	w9, w9, #1                      // =1
	mov	w10, #1
	mov	x0, xzr
	lsl	x9, x10, x9
.LBB0_3:                                // =>This Inner Loop Header: Depth=1
	add	x10, x9, x0
	lsl	x11, x9, #1
	cmp	x8, x10
	csel	x11, xzr, x11, lt
	csel	x10, xzr, x10, lt
	add	x11, x11, x0
	sub	x8, x8, x10
	asr	x9, x9, #2
	asr	x0, x11, #1
	cbnz	x9, .LBB0_3
// %bb.4:
	ret
.LBB0_5:
	mov	x0, #9223372036854775807
	ret
.LBB0_6:
	mov	x0, xzr
	ret
.Lfunc_end0:
	.size	_Z4sqrtN9fixedmath7fixed_tE, .Lfunc_end0-_Z4sqrtN9fixedmath7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
