<h1 align="center">💡<strong> Expressions</strong></h1>
<p align="center">
  <a href="#abacus-arithmetic-operators">Arithmetic Operators</a> •
  <a href="#🟰-assignment-operators">Assignment Operators</a> •
  <a href="#➕-increment-and-decrement-operators-➖">Increment And Decrement Operators</a> •
  <a href="#gear-expression-evaluation"> Expression Evaluation</a> •
  <a href="#speech_balloon-expression-statements"> Expression Statements</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :abacus: Arithmetic Operators

### :small_blue_diamond: Generalities

* Arithmetic operators are operators that perform addition, subtraction, multiplication and division. They are a staple of all programming languages.
* C provides seven arithmetic operators:
   * Unary operators: Plus ```+```, Minus ```-```.
   * Binary operators: Addition ```+```, Subtraction ```-```, Multiplication ```*```, Division ```/```, Remainder ```%```.
* A unary operator is an operator that requires a single operand.
* A binary operator is an operator that requires two operands.
* C's binary arithmetic operators can be further broken down into two groups:
   * Additive operators: Addition ```+```, Subtraction ```-```.
   * Multiplicative operators: Multiplication ```*```, Division ```/```, Remainder ```%```.
* The unary plus ```+``` operator does nothing. It's used to emphasize that a numeric constant is positive. It wasn't even part of K&R C and was later introduced in the ANSI C C89 standard mostly for consistency (since C already supported the unary minus operator) and to match other programming languages of the time like Fortran and Pascal.
* C's binary arithmetic operators, with the exception of the remainder operator ```%```, support both integer and floating-point operands with mixing allowed. The result of an operation involving integer and floating-point operands is always a floating-point number.
* When used with integer operands, the division operator truncates the result by removing the fractional part. This is true when both operands are positive integers. If either of them is negative, the resulting behavior is slightly more complicated and will be discussed further down.
   * Example: ```3 / 5``` yields ```0```.
* The remainder operator requires integer operands. If either operand is not an integer, the program won't even compile.
* Providing ```0``` as the right operand to either the division operator ```/``` or the remainder operator ```%``` yields undefined behavior.
* Providing negative operands to either the division operator ```/``` or the remainder operator ```%``` requires a breakdown. Assuming ```i``` and ```j``` have different signs:
   * In C89, the result of ```i / j``` can be rounded to the nearest integer down or up depending on the C implementation used.
   * In C89, the result of ```i % j``` can be of either sign depending on the C implementation used.
   * In C99, the result of ```i / j``` is always rounded toward zero.
   * In C99, the result of ```i % j``` always has the same sign as ```i```.
* C89's division operator ```/``` and remainder operator ```%``` handle the result of an operation with two negative operands exactly the same way they handle operations where both operands are positive. In a way, operations involving operands of the same sign are fairly straightforward. Complexity only arises for operations involving operands of different signs.
* A clever way to look at this is to bear in mind that C89 has two ways of rounding integer division results:
   * Rounding toward zero.
   * Rounding toward negative infinity also known as "flooring".
When both division operands have the same sign, both these rounding techniques yield the same result. The difference only emerges when operands have different signs.
* A C implementation is the software responsible for compiling, linking and executing a C program on a particular platform.
* The C standard leaves some parts of the language unspecified on purpose. The idea here is for every C implementation to fill in those unspecified gaps with whatever makes sense for the target platform. This is known as "implementation-defined" behavior.
* C's biggest claim to fame is its efficiency and ability to adapt to different platforms. This efficiency is exactly why the language allows for implementation-defined behavior to reflect the different ways hardware platforms process data.
* Rounding the result of an integer division up or down and the sign of the result of a remainder operation are two examples of implementation-defined behavior in C89. Some CPUs round up, while others round down. C89 allows both to ensure efficient computation on both types of platforms.
* It's usually best to avoid writing implementation-defined code to ensure portability across different platforms.

### :small_blue_diamond: Operator Precedence And Associativity

## 🟰 Assignment Operators

## ➕ Increment And Decrement Operators ➖

## :gear: Expression Evaluation

## :speech_balloon: Expression Statements

## :game_die: Miscellaneous