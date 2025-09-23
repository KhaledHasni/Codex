<h1 align="center">💡<strong> The Standard Library</strong></h1>
<p align="center">
  <a href="#books-using-the-library">Using The Library</a> •
  <a href="#mag-c89-library-overview">C89 Library Overview</a> •
  <a href="#recycle-c99-library-changes">C99 Library Changes</a> •
  <a href="#jigsaw-the-stddefh-header">The &lt;stddef.h&gt; Header</a> •
  <a href="#white_check_mark-the-stdboolh-header-x">The &lt;stdbool.h&gt; Header</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :books: Using The Library

* The C89 standard library has 15 headers:
   * assert.h
   * ctype.h
   * errno.h
   * float.h
   * limits.h
   * locale.h
   * math.h
   * setjmp.h
   * signal.h
   * stdarg.h
   * stddef.h
   * stdio.h
   * stdlib.h
   * string.h
   * time.h
* C99 introduces an extra nine headers to make it a total of 24:
   * complex.h
   * fenv.h
   * inttypes.h
   * iso646.h
   * stdbool.h
   * stdint.h
   * tgmath.h
   * wchar.h
   * wctype.h
* These 24 headers constitute C99's standard library, which is an inherent part of the C programming language.
* Some C compilers provide a more extensive library. The extra headers are not part of the standard library. They usually provide platform-specific utilities.
* C's standard headers mostly contain:
   * Function prototypes.
   * Type definitions.
   * Macro definitions.
* Including a standard header requires the use of the ```#include``` preprocessor directive.
   * The order in which standard headers are included in a source file is irrelevant.
   * C allows including a standard header more than once in the same source file.
* When using C's standard library, it's important to keep some rules in mind to avoid portability issues:
   * A C file that includes a standard header can't use any macro defined in that header for a different purpose.
      * Example: ```NULL``` can't be reused in a file if ```stdio.h``` is included.
   * A C file that includes a standard header can't redefine an identifier with file scope, particularly a typedef name, and grant it file scope.
      * Example: ```size_t``` can't be redefined with file scope if ```stdio.h``` is included.
      * If ```stdio.h``` is included, ```size_t``` can still be redefined if given a different scope (block scope for example).
      * If ```stdio.h``` is not included, ```size_t``` can be redefined anywhere in a file and can even be given file scope.
      * Needless to say that redefining ```size_t```, although allowed in some cases, is a bad idea and undermines program portability and scalability.
   * Identifiers with names that begin with an underscore ```_``` followed by another underscore or an uppercase letter, are reserved for use inside the library. Programs should avoid using such names.
   * Identifiers with names that begin with an underscore are reserved for use as identifiers and tags with file scope. Programs should not use such names for identifiers unless they denote objects that don't have file scope.
   * Identifiers with external linkage in the standard library are reserved for use as identifiers with external linkage.
      * A direct implication of this is that the names of all standard library functions are reserved.
      * A program cannot define a function that shares the name of a standard library function even in files that don't include the corresponding standard header.
   * All these rules apply to identifiers currently defined in the standard library. They also apply to identifier names reserved for future use by the standard library.
      * The full list of identifier names reserved for future use is found in the C standard under "Future Library Directions".
* It's not uncommon for the C standard library and for some C programmers to define parameterized macros with the same names as some standard library functions.
   * When this is done, the macro overrides the function since macros are expanded during preprocessing.
   * This practice helps make programs faster by avoiding function call overhead.
* Assuming we have a function that has the same name as a parameterized macro.
   * When the actual function call is needed, the macro definition can be undone using the ```#undef``` directive.
   * Alternatively, individual uses of the macro can be wrapped in parentheses.
      * The preprocessor doesn't recognize a parameterized macro unless its name is immediately followed by a left parenthesis.
      * The compiler, unlike the preprocessor, will recognize the identifier as a function call.

## :mag: C89 Library Overview

* The following is a rundown of C89's standard headers:
   * ```assert.h```
      * Defines the ```assert``` macro used for program diagnostics.
      * If an ```assert``` call fails, the program immediately terminates.
   * ```ctype.h```
      * Mainly used for character handling.
      * Contains functions used for character classification.
      * Provides functions used to convert letter characters from uppercase to lowercase or the other way around.
   * ```errno.h```
      * ```errno``` stands for "error number".
      * Provides ```errno``` which is an lvalue that can be checked after certain library function calls to make sure an error did not occur during the call.
   * ```float.h```
      * Defines macros that describe the characteristics of floating types, including their accuracy and range.
      * Floating types in C are used to represent real numbers.
      * C provides three standard floating types: ```float```, ```double``` and ```long double```.
   * ```limits.h```
      * Is primarily concerned with sizes of integer types.
      * Defines macros that describe the characteristics of integer types (including character types), including their maximum and minimum values.
   * ```locale.h```
      * Provides utilities and functions that allow a program to adapt its behavior to a particular geographic area. This includes:
         * The character set.
         * Date and time formats.
         * The format of monetary values (the currency symbol for example).
         * The character used as the decimal point when printing floating-point numbers.
   * ```math.h```
      * Provides common mathematical functions including:
         * Logarithmic functions.
         * Exponential functions.
         * Trigonometric functions.
         * Hyperbolic functions.
         * Absolute value.
         * Nearest integers.
   * ```setjmp.h```
      * Handles nonlocal jumps.
      * Mainly provides two functions:
         * ```setjmp``` : Marks a place in a program.
         * ```longjmp```: Returns to a place marked using ```setjmp```.
      * When used in tandem, these functions allow a program to jump from one function into another active function, bypassing the normal function return mechanism.
   * ```signal.h```
      * Defines functions that handle exceptional conditions known as ```signals```.
      * Interrupts and run-time errors are two of the most common signals in C programs.
      * The ```signal``` function registers a function to be called should a particular signal be raised.
      * The ```raise``` function causes a signal to occur.
   * ```stdarg.h```
      * Provides utilities for writing functions that have a variable number of arguments.
   * ```stddef.h```
      * Defines some of C's most frequently used types and macros.
   * ```stdio.h```
      * Provides functions that handle input and output, including operations on sequential and random-access files.
   * ```stdlib.h```
      * Provides general utilities that don't fit into any of the other headers.
      * Contains an assortment of functions that perform several tasks including:
         * Converting strings to numbers.
         * Generating pseudo-random numbers.
         * Performing memory management tasks.
         * Performing searching and sorting.
         * Communicating with the operating system.
   * ```string.h```
      * Is primarily concerned with handling strings.
      * Provides functions that perform various operations on strings including:
         * Copying.
         * Concatenation.
         * Searching.
         * Comparing.
   * ```time.h```
      * Provides functions for handling the time and date.

## :recycle: C99 Library Changes

* C99 introduced an extensive set of changes that can be broken down into three groups:
   * New headers.
      * Nine new headers are introduced.
      * Three of these headers were actually introduced in C's 1995 amendment (```iso646.h```, ```wchar.h``` and ```wctype.h```).
   * New macros and functions introduced to existing headers.
   * New capabilities added to existing functions.
* The following is a rundown of C99's new standard headers:
   * ```complex.h```
      * Provides functions that can be used to perform mathematical operations on complex numbers.
      * Defines the ```complex``` and ```I``` macros used in complex arithmetic.
   * ```fenv.h```
      * Provides access to floating-point control modes.
         * This can be used to specify how rounding a floating-point number should be done.
      * Provides access to floating-point status flags.
         * This can be used to check if overflow occurred during an operation on a floating-point number.
   * ```inttypes.h```
      * Defines a set of macros that can be used in format strings involving integer types defined in ```stdint.h```.
      * Provides utilities for working with greatest-width integers such as ```intmax_t```.
   * ```iso646.h```
      * Defines macros that provide alternative spellings for some characters that might not be part of the character set available on some platforms.
      * The macros provided are used primarily to represent operators that are written using one or more of these symbols: ```&```, ```|```, ```~```, ```!``` and ```^```.
   * ```stdbool.h```
      * Primarily useful for its ```bool```, ```true``` and ```false``` macros.
   * ```stdint.h```
      * Declares integer types with specific widths.
      * Defines macros that specify the maximum and minimum value of each integer type.
   * ```tgmath.h```
      * C99 provides multiple versions of certain math functions, split between ```math.h``` and ```complex.h```.
      * ```tgmath.h``` defines type-generic macros that can detect the correct version of the call based on the arguments passed and substitute a call of the appropriate function.
   * ```wchar.h```
      * Includes multibyte and wide character utilities.
      * Provides utilities for wide character input/output and wide string manipulation.
   * ```wctype.h```
      * Offers the wide-character version of ```ctype.h```.
      * Provides functions for changing the case of wide characters.

## :jigsaw: The <stddef.h> Header

* ```stddef.h``` provides definitions of frequently used types and macros. It doesn't define any functions.
* The types defined in ```stddef.h``` are:
   * ```ptrdiff_t```: The type of the result when the difference between two pointers is computed. This is a signed type.
   * ```size_t```: The type of the result produced by the ```sizeof``` operator. This is an unsigned type.
   * ```wchar_t```: A type designed to be large enough to represent characters in all supported locales.
   * All three are integer types.
* ```stddef.h``` defines the ```NULL``` macro which represents the null pointer.
* ```stddef.h``` also defines a parameterized macro called ```offsetof``` which takes two arguments:
   * ```type```: A structure type.
   * ```member-designator```: A member within the structure.
* The ```offsetof``` macro computes the number of bytes between the beginning of the structure passed as argument, and the designated member.
   * C guarantees that a structure and its first member share the same address.
      * As a result, assuming the following declaration is in effect:
      ```c
      struct s {
         char a;
         int n;
         char str[10];
      };
      ```
         * ```offsetof(struct s, a)``` is equal to ```0```.
         * ```offsetof(struct s, n)``` could be either:
            * ```1``` (```char``` values are 1 byte long).
            * ```4``` if the compiler doesn't pack structure members and leaves padding bytes between.
            * Other values are also possible.
   * ```offsetof``` is guaranteed to produce the correct byte offset whether the compiler leaves holes or not, and irrespective of the platform being used.
* Some of the macros defined in ```stddef.h``` are defined in other standard headers as well. For this reason, most programs don't include ```stddef.h```.

## :white_check_mark: The <stdbool.h> Header :x:

* The ```stdbool.h``` standard header is a C99 addition.
* ```stdbool.h``` defines four macros:
   * ```bool``` represents C99's ```_Bool``` type.
   * ```true``` defined to be ```1```.
   * ```false``` defined to be ```0```.
   * ```__bool_true_false_are_defined``` defined to be ```1```.

## :game_die: Miscellaneous

* According to the C standard, standard headers don't need to be stored in files. In most cases, the headers come in the form of files, but in some cases, they could be built into the compiler itself. For this reason, it's best to say "standard headers" instead of "standard header files".
* According to the C standard, parameterized macros that substitute for library functions must satisfy two conditions:
   * They must evaluate their arguments exactly once.
      * This avoids some of C's classic pitfalls when using parameterized macros.
      * Suppose we have the following parameterized macro:
      ```c
      #define SQUARE(x) ((x) * (x))
      ```
         * This macro will evaluate its argument ```x``` twice. If ```x``` has side effects, it will be evaluated twice.
         * An equivalent function will only evaluate its argument once.
   * They must be fully protected using parentheses.
      * This avoids operator precedence issues when the macro is expanded.