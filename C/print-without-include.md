```C
// noheader.c

#define XYZ 2

int main(void) {
    printf("%d\n", XYZ);
    return 0;
}
```

```C
// withheader.c
#include <stdio.h>

#define XYZ 2

int main(void) {
    printf("%d\n", XYZ);
    return 0;
}
```

Both sources produce the same assembler code. Why? 
Although `gcc -S noheader.c.` produces warnings it still generates assembler code.

```
	.file	"..."
	.text
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$2, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
```

It even builds and run `gcc noheader.c -o noheader`. Why?

https://stackoverflow.com/questions/4654147/without-including-stdio-h

>Definition of printf() is there in libc.so and the dynamic linker will take care of it even if you don't include the header file. During compile time, printf() will be an undefined symbol and it assumes that it may find the definition later. The header file will just give the proto-type and suppress the compiler(warnings) stating that the definition of the prototype is present in glibc. So basically, the header files are included just to make sure that the definitions are available in our libraries, to help the developer.

>As Abi pointed out, your code builds successfully without including stdio.h because the linker is defaulting to the system std library for the undefined symbol (printf).

>When you use a function that has not been declared, then the compiler will assume this function returns an int and takes an unspecified, but fixed, number of arguments.

If this assumption matches with the definition of the function, and if the arguments you provided also match (modulo the default argument promotions) the parameters that the function expects to receive, then everything is well.
If the assumption is incorrect (like for printf, which is a variadic function), or when the arguments don't match, the results are undefined. One of the nasty things of undefined behaviour is that it can appear to work as expected.