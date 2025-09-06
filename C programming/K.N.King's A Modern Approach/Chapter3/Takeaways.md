<h1 align="center">💡<strong> Formatted Input/Output</strong></h1>

## :printer: The printf Function

### :large_blue_diamond: Generalities

* The printf function is part of C's standard Input/Output library.
* It's designed to display a string with possible values inserted at specified points.
* The string to be displayed is called the format string, and it's passed to printf as the first argument.
* Subsequent printf arguments, if there are any, are the values to be inserted in the string.
* printf doesn't put any limit on the number of values that can be injected into the format string.
* The values to be inserted can be constants, variables, or other more complex expressions.
* The format string can have two types of characters:
   * Ordinary characters: Copied as is to the output line.
   * Conversion specifications: Begin with the '%' character and are placeholders for the values to be inserted in the format string.
* The characters following '%' in a conversion specification provide information on how the value to be inserted is converted from its binary form to printed form.
* As an example, the %d conversion specification instructs printf to convert an integer value from its binary form to a string of decimal digits.
* The values are inserted in the format string in the order they are provided to printf.
* C compilers can't detect a mismatch between the number of conversion specifications in a printf format string and the number of provided values.
* If more conversion specifications than values are provided, the extra conversion specifications will be replaced by meaningless values.
* If fewer conversion specifications than values are provided, the extra values will not be displayed in the output.
* C compilers can't tell if a programmer has provided an inappropriate conversion specification for the type of value to be injected in the format string. If this happens, printf will attempt to perform the conversion and will, more than likely, produce unexpected results.
* printf has no way of knowing the types of the values to be inserted in the format string at compile-time. Instead, it relies entirely on the conversion specifiers to interpret the raw bytes it gets.

### :large_blue_diamond: Conversion Specifications

* Conversion specifications can be used to influence the way printf displays values.
* They can even contain formatting information.
* The general form of a conversion specification is as follows: ```%m.pX```:
   * m and p are integer constants and X is a letter.
   * m and p are both optional. If m is omitted, p must keep its dot. If p is omitted, the dot must also be removed.
   * X, called the conversion specifier, indicates what type of conversion should be applied to a value before it's printed.
   * m, called the "minimum field width", indicates the minimum overall number of characters to be used to display the converted value.
   * p is called the precision.
* The minimum field width m can be used in slightly varying ways:
   * If printf tries to display a value containing fewer than m characters inside an m-sized field, the value will be right-justified. In other words, space paddings will precede the value to take up m characters.
   * If printf tries to display a value containing more than m characters inside an m-sized field, the field will expand to the right size and no characters will be lost.
   * A minus sign in front of m causes left-justification inside the m-sized field.
* Some of the most common conversion specifiers for numeric values are:
   * ```d```: Displays an integer value in decimal form.
   * ```e```: Displays a floating-point number in exponential format also known as scientific notation.
   * ```f```: Displays a floating-point number in fixed decimal format.
   * ```g```: Displays a floating-point number in either exponential or fixed decimal format depending on the number's size.
      * It won't display the decimal point if the value has no digits after the decimal point.
      * It won't display trailing zeros in contrast to the f specifier.
      * Usually used with floating-point numbers whose size can't be predicted when writing a program, or whose size may vary substantially at runtime.
      * It's mostly left up to the compiler to choose which of the two formats to use, but it's safe to assume that reasonably-sized numbers will be displayed in fixed decimal form, while very large/small numbers will be displayed in exponential form.
* The precision p can mean a lot of things depending on the conversion specifier:
   * ```d```: p indicates the minimum number of digits to be displayed. Extra zeros can be added to reach the required number. If p is removed, it's as if it had the value 1.
   * ```e```: p indicates the number of digits that should appear after the decimal point. The default value is 6. The decimal point is not displayed if p is zero.
   * ```f```: p has the same meaning as with the e conversion specifier.
   * ```g```: p indicates the maximum number of digits before the decimal point to be displayed.

### :large_blue_diamond: Escape Sequences

* Escape sequences enable strings to contain characters that can't simply be injected in strings lest they be misinterpreted by the compiler.
* Such characters include nonprinting control characters and characters that have special meaning to the compiler.
* When used inside a printf format string, escape sequences represent actions to be performed.
* Common escape sequences include:
   * ```\a``` Alert: Causes a beep on most machines (many modern systems may ignore it).
   * ```\b``` Backspace: Moves the cursor back one position.
   * ```\n``` Newline: Moves the cursor to the beginning of a new line.
   * ```\t``` Horizontal Tab: Moves the cursor to the next tab stop.
* A printf format string can have any number of escape sequences.
* Some characters can't be used inside printf format strings unless bundled in an escape sequence. Examples include:
   * ```"```: String literal delimiter. Might cause confusion inside a format string (does it indicate the start/end of the string?). Must be escaped as ```\"```.
   * ```\```: Escape sequence indicator. Might cause confusion inside a format string (does it indicate an upcoming escape sequence?). Must be escaped as ```\\```.
