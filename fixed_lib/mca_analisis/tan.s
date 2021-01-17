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
	mov	x8, #12127
	movk	x8, #29010, lsl #16
	cmp	x0, #0                          // =0
	movk	x8, #52354, lsl #32
	movk	x8, #20860, lsl #48
	cneg	x11, x0, mi
	mov	w9, #9279
	mov	w10, #37407
	umulh	x8, x11, x8
	movk	w9, #3, lsl #16
	movk	w10, #1, lsl #16
	lsr	x8, x8, #16
	cmp	x11, x10
	msub	x8, x8, x9, x11
	csel	x8, x8, x11, gt
	add	x9, x10, #1                     // =1
	cmp	x8, x9
	b.eq	.LBB1_9
// %bb.1:
	lsr	x9, x8, #4
	cmp	x9, #3216                       // =3216
	b.hi	.LBB1_3
// %bb.2:
	mov	x11, #19973
	mul	x9, x8, x8
	mov	w10, #12065
	movk	x11, #1248, lsl #16
	movk	w10, #14, lsl #16
	movk	x11, #57422, lsl #32
	lsr	x9, x9, #16
	movk	x11, #19972, lsl #48
	mul	x10, x9, x10
	umulh	x10, x10, x11
	mov	w11, #1431568384
	add	x10, x11, x10, lsr #5
	mov	x11, #1681
	movk	x11, #36969, lsl #16
	movk	x11, #26886, lsl #32
	mul	x10, x10, x9
	movk	x11, #1680, lsl #48
	lsr	x10, x10, #16
	umulh	x10, x10, x11
	mov	w11, #90570752
	add	x10, x10, x11
	mov	x11, #42897
	movk	x11, #30980, lsl #16
	movk	x11, #36938, lsl #32
	mul	x10, x10, x9
	movk	x11, #1191, lsl #48
	lsr	x10, x10, #16
	umulh	x10, x10, x11
	mov	x11, #58255
	movk	x11, #36408, lsl #16
	movk	x11, #14563, lsl #32
	add	x10, x10, #992, lsl #12         // =4063232
	movk	x11, #58254, lsl #48
	mul	x10, x10, x9
	umulh	x10, x10, x11
	mov	x11, #3121
	lsr	x10, x10, #19
	movk	x11, #12483, lsl #16
	add	x10, x10, #272, lsl #12         // =1114112
	movk	x11, #49932, lsl #32
	mul	x10, x10, x9
	movk	x11, #3120, lsl #48
	lsr	x10, x10, #16
	umulh	x10, x10, x11
	mov	x11, #-3689348814741910324
	add	x10, x10, #32, lsl #12          // =131072
	movk	x11, #52429
	mul	x10, x10, x9
	umulh	x10, x10, x11
	lsr	x10, x10, #18
	add	w10, w10, #16, lsl #12          // =65536
	mul	w9, w10, w9
	mov	w10, #43691
	movk	w10, #43690, lsl #16
	umull	x9, w9, w10
	lsr	x9, x9, #49
	orr	w9, w9, #0x10000
	mul	x8, x8, x9
	lsr	x8, x8, #16
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_3:
	mov	w9, #3092
	movk	w9, #1, lsl #16
	cmp	x8, x9
	b.hi	.LBB1_5
// %bb.4:
	mov	x9, #-51472
	add	x8, x8, x9
	mov	w10, #12065
	mul	x9, x8, x8
	movk	w10, #14, lsl #16
	mov	w11, #33081
	lsr	x9, x9, #16
	movk	w11, #14355, lsl #16
	mul	w10, w9, w10
	umull	x11, w10, w11
	lsr	x11, x11, #32
	sub	w10, w10, w11
	add	w10, w11, w10, lsr #1
	mov	w11, #1431568384
	add	w10, w11, w10, lsr #6
	mov	x11, #1681
	movk	x11, #36969, lsl #16
	movk	x11, #26886, lsl #32
	mul	x10, x9, x10
	movk	x11, #1680, lsl #48
	lsr	x10, x10, #16
	umulh	x10, x10, x11
	mov	w11, #90570752
	add	x10, x10, x11
	mov	x11, #42897
	movk	x11, #30980, lsl #16
	movk	x11, #36938, lsl #32
	mul	x10, x10, x9
	movk	x11, #1191, lsl #48
	lsr	x10, x10, #16
	umulh	x10, x10, x11
	mov	x11, #58255
	movk	x11, #36408, lsl #16
	movk	x11, #14563, lsl #32
	add	x10, x10, #992, lsl #12         // =4063232
	movk	x11, #58254, lsl #48
	mul	x10, x10, x9
	umulh	x10, x10, x11
	mov	x11, #3121
	lsr	x10, x10, #19
	movk	x11, #12483, lsl #16
	add	x10, x10, #272, lsl #12         // =1114112
	movk	x11, #49932, lsl #32
	mul	x10, x10, x9
	movk	x11, #3120, lsl #48
	lsr	x10, x10, #16
	umulh	x10, x10, x11
	mov	w11, #52429
	add	w10, w10, #32, lsl #12          // =131072
	movk	w11, #52428, lsl #16
	mul	w10, w10, w9
	umull	x10, w10, w11
	lsr	x10, x10, #50
	mov	w11, #43691
	orr	w10, w10, #0x10000
	movk	w11, #43690, lsl #16
	mul	w9, w10, w9
	umull	x9, w9, w11
	lsr	x9, x9, #49
	orr	w9, w9, #0x10000
	mov	w10, #65536
	mov	x11, #4294967296
	mul	x8, x8, x9
	sub	x9, x10, x8, asr #16
	add	x8, x8, x11
	and	x8, x8, #0xffffffffffff0000
	sdiv	x8, x8, x9
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_5:
	mov	w9, #30544
	movk	w9, #1, lsl #16
	cmp	x8, x9
	mov	w9, #12065
	movk	w9, #14, lsl #16
	b.hi	.LBB1_7
// %bb.6:
	mov	x10, #-3093
	movk	x10, #65534, lsl #16
	mov	x11, #19973
	add	x8, x8, x10
	movk	x11, #1248, lsl #16
	mul	x10, x8, x8
	movk	x11, #57422, lsl #32
	lsr	x10, x10, #16
	movk	x11, #19972, lsl #48
	mul	x9, x10, x9
	umulh	x9, x9, x11
	mov	w11, #1431568384
	add	x9, x11, x9, lsr #5
	mov	x11, #1681
	movk	x11, #36969, lsl #16
	movk	x11, #26886, lsl #32
	mul	x9, x9, x10
	movk	x11, #1680, lsl #48
	lsr	x9, x9, #16
	umulh	x9, x9, x11
	mov	w11, #90570752
	add	x9, x9, x11
	mov	x11, #42897
	movk	x11, #30980, lsl #16
	movk	x11, #36938, lsl #32
	mul	x9, x9, x10
	movk	x11, #1191, lsl #48
	lsr	x9, x9, #16
	umulh	x9, x9, x11
	mov	x11, #58255
	movk	x11, #36408, lsl #16
	movk	x11, #14563, lsl #32
	add	x9, x9, #992, lsl #12           // =4063232
	movk	x11, #58254, lsl #48
	mul	x9, x9, x10
	umulh	x9, x9, x11
	mov	x11, #3121
	lsr	x9, x9, #19
	movk	x11, #12483, lsl #16
	add	x9, x9, #272, lsl #12           // =1114112
	movk	x11, #49932, lsl #32
	mul	x9, x9, x10
	movk	x11, #3120, lsl #48
	lsr	x9, x9, #16
	umulh	x9, x9, x11
	mov	w11, #52429
	add	w9, w9, #32, lsl #12            // =131072
	movk	w11, #52428, lsl #16
	mul	w9, w9, w10
	umull	x9, w9, w11
	lsr	x9, x9, #50
	mov	w11, #43691
	orr	w9, w9, #0x10000
	movk	w11, #43690, lsl #16
	mul	w9, w9, w10
	umull	x9, w9, w11
	lsr	x9, x9, #49
	orr	w9, w9, #0x10000
	mov	w10, #47976
	mul	x8, x8, x9
	mov	x9, #3144155136
	movk	w10, #1, lsl #16
	mov	w11, #65536
	movk	x9, #1, lsl #32
	b	.LBB1_8
.LBB1_7:
	mov	x10, #-30545
	movk	x10, #65534, lsl #16
	mov	x11, #19973
	add	x8, x8, x10
	movk	x11, #1248, lsl #16
	mul	x10, x8, x8
	movk	x11, #57422, lsl #32
	lsr	x10, x10, #16
	movk	x11, #19972, lsl #48
	mul	x9, x10, x9
	umulh	x9, x9, x11
	mov	w11, #1431568384
	add	x9, x11, x9, lsr #5
	mov	x11, #1681
	movk	x11, #36969, lsl #16
	movk	x11, #26886, lsl #32
	mul	x9, x9, x10
	movk	x11, #1680, lsl #48
	lsr	x9, x9, #16
	umulh	x9, x9, x11
	mov	w11, #90570752
	add	x9, x9, x11
	mov	x11, #42897
	movk	x11, #30980, lsl #16
	movk	x11, #36938, lsl #32
	mul	x9, x9, x10
	movk	x11, #1191, lsl #48
	lsr	x9, x9, #16
	umulh	x9, x9, x11
	mov	x11, #58255
	movk	x11, #36408, lsl #16
	movk	x11, #14563, lsl #32
	add	x9, x9, #992, lsl #12           // =4063232
	movk	x11, #58254, lsl #48
	mul	x9, x9, x10
	umulh	x9, x9, x11
	mov	x11, #3121
	lsr	x9, x9, #19
	movk	x11, #12483, lsl #16
	add	x9, x9, #272, lsl #12           // =1114112
	movk	x11, #49932, lsl #32
	mul	x9, x9, x10
	movk	x11, #3120, lsl #48
	lsr	x9, x9, #16
	umulh	x9, x9, x11
	mov	x11, #-3689348814741910324
	add	x9, x9, #32, lsl #12            // =131072
	movk	x11, #52429
	mul	x9, x9, x10
	umulh	x9, x9, x11
	lsr	x9, x9, #18
	mov	x11, #-6148914691236517206
	add	x9, x9, #16, lsl #12            // =65536
	movk	x11, #43691
	mul	x9, x9, x10
	umulh	x9, x9, x11
	lsr	x9, x9, #17
	add	x9, x9, #16, lsl #12            // =65536
	mov	w10, #33728
	mul	x8, x9, x8
	mov	x9, #2210398208
	movk	w10, #9, lsl #16
	mov	w11, #65536
	movk	x9, #9, lsl #32
.LBB1_8:
	add	x9, x8, x9
	asr	x8, x8, #16
	mul	x8, x8, x10
	sub	x8, x11, x8, asr #16
	and	x9, x9, #0xffffffffffff0000
	sdiv	x8, x9, x8
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_9:
	mov	x0, #9223372036854775807
	ret
.Lfunc_end1:
	.size	_ZN9fixedmath3tanENS_7fixed_tE, .Lfunc_end1-_ZN9fixedmath3tanENS_7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
