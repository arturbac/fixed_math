	.text
	.file	"asin.cc"
	.globl	_Z4asinN9fixedmath7fixed_tE     // -- Begin function _Z4asinN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z4asinN9fixedmath7fixed_tE,@function
_Z4asinN9fixedmath7fixed_tE:            // @_Z4asinN9fixedmath7fixed_tE
// %bb.0:
	b	_ZN9fixedmath4asinENS_7fixed_tE
.Lfunc_end0:
	.size	_Z4asinN9fixedmath7fixed_tE, .Lfunc_end0-_Z4asinN9fixedmath7fixed_tE
                                        // -- End function
	.section	.text._ZN9fixedmath4asinENS_7fixed_tE,"axG",@progbits,_ZN9fixedmath4asinENS_7fixed_tE,comdat
	.weak	_ZN9fixedmath4asinENS_7fixed_tE // -- Begin function _ZN9fixedmath4asinENS_7fixed_tE
	.p2align	2
	.type	_ZN9fixedmath4asinENS_7fixed_tE,@function
_ZN9fixedmath4asinENS_7fixed_tE:        // @_ZN9fixedmath4asinENS_7fixed_tE
	.cfi_startproc
// %bb.0:
	cmp	x0, #0                          // =0
	cneg	x13, x0, mi
	cmp	x13, #16, lsl #12               // =65536
	b.gt	.LBB1_9
// %bb.1:
	mov	w10, #39322
	mov	w11, #41705
	mov	w12, #14564
	mov	w9, #28087
	mov	w8, #39322
	cmp	x13, x10
	mov	w10, #21845
	movk	w11, #91, lsl #16
	movk	w12, #62, lsl #16
	movk	w9, #11, lsl #16
	movk	w8, #9, lsl #16
	movk	w10, #5, lsl #16
	b.gt	.LBB1_3
// %bb.2:
	lsl	x13, x13, #4
	mul	x14, x13, x13
	lsr	x14, x14, #20
	mul	x11, x14, x11
	add	x11, x12, x11, lsr #21
	mul	x11, x11, x14
	add	x9, x9, x11, lsr #23
	mul	x9, x9, x14
	add	x8, x8, x9, lsr #21
	mul	x8, x8, x14
	add	x8, x10, x8, lsr #22
	mul	x8, x8, x14
	lsr	x8, x8, #21
	add	x8, x8, #256, lsl #12           // =1048576
	mul	x8, x8, x13
	asr	x8, x8, #24
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_3:
	mov	w14, #65536
	sub	x13, x14, x13
	asr	x13, x13, #1
	lsr	x14, x13, #48
	cbnz	x14, .LBB1_10
// %bb.4:
	cbz	x13, .LBB1_8
// %bb.5:
	lsl	x13, x13, #16
	mov	w15, #64
	clz	x16, x13
	sub	w15, w15, w16
	eor	w16, w16, #0x3f
	tst	w15, #0x1
	csel	w15, w16, w15, eq
	sub	w15, w15, #1                    // =1
	mov	w16, #1
	mov	x14, xzr
	lsl	x15, x16, x15
.LBB1_6:                                // =>This Inner Loop Header: Depth=1
	add	x16, x15, x14
	lsl	x17, x15, #1
	cmp	x13, x16
	csel	x17, xzr, x17, lt
	csel	x16, xzr, x16, lt
	add	x14, x17, x14
	sub	x13, x13, x16
	asr	x15, x15, #2
	asr	x14, x14, #1
	cbnz	x15, .LBB1_6
// %bb.7:
	lsl	x13, x14, #4
.LBB1_8:
	mul	x14, x13, x13
	lsr	x14, x14, #20
	mul	x11, x14, x11
	add	x11, x12, x11, lsr #21
	mul	x11, x11, x14
	add	x9, x9, x11, lsr #23
	mul	x9, x9, x14
	add	x8, x8, x9, lsr #21
	mul	x8, x8, x14
	add	x8, x10, x8, lsr #22
	mul	x8, x8, x14
	lsr	x8, x8, #21
	mov	w12, #37408
	add	x8, x8, #256, lsl #12           // =1048576
	movk	w12, #1, lsl #16
	mul	x8, x8, x13
	sub	x8, x12, x8, asr #23
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_9:
	mov	x0, #9223372036854775807
	ret
.LBB1_10:
	mov	x13, #-16
	b	.LBB1_8
.Lfunc_end1:
	.size	_ZN9fixedmath4asinENS_7fixed_tE, .Lfunc_end1-_ZN9fixedmath4asinENS_7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
