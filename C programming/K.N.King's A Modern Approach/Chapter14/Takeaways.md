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
   * C allows writing a directive on multiple lines using a technique that the C standard calls "splicing".
   * If we want to continue writing a directive on the next line, we must end the current line with a backslash character ```\```.
* A directive can be followed by a comment on the same line.
* Preprocessing directives can appear anywhere in a program, even in the middle of functions.

## :label: Macro Definitions

### :small_blue_diamond: Simple Macros

* "Simple macros", also known as "object-like macros", are macros that don't take any arguments.
* A simple macro in C has the following general form: ```#define identifier replacement_list```.
   * ```replacement_list``` is any sequence of preprocessing tokens separated by whitespace characters.
   * A replacement list may include identifiers, keywords, numeric constants, character constants, string literals, operators and punctuation.
   * The replacement list replaces any occurrence of the identifier in the program text once the macro is expanded.
* Any symbols following a macro's identifier are part of its replacement list. Failing to remember this rule leads to some common errors beginner C programmers make:
   * Ending a macro definition with a semicolon ```;```.
      * Although perfectly legal, the semicolon will be part of the macro's replacement list which is usually not the desired effect.
   * Adding an equal sign ```=``` between the identifier and its replacement list.
      * The preprocessor will expand every occurrence of ```identifier``` to its replacement list. There's no need for the equal sign.
   * If such mistakes slip through the preprocessor, they will usually be detected by the compiler.
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
      * Others use simple macros to replace entire statements like ```if``` and ```for```.
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
* It creates string literals out of a parameterized macro's argument. This operation is what the C standard refers to as "stringization".
* Assuming this macro definition ```#define PRINT_INT(x) printf(#x " = %d", x)``` and this declaration ```int a = 5;``` are in effect:
   * When ```PRINT_INT``` is invoked, it converts its argument's name into a string literal and concatenates it with ``` = %d``` to create a ```printf``` format string.
   * ```PRINT_INT(a)``` expands to ```printf("a" " = %d, a)```, which will print ```a = 5```.

### :small_blue_diamond: The ## Operator

* The ```##``` operator is not recognized by the compiler.
* It is called the "token-pasting" operator.
* It can be used to paste together two tokens to create a single token.
* If one of the tokens is a parameterized macro's parameter, the parameter is first replaced by its corresponding argument when the macro is expanded, then the two tokens are pasted together.
* Assuming this macro definition is in effect: ```#define INT_VAR(x) i##x```:
   * Executing ```int INT_VAR(1), INT_VAR(2);``` will create the following declarations: ```int i1, i2;```.

### :small_blue_diamond: General Properties Of Macros

* General rules apply to both simple and parameterized macros:
   * A macro's replacement list can contain other macro invocations.
      * When the preprocessor expands a macro, it rescans the replacement list for other macro names.
      * If another macro name is found, it will be replaced by its replacement list as well.
      * This expand and rescan cycle will continue until all macro names have been replaced by their replacement lists.
      * According to the C standard, if the original macro name reappears after expansion, it will not be expanded again. This point will be discussed further down.
   * The preprocessor expands entire tokens only.
      * Parts of tokens or tokens embedded in string literals, identifiers and character constants are not expanded.
   * Unless undefined using the ```#undef``` directive, a macro definition remains in effect until the end of the file.
      * Since they're handled by the preprocessor, macros don't abide by the compiler's scope rules.
      * A macro defined in the middle of a function will remain in effect until the end of the file.
   * Redefining a macro is not allowed.
      * Creating a macro with the same name as an already defined macro is allowed, as long as:
         * The tokens in both macros' replacement lists are exactly identical.
         * The macros' parameters are exactly identical in name and number.
         * Whitespace characters between tokens in both macros can be different.
   * Macros can be undefined.
      * The ```#undef``` directive allows us to remove the current definition of a macro.
      * It has the following general form: ```#undef identifier```, where ```identifier``` is the name of a macro.

### :small_blue_diamond: Parentheses In Macro Definitions

* Macro replacement lists in C are usually riddled with parentheses. To the untrained eye, this might look unnecessary. But seasoned C programmers know very well that a shortage of parentheses in macro replacement lists can lead to some of C's most subtle bugs.
* C programmers usually follow two rules when deciding whether or not to use parentheses in a macro replacement list.
   * If the macro contains an operator, the whole replacement list should be enclosed in parentheses.
   * If the macro has parameters, every parameter occurrence in the replacement list should be enclosed in parentheses.
* These two rules mitigate the risk of the compiler applying operator precedence and associativity rules in ways we did not anticipate.

### :small_blue_diamond: Creating Longer Macros

* The comma operator ```,``` offers macros a great deal of versatility and allows writing replacement lists containing multiple expressions.
* As an example, we can create a macro that performs an echo (read/write) every time it's invoked:
```c
#define ECHO(s) (gets(s), puts(s))
```
* It might be tempting to ask why we used the comma operator when we could have used a compound statement in the replacement list:
```c
#define ECHO(s) {gets(s); puts(s);}
```
* The compound statement in this case is problematic. Invoking the macro inside an ```if``` statement is a good example to illustrate why:
```c
if(/* condition */)
   ECHO(s);
else
/* statement */
```
* When ```ECHO``` is expanded, it's replaced by the compound statement containing ```gets``` and ```puts```. Since the compound statement does not require a semicolon ```;``` after its right curly brace, the semicolon at the end of ```ECHO(s)``` is treated by the compiler as a null statement and the ```else``` clause is therefore orphaned. As a result, the compiler will throw an error.
   * This problem can be avoided by not placing a semicolon after ```ECHO(s)```, but that makes the program look unnatural.
* The comma operator ```,``` can help create sophisticated macros with replacement lists containing more than a single expression. It doesn't offer much help though if we want to create macros with multiple statements in the replacement list.
   * Some C programmers use a trick to achieve this goal: They wrap all statements in a ```do``` loop whose controlling expression is always false.
   ```c
   #define EXAMPLE do {
                      statement_1;
                      statement_2;
                      ...
                      statement_n;
                   } while(0)
   ```
   * The ```do``` loop's controlling expression being false, the compound statement will be executed once.
   * The ```do``` statement is incomplete. It requires a semicolon ```;``` at the end. An invocation of this macro will look like this ```EXAMPLE;```.

### :small_blue_diamond: Predefined Macros

* C offers several macros built into the compiler itself no matter the C implementation.
* No headers need to be included to use these macros.
* These macros' replacement lists are either an integer constant or a string literal.
* They provide information about the current compilation or about the compiler itself.
* These predefined macros are:
   * ```__LINE__```.
      * Represents the current line number of the file being compiled.
      * The line number is an integer constant.
      * Typically used to identify the culprit when a program crashes or terminates prematurely.
   * ```__FILE__```.
      * Represents the name of the current file being compiled.
      * The file name is a string literal.
      * Typically used to pinpoint problematic statements that cause premature termination of the program.
   * ```__DATE__```.
      * Represents the date of compilation of the program.
      * The date is a string literal in the form ```"Mmm dd yyyy"```.
      * Can be used to distinguish between different compiled versions of the program.
   * ```__TIME__```.
      * Represents the time of compilation of the program.
      * The time is a string literal in the form ```"hh:mm:ss"```.
      * Can also be used to distinguish between different compiled versions of the program.
   * ```__STDC__```.
      *  Has the value ```1``` if the compiler used to compile the program conforms to the C standard (C89 or C99).

### :small_blue_diamond: Additional Predefined Macros In C99

* A C implementation is a compiler along with any other software necessary to execute C programs.
* The C99 standard breaks down C implementations into two categories:
   * Hosted implementations: Must accept all C programs that conform to the C99 standard.
   * Freestanding implementations: Don't have to accept programs that use complex types or standard headers beyond a few of the most basic.
* C99 introduces several new macros built into the compiler.
* No headers need to be included to use these macros.
* These predefined macros added by C99 are:
   * ```__STDC__HOSTED__```.
      * Represents the value ```1``` if the compiler belongs to a hosted implementation.
      * Represents the value ```0``` if the compiler belongs to a freestanding implementation.
   * ```__STDC__VERSION__```.
      * Represents a long integer constant.
      * This long integer provides information on the version of the C standard recognized by the compiler used to compile the program.
      * It was first introduced by Amendment 1 to the C89 standard. It had the value ```199409L``` (Amendment 1 dates back to September 1994).
      * For C99, it has the value ```199901L``` (C99 dates back to January 1999).
      * This macro has a different value for every version and amendment to the C standard.
   * The following three macros are defined for some C99 compilers and not defined for others:
      * ```__STDC_IEC_559__```.
         * This macro is defined and represents the value ```1``` if the compiler performs floating-point arithmetic according to the IEC 60559 standard.
         * IEC 60559 is another name for the IEEE 754 standard.
      * ```__STDC_IEC_559_COMPLEX__```.
         * This macro is defined and represents the value ```1``` if the compiler performs complex arithmetic according to the IEC 60559 standard.
      * ```__STDC_ISO_10646__```.
         * This macro is defined and represents a long integer constant of the form ```yyyymmL``` if values of type ```wchar_t``` are represented by the codes in the
         ISO/IEC 10646 standard.
         * ```yyyy``` and ```mm``` represent the year and month of the considered ISO/IEC 10646 standard revision.

### :small_blue_diamond: Empty Macro Arguments In C99

* C99 allows supplying empty arguments to parameterized macros.
* In most cases, when an empty argument is supplied to a parameterized macro, the preprocessor simply eliminates any occurrence of the corresponding parameter from the replacement list.
* This rule has two noteworthy exceptions:
   * When the missing argument is an operand of the ```#``` operator.
      * When the preprocessor stringizes an empty argument, it produces an empty string ```""```.
   * When the missing argument is an operand of the ```##``` operator.
      * When provided an empty argument, the token-pasting operator ```##``` replaces it with an invisible placemarker token in the macro's replacement list.
      * A placemarker token pasted together with an ordinary token disappears. The result is the ordinary token.
      * A placemarker token pasted together with another placemarker token produces a single placemarker token.
      * Any remaining placemarker tokens after macro expansion simply disappear.

### :small_blue_diamond: Macros With A Variable Number Of Arguments In C99

* In C89, parameterized macros have a fixed number of arguments.
* C99 allows a parameterized macro to have an unlimited number of arguments.
* Since functions in C have always had the ability to request an unlimited number of arguments, C99 granted this ability to macros as well. This was mainly done to allow parameterized macros to pass arguments to functions that request an unlimited number of arguments.
* The definition of a parameterized macro with a variable number of arguments might look like this:
```c
#define EXAMPLE(a, ...) replacement_list
```
* The ```...``` token is called an "ellipsis". It should appear at the end of a parameterized macro's parameter list, if said macro has a variable number of arguments. It can be preceded by any number of ordinary arguments.
* A special identifier usually appears in the replacement list of macro with a variable number of arguments.
   * This is the ```__VA_ARGS__``` identifier.
   * It represents all macro arguments that correspond to the ellipsis ```...```.
   * When such a macro is invoked, all ordinary arguments are injected in the replacement list, each replacing their corresponding parameter.
   * All arguments that correspond to the ellipsis will replace the ```__VA_ARGS__``` identifier in the replacement list, just the way they are in the macro invocation (even separating commas are preserved).
   * These macros are commonly used to pass format strings and variables as arguments to the ```printf``` and ```scanf``` functions.

### :small_blue_diamond: The __func__ identifier In C99

* C99 provides the ```__func__``` identifier which can be useful for debugging.
* The ```__func__``` identifier is not a preprocessor macro. As a matter of fact, it has nothing to do with the preprocessor.
   * It's a special predefined identifier that the compiler automatically creates inside every function.
   * Its type is a constant array of characters ```const char[]```.
   * It's basically a string variable that holds the name of the currently executing function.
   * It's exactly as though the following declaration were made at the top of the function's body: ```static const char __func__[] = "function_name";``` with ```function_name``` being the name of the enclosing function.
* The ```__func__``` identifier is primarily used for two purposes.
   * Logging function names when they're executed to locate potential bugs and errors.
   * Creating a call stack, by informing every function of the name of the function that called it.

## :vertical_traffic_light: Conditional Compilation

* Conditional compilation is the process of excluding or including portions of a program's text when compiling it, depending on a condition that the preprocessor can test.

### :small_blue_diamond: The #if and #endif Directives

* C's ```#if``` directive performs a preprocessing test.
   * It has the following general form: ```#if constant_expression```.
   * The test fails if ```constant_expression``` has the value ```0```.
   * The test succeeds if ```constant_expression``` has any nonzero value.
* C provides another preprocessing directive that's usually used in tandem with the ```#if``` directive: The ```#endif``` directive.
   * It has the following general form: ```#endif```.
   * An ```#endif``` directive is used to signal the end of a preprocessing ```#if``` block.
* When the preprocessor encounters an ```#if``` directive:
   * It evaluates the ```constant_expression```.
   * If it has a nonzero value, the block of code between the ```#if``` and ```#endif``` directives is left for the compiler to process.
   * If its value is zero, the block of code between the ```#if``` and ```#endif``` directives is removed from the program text and won't be seen by the compiler.
   * In both cases, the ```#if``` and ```#endif``` directives themselves are replaced by empty lines.
* C's ```#if``` directive treats an undefined macro as a macro that has the value ```0```. Assuming ```UNDEFINED_MACRO``` is an undefined macro name:
   ```c
   #if UNDEFINED_MACRO /* This test will fail */
   #endif
   #if !UNDEFINED_MACRO /* This test will succeed */
   #endif
   ```

### :small_blue_diamond: The defined Operator

* C's preprocessor has only three operators.
   * The "stringization" operator ```#```.
   * The "token-pasting" operator ```##```.
   * The ```defined```operator.
* When applied to an identifier, the ```defined``` operator produces the value ```1``` if the identifier matches the name of a currently defined macro, otherwise, it produces the value ```0```.
* C's ```defined``` operator is typically used in tandem with the ```#if``` directive to conditionally compile a block of code depending on whether or not a macro is defined.
```c
#if defined TEST
/* This block of code will be compiled if a macro called TEST is defined */
#endif
```
* Since the ```defined```operator tests whether or not a macro is defined:
   * The macro can be defined without a value.
   ```c
   #define TEST
   ```
   * The macro can be defined and have the value ```0```.
   ```c
   #define TEST 0
   ...
   #if defined TEST
   /* This block of code will be compiled */
   #endif
   ```
* The ```defined``` operator's operand can be enclosed in parentheses.

### :small_blue_diamond: The #ifdef and #ifndef Directives

* C's ```#ifdef``` directive can be used to test whether an identifier matches the name of a currently defined macro.
   * It has the following general form: ```#ifdef identifier```.
   * ```#ifdef``` is exactly equivalent to ```#if defined```.
   * ```#ifdef``` requires an ```#endif``` directive to enclose the block of code subject to conditional compilation.
* C's ```#ifndef``` directive can be used to test whether an identifier is not a currently defined macro.
   * It has the following general form: ```#ifndef identifier```.
   * ```#ifndef``` is exactly equivalent to ```#if !defined```.
   * Like ```#ifdef```, ```#ifndef``` also requires an ```#endif``` directive to enclose the block of code subject to conditional compilation.

### :small_blue_diamond: The #elif and #else Directives

* C allows ```#if```, ```#ifdef``` and ```#ifndef``` directives to be nested just like with ordinary ```if``` statements.
* Some C programmers add a comment after each ```#endif``` directive to mention the matching ```#if```, ```#ifdef``` or ```#ifndef``` directive.
* C also provides the ```#elif``` and ```#else``` directives to allow the preprocessor to perform multiple tests and conditionally compile multiple blocks of code accordingly.
* ```#elif``` and ```#else``` are used in conjunction with ```#if```, ```#ifdef``` and ```#ifndef```.
* C does not enforce any limit on the number of ```#elif``` directives that may appear between an ```#if``` and ```#endif``` pair of directives, nor does it require an ```#else``` directive to be present.
```c
#if expression_1
/* Compiled if expression_1 is nonzero */
#elif expression_2
/* Compiled if expression_2 is nonzero */
...

#elif expression_n
/* Compiled if expression_n is nonzero */
#else
/* Compiled if none of the above expressions have a nonzero value */
#endif
```

### :small_blue_diamond: Uses Of Conditional Compilation

* Conditional compilation can be useful in many situations.
   * Debugging.
      * It's common for C programmers to add ```printf``` calls in critical places of their code when debugging it.
      * The idea is to be able to access the content of variables without using a debugger.
      * These ```printf``` calls are only useful when debugging and are ideally left out of the final compiled code.
      * C programmers customarily define a macro called ```DEBUG``` for this purpose.
      * All calls to ```printf``` are enclosed in a pair of ```#if DEBUG``` and ```#endif``` directives.
      * Once all bugs have been located and fixed, the program is recompiled with the following ```#define DEBUG 0```.
   * Compiling a program for multiple platforms.
      * It's not uncommon for a C program to be designed to run on different platforms.
      * Some parts of the program might need to be compiled for one platform and not for another.
      * C programmers usually resolve this problem by defining a program at the beginning of the program indicating the target platform.
      * Every time the program is compiled with a new macro value, different blocks of code are conditionally compiled.
   * Writing a program designed to be compiled with different compilers.
      * Different compilers sometimes require slightly different versions of a program.
      * Some compilers accept a standard version of C, while others don't.
      * Some compilers provide machine-specific language extensions, while others don't.
      * Conditional compilation can be used to allow a program to adjust to different types of compilers.
   * Disabling blocks of code.
      * This is often done by commenting out any code we don't want to compile.
      * This can also be done using conditional compilation.
      * A block of code left out using conditional compilation is said to be "conditioned out".
   * Defining include guards.

## :toolbox: Other Directives

### :small_blue_diamond: The #error Directive

* The ```#error``` directive has the following general form: ```#error message```.
   * ```message``` should be a series of tokens.
   * When the preprocessor encounters an ```#error``` directive, it prints a message that includes the token sequence ```message```.
   * Different compilers may print slightly varying messages, but all of them will include ```message```.
* Upon encountering an ```#error``` directive, some compilers immediately abort compilation.
   * The ```#error``` directive indicates a serious problem in the program.
   * It's often used to alert the programmer of an abnormal behavior in their program.
* The ```#error``` directive is usually used in conjunction with conditional compilation.
   * The ```#error``` directive is used to signal situations that shouldn't happen during normal execution.
   * It often appears in the ```#else``` clause of an ```#if```, ```#elif``` sequence.

### :small_blue_diamond: The #line Directive

* The ```#line``` directive has two general forms:
   * ```#line n```.
      * ```n``` is a sequence of digits that represents an integer between ```1``` and ```32767``` in C89 (```1``` and ```2147483647``` in C99).
      * Each line in a program text has a rank. The first line in a given file is ranked ```1```, the second line is ranked ```2``` and so on.
      * The ```#line``` directive in this form causes the subsequent line to be ranked ```n``` instead of its natural rank.
      * All subsequent lines in the current file will be ranked ```n + 1```, ```n + 2``` and so on.
   * ```#line n "file"```.
      * This form of the ```#line``` directive is exactly the same as the first form, with one notable difference.
      * ```"file"``` represents the name of a file.
      * The lines that follow this directive in the current file are assumed to come from the file called ```"file"``` with line numbers starting at ```n```.
* C allows using macros to specify the values of ```n``` and ```"file"``` in both forms of the ```#line``` directive.
* The ```#line``` directive in its first form changes the value of the ```__LINE__``` macro.
* The ```#line``` directive in its second form changes the values of both the ```__LINE__``` and ```__FILE__``` macros.
* Most compilers will use the new line ranks created by the ```#line``` directive when generating error messages detected on subsequent lines.
* It's worth asking why would we want to change line ranks in a program and produce error messages based on the new ranks, when all that seemingly does is make programs harder to debug. That's a legitimate question, and it can be answered as follows:
   * The ```#line``` directive is rarely used by C programmers.
   * It's used primarily by programs that generate C code as output ("yacc" is a good example of such a program).
   * "yacc"'s input is a "grammar specification file" that describes the syntax of a language in terms of production rules and specifies what actions to take when each rule is matched. It also has an auxiliary C code section.
   * "yacc" uses this input file to generate a C program called ```y.tab.c``` which implements a token parser. This file will usually contain big chunks of the C code fed into "yacc" by the programmer.
   * The programmer then needs to compile ```y.tab.c``` in the usual manner. Therefore, any errors detected will be traced back to ```y.tab.c```.
   * To work around this inconvenience, "yacc" inserts ```line``` directives in ```y.tab.c``` to trick the compiler into thinking the errors come from the original file provided by the programmer.

### :small_blue_diamond: The #pragma Directive

* The ```#pragma``` directive is used to request special behavior from the compiler.
* The ```#pragma``` has the following general form ```#pragma tokens```.
   * ```tokens``` are a sequence of arbitrary tokens.
   * A ```#pragma``` directive can be very simple, with one single token. It can also be much more complex.
   * Each C compiler has its own list of commands that can appear in a ```#pragma``` directive. The full list of commands can usually be found in each compilers' respective documentation.
   * When it encounters an unrecognized command in a ```#pragma``` directive, the preprocessor simply ignores it. No errors or warnings are produced.
* C89 provides no standard pragmas. They're all implementation-defined.
* C99 provides three standard pragmas, all of which use STDC as the first token.
   * ```FP_CONTRACT```.
   * ```CX_LIMITED_RANGE```.
   * ```FENV_ACCESS```.
* C99 introduces the ```_Pragma``` operator that can be used in tandem with the ```#pragma``` directive.
   * A ```_Pragma``` expression has the following general form ```_Pragma(string_literal)```.
   * When the preprocessor encounters a ```_Pragma``` expression, it destringizes the provided string literal.
   * Destringizing a string literal requires removing the enclosing ```"``` characters and replacing the escape sequences ```//``` and ```\"``` by ```/``` and ```"``` respectively.
   * The resulting series of tokens are then provided to a ```#pragma``` directive.
   * ```_Pragma("This is a dummy string literal")``` is equivalent to ```#pragma This is a dummy string literal```.
* The ```_Pragma``` operator can be used in a macro's replacement list.
* The ```_Pragma``` operator was primarily introduced to work around one of the preprocessor's biggest limitations: The fact that a preprocessing directive can't generate another preprocessing directive.
   * By using the ```_Pragma``` operator in the replacement list of a macro, we can create a preprocessing directive by way of a macro expansion.

## :game_die: Miscellaneous

* "yacc" (Yet Another Compiler-Compiler) is a UNIX utility that generates part of a compiler. Its GNU version is called "Bison".
* A ```#``` symbol on a line by itself is called the "null directive". It is perfectly legal. It has no effect and is completely ignored by the preprocessor.
   * Some programmers use null directives as spacing in conditional compilation blocks.
   ```c
   #if (condition)
   #
   #error "This is a dummy error message"
   #
   #endif
   ```
* Most C programmers use two rules to determine whether a constant (numeric, character, string) should be defined as a macro.
   * The constant is used more than once in the program.
   * The constant's value might be changed in the future.
* The ```#``` operator replaces ```"``` and ```\``` by ```\"``` and ```\\``` respectively when stringizing its operand.
* Some macro expansion rules in C are counter-intuitive and may not be very well known among C programmers. One example of such rules is:
   * A macro parameter used as an operand of the ```##``` operator in a macro's replacement list is not expanded at the time of substitution.
   * Assuming the following macro definition is in effect ```#define CONCAT(a,b) (a##b)```:
      * ```CONCAT(a, CONCAT(b,c))``` will not expand in the way most people expect.
      * The inner macro invocation is an operand of ```##``` in ```CONCAT```'s replacement list. Consequently, it's not expanded at the time of substitution as stated by the rule.
      * The result is that ```CONCAT(a,CONCAT(b,c))``` produces ```aCONCAT(b,c)```.
      * Since there's no macro called ```aCONCAT```, this result can't be further expanded.
      * One way to work around this is to define a second macro that calls the first one: ```CONCAT2(a,b) CONCAT(a,b)```.
      * ```CONCAT2(a, CONCAT2(b,c))``` now expand to ```abc``` as we'd expect.
      * The difference is that ```CONCAT2```'s replacement list does not contain the ```##```operator.
   * Similarly, a macro parameter used as an operand of the ```#``` operator in a macro's replacement list is not expanded at the time of substitution.
* If the name of the original macro reappears during preprocessor rescanning, it is not expanded again. This rule is explicitly stated in the C standard.
* A hosted implementation is used for programs that rely on an underlying operating system for a myriad of services. A freestanding implementation on the other hand is used for programs that require little to no operating system support. Examples of such programs are operating system kernels and programs designed to run on resource-constrained embedded systems.
* The preprocessor is less sophisticated, and knows much less about the C programming language than the compiler. That being said, it knows enough to be able to evaluate constant expressions in an ```#if``` directive for example.
* The operands in a preprocessor constant expression are usually one of three kinds:
   * Constants.
   * Macros that represent constants.
   * An expression involving the ```defined``` operator.
* C's ```#ifdef``` and ```#ifndef``` were part of the language from the very beginning. The same can't be said of the ```defined``` operator, which was added to the language during standardization.
   * The ```defined``` operator might seem futile since it can largely be replaced by the ```#ifdef``` and ```#ifndef``` directives.
   * The ```defined``` operator was added to the language to offer more flexibility when writing preprocessing directives.
      * The ```defined``` operator can be used to write the following ```#if defined(condition1) && defined(condition2)```.
      * The same conditional expression can't be written using the ```#ifdef``` directive.
* Comments in a C program are processed before preprocessing directives are executed.
   * For this reason, if a block of code contains an unterminated comment, it will produce an error when compiled, even if this block is conditioned out using conditional compilation.
   * An unpaired ```"``` character can also result in undefined behavior even if it appears in a conditioned out block of code.