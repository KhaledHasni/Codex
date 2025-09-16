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

* C uses operator precedence rules to resolve the ambiguity that arises when more than one operator is used in the same expression.
* As a general rule, C imposes no restrictions on the use of parentheses in such expressions to avoid said ambiguity.
* C's arithmetic operators have three levels of relative precedence:
   * Highest: Unary plus ```+```, Unary minus ```-```.
   * Intermediate: ```*```, ```/```, ```%```.
   * Lowest: Binary plus ```+```, Binary minus ```-```.
* When evaluating an expression containing more than one arithmetic operator with no parentheses, the idea is to break it down into subexpressions starting with the highest operator precedence and working our way down. This is equivalent to enclosing these subexpressions in parentheses and evaluating the resulting expression:
   * ```i + j * k``` is equivalent to ```i + (j * k)```
   * ```i + -j / k``` is equivalent to ```i + ((-j) / k)```
* Precedence rules are not enough when more than one operator of the same precedence level are used in the same expression. This is where operator associativity comes into play.
* An operator is said to be left-associative if it groups from left to right. All of C's binary arithmetic operators are left-associative.
   * Example: ```i + j - k``` is equivalent to ```(i + j) - k```.
* An operator is said to be right-associative if it groups from right to left. C's unary plus and minus operators are right-associative.
   * Example: ```+-i``` is equivalent to ```+(-i)```.
* A C programmer will have to learn these precedence and associativity rules to be able to efficiently navigate arithmetic expressions. Most C programmers don't bother to learn them however, opting instead for using a lookup table of rules when necessary or relying on parentheses whenever in doubt.

## 🟰 Assignment Operators

* C's simple assignment ```=``` operator is used to store the value of an expression in a variable for later use.
* C also offers compound assignment operators to modify a value already stored in a variable.
* Using the ```=``` operator will essentially evaluate the right operand and copy the result into the left operand.
* ```=```'s right operand can be a constant, a variable or even an expression.
* If the right and left operands don't have matching types, the right operand will be converted to the left operand's type as the assignment happens. Assuming ```i``` is an integer variable and ```f``` is a floating-point variable:
   * ```i = 3.2f``` will result in ```i``` having the value ```3```.
   * ```f = 5``` will result in ```f``` having the value ```5.0```.
* Assignment in C is an operator. It produces a result just like any other operator.
* The value of ```v = e``` is the value of ```v``` after the assignment takes place. Assuming ```i``` and ```f``` are an integer and a floating-point variable respectively:
   * The value of the assignment ```i = 3.5f``` is ```3``` and not ```3.5```.
* An operator is said to have a side effect if it alters the value of one or more of its operands.
* C's simple assignment operator has side effects. It evaluates its right operand, then modifies the value of its left operand by copying the result into it.
* In the assignment ```v = e```, ```=``` evaluates ```e``` and as a side effect assigns that value to ```v```.
* The fact that C sees ```=``` as an operator means several assignments can be chained together in the same expression.
* The simple assignment ```=``` operator is right-associative:
   * ```i = j = k = 5``` is equivalent to ```i = (j = (k = 5))``` and will assign ```5``` to ```k``` then to ```j``` then to ```i```.
* Type conversion when right and left ```=``` operands are of different types still applies for chained assignments.
* An assignment of the form ```v = e``` is allowed wherever a value of type ```v``` is allowed:
   * ```i = k + (j = 6)``` will assign ```6``` to ```j```, add ```6``` to ```k``` and assign the result to ```i```.
* Using chained assignments can make programs hard to read.
* C's simple assignment operator requires an lvalue as its left operand.
* An lvalue is an object that occupies a place in computer memory unlike a constant value or an expression.
* Variables are lvalues.
* Using an expression or a constant or any other non-lvalue as ```=```'s left operand will result in a compilation error.
* C provides compound assignment operators that allow us to overwrite the value of a variable with a new value computed using the old value.
   * ```i += 1``` performs the same task as ```i = i + 1```.
* C provides a total of 10 compound assignment operators.
* Assuming ```v``` is a variable and ```e``` is an expression:
   * ```v += e``` adds the value of ```e``` to that of ```v``` and stores the result in ```v```.
   * ```v -= e``` subtracts the value of ```e``` from that of ```v``` and stores the result in ```v```.
   * ```v *= e``` multiplies the value of ```e``` with that of ```v``` and stores the result in ```v```.
   * ```v /= e``` divides the value of ```v``` by that of ```e``` and stores the result in ```v```.
   * ```v %= e``` computes the remainder when the value of ```v``` is divided by that of ```e``` and stores the result in ```v```.
* C's compound assignment operators, like the simple assignment operator, are right-associative.
   * ```i += j += k``` is equivalent to ```i += (j += k)```.
* Assuming ```v``` is a variable and ```e``` is an expression, ```v *= e``` is not necessarily equivalent to ```v = v * e``` since we have to account for operator precedence. If ```e``` is equal to ```i + j``` for example, we can clearly see ```v *= i + j``` is not equivalent to ```v = v * i + j``` since the ```*``` takes precedence over the binary ```+``` operator. Enclosing ```i + j``` in parentheses would solve this issue however.
* The same can be said for ```+=``` and other compound operators especially when their left operand has side effects.
   * ```array[i++] += 1``` is a classic example of this.

## ➕ Increment And Decrement Operators ➖

## :gear: Expression Evaluation

## :speech_balloon: Expression Statements

## :game_die: Miscellaneous