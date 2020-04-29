	.file	"test.c"
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	movq	-24(%rbp), %rax
	movzbl	4(%rax), %eax
	movb	%al, -1(%rbp)
	movq	-24(%rbp), %rax
	movzbl	8(%rax), %eax
	movb	%al, -1(%rbp)
	movq	-24(%rbp), %rax
	movzbl	10(%rax), %eax
	movb	%al, -1(%rbp)
	movq	-24(%rbp), %rax
	addq	$5, %rax
	movb	$116, (%rax)
	movq	-24(%rbp), %rax
	addq	$10, %rax
	movb	$101, (%rax)
	movq	-24(%rbp), %rax
	addq	$20, %rax
	movb	$115, (%rax)
	movq	-24(%rbp), %rax
	addq	$30, %rax
	movb	$116, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	foo, .-foo
	.section	.rodata
.LC0:
	.string	"./file.txt"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$256, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L3
	movl	$-1, %eax
	jmp	.L4
.L3:
	movl	$0, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -12(%rbp)
	movq	-8(%rbp), %rcx
	movl	-12(%rbp), %eax
	movl	$256, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	read@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	close@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	foo
	movl	$0, %eax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-10ubuntu2) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
