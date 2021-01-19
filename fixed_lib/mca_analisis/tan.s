	.text
	.file	"tan.cc"
	.globl	_Z3tanN9fixedmath7fixed_tE      // -- Begin function _Z3tanN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z3tanN9fixedmath7fixed_tE,@function
_Z3tanN9fixedmath7fixed_tE:             // @_Z3tanN9fixedmath7fixed_tE
// %bb.0:
	b	_ZN9fixedmath3tanENS_7fixed_tE
.Lfunc_end0:
	.size	_Z3tanN9fixedmath7fixed_tE, .Lfunc_end0-_Z3tanN9fixedmath7fixed_tE
                                        // -- End function
	.section	.text._ZN9fixedmath3tanENS_7fixed_tE,"axG",@progbits,_ZN9fixedmath3tanENS_7fixed_tE,comdat
	.weak	_ZN9fixedmath3tanENS_7fixed_tE  // -- Begin function _ZN9fixedmath3tanENS_7fixed_tE
	.p2align	2
	.type	_ZN9fixedmath3tanENS_7fixed_tE,@function
_ZN9fixedmath3tanENS_7fixed_tE:         // @_ZN9fixedmath3tanENS_7fixed_tE
	.cfi_startproc
// %bb.0:
	cmp	x0, #0                          // =0
	mov	w9, #37408
	cneg	x8, x0, mi
	movk	w9, #1, lsl #16
	cmp	x8, x9
	b.eq	.LBB1_4
// %bb.1:
	mov	x9, #1430257664
	mov	w10, #12065
	mov	w11, #51472
	movk	x9, #5, lsl #32
	movk	w10, #14, lsl #16
	cmp	x8, x11
	lsl	x8, x8, #4
	b.gt	.LBB1_3
// %bb.2:
	mov	x12, #19973
	mul	x11, x8, x8
	movk	x12, #1248, lsl #16
	movk	x12, #57422, lsl #32
	lsr	x11, x11, #20
	movk	x12, #19972, lsl #48
	mul	x10, x11, x10
	umulh	x10, x10, x12
	mov	x12, #1681
	movk	x12, #36969, lsl #16
	add	x9, x9, x10, lsr #5
	movk	x12, #26886, lsl #32
	mul	x9, x9, x11
	movk	x12, #1680, lsl #48
	lsr	x9, x9, #20
	mov	w10, #1449132032
	umulh	x9, x9, x12
	mov	x12, #42897
	movk	x12, #30980, lsl #16
	add	x9, x9, x10
	movk	x12, #36938, lsl #32
	mul	x9, x9, x11
	movk	x12, #1191, lsl #48
	lsr	x9, x9, #20
	umulh	x9, x9, x12
	mov	x12, #58255
	mov	w10, #65011712
	movk	x12, #36408, lsl #16
	movk	x12, #14563, lsl #32
	add	x9, x9, x10
	movk	x12, #58254, lsl #48
	mul	x9, x9, x11
	mov	w10, #17825792
	umulh	x9, x9, x12
	mov	x12, #3121
	movk	x12, #12483, lsl #16
	add	x9, x10, x9, lsr #23
	movk	x12, #49932, lsl #32
	mul	x9, x9, x11
	movk	x12, #3120, lsl #48
	lsr	x9, x9, #20
	umulh	x9, x9, x12
	mov	x10, #-3689348814741910324
	add	x9, x9, #512, lsl #12           // =2097152
	movk	x10, #52429
	mul	x9, x9, x11
	umulh	x9, x9, x10
	lsr	x9, x9, #22
	add	x9, x9, #256, lsl #12           // =1048576
	mov	x10, #-6148914691236517206
	mul	x9, x9, x11
	movk	x10, #43691
	umulh	x9, x9, x10
	lsr	x9, x9, #21
	add	x9, x9, #256, lsl #12           // =1048576
	mul	x8, x9, x8
	asr	x8, x8, #24
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_3:
	mov	w11, #8704
	movk	w11, #25, lsl #16
	mov	x12, #19973
	sub	x8, x11, x8
	movk	x12, #1248, lsl #16
	mul	x11, x8, x8
	movk	x12, #57422, lsl #32
	lsr	x11, x11, #20
	movk	x12, #19972, lsl #48
	mul	x10, x11, x10
	umulh	x10, x10, x12
	mov	x12, #1681
	movk	x12, #36969, lsl #16
	add	x9, x9, x10, lsr #5
	movk	x12, #26886, lsl #32
	mul	x9, x9, x11
	movk	x12, #1680, lsl #48
	lsr	x9, x9, #20
	mov	w10, #1449132032
	umulh	x9, x9, x12
	mov	x12, #42897
	movk	x12, #30980, lsl #16
	add	x9, x9, x10
	movk	x12, #36938, lsl #32
	mul	x9, x9, x11
	movk	x12, #1191, lsl #48
	lsr	x9, x9, #20
	umulh	x9, x9, x12
	mov	x12, #58255
	mov	w10, #65011712
	movk	x12, #36408, lsl #16
	movk	x12, #14563, lsl #32
	add	x9, x9, x10
	movk	x12, #58254, lsl #48
	mul	x9, x9, x11
	mov	w10, #17825792
	umulh	x9, x9, x12
	mov	x12, #3121
	movk	x12, #12483, lsl #16
	add	x9, x10, x9, lsr #23
	movk	x12, #49932, lsl #32
	mul	x9, x9, x11
	movk	x12, #3120, lsl #48
	lsr	x9, x9, #20
	umulh	x9, x9, x12
	mov	x10, #-3689348814741910324
	add	x9, x9, #512, lsl #12           // =2097152
	movk	x10, #52429
	mul	x9, x9, x11
	umulh	x9, x9, x10
	lsr	x9, x9, #22
	mov	x12, #-6148914691236517206
	add	x9, x9, #256, lsl #12           // =1048576
	movk	x12, #43691
	mul	x9, x9, x11
	umulh	x9, x9, x12
	lsr	x9, x9, #21
	add	x9, x9, #256, lsl #12           // =1048576
	mul	x8, x9, x8
	asr	x8, x8, #24
	mov	x9, #4294967296
	sdiv	x8, x9, x8
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_4:
	mov	x0, #9223372036854775807
	ret
.Lfunc_end1:
	.size	_ZN9fixedmath3tanENS_7fixed_tE, .Lfunc_end1-_ZN9fixedmath3tanENS_7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
