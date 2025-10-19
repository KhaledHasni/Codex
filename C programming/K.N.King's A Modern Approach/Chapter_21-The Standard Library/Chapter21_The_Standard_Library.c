/* Takeaways */

/*
1) The C89 standard library is divided into 15 parts with each part described by a header file. The C99 adds 9 extra headers for a total of 24:
    *) Introduced by C89: <assert.h>, <ctype.h>, <errno.h>, <float.h>, <limits.h>, <locale.h>, <math.h>, <setjmp.h>, <signal.h>, <stdarg.h>, <stddef.h>,
<stdio.h>, <stdlib.h>, <string.h>, <time.h>
    *) Added by C99: <complex.h>, <fenv.h>, <inttypes.h>, <iso646.h>, <stdbool.h>, <stdint.h>, <tgmath.h>, <wchar.h>, <wctype.h>
2) Most compilers come with a more extensive library that has many more headers that don't appear in the list mentioned in point 1. The extra headers are not
standard though so we can't count on them being available with other compilers. These often provide functions that are specific to a particular computer or
operating system which is why they're not standard in the first place. Some of them for example provide functions that allow more control over the screen and
keyboard of the device being used. Headers that support graphics or a window-based user interface are also common.
3) The standard headers consist primarily of function prototypes, type definitions and macro definitions. If a developer writes a file that contains a call to
function declared in a header or uses one of the types or macros defined there, that file should include the header at the beginning of the file. If a file
includes several standard headers, the order in which the #include directives are called doesn't matter. It also doesn't matter if a standard header is included
more than once.
4) A file that includes a standard header must obey some rules:
    *) The file can't use the names of macros defined in that header for any other purpose. Example: If a file includes <stdio.h>, it can't reuse NULL since a
macro by that name is already defined in <stdio.h>.
    *) Library names with file scope, particularly typedef names, can't be redefined at file level. Example: If a file includes <stdio.h>, it can't define size_t
as an identifier with file scope, since <stdio.h> already defines size_t to be a typedef name.
    *) Identifiers that begin with an underscore '_' followed by an upper case letter or another underscore are reserved for use within the library and programs
should refrain from using names of this form for any purpose.
    *) Identifiers that begin with an underscore '_' are reserved for use as identifiers and tags with file scope. A programmer should therefore never use a name
of this form for any purpose unless it's for an identifier that's declared inside a function.
    *) Every identifier with external linkage in the standard library is reserved for use as an identifier with external linkage. In particular, the names of all
standard library functions are reserved. Example: Even if a file doesn't include <stdio.h>, it shouldn't define an external function called printf since there's
already a function with this name in the library.
--> These rules apply to every file in the program, regardless of which headers it includes. It's worth noting that these rules are not always enforced, but
failing to abide by them may lead to a program that's not portable. 
5) The rules mentioned in point 4 apply not just to names that are currently being used in the library, but also to names that are set aside for future use.
The complete description of which names are actually reserved for future use can be found in the C standard in the section "future library directions". Example:
C reserves identifiers that begin with str followed by a lower case letter so that functions with such names can be added to the <string.h> header.
6) It's common when developing C code to replace small functions by parameterized macros. This practice happens even in the standard library. In fact, the C
standard allows headers to define macros that have the same name as library functions but requires that a true function with that name be available as well.
Consequently, it's not unusual for a library header to declare a function and define a macro with the same name. Example: getchar is a library function declared
in the <stdio.h> header and has the following prototype: int getchar(void); but <stdio.h> usually defines getchar as a macro as well:
#define getchar getc(stdin)
--> By default, a call of getchar will be treated as a macro invocation since macro names are expanded during preprocessing. More often than not, C programmers
are happy using macros instead of functions because that makes the program run slightly faster. But at times, they might want to use true functions instead
perhaps to minimize the size of the executable code. In the latter case, we can remove the macro definition and thus gain access to the true function by using
the #undef directive. Example: We can undefine the getchar macro after including <stdio.h>:
#include <stdio.h>
#undef getchar
--> In the event that getchar is not defined as a macro in the first place, using the #undef directive macro in this manner doesn't do any harm since the #undef
macro has no effect when given a name that's not defined as a macro.
--> If we want to disable individual instances of a macro being called, we can enclose its name in parentheses. The logic behind this stems from the fact that
the preprocessor can't spot a parameterized macro unless its name is followed by an open parenthesis, while the compiler can still recognize that same name as
a function (if it's declared as such) despite the enclosing parenthesis. Example:
ch = (getchar)(); //this would replace ch = getchar();
7) The following is a brief description of each of the headers in the standard C89 library:
    *) <assert.h>: Diagnostics: Contains only the assert macro which allows us to insert self-checks into the program. If any of these checks fail, the program
terminates. 
    *) <ctype.h>: Character handling: Provides functions for classifying characters and for converting letters from upper to lower case or vice versa.
    *) <errno.h>: Errors: Provides "errno" which stands for "error number". This is an lvalue that can be tested after certain library function calls to check if
an error occurred during the call.
    *) <float.h>: Characteristics of floating types: Provides macros that describe the characteristics of floating types including their range and accuracy.
    *) <limits.h>: Sizes of integer types: Provides macros that describe the characteristics of integer types (which include character types) including their
maximum and minimum values.
    *) <locale.h>: Localization: Provides functions that help a program adapt its behavior to a country or a specific geographic location. Locale-specific
behavior includes the way numbers are printed particularly the character used as the decimal point, the format of monetary values particularly the currency
symbol, the character set and the appearance of date and time.
    *) <math.h>: Mathematics: Provides common mathematical functions including trigonometric, hyperbolic, exponential, logarithmic, power, nearest integer,
absolute value and remainder functions.
    *) <setjmp.h>: Nonlocal jumps: Provides the setjmp and longjmp functions. setjmp marks a place in a program and longjmp can be used to return to the place
in the program at a later stage. These calls make it possible to jump from one function to another still-active function, bypassing the normal function return
mechanism. setjmp and longjmp are primarily used for handling serious problems that arise during the execution of a program.
    *) <signal.h>: Signal handling: Provides functions that deal with exceptional conditions known as signals such as interrupts and run-time errors. The signal
function installs a function to be called if a given signal is called at a later stage. The raise function on the other hand causes a signal to occur.
    *) <stdarg.h>: Variable arguments: Provides tools for writing functions that have a variable number of arguments like printf and scanf.
    *) <stddef.h>: Common definitions: Provides definitions of frequently used types and macros.
    *) <stdio.h>: Input/Output: Provides a large collection of input/output functions including operations on both sequential and random-access files.
    *) <stdlib.h>: General utilities: A catch-all header for functions that don't belong into any of the other headers. The functions in this header can convert
strings to numbers, generate pseudo-random numbers, perform memory management tasks, communicate with the operating system, perform searching and sorting and
perform conversions between multibyte characters and wide characters.
    *) <string.h>: String handling: Provides functions that perform operations on strings including copying, concatenation, comparison, searching and functions
that operate on arbitrary blocks of memory.
    *) <time.h>: Date and Time: Provides functions for determining the date and time, manipulating times and formatting them for display.
8) Some of the biggest changes introduced in C99 compared to C89 affect the standard library. These changes fall into three categories:
    *) Additional headers: The C99 standard library has nine additional headers that don't exist in C89, three of which (<iso646.h>, <wchar.h> and <wctype.h>)
were added to C in 1995 when C89 was amended. The other six headers (<complex.h>, <fenv.h>, <inttypes.h>, <stdbool.h>, <stdint.h> and <tgmath.h>) are new in C99.
    *) Additional macros and functions: The C99 standard adds macros and functions to several existing headers, primarily <float.h>, <math.h> and <stdio.h>. The
additions to the <math.h> header are particularly extensive.
    *) Enhanced versions of already existing functions: Some existing functions have additional capabilities in C99 like print and scanf for example.
9) The following is a brief description of each of the headers introduced by the standard C99 standard library:
    *) <complex.h>: Complex arithmetic: Defines the complex and I macros which are useful when working with complex numbers. Also provides functions for
performing mathematical operations on complex numbers.
    *) <fenv.h>: Floating-point environment: Provides access to floating-point status flags and control modes. For example, a program might test a flag to see
if overflow occurred during a floating-point operation or set a control mode to specify how rounding should be done.
    *) <inttypes.h>: Format conversion of integer types: Defines macros that can be used in format strings for input/output of the integer types declared in
<stdint.h>. Also provides functions for working with greatest-width integers.
    *) <iso646.h>: Alternative spellings: Defines macros that represent certain operators (the ones containing the characters &, |, ~, ! and ^). These macros
are useful for writing programs in an environment where these characters might not be part of the local character set. 
    *) <stdbool.h>: Boolean type and values: Defines the bool, true and false macros as well as a macro that can be used to test whether these macros have been
defined.
    *) <stdint.h>: Integer types: Declares integer types with specified widths and defines related macros such as the ones that specifiy the maximum and minimum
value of each type. Also provides parameterized macros that construct integer constants with specific types.
    *) <tgmath.h>: Type-generic math: In C99, there are multiple versions of many functions in the <math.h> and <complex.h> headers. The type-generic macros in
<tgmath.h> can detect the types of arguments passed to them and substitute a call of the appropriate <math.h> or <complex.h> function.
    *) <wchar.h>: Extended multibyte and wide-character utilities: Provides functions for wide-character input/ouput and wide string manipulation.
    *) <wctype.h>: Wide-character classification and mapping utilities: This is the wide-character version of <ctype.h>. Provides functions for classifying and
changing the case of wide characters.
10) The <stddef.h> header provides definitions of frequently used types and macros and doesn't declare any functions. The types are:
    *) ptrdiff_t: The type of the result of subtracting one pointer from another.
    *) size_t: The type returned by the sizeof operator.
    *) wchar_t: A type that's large enough to represent all possible characters in all supported locales.
--> All three are names for integer types. ptrdiff_t must be a signed type while size_t must be an unsigned type.
11) The <stddef.h> header also defines two macros. One of them is NULL which represents the null pointer. The other macro which is offsetof requires two
arguments: type (s structure type) and member-designator (a member of the structure). The offsetof macro computes the number of bytes between the structure and
the specified member. Example: In the following structure:
struct s {
    char a;
    int b[2];
    float c;
};
The value of offsetof(struct s, a) must be 0. In fact, C guarantees that the first member of a structure has the same address as the structure itself. The offsets
of b and c are not that straightforward on the other hand. We might be tempted to say that offsetof(struct s, b) is 1 since a is 1-byte long and
offsetof(struct s, c) is 9 assuming integers are stored over 4 bytes. However, some compilers leave holes or unused bytes between members of structures which
can affect the value produced by offsetof. For example, if a compiler leaves a 3-byte hole after storing the a member of the s structure, then
offsetof(struct s, b) will produce 4 while offsetof(struct s, c) will produce 12. In any case, offsetof always produces the correct offset values no matter how the
compiler stores members of a structure which helps in writing portable programs.
12) The offsetof macro can be useful in many ways. For example, based on the declaration of the s structure in point 11, if we want to save the first two members
of an s structure in a file and ignore the c member, traditionally, we would have the fwrite function write sizeof(struct s) bytes which would save the entire
structure. Instead, we can instruct fwrite to write offsetof(struct s, c) bytes.
13) Some of the types and macros defined <stddef.h> appear in other headers as well. For example, the NULL macro is also defined in <locale.h>, <stdio.h>,
<string.h>, <stdlib.h>, <time.h> and <wchar.h>. Consequently, few programs need to include <stddef.h>.
14) The <stdbool.h> header defines four macros:
    *) bool: Defined to be _Bool.
    *) true: Defined to be 1.
    *) false: Defined to be 0.
    *) __bool_true_false_are_defined: Defined to be 1.
--> A program could for example use a preprocessing #if or #ifdef directive to test the __bool_true_false_are_defined before attempting to define its own version
of bool, true or false.
15) According to the C standard, a standard header need not be a file. Although most compilers do indeed store standard headers as files, the header could
alternatively be built into the compiler itself.
16) According to the C standard, a parameterized macro that substitutes for a library function must be fully protected by parentheses and must evaluate its
arguments exactly once.
*/