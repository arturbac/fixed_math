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
	mul	x9, x0, x0
	lsr	x9, x9, #16
	mov	x10, #-6148914691236517206
	mul	x12, x9, x0
	movk	x10, #43691
	asr	x12, x12, #16
	movk	x10, #10922, lsl #48
	mul	x13, x12, x9
	mov	x8, #7378697629483820646
	smulh	x10, x12, x10
	asr	x12, x13, #16
	movk	x8, #26215
	mov	x11, #18725
	mul	x13, x12, x9
	add	x12, x12, x12, lsl #1
	movk	x11, #9362, lsl #16
	smulh	x12, x12, x8
	movk	x11, #37449, lsl #32
	asr	x13, x13, #16
	asr	x14, x12, #4
	movk	x11, #18724, lsl #48
	add	x12, x14, x12, lsr #63
	add	x14, x13, x13, lsl #2
	add	x10, x10, x10, lsr #63
	smulh	x11, x14, x11
	add	x10, x10, x0
	add	x12, x10, x12
	asr	x10, x11, #5
	mov	x15, #36409
	add	x11, x10, x11, lsr #63
	movk	x15, #14563, lsl #16
	mul	x10, x13, x9
	mov	w14, #35
	movk	x15, #58254, lsl #32
	asr	x10, x10, #16
	movk	x15, #3640, lsl #48
	mul	x13, x10, x14
	smulh	x13, x13, x15
	add	x11, x12, x11
	asr	x12, x13, #6
	add	x16, x0, #8, lsl #12            // =32768
	add	x12, x12, x13, lsr #63
	cmp	x16, #16, lsl #12               // =65536
	add	x0, x11, x12
	b.ls	.LBB0_3
// %bb.2:
	mul	x10, x10, x9
	mov	x11, #35747
	movk	x11, #47662, lsl #16
	asr	x10, x10, #16
	movk	x11, #41704, lsl #32
	lsl	x13, x10, #6
	movk	x11, #11915, lsl #48
	sub	x13, x13, x10
	smulh	x11, x13, x11
	mov	x13, #20165
	movk	x13, #50412, lsl #16
	mul	x10, x10, x9
	mov	w12, #231
	movk	x13, #60494, lsl #32
	asr	x10, x10, #16
	movk	x13, #20164, lsl #48
	mul	x12, x10, x12
	smulh	x12, x12, x13
	asr	x13, x11, #9
	mul	x10, x10, x9
	add	x11, x13, x11, lsr #63
	mov	w13, #143
	asr	x10, x10, #16
	mul	x9, x10, x9
	mul	x10, x10, x13
	asr	x13, x12, #12
	add	x12, x13, x12, lsr #63
	mov	w13, #6435
	smulh	x8, x10, x8
	mov	x10, #8680820740569200760
	asr	x9, x9, #16
	movk	x10, #30841
	mul	x9, x9, x13
	add	x11, x11, x0
	asr	x14, x8, #12
	smulh	x9, x9, x10
	add	x11, x11, x12
	add	x8, x14, x8, lsr #63
	asr	x10, x9, #18
	add	x9, x10, x9, lsr #63
	add	x8, x11, x8
	add	x0, x8, x9
.LBB0_3:
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
