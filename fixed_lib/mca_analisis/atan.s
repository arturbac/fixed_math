	.text
	.file	"atan.cc"
	.globl	_Z4atanN9fixedmath7fixed_tE     // -- Begin function _Z4atanN9fixedmath7fixed_tE
	.p2align	2
	.type	_Z4atanN9fixedmath7fixed_tE,@function
_Z4atanN9fixedmath7fixed_tE:            // @_Z4atanN9fixedmath7fixed_tE
// %bb.0:
	b	_ZN9fixedmath4atanENS_7fixed_tE
.Lfunc_end0:
	.size	_Z4atanN9fixedmath7fixed_tE, .Lfunc_end0-_Z4atanN9fixedmath7fixed_tE
                                        // -- End function
	.section	.text._ZN9fixedmath4atanENS_7fixed_tE,"axG",@progbits,_ZN9fixedmath4atanENS_7fixed_tE,comdat
	.weak	_ZN9fixedmath4atanENS_7fixed_tE // -- Begin function _ZN9fixedmath4atanENS_7fixed_tE
	.p2align	2
	.type	_ZN9fixedmath4atanENS_7fixed_tE,@function
_ZN9fixedmath4atanENS_7fixed_tE:        // @_ZN9fixedmath4atanENS_7fixed_tE
	.cfi_startproc
// %bb.0:
	cmp	x0, #0                          // =0
	mov	x11, #-37449
	mov	x8, #-43690
	mov	w9, #13107
	cneg	x12, x0, mi
	mov	w10, #14563
	movk	x11, #65534, lsl #16
	movk	x8, #65532, lsl #16
	movk	w9, #2, lsl #16
	cmp	x12, #7, lsl #12                // =28672
	movk	w10, #1, lsl #16
	b.ge	.LBB1_2
// %bb.1:
	mul	x13, x0, x0
	lsr	x13, x13, #16
	sub	x10, x10, x13
	mul	x10, x10, x13
	add	x10, x11, x10, asr #16
	mul	x10, x10, x13
	add	x9, x9, x10, asr #16
	mul	x9, x9, x13
	add	x8, x8, x9, asr #16
	mul	x8, x8, x13
	asr	x8, x8, #16
	mov	x9, #35747
	add	x8, x8, #176, lsl #12           // =720896
	movk	x9, #47662, lsl #16
	mul	x8, x8, x12
	movk	x9, #41704, lsl #32
	asr	x8, x8, #16
	movk	x9, #11915, lsl #48
	smulh	x8, x8, x9
	asr	x9, x8, #1
	add	x8, x9, x8, lsr #63
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_2:
	cmp	x12, #11, lsl #12               // =45056
	b.ge	.LBB1_4
// %bb.3:
	mov	w13, #28672
	mov	x14, #-65536
	mul	x13, x12, x13
	movk	x14, #36864, lsl #16
	lsr	x13, x13, #16
	add	x12, x14, x12, lsl #16
	add	x13, x13, #16, lsl #12          // =65536
	sdiv	x12, x12, x13
	mul	x13, x12, x12
	lsr	x13, x13, #16
	sub	x10, x10, x13
	mul	x10, x10, x13
	add	x10, x11, x10, asr #16
	mul	x10, x10, x13
	add	x9, x9, x10, asr #16
	mul	x9, x9, x13
	add	x8, x8, x9, asr #16
	mul	x8, x8, x13
	mov	x14, #35747
	asr	x8, x8, #16
	movk	x14, #47662, lsl #16
	add	x8, x8, #176, lsl #12           // =720896
	movk	x14, #41704, lsl #32
	mul	x8, x8, x12
	movk	x14, #11915, lsl #48
	asr	x8, x8, #16
	smulh	x8, x8, x14
	asr	x9, x8, #1
	add	x8, x9, x8, lsr #63
	mov	w9, #27028
	add	x8, x8, x9
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_4:
	sub	x13, x10, #2275                 // =2275
	cmp	x12, x13
	b.ge	.LBB1_6
// %bb.5:
	mov	w13, #45056
	mov	x14, #-65536
	mul	x13, x12, x13
	movk	x14, #20480, lsl #16
	lsr	x13, x13, #16
	add	x12, x14, x12, lsl #16
	add	x13, x13, #16, lsl #12          // =65536
	sdiv	x12, x12, x13
	mul	x13, x12, x12
	lsr	x13, x13, #16
	sub	x10, x10, x13
	mul	x10, x10, x13
	add	x10, x11, x10, asr #16
	mul	x10, x10, x13
	add	x9, x9, x10, asr #16
	mul	x9, x9, x13
	add	x8, x8, x9, asr #16
	mul	x8, x8, x13
	mov	x14, #35747
	asr	x8, x8, #16
	movk	x14, #47662, lsl #16
	add	x8, x8, #176, lsl #12           // =720896
	movk	x14, #41704, lsl #32
	mul	x8, x8, x12
	movk	x14, #11915, lsl #48
	asr	x8, x8, #16
	smulh	x8, x8, x14
	asr	x9, x8, #1
	add	x8, x9, x8, lsr #63
	mov	w9, #39472
	add	x8, x8, x9
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_6:
	cmp	x12, #39, lsl #12               // =159744
	b.ge	.LBB1_8
// %bb.7:
	mul	x13, x12, x13
	mov	x14, #-8589934592
	movk	x14, #53248, lsl #16
	lsr	x13, x13, #16
	add	x12, x14, x12, lsl #16
	add	x13, x13, #16, lsl #12          // =65536
	sdiv	x12, x12, x13
	mul	x13, x12, x12
	lsr	x13, x13, #16
	sub	x10, x10, x13
	mul	x10, x10, x13
	add	x10, x11, x10, asr #16
	mul	x10, x10, x13
	add	x9, x9, x10, asr #16
	mul	x9, x9, x13
	add	x8, x8, x9, asr #16
	mul	x8, x8, x13
	mov	x14, #35747
	asr	x8, x8, #16
	movk	x14, #47662, lsl #16
	add	x8, x8, #176, lsl #12           // =720896
	movk	x14, #41704, lsl #32
	mul	x8, x8, x12
	movk	x14, #11915, lsl #48
	asr	x8, x8, #16
	smulh	x8, x8, x14
	asr	x9, x8, #1
	add	x8, x9, x8, lsr #63
	mov	w9, #57076
	add	x8, x8, x9
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.LBB1_8:
	mov	w13, #28672
	movk	w13, #2, lsl #16
	mov	x14, #2415919104
	movk	x14, #65533, lsl #32
	mul	x13, x12, x13
	movk	x14, #65535, lsl #48
	lsr	x13, x13, #16
	add	x12, x14, x12, lsl #16
	add	x13, x13, #16, lsl #12          // =65536
	sdiv	x12, x12, x13
	mul	x13, x12, x12
	lsr	x13, x13, #16
	sub	x14, x10, x13
	mul	x14, x14, x13
	add	x11, x11, x14, asr #16
	mul	x11, x11, x13
	add	x9, x9, x11, asr #16
	mul	x9, x9, x13
	add	x8, x8, x9, asr #16
	mul	x8, x8, x13
	asr	x8, x8, #16
	mov	x9, #35747
	add	x8, x8, #176, lsl #12           // =720896
	movk	x9, #47662, lsl #16
	mul	x8, x8, x12
	movk	x9, #41704, lsl #32
	asr	x8, x8, #16
	movk	x9, #11915, lsl #48
	smulh	x8, x8, x9
	asr	x9, x8, #1
	add	x8, x9, x8, lsr #63
	add	x8, x10, x8
	sub	x8, x8, #2670                   // =2670
	cmp	x0, #0                          // =0
	cneg	x0, x8, lt
	ret
.Lfunc_end1:
	.size	_ZN9fixedmath4atanENS_7fixed_tE, .Lfunc_end1-_ZN9fixedmath4atanENS_7fixed_tE
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 11.0.1"
	.section	".note.GNU-stack","",@progbits
