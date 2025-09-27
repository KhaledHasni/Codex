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

## :toolbox: Other Directives

## :game_die: Miscellaneous