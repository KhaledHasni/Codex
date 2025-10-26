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

   // ptr now points to the first character in the dummy_string string variable, and can be used as a modifiable
   // string
   ptr = dummy_string;
   ```
   * Pointers can also be made to point to dynamically allocated strings.
   * It's crucial not to use an uninitialized pointer as a string.

## :keyboard: Reading And Writing Strings

* Reading and writing strings are common especially in menu-driven C programs.
* Writing a string in C can be done using either the ```printf``` or the ```puts``` function.
* Reading a string in C can be a bit tricky, since the programmer will have to be careful not to read more characters beyond the size of the destination string variable.
   * A string can be read in a one go using the ```scanf``` or the ```gets``` function.
   * A string can also be read one character at a time.

### :small_blue_diamond: Writing A String Using printf And puts

* ```printf``` is often used in conjunction with the ```%s``` conversion specification to write strings.
```c
// string variable declaration
char str[] = "Learning C becomes more worth it the deeper you get into it";

// printf call to write string
printf("%s\n", str);
```
* In the previous example, the ```printf``` call will produce ```Learning C becomes more worth it the deeper you get into it```.
* ```printf``` writes a string starting from the first character, until it reaches the first null character.
* ```printf``` can be used to format a string in different ways.
   * When used with the ```%.ps``` conversion specification, ```printf``` will display the first ```p``` characters of the string.
   * When used with the ```%ms``` conversion specification, ```printf``` will display the string in a field of size ```m```.
      * If the string is longer than the field width ```m```, it will not be truncated.
      * If the string is shorter than the field width ```m```, it will be right justified within the field.
      * Adding a minus sign ```-``` to the immediate left of ```m``` will cause the string to be left-justified within the field.
   * When used with the ```%m.ps``` conversion specification, ```printf``` will display the first ```p``` characters of the string in a field of size ```m```.
* The C library provides another function that can be used to write strings: The ```puts``` function.
* ```puts``` takes a single argument which is the string to be printed.
* ```puts``` always inserts a new-line character at the end of the string.
```c
// string variable declaration
char str[] = "Learning C becomes more worth it the deeper you get into it";

// puts call to write string
puts(str);
```
* Both ```printf``` and ```puts``` expect a null-terminated string.
   * Both functions will keep advancing in memory, writing characters as they move along until they encounter the first null character.

### :small_blue_diamond: Reading A String Using scanf And gets

* ```scanf``` is often used in conjunction with the ```%s``` conversion specification to read strings.
```c
// string variable declaration
char str[50];

// scanf call to read string
scanf("%s", str);
```
* In the previous example, the character array doesn't need to be preceded by the ```&``` operator when passed to ```scanf```.
   * Array names decay to pointers when passed as arguments to functions.
* When ```scanf``` is called to read a string:
   * It skips all leading whitespace characters.
      * A whitespace character is any character for which the ```isspace()``` function returns ```true```. These characters are:
         * Space: ```' '```.
         * Horizontal tab: ```'\t'```.
         * Vertical tab: ```'\v'```.
         * Newline: ```'\n'```.
         * Carriage return: ```'\r'```.
         * Form feed: ```'\f'```.
   * It then reads non-whitespace characters into the destination string variable one by one.
   * It stops reading as soon as it encounters the first whitespace character.
   * It appends a null character to the end of the string.
* Since ```scanf``` skips leading whitespace characters and stops at the first subsequent whitespace character, it can never read a full line of input in one go.
* The C library provides the ```gets``` function which can be used to read an entire line of input in one go.
* ```gets``` and ```scanf``` have some similarities:
   * They both read characters from standard input into a destination buffer supplied to the function as an argument.
   * They both append a null character to the end of the string they read.
* ```gets``` and ```scanf``` have some differences:
   * Unlike ```scanf```, ```gets``` does not skip leading whitespace characters when reading input.
   * While ```scanf``` will stop reading at the first encounter of a whitespace character, ```gets``` stops reading when it comes across a newline character.
      * ```gets``` does not store the newline character, the null character takes its place.
* ```scanf``` and ```gets``` will handle reading the same input differently.
   * Assuming the user is prompted to enter some input and this is what they provide: ```This input will be read differently by scanf and gets```.
   * ```scanf("%s", str);```.
      * After this call, ```str``` will contain ```This```.
      * The next ```scanf``` call will skip over the space which is now leading the input stream, and store ```input``` in the destination buffer.
      * This cycle will continue, with ```scanf``` reading adjacent streams of characters and stopping at the first encounter of a whitespace character.
   * ```gets(str);```.
      * After this call, ```str``` will contain ```This input will be read differently by scanf and gets```.
* ```scanf``` and ```gets``` are both inherently unsafe.
   * Both functions have no way of telling whether the destination buffer is full.
   * They will only stop storing characters in the destination buffer when they meet their own stopping conditions (whitespace and newline characters respectively).
   * Some C programmers like to use the ```%ms``` conversion specification with ```scanf``` to limit the number of characters to be stored to a maximum of ```m```.
   * On the other hand, nothing can be done to mitigate the risk of using ```gets```.
      * For this reason, most C programmers prefer not to use it, and opt for ```fgets``` instead.

### :small_blue_diamond: Reading A String Character By Character

* ```scanf``` and ```gets``` are inherently unsafe and don't offer much versatility and flexibility.
* For this reason, most C programmers prefer to write their own input functions. These functions will often read input one character at a time.
* When writing an input function, a programmer will have to consider several points:
   * Should the input function skip leading whitespace characters or should it store them as part of the input?
   * At what point should the function stop reading? At the first encounter of a newline character, whitespace character or maybe something else entirely?
   * When the function does encounter the character that causes it to stop reading, does it include it in the stored string or does it discard it?
   * If the input exceeds the amount of space allocated for the destination character buffer, does the function leave leftover characters for subsequent read calls or does it discard them?
* The following is an example implementation of such a function:
```c
int read_line(char str[], int max) {
   int ch, i = 0;

   while((ch = getchar()) != '\n')
      if(i < max)
         str[i++] = ch;
   str[i] = '\0';
   return i;
}
```
* Here's how the input function in the previous example works:
   * The function takes two arguments.
      * ```str``` is the destination character array where input will be stored.
      * ```max``` is the maximum number of characters to be read.
   * The function returns an integer value which represents the number of characters actually read at the end of the call.
      * This value is contained in the ```0 - max``` range (inclusively).
   * The heart of this function is the ```while``` statement, where ```getchar``` is called to read the next character in the input stream.
      * ```getchar``` returns the character it reads as an integer value, which explains why ```ch``` is an ```int``` variable as opposed to ```char```.
      * The ```while``` loop will not terminate until a newline character ```\n```is read.
   * Inside the ```while``` loop's body, the function checks whether ```max``` characters have been read already, by comparing the current position index ```i``` inside the buffer against ```max```.
   * If ```max``` characters have already been read, the input character will be discarded and not stored in the buffer.
   * If there's still room in the buffer, the function stores the input character and advances the position index ```i``` inside the buffer.
   * Once a newline character is read, the ```while``` loop terminates and the function appends a null character ```\0``` to the buffer to terminate the string.
   * Finally, the function returns the number of characters in the buffer, represented by the current position index ```i```.
* Based on the description of how ```read_line``` works, we can conclude the following:
   * The function will not skip leading whitespace characters and will store them in the destination buffer.
   * The function will stop reading at the first encounter of a newline character.
   * Once it finds a newline character, the function will not store it in the destination buffer.
   * Once the destination buffer is full, all leftover characters in the input stream will be discarded.
* This function has one minor flaw: It fails to check whether ```getchar``` calls have failed, in which case it should probably terminate the read operation.

## :mag_right: Accessing The Characters In A String

## :books: Using The C String Library

## :sparkles: String Idioms

## :card_index_dividers: Arrays Of Strings

## :game_die: Miscellaneous