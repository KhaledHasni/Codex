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
   * <assert.h>
   * <ctype.h>
   * <errno.h>
   * <float.h>
   * <limits.h>
   * <locale.h>
   * <math.h>
   * <setjmp.h>
   * <signal.h>
   * <stdarg.h>
   * <stddef.h>
   * <stdio.h>
   * <stdlib.h>
   * <string.h>
   * <time.h>
* C99 introduces an extra nine headers to make it a total of 24:
   * <complex.h>
   * <fenv.h>
   * <inttypes.h>
   * <iso646.h>
   * <stdbool.h>
   * <stdint.h>
   * <tgmath.h>
   * <wchar.h>
   * <wctype.h>
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
      * Example: ```NULL``` can't be reused in a file if ```<stdio.h>``` is included.
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
   * ```<assert.h>```
      * Defines the ```assert``` macro used for program diagnostics.
      * If an ```assert``` call fails, the program immediately terminates.
   * ```<ctype.h>```
      * Mainly used for character handling.
      * Contains functions used for character classification.
      * Provides functions used to convert letter characters from uppercase to lowercase or the other way around.
   * ```<errno.h>```
      * ```errno``` stands for "error number".
      * Provides ```errno``` which is an lvalue that can be checked after certain library function calls to make sure an error did not occur during the call.
   * ```<float.h>```
      * Defines macros that describe the characteristics of floating types, including their accuracy and range.
      * Floating types in C are used to represent real numbers.
      * C provides three standard floating types: ```float```, ```double``` and ```long double```.
   * ```<limits.h>```
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
   * ```<setjmp.h>```
      * Handles nonlocal jumps.
      * Mainly provides two functions:
         * ```setjmp``` : Marks a place in a program.
         * ```longjmp```: Returns to a place marked using ```setjmp```.
      * When used in tandem, these functions allow a program to jump from one function into another active function, bypassing the normal function return mechanism.   
   * ```<signal.h>```
      * Defines functions that handle exceptional conditions known as ```signals```.
      * Interrupts and run-time errors are two of the most common signals in C programs.
      * The ```signal``` function registers a function to be called should a particular signal be raised.
      * The ```raise``` function causes a signal to occur.
   * ```<stdarg.h>```
      * Provides utilities for writing functions that have a variable number of arguments.
   * ```<stddef.h>```
      * Defines some of C's most frequently used types and macros.
   * ```<stdio.h>```
      * Provides functions that handle input and output, including operations on sequential and random-access files.
   * ```<stdlib.h>```
      * Provides general utilities that don't fit into any of the other headers.
      * Contains an assortment of functions that perform several tasks including:
         * Converting strings to numbers.
         * Generating pseudo-random numbers.
         * Performing memory management tasks.
         * Performing searching and sorting.
         * Communicating with the operating system.
   * ```<string.h>```
      * Is primarily concerned with handling strings.
      * Provides functions that perform various operations on strings including:
         * Copying.
         * Concatenation.
         * Searching.
         * Comparing.
   * ```<time.h>```
      * Provides functions for handling the time and date.

## :recycle: C99 Library Changes

## :jigsaw: The <stddef.h> Header

## :white_check_mark: The <stdbool.h> Header :x:

## :game_die: Miscellaneous