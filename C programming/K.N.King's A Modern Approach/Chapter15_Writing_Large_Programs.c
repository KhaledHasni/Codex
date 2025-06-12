/* Takeaways */

/*
1) A C program can contain a single file just as it can be divided among multiple source files. A source file by default has the extension .c and contains
function definitions and variables. One of these source files in a program must contain a function called "main" which will serve as the entry point of
the program.
2) Let's look at a case study: Suppose we want to write a program that simulates a calculator that evaluates integer expressions entered in Reverse Polish
notation (RPN). This is a notation where operators follow their operands like this for example: 30 5 - 7 *. One strategy we can use to create such a program
is to have it read the integer expression one token at a time, compute and store the intermediate results in a data structure like a stack for example. If
the program reads a number, it gets pushed onto the stack, if it reads an operator, 2 numbers get popped from the stuck, they will serve as that operator's
two operands, the result is computed then pushed back onto the stack. By the time the program would have read all of the user's input, the final result would
be available in the stack.
3) So if we apply the previous algorithm on the following RPN expression: 30 5 - 7 *, this is how it would get resolved:
    *) The program reads the first token, 30 and pushed it onto the stack.
    *) The program reads the next tpken, 5 and pushed it onto the stack.
    *) The program reads the next token, - which is an operator so it pops its two operands from the stack which would be 30 and 5.
    *) The program computes the result of 30 - 5 which is 25 and pushes it onto the stack.
    *) The program reads the next token, 7 and pushes it onto the stack.
    *) The program reads the final token, * which is an operator so it pops its two operands from the stack which would be 25 and 7.
    *) The program computes the result of 25 * 7 which is 175 and pushes it onto the stack.
4) Turning this algorithm into a program isn't hard, we could just write a loop in its main function that would read a token from the user's input, if that
token is a number, it will push it onto the stack, if its an operand, it would pop its two operands from the stack, compute the result of the operation and
push the result onto the stack.
5) The previous example shows that it makes sense to divide a program into source files that have semantically related elements. So for example, the function
that would read the tokens one at a time from the user's input can go into a separate file that might be called token.c, along with any other functions or
variables that have to do with tokens. Functions that are related to the stack like push(), pop(), is_empty(), is_full(), clear_stack() can all go in a file
called stack.c along with the actual data structure that would represent the stack itself like an array for example. The main function could go in another
file called calc.c for example.
6) Splitting a C program into multiple source files has a lot of advantages:
    *) Grouping related functions and variables into a single program helps clrify the structure of the program.
    *) Each source file can be compiled separately which saves a lot of time especially if the program is large and changes frequently.
    *) It makes the program more modular which makes it easier to maintain, easier to debug, and makes large portions of it reusable.
7) When we split a program over multiple source files, these files will more than likely need to be able to share information. Otherwise, how would a function
in a file call another function defined in a different file? And how would two files be able to share macro definitions or type definitions? And what if a
function in a file needs an external variable declared in a different file? This sharing of information happens through the #include directive.
8) The #include directive instructs the preprocessor to open a specified file and insert its contents into the file where the directive is being expanded. So
if we want several source files to have access to the same information, we can technically put that information in a file and include it in all those source
files using the #include directive. These files that get included are called "header files" or sometimes "include files" and usually have the extension .h.
9) The C standard calls all files written by the developer "source files", not just .c files.
10) The #include directive has two forms:
    *) #include <filename> --> used for header files that belong to C's own library.
    *) #include "filename" --> used for all other files including the ones we write.
This difference stems from how the compiler would go about locating the file to be included.
    *) #include <filename> means search for file in the directory (or directories) where system header files reside. On UNIX systems for example, system header
files can be found in /usr/include.
    *) #include "filename" means search the current directory then the directory (or directories) where system header files reside.
11) We can usually change the places to be searched for header files using a command-line option like -Ipath.
12) We shouldn't use <> when including header files that we have written, as the preprocessor will go look for it where the system header files are kept and won't
find it.
13) The filename provided to an include directive may contain information that helps locate the file such as a directory path or drive specifier. Examples:
    *) #include "C:\cprogs\utils.h" --> On a Windows system.
    *) #include "/cprogs/utils.h" --> On a UNIX system.
14) Although filenames in #include directives are surrounded by "" which makes thel look like string literals, the preprocessor doesn't treat them that way. In fact,
had they been treated as string literals, the Windows example from above would have been problematic since \c and \u would have been treated as escape sequences.
15) It's usually best not to include path or drive information in include directives as it makes it harder for such a program to be transported to another machine or
operating system.
16) Using "utils.h" and "..\include\utils.h" instead of "d:utils.h" and "d:\cprogs\include\utils.h" respectively is better since they don't mention any specific drives
and paths are relative rather than absolute.
17) There's a third, less frequently used form of the #include directive: #include tokens, where tokens is any series of preprocessing tokens. These tokens get scanned
by the preprocessor for any macros that it might find. The resulting directive after macro replacement must match one of the other two forms of the #include directive.
This allows the included filename to be defined by a macro rather than hardcoded in the #include directive. Example:
#if defined (IA32)
    #define CPU_FILE "ia32.h"
#elif define (IA64)
    #define CPU_FILE "ia64.h"
#elif defined (AMD64)
    #define CPU_FILE "amd64.h"
#endif
#include CPU_FILE
18) Most large programs need to share macro and type definitions between source files to some extent. For example, consider the case where we need to define macros named
BOOL, TRUE and FALSE to incorporate a boolean logic into our program. C99 already has these defined in <stdbool.h> but let's assume we can't use C99 for now. We can
define these macros in every source file that needs them or, we can go down a better route by defining them in a header file called boolean.h and include that file in all
source files that need those definitions:
#define BOOL  int
#define TRUE  1
#define FALSE 0
We could have replaced the BOOL macro defintion by a type definition since they're also just as common as macro definitions in geader files:
#define TRUE  1
#define FALSE 0
typedef int   Bool;
19) Defining types and macros in header files has a lot of advantages:
    *) We save time as developers by not having to manually copy these definitions to all source files that need them.
    *) We mitigate the risk of inconsistencies between source files when it comes to these definitions.
    *) The program becomes much easier to modify. We can change the definitions of types and macros in a single header file instead of chasing them across multiple source files.
20)  

*/