	.text
	.file	"asin.cc"
	.globl	_Z4asinN9fixedmath7fixed_tE     // -- Begin function _Z4asinN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z4asinN9fixedmath7fixed_tE,@function
_Z4asinN9fixedmath7fixed_tE:            // @_Z4asinN9fixedmath7fixed_tE
	.cfi_startproc
// %bb.0:
	add	x8, x0, #16, lsl #12            // =65536
	cmp	x8, #32, lsl #12                // =131072
	b.hi	.LBB0_4
// %bb.1:
	mov	w9, #58255
	mul	x8, x0, x0
	add	x10, x0, #8, lsl #12            // =32768
	movk	w9, #3, lsl #16
	cmp	x10, #16, lsl #12               // =65536
	lsr	x8, x8, #16
	b.ls	.LBB0_3
// %bb.2:
	mov	x11, #8549
	mov	w10, #21
	movk	x11, #22795, lsl #16
	movk	x11, #17096, lsl #32
	mul	x10, x8, x10
	movk	x11, #45590, lsl #48
	lsr	x10, x10, #1
	umulh	x10, x10, x11
	mov	w11, #34328
	add	x10, x11, x10, lsr #4
	mul	x10, x10, x8
	mov	w11, #4199
	lsr	x10, x10, #16
	mul	x10, x10, x11
	mov	w11, #48290
	movk	w11, #639, lsl #16
	add	x10, x11, x10, lsr #2
	mov	w11, #34696
	movk	w11, #378, lsl #16
	mul	x10, x10, x8
	add	x10, x11, x10, lsr #17
	mov	w11, #39322
	movk	w11, #28, lsl #16
	mul	x10, x10, x8
	add	x10, x11, x10, lsr #20
	mov	w11, #50413
	movk	w11, #17, lsl #16
	mul	x10, x10, x8
	add	x10, x11, x10, lsr #17
	mov	w11, #47663
	mul	x10, x10, x8
	movk	w11, #5, lsl #16
	add	x10, x11, x10, lsr #18
	mul	x10, x10, x8
	add	x9, x9, x10, lsr #17
.LBB0_3:
	mul	x9, x9, x8
	asr	x9, x9, #16
	add	x10, x9, #7                     // =7
	cmp	x9, #0                          // =0
	csel	x9, x10, x9, lt
	mov	w10, #46812
	add	x9, x10, x9, asr #3
	mul	x9, x9, x8
	asr	x9, x9, #16
	cmp	x9, #0                          // =0
	mov	w10, #39322
	cinc	x9, x9, lt
	add	x9, x10, x9, asr #1
	mul	x9, x9, x8
	asr	x9, x9, #16
	add	x10, x9, #3                     // =3
	cmp	x9, #0                          // =0
	csel	x9, x10, x9, lt
	mov	w10, #21845
	add	x9, x10, x9, asr #2
	mul	x8, x9, x8
	asr	x8, x8, #16
	cmp	x8, #0                          // =0
	cinc	x8, x8, lt
	asr	x8, x8, #1
	add	x8, x8, #16, lsl #12            // =65536
	mul	x8, x8, x0
	asr	x0, x8, #16
	ret
.LBB0_4:
	mov	x0, #9223372036854775807
	ret
.Lfunc_end0:
	.size	_Z4asinN9fixedmath7fixed_tE, .Lfunc_end0-_Z4asinN9fixedmath7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
