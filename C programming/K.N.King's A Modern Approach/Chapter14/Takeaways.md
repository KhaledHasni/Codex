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

## :vertical_traffic_light: Conditional Compilation

## :toolbox: Other Directives

## :game_die: Miscellaneous