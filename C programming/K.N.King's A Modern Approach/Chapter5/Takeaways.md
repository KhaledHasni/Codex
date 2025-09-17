<h1 align="center">💡<strong> Selection Statements</strong></h1>
<p align="center">
  <a href="#brain-logical-expressions">Logical Expressions</a> •
  <a href="#twisted_rightwards_arrows-the-if-statement">The if Statement</a> •
  <a href="#question-the-switch-statement">The switch Statement</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :brain: Logical Expressions

### :small_blue_diamond: Relational Operators

* C provides four relational operators.
   * The less than operator ```<```.
   * The greater than operator ```>```.
   * The less than or equal to operator ```<=```.
   * The greater than or equal to operator ```>=```.
* C's relational operators produce either ```0``` or ```1``` when used in expressions.
* C's relational operators can be used with integer and floating-point operands with mixed types allowed.
* C's relational operators have a lower precedence level compared to C's arithmetic operators.
* C's relational operators are left-associative.
   * ```i < j < k``` is equivalent to ```(i < j) < k``` which tests whether ```i``` is less than ```j``` producing either ```0``` or ```1```, then comparing that to ```k```.

### :small_blue_diamond: Equality Operators

* C provides two equality operators.
   * The equal to operator ```==```.
   * The not equal to operator ```!=```.
* C's equality operators produce either ```0``` or ```1``` when used in expressions.
* C's equality operators are left-associative.
* C's equality operators have lower precedence level compared to C's relational operators.
   * ```i < j == i < k``` is equivalent to ```(i < j) == (i < k)``` which essentially tests whether ```i < j``` and ```i < k``` both produce ```false``` or both produce ```true```.

### :small_blue_diamond: Logical Operators

* C allows building complex logical expressions by combining simple ones using the three common logical operators.
   * The logical and operator ```&&```. This is a binary operator.
   * The logical or operator ```||```. This is a binary operator.
   * The logical negation operator ```!```. This is a unary operator.
* C's logical operators produce either ```0``` or ```1``` when used in expressions.
* C's logical operators treat all nonzero operands as ```true``` and all zero operands as ```false```.
* Assuming ```e1``` and ```e2``` are expressions:
   * ```!e1``` is true if ```e1``` is false.
   * ```e1 && e2``` is true if both ```e1``` and ```e2``` are true.
   * ```e1 || e2``` is true if either ```e1``` or ```e2``` (or both) is true.
   * Every other combination will produce false.
* The ```&&``` and ```||``` operators don't evaluate both their operands if the result of the whole expression can be deduced from evaluating the first operand only (the left operand). This is called "short-circuit" evaluation.
   * ```e1 && e2``` yields false if ```e1``` is false regardless of the value of ```e2```.
   * ```e1 || e2``` yields true if ```e1``` is true regardless of the value of ```e2```.
* The logical negation operator ```!``` is right-associative.
* The logical negation operator ```!``` has the same level of precedence as the unary plus and minus operators.
* The logical or ```||``` and logical and ```&&``` operators are left-associative.
* The logical or ```||``` and logical and ```&&``` operators have a lower precedence level compared to the relational and equality operators.

## :twisted_rightwards_arrows: The if Statement

## :question: The switch Statement

## :game_die: Miscellaneous
