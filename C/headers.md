
# cpp - The C Preprocessor

The C preprocessor, often known as cpp, is a macro processor that is used automatically by the C compiler to transform your program before compilation.  It is called a macro processor because it allows you to define macros, which are brief abbreviations for longer constructs.

```
$ echo '#include <stdio.h>' | cpp -H -o /dev/null

. /usr/include/stdio.h
.. /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
... /usr/include/features.h
.... /usr/include/features-time64.h
..... /usr/include/x86_64-linux-gnu/bits/wordsize.h
..... /usr/include/x86_64-linux-gnu/bits/timesize.h
...... /usr/include/x86_64-linux-gnu/bits/wordsize.h
.... /usr/include/x86_64-linux-gnu/sys/cdefs.h
..... /usr/include/x86_64-linux-gnu/bits/wordsize.h
..... /usr/include/x86_64-linux-gnu/bits/long-double.h
.... /usr/include/x86_64-linux-gnu/gnu/stubs.h
..... /usr/include/x86_64-linux-gnu/gnu/stubs-64.h
.. /usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h
.. /usr/lib/gcc/x86_64-linux-gnu/11/include/stdarg.h
.. /usr/include/x86_64-linux-gnu/bits/types.h
... /usr/include/x86_64-linux-gnu/bits/wordsize.h
... /usr/include/x86_64-linux-gnu/bits/timesize.h
.... /usr/include/x86_64-linux-gnu/bits/wordsize.h
... /usr/include/x86_64-linux-gnu/bits/typesizes.h
... /usr/include/x86_64-linux-gnu/bits/time64.h
.. /usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h
... /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
.. /usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h
.. /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
.. /usr/include/x86_64-linux-gnu/bits/types/FILE.h
.. /usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h
.. /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
.. /usr/include/x86_64-linux-gnu/bits/floatn.h
... /usr/include/x86_64-linux-gnu/bits/floatn-common.h
.... /usr/include/x86_64-linux-gnu/bits/long-double.h
Multiple include guards may be useful for:
/usr/include/features-time64.h
/usr/include/x86_64-linux-gnu/bits/libc-header-start.h
/usr/include/x86_64-linux-gnu/bits/time64.h
/usr/include/x86_64-linux-gnu/bits/typesizes.h
/usr/include/x86_64-linux-gnu/gnu/stubs-64.h
/usr/include/x86_64-linux-gnu/gnu/stubs.h
/usr/lib/gcc/x86_64-linux-gnu/11/include/stddef.h

```