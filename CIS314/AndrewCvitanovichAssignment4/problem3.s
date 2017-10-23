	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_f
	.p2align	4, 0x90
_f:                                     ## @f
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	imull	$3, 8(%ebp), %eax
	popl	%ebp
	retl

	.globl	_g
	.p2align	4, 0x90
_g:                                     ## @g
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$16, %esp
	movl	12(%ebp), %edi
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	calll	_f
	movl	%eax, %esi
	movl	%edi, (%esp)
	calll	_f
	addl	%esi, %eax
	addl	$16, %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	retl


.subsections_via_symbols
