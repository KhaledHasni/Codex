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

* String variables in C don't have their own data type.
* A one-dimensional array of characters can be used to store a string variable.
* A string variable must be null-terminated.
* The fact that C uses character arrays to store strings is a bit of an inconvenience for several reasons.
   * It's not always immediately apparent whether a character array is being used to store a string.
   * Correctly managing the null character is crucial when processing string variables in C, and this responsibility is left entirely up to the programmer.
      * Most C programmers write their own string-handling functions so they don't have to deal with managing the null character more than once.
   * The most efficient way to determine the length of a string is a character by character search for the null character.
* To declare a string variable capable of storing strings of up to ```n``` characters, C programmers will usually declare an array of ```n + 1``` characters in the following manner:
```c
#define MAX_LENGTH 10

// string variable declaration
char dummy_string[MAX_LENGTH + 1];
```
* In the previous example, the array's length was explicitly made to be the string's maximum length plus one to make it clear that the actual string's maximum length is ```MAX_LENGTH```, and the extra byte is just for the null character.
* C's string library functions assume the string variables they process are all correctly null-terminated.
   * For this reason, it's crucial to always allocate an extra byte for the null character when declaring a string variable.
* The length of a string in C depends entirely on the position of the null character.
   * A string stored in a character array of length ```MAX_LENGTH + 1``` doesn't necessarily have to be ```MAX_LENGTH``` characters long.
   * A character array of length ```MAX_LENGTH + 1``` can hold strings of different lengths ranging from ```0``` to ```MAX_LENGTH```.
* C allows a string variable to be initialized at the time of its declaration.
   * ```char dummy_string[12] = "Test string";```.
      * In this example, the compiler stores the characters in the array one by one and adds a null character at the end so the array can be used as a string variable.
      * ```"Test_string"``` in this case is not a string literal, it's an abbreviation for an array initializer instead.
         * It's equivalent to ```{'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g', '\0'}```.
      * Recall that if an array initializer is shorter than the actual array, the compiler will zero all leftover bytes.
         * Since string variables are just character arrays in disguise, they are no exception to this rule.
         * If a string initializer is shorter than the string variable, all leftover bytes in the string are initialized to the null character ```\0```.
         * Providing a string initializer that's longer than the character array is illegal just like it is for ordinary arrays.
         * Providing a string initializer that's exactly as long as the character array (excluding the null character) is legal, although it makes the character array essentially unusable as a string since there's no space left to store a null character.
* A string variable declaration doesn't necessarily have to mention the length of the character array if it has an initializer.
   * The compiler will compute the length of the initializer, including the null character, and allocate exactly enough space for it.
   * ```char dummy_string[] = "Test string";``` will allocate ```12``` bytes for this string.
   * The fact that the declaration does not mention the array's length does not mean it can be modified later by the program.
      * Once the program is compiled, the array's length is fixed.
   * C programmers usually omit the array length when it has a fairly long initializer.
* Character arrays and character pointers are closely related, but they're not identical.
   * ```char dummy_string[] = "Test string";``` and ```char *dummy_string = "Test string";``` can be used interchangeably in a lot of cases, but not always.
   * When ```dummy_string``` is an array name:
      * ```Test string``` is an abbreviation for an array initializer.
      * The characters in ```dummy_string``` are modifiable just like the elements of an ordinary array.
      * ```dummy_string``` is an immutable array name. It can't be made to point to something else.
   * When ```dummy_string``` is a pointer:
      * ```Test string``` is a non-modifiable string literal.
      * ```dummy_string``` is a pointer variable that can be made to point to something else during program execution.
* A modifiable string requires the use of an array of characters.
   * A pointer is not enough in this case. In fact, when a pointer to a character is declared, the compiler only sets aside enough storage for a pointer variable.
   * A pointer to a character can't be used as a modifiable string until it's made to point to a character array.
   ```c
   // pointer to character and string variable declaration
   char *ptr, dummy_string[MAX_LENGTH + 1];

   // ptr now points to the first character in the dummy_string string variable, and can be used as a modifiable string
   ptr = dummy_string;
   ```
   * Pointers can also be made to point to dynamically allocated strings.
   * It's crucial not to use an uninitialized pointer as a string.

## :keyboard: Reading And Writing Strings

## :mag_right: Accessing The Characters In A String

## :books: Using The C String Library

## :sparkles: String Idioms

## :card_index_dividers: Arrays Of Strings

## :game_die: Miscellaneous