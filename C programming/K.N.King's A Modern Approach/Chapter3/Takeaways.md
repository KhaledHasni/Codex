<h1 align="center">💡<strong> Formatted Input/Output</strong></h1>
<p align="center">
  <a href="#printer-the-printf-function">The printf Function</a> •
  <a href="#mag-the-scanf-function">The scanf Function</a> •
  <a href="#crossed_swords-printf-vs-scanf">printf vs scanf</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :printer: The printf Function

### :small_blue_diamond: Generalities

* The ```printf``` function is part of C's standard Input/Output library.
* It's designed to display a string with possible values inserted at specified points.
* The string to be displayed is called the format string, and it's passed to ```printf``` as the first argument.
* Subsequent ```printf``` arguments, if there are any, are the values to be inserted in the string.
* ```printf``` doesn't put any limit on the number of values that can be injected into the format string.
* The values to be inserted can be constants, variables, or other more complex expressions.
* The format string can have two types of characters:
   * Ordinary characters: Copied as is to the output line.
   * Conversion specifications: Begin with the ```%``` character and are placeholders for the values to be inserted in the format string.
* The characters following ```%``` in a conversion specification provide information on how the value to be inserted is converted from its binary form to printed form.
* As an example, the %d conversion specification instructs ```printf``` to convert an integer value from its binary form to a string of decimal digits.
* The values are inserted in the format string in the order they are provided to ```printf```.
* C compilers can't detect a mismatch between the number of conversion specifications in a ```printf``` format string and the number of provided values.
* If more conversion specifications than values are provided, the extra conversion specifications will be replaced by meaningless values.
* If fewer conversion specifications than values are provided, the extra values will not be displayed in the output.
* C compilers can't tell if a programmer has provided an inappropriate conversion specification for the type of value to be injected in the format string. If this happens, ```printf``` will attempt to perform the conversion and will, more than likely, produce unexpected results.
* ```printf``` has no way of knowing the types of the values to be inserted in the format string at compile-time. Instead, it relies entirely on the conversion specifiers to interpret the raw bytes it gets.

### :small_blue_diamond: Conversion Specifications

* Conversion specifications can be used to influence the way ```printf``` displays values.
* They can even contain formatting information.
* The general form of a conversion specification is as follows: ```%m.pX```:
   * ```m``` and ```p``` are integer constants and ```X``` is a letter.
   * ```m``` and ```p``` are both optional. If ```m``` is omitted, ```p``` must keep its dot. If ```p``` is omitted, the dot must also be removed.
   * ```X```, called the conversion specifier, indicates what type of conversion should be applied to a value before it's printed.
   * ```m```, called the "minimum field width", indicates the minimum overall number of characters to be used to display the converted value.
   * ```p``` is called the precision.
* The minimum field width ```m``` can be used in slightly varying ways:
   * If ```printf``` tries to display a value containing fewer than ```m``` characters inside an ```m``` sized field, the value will be right-justified. In other words, space paddings will precede the value to take up ```m``` characters.
   * If ```printf``` tries to display a value containing more than ```m``` characters inside an ```m``` sized field, the field will expand to the right size and no characters will be lost.
   * A minus sign in front of ```m``` causes left-justification inside the ```m``` sized field.
* Some of the most common conversion specifiers for numeric values are:
   * ```d```: Displays an integer value in decimal form.
   * ```e```: Displays a floating-point number in exponential format also known as scientific notation.
   * ```f```: Displays a floating-point number in fixed decimal format.
   * ```g```: Displays a floating-point number in either exponential or fixed decimal format depending on the number's size.
      * It won't display the decimal point if the value has no digits after the decimal point.
      * It won't display trailing zeros in contrast to the f specifier.
      * Usually used with floating-point numbers whose size can't be predicted when writing a program, or whose size may vary substantially at runtime.
      * It's mostly left up to the compiler to choose which of the two formats to use, but it's safe to assume that reasonably-sized numbers will be displayed in fixed decimal form, while very large/small numbers will be displayed in exponential form.
* The precision ```p``` can mean a lot of things depending on the conversion specifier:
   * ```d```: ```p``` indicates the minimum number of digits to be displayed. Extra zeros can be added to reach the required number. If ```p``` is removed, it's as if it had the value ```1```.
   * ```e```: ```p``` indicates the number of digits that should appear after the decimal point. The default value is ```6```. The decimal point is not displayed if ```p``` is zero.
   * ```f```: ```p``` has the same meaning as with the ```e``` conversion specifier.
   * ```g```: ```p``` indicates the maximum number of digits before the decimal point to be displayed.

### :small_blue_diamond: Escape Sequences

* Escape sequences enable strings to contain characters that can't simply be injected in strings lest they be misinterpreted by the compiler.
* Such characters include nonprinting control characters and characters that have special meaning to the compiler.
* When used inside a ```printf``` format string, escape sequences represent actions to be performed.
* Common escape sequences include:
   * ```\a``` Alert: Causes a beep on most machines (many modern systems may ignore it).
   * ```\b``` Backspace: Moves the cursor back one position.
   * ```\n``` New-line: Moves the cursor to the beginning of a new line.
   * ```\t``` Horizontal Tab: Moves the cursor to the next tab stop.
* A ```printf``` format string can have any number of escape sequences.
* Some characters can't be used inside ```printf``` format strings unless bundled in an escape sequence. Examples include:
   * ```"```: String literal delimiter. Might cause confusion inside a format string (does it indicate the start/end of the string?). Must be escaped as ```\"```.
   * ```\```: Escape sequence indicator. Might cause confusion inside a format string (does it indicate an upcoming escape sequence?). Must be escaped as ```\\```.

## :mag: The scanf Function

### :small_blue_diamond: Generalities

* The ```scanf``` function is part of C's standard Input/Output library.
* It's designed to read input in a specified format.
* It takes a format string as its first argument, followed by pointers to variables that will hold the values being read.
* A ```scanf``` format string may contain both ordinary characters and conversion specifications which are largely the same as ```printf```'s.
* There's no limit on the number of conversion specifications that can appear in a ```scanf``` format string.
* When a program encounters a ```scanf``` call, it reads user input, converts the values read according to the specifiers and stores them in the variables whose pointers are provided. The following call for example ```scanf("%d", &i)``` will read an integer value from standard input as characters, convert it to its numeric value and store it in the variable ```i```.
* ```scanf``` has two major pitfalls:
   * Just like with ```printf```, C compilers are not required to check for a possible mismatch between the number of conversion specifications in the format string and the number of input variables provided. They're also not required to check whether the specifiers used are appropriate for the type of data being read or the target variable's type.
   * The ```&``` symbol in front of input variables is usually necessary and can easily be forgotten. Failing to provide it when it's needed can have terrible results (crashes, target variable not being assigned the value read...). Some compilers may be able to detect a missing ```&``` in a ```scanf``` call and issue a warning.
* Many C programmers avoid using ```scanf``` altogether, preferring to read input as characters and later convert it manually.

### :small_blue_diamond: How It Works

* ```scanf```'s behavior is in many ways controlled by the format string.
* When called, ```scanf``` will process the format string starting from the left.
* When it encounters a conversion specification, it will try to match it with an appropriate item read from the input stream of characters.
* ```scanf``` has the built-in ability to skip whitespace characters (space, horizontaltab, vertical tab, form-feed and new-line) if necessary. This is the case for example when scanning for the beginning of numbers in a stream of input characters.
* ```scanf``` will stop reading an item as soon as it encounters a character that can't possibly belong to said item. That character will be returned to the input stream to be processed by the next input item or the next ```scanf``` call.
* If an input item was read successfully, ```scanf``` will continue processing the format string.
* If ```scanf``` fails to read an input item, it immediately returns without processing the rest of the format string or input data.
* A new-line character at the end of an input stream is put back for the next call of ```scanf``` to handle.
* ```scanf``` abides by several rules to identify numbers in an input stream of characters:
   * Integers:
      * Looks for leading a digit, plus sign or minus sign.
      * Reads subsequent adjacent digits until it reaches a nondigit.
   * Floating-point numbers:
      * Looks for a leading digit, plus or minus sign.
      * Reads subsequent adjacent digits including a possible decimal point.
      * Reads an optional exponent (an ```e``` or ```E``` letter) followed by an optional plus or minus sign, followed by adjacent digits.
      * Stops when it reaches the first nondigit.
      * Note that the ```%e```, ```%f``` and ```%g``` conversion specifications all use the same rules to identify a floating-point number.

### :small_blue_diamond: Ordinary Characters In Format Strings

* ```scanf``` format strings can contain both ordinary characters and conversion specifications.
* When ```scanf``` encounters an ordinary character in its format string, it checks whether or not it's a whitespace character:
   * Whitespace character: If ```scanf``` encounters one or more consecutive whitespace characters in the format string, it tries to match them with whitespace characters in the input character stream. It doesn't matter how many consecutive whitespace characters appear in the format string. The whole block will be matched with any number of consecutive whitespace characters found in standard input (including none).
   * Non-whitespace characters: If ```scanf``` encounters a non-whitespace character in the format string, it compares it to the next input character. If the two match, the character will be discarded and the rest of the format string will be processed. Otherwise, the character is returned to the input stream for the next ```scanf``` call, and the current call immediately terminates.
* A whitespace character in a ```scanf``` format string will essentially skip all consecutive whitespace characters in the input stream up to the next non-whitespace character.

## :crossed_swords: printf vs scanf

* Beginners might be tempted to look at ```scanf``` and ```printf``` calls in the same light, but there are several differences between the two.
* ```scanf``` calls expect pointers to variables to be able to store data items read from input. ```printf```, on the other hand, expects expressions (including variables).
* ```scanf``` and ```printf``` format strings serve entirely different purposes. ```printf``` usually has both conversion specifications and ordinary characters in its format string while it's usually a bad idea to use ordinary characters in ```scanf``` format strings unless we're trying to pattern-match input with an expected format.

## :game_die: Miscellaneous

* The ```%i``` conversion can be used with integers in printf and scanf format strings:
   * printf: ```%i``` and ```%d``` are equivalent.
   * scanf: ```%d``` reads an integer item in decimal base 10 form while ```%i``` can read an integer item in decimal, octal or hexadecimal form. ```%i``` reads ```012``` for example as ```10``` (```012``` in octal is equivalent to ```10``` in decimal) and ```0xA``` (or ```0XA```) as ```10```.
* Two consecutive ```%``` characters in a printf format string are printed as one ```%``` character.
* Printing the ```\t``` escape sequence is supposed to advance the cursor to the next tab stop. C has no influence on how far apart tab stops are. They're typically 8 characters apart but it's entirely up to the operating system.
* Input streams of characters are stored in a hidden buffer that scanf has access to. scanf "putting back" characters simply means leaving them in the buffer.
