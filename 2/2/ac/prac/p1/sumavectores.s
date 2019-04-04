	.file	"sumavectores.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\302\272 componentes del vector"
	.align 8
.LC4:
	.string	"Tiempo(seg.):%11.9f\t / Tama\303\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / /  V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$48, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L10
	xorl	%eax, %eax
	movsd	.LC1(%rip), %xmm3
	movsd	.LC2(%rip), %xmm1
	leaq	v1(%rip), %rbx
	leaq	v2(%rip), %rbp
	.p2align 4,,10
	.p2align 3
.L2:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm7
	cvtsi2sd	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	movapd	%xmm0, %xmm2
	subsd	%xmm0, %xmm7
	addsd	%xmm1, %xmm2
	movsd	%xmm7, 0(%rbp,%rax,8)
	movsd	%xmm2, (%rbx,%rax,8)
	addq	$1, %rax
	cmpq	$33554432, %rax
	jne	.L2
	movq	%rsp, %rsi
	xorl	%edi, %edi
	leaq	v3(%rip), %r12
	call	clock_gettime@PLT
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movsd	(%rbx,%rax), %xmm0
	addsd	0(%rbp,%rax), %xmm0
	movsd	%xmm0, (%r12,%rax)
	addq	$8, %rax
	cmpq	$268435456, %rax
	jne	.L3
	xorl	%edi, %edi
	leaq	16(%rsp), %rsi
	call	clock_gettime@PLT
	movq	24(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	8(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC3(%rip), %xmm0
	movsd	268435448(%r12), %xmm6
	movsd	268435448(%rbp), %xmm5
	movsd	(%r12), %xmm3
	movsd	0(%rbp), %xmm2
	movl	$33554431, %edx
	movl	$33554431, %r8d
	movl	$33554431, %ecx
	movsd	268435448(%rbx), %xmm4
	movl	$33554432, %esi
	leaq	.LC4(%rip), %rdi
	movl	$7, %eax
	addsd	%xmm1, %xmm0
	movsd	(%rbx), %xmm1
	call	printf@PLT
	xorl	%eax, %eax
	movq	40(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L11
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L10:
	.cfi_restore_state
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	orl	$-1, %edi
	call	exit@PLT
.L11:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.comm	v3,268435456,32
	.comm	v2,268435456,32
	.comm	v1,268435456,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	2576980378
	.long	1069128089
	.align 8
.LC2:
	.long	2576980378
	.long	1095342489
	.align 8
.LC3:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 8.2.1 20181127"
	.section	.note.GNU-stack,"",@progbits
