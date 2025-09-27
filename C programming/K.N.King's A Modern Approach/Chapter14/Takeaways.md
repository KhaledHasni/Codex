<h1 align="center">💡<strong> The Preprocessor</strong></h1>
<p align="center">
  <a href="#wrench-how-the-preprocessor-works">How The Preprocessor Works</a> •
  <a href="#magic_wand-preprocessing-directives">Preprocessing Directives</a> •
  <a href="#label-macro-definitions">Macro Definitions</a> •
  <a href="#vertical_traffic_light-conditional-compilation">Conditional Compilation</a> •
  <a href="#toolbox-other-directives">Other Directives</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :wrench: How The Preprocessor Works

* The preprocessor is controlled by a special type of commands called "preprocessing directives".
   * These are commands in a C program that begin with the ```#``` character.
* Two of the most common preprocessing directives are ```#define``` and ```#include```.
   * The ```#define``` directive defines what is called a "macro".
      * A macro is a name that represents something else, usually a frequently used constant or expression.
      * When the preprocessor executes a ```#define``` directive, it stores the macro along with the value it represents called its "definition".
      * When that macro is later encountered in the program text, the preprocessor "expands" it. This means it replaces it with the value it represents.
   * The ```#include``` directive opens a designated file and copies its content into the file being compiled.
* The preprocessor comes before the compiler in a C program's compilation chain.
   * Preprocessing is the first stage that a C program goes through when being compiled.
   * The preprocessor executes any directives contained in the original program.
   * An executed directive is then removed from the program text.
   * The preprocessor produces a modified version of the original program.
      * Lines containing preprocessing directives (except ```#include```) are replaced with empty lines.
      * The content of files included using the ```#include``` directive are pasted.
      * Macros are expanded.
      * Comments are replaced with a single space character.
      * Some preprocessors remove unnecessary whitespace characters.
* Modern C preprocessors and compilers are not necessarily distinct entities.
   * Older preprocessors used to come in the form of a program, distinct from the compiler.
   * Such preprocessors will modify the original program and feed their output into the compiler.
   * Modern preprocessors and compilers are usually bundled together.
   * Modern preprocessor output is not always pure C code.
      * A common example of this is the preprocessor's response to an ```#include``` directive, which doesn't always copy the content of files into the current translation unit. Some modern preprocessors merely make functions declared in the file, available to the current translation unit.
    * Most C compilers offer the ability to see the preprocessor's output.
       * GNU's GCC will do this when the ```-E``` option is used.
* It's important to bear in mind that the preprocessor only has a limited knowledge of the C programming language.
   * It's not uncommon for the preprocessor to create invalid statements or illegal expressions after processing a program.

## :magic_wand: Preprocessing Directives

* C's preprocessing directives can be broken down into four groups:
   * Macro definition.
      * ```#define```: Defines a macro.
      * ```#undef``` : Removes the definition of a macro.
   * File inclusion.
      * ```#include``` : Includes the content of a designated file.
   * Conditional compilation.
      * ```#if```, ```#ifdef```, ```#ifndef```, ```#elif```, ```#else``` and ```#endif```.
      * These directives cause a specific block of the program's text to be either compiled or ignored.
      * The choice of whether or not to compile the designated block of text depends on a condition that the preprocessor can test.
   * Other directives.
      * This fourth category includes all remaining directives.
      * ```#error```, ```#line``` and ```#pragma```.
* A preprocessing directive always begins with the ```#``` symbol.
   * The ```#``` symbol does not necessarily have to appear at the beginning of the line.
   * If it doesn't appear at the beginning of the line, it can only be preceded by whitespace characters.
   * The name of the directive comes right after the ```#``` symbol.
   * Any other tokens that the directive might need come last.
* C is a permissive language with regards to whitespace characters. As a result, a preprocessing directive's tokens can be separated by any number of spaces and horizontal tabs.
* A preprocessing directive ends at the first new-line character.
   * C allows writing directives on multiple lines using a technique that the C standard calls "splicing".
   * If we want to write to continue a directive on the next line, we must end the current line with a backslash character ```\```.
* A directive can be followed by a comment on the same line.
* Preprocessing directives can appear anywhere in a program, even in the middle of functions.

## :label: Macro Definitions

### :small_blue_diamond: Simple Macros

* "Simple macros", also known as "object-like macros", are macros that don't take any arguments.
* A simple macro in C has the following general form: ```#define identifier replacement_list```.
   * ```replacement_list``` is any sequence of preprocessing tokens separated by white space characters.
   * A replacement list may include identifiers, keywords, numeric constants, character constants, string literals, operators and punctuation.
   * The replacement list replaces any occurrence of the identifier in the program text once the macro is expanded.
* Any symbols following a macro's identifier are part of its replacement list. Failing to remember this rule leads to some common errors beginner C programmers make:
   * Ending a macro definition with a semicolon ```;```.
      * Although perfectly legal, the semicolon will be part of the macro's replacement list which is usually not the desired effect.
   * Adding an equal sign ```=``` between the identifier and its replacement list.
      * The preprocessor will expand every occurrence of identifier to its replacement list. There's no need for the equal sign.
   * If such mistakes slip through the preprocessor, they will be detected by the compiler.
* Simple macros are primarily used to define numeric, character and string constants.
   * Kernighan and Ritchie would call these "manifest constants".
* Using a simple macro to associate a name to a manifest constant is usually done for a variety of reasons:
   * Assigning a meaning to otherwise mysterious values. This assumes that macro names are well-chosen.
   * Mitigating the risk of typos and inconsistencies when writing the same value multiple times in a program. By defining a macro, we only have to write a value once.
   * Making it easier to modify the value later by changing it once instead of sifting through lines of code looking for all of its occurrences.
* Simple macros can be used for other reasons as well:
   * Renaming types.
      * Prior to the addition of the ```_BOOL``` type in C99, some C programmers used to define a dummy boolean type using macros: ```#define BOOL int```.
      * Using ```typedef``` is usually better to achieve this goal.
   * Creating a new syntax rule set.
      * Some C programmers use simple macros like ```#define BEGIN {``` and ```#define END }``` to replace C's compound statement delimiters (curly braces).
      * Others use simple macros to replace entire statements like ```if``` and ```for``` statements.
      * This makes programs almost impossible to read.
   * Defining a preprocessing symbol or flag for conditional compilation.
* A simple macro with an empty replacement list is perfectly legal.

### :small_blue_diamond: Parameterized Macros

* "Parameterized macros", also known as "function-like macros", are macros that expect arguments.
* A parameterized macro in C has the following general form: ```#define identifier(x1, x2,...,xn) replacement_list```.
   * All ```x``` tokens are identifiers. They are the macro's parameters.
   * C enforces no limit on the number of times these parameters can appear in the replacement list.
   * There must be no space between a parameterized macro's name and the left parenthesis enclosing its parameter list. If space is left, the preprocessor will think we're defining a simple macro.
* The occurrence of a parameterized macro after its definition is called a "macro invocation".
* When a parameterized macro is invoked, it should be supplied with as many arguments as the macro's parameters. Assuming this macro is defined ```#define identifier(x1, x2,...,xn) replacement_list```:
   * An invocation of this macro will look something like this: ```identifier(y1, y2,...,yn)```.
   * When this macro is expanded, it will be replaced by the macro's replacement list, substituting ```y1``` for ```x1```, ```y2``` for ```x2``` until all parameters are replaced.
* A parameterized macro's parameter list may be empty.
   * If that's the case, the parentheses are no longer needed.
   * Some C programmers still keep the parentheses despite the parameter list being empty. This is usually done to give the macro that distinctive function-like look.
* Using parameterized macros instead of functions has several advantages:
   * They can make programs faster.
      * A macro invocation requires no run-time overhead.
      * A function call on the other hand, usually requires saving context information and copying arguments which might cumulatively create significant run-time overhead (C99's inline functions are a noteworthy exception).
   * They can be used in more than one way.
      * Unlike functions, parameterized macros don't have typed parameters.
      * We can theoretically supply a macro with parameters of different types as long as the resulting program, after preprocessing, is valid.
      * Functions on the other hand expect arguments of a certain type.
      * Failing to supply a function with an argument of the correct type is usually an error that the compiler will detect.
* Using parameterized macros instead of functions has some disadvantages:
   * The compiled code will often be larger.
      * Every macro invocation is expanded to its replacement list which naturally increases the size of the source code.
      * This becomes even more pronounced the larger the macro's replacement list and the more times it's invoked.
      * Nesting macro invocations can quickly increase the size of the compiled code as well.
   * Type-checking can't be performed.
      * Functions in C expect arguments of certain types.
      * If the compiler detects a type mismatch between a function's parameter and a supplied argument, one of two things will happen:
         * The compiler throws an error.
         * The compiler silently converts the argument to the correct type.
      * Macro arguments are not type-checked whatsoever.
   * Pointers to macros can't be created.
      * C allows creating pointers to functions.
      * Conversely, there's no such thing as a pointer to a macro.
      * Since macros are removed after preprocessing, the compiler won't have anything to point to by the time it starts processing the preprocessor's output.
   * Parameterized macros can be error-prone.
      * One common pitfall relates to the fact that a function's argument is always evaluated once.
      * A macro's argument, on the other hand, can be evaluated more than once.
      * This may lead to subtle bugs, especially if the argument has side effects.

### :small_blue_diamond: The # Operator

* The ```#``` operator is not recognized by the compiler.
* It can only appear in the replacement list of a parameterized macro.
* It creates string literals out of a parameterized macro's arguments. This operation is what the C standard refers to as "stringization".
* Assuming this macro definition ```#define PRINT_INT(x) printf(#x " = %d", x)``` and this declaration ```int a = 5;``` are in effect:
   * When ```PRINT_INT``` is invoked, it converts its argument's name into a string literal and concatenates it with ``` = %d``` to create a ```printf``` format string.
   * ```PRINT_INT(a)``` expands to ```a = 5```.

### :small_blue_diamond: The ## Operator

* The ```##``` operator is not recognized by the compiler.
* It is called the "token-pasting" operator.
* It can be used to paste together two tokens to create a single token.
* If one of the tokens is a parameterized macro's parameter, the parameter is first replaced by its corresponding argument when the macro is expanded, then the two tokens are pasted together.
* Assuming this macro definition is in effect: ```#define INT_VAR(x) i##x```:
   * Executing ```int INT_VAR(1), INT_VAR(2);``` will create the following declarations: ```int i1, i2;```.

### :small_blue_diamond: General Properties Of Macros

*

## :vertical_traffic_light: Conditional Compilation

## :toolbox: Other Directives

## :game_die: Miscellaneous