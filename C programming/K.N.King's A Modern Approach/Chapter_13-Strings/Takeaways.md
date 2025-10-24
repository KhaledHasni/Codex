<h1 align="center">💡<strong> Strings</strong></h1>
<p align="center">
  <a href="#fountain_pen-string-literals">String Literals</a> •
  <a href="#toolbox-string-variables">String Variables</a> •
  <a href="#keyboard-reading-and-writing-strings">Reading And Writing Strings</a> •
  <a href="#mag_right-accessing-the-characters-in-a-string">Accessing The Characters In A String</a> •
  <a href="#books-using-the-c-string-library">Using The C String Library</a> •
  <a href="#sparkles-string-idioms">String Idioms</a> •
  <a href="#card_index_dividers-arrays-of-strings">Arrays Of Strings</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :fountain_pen: String Literals

* A string literal is a sequence of characters enclosed in double quotes ```"```.
* String literals in C may contain character escapes, and to a much lesser extent, octal and hexadecimal escapes.
   * An octal escape sequence ends with the first non-octal character, or after the third octal character.
      * Recall that octal characters are the following: ```0```, ```1```, ```2```, ```3```, ```4```, ```5```, ```6``` and ```7```.
      * An escape sequence that has an octal character immediately after the backslash character ```\``` is treated as an octal escape sequence.
      * The string ```"\1234"``` contains two characters: ```\123``` and ```4```.
      * The string ```"\289"``` contains three characters: ```\2```, ```8``` and ```9```.
   * A hexadecimal escape sequence ends with the first non-hexadecimal character only.
      * Recall that hexadecimal characters are in the ```0 - 9```, ```a - f``` and ```A - F``` range.
      * A hexadecimal escape sequence has an ```x``` character immediately after the backslash character ```\```.
      * The string ```"Z\xfcrich"``` has six characters: ```Z```, ```ü```, ```r```, ```i```, ```c``` and ```h```.
         * The ```\xfc``` escape sequence represents the ```ü``` character from the Latin-1 ASCII extension character set.
         * This is a hexadecimal escape sequence, so it ends with the first non-hexadecimal character which is ```r``` in this case.
      * The string ```"\xfcber"``` contains two characters: ```\xfcbe``` and ```r```.
         * The escape sequence in this case ends with the first non-hexadecimal character which is again ```r```.
         * Most compilers will not accept the ```"\xfcber"``` string, since most hexadecimal escape sequences are limited to the ```\x0 - \xff``` range.
* C allows a string literal to be divided over multiple lines of program text.
   * To do so, every line containing a portion of the string literal, except the last, must end with a backslash character ```\```.
   * There shouldn't be any other characters after the backslash character, except the invisible new-line character.
   * This technique is not unique to string literals. C allows joining together any two lines of program text to form a single line using the same technique.
   * This technique is called "splicing" in the C standard.
* A "spliced" string literal must start at the beginning of the line, which could sometimes hurt a program's indented structure.
   * For this reason, C programmers usually prefer to use another trick to deal with long string literals that don't conveniently fit on a single line.
   * This trick is based on a rule: The compiler will always concatenate any two string literals separated by white spaces only.
   ```c
   printf("This string literal is way too long for its own good."
          "It doesn't fit on a single line and must be chopped into portions."
          "Luckily, it can be split in the manner you're reading right now.");
   ```
* When a compiler comes across a string literal containing ```n``` characters, it allocates ```n + 1``` bytes for it, just enough space to hold the string and an extra "null character" that marks its end.
   * The null character is represented by the ```\0``` escape sequence. It's a byte whose bits are all zero.
   * The null character's numeric code is ```0```. It shouldn't be confused with the ```0``` character.
* A string literal may be empty ```""```, in which case it is stored as a single null character.
* C treats string literals as arrays of characters.
   * Since arrays will decay to pointers in most cases, string literals are often treated as char pointers ```char *```.
   * C's ```printf``` and ```scanf``` functions for example expect a ```char *``` value as their first argument.
   * When ```printf("test");``` is called, ```printf``` is passed a pointer to where ```t``` is stored.
* C allows the use of a string literal anywhere a ```char *``` is expected.
   * A string literal is an rvalue and can appear on the right side of an assignment operator.
      * In that case, it should be assigned to an lvalue of type ```char *```.
      * That entity will contain a pointer to where the first character in the string literal is stored in memory.
   * A string literal can be subscripted just like a pointer can.
      * Subscripting a string literal allows access to individual characters in the string.
      * If a string literal is subscripted beyond its limit, the result is undefined behavior.
* The C standard explicitly forbids trying to modify a string literal.
   * String literals have static storage duration and they're typically stored in static memory in a read-only segment of the program often called ```.rodata```.
   * Trying to modify a string literal causes undefined behavior.
   ```c
   char *str = "dummy string literal";
   *str = 'm'; // will cause undefined behavior
   ```
* String literals containing a single character are not the same as a character constant.
   * A string literal with a single character is represented by a pointer to the memory location where that character is stored followed by a null character.
   * A character constant on the other hand is represented by an integer.
   * The two should never be conflated.

## :toolbox: String Variables

## :keyboard: Reading And Writing Strings

## :mag_right: Accessing The Characters In A String

## :books: Using The C String Library

## :sparkles: String Idioms

## :card_index_dividers: Arrays Of Strings

## :game_die: Miscellaneous