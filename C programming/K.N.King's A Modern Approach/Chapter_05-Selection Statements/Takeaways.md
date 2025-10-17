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

* C's ```if``` statement allows a program to selectively execute a statement depending on whether or not an expression is true.
* In its simplest form, C's ```if``` statement looks like this: ```if(expression) statement```.
   * The parentheses around the expression are mandatory and are part of the ```if``` statement's syntax.
   * Some other programming languages like Pascal add a keyword like ```then``` after the expression. C does not do that.
   * When such a statement is executed, the expression between parentheses is evaluated. If it's nonzero (true), the subsequent statement will be executed.
* One of C's most common programming mistakes is confusing the equal to operator ```==``` with the assignment operator ```=``` inside an ```if``` statement's expression. The confusion probably stems from the fact that ```=``` denotes the equality operator in mathematics.
   * ```if(i == 0)``` tests whether ```i``` is equal to ```0```.
   * ```if(i = 0)``` assigns ```0``` to ```i```, fetches the resulting value since ```i = 0``` is an expression, and tests whether that value is nonzero. This ```if``` statement's condition will always evaluate to false.
* Just like in other programming languages, we can use De Morgan's law to find the equivalent of a negated logical expression.
   * ```if(!(a && b))``` is equivalent to ```if(!a || !b)```.
   * ```if(!(a || b))``` is equivalent to ```if(!a && !b)```.
* C expects a single statement to be executed if the expression enclosed in parentheses is true.
* If we want multiple statements to be executed in response to an ```if``` expression evaluating to true, we can enclose them in braces ```{statements}``` to force the compiler to treat them as a single statement. This kind of statement is called a "compound statement".
* Each statement inside a compound statement needs to end in a semicolon, but the compound statement itself does not.
* An ```if``` statement used with a compound statement would look something like this:
```c
if(i % 2 == 0) {
  printf("i is even, divide by 2");
  i /= 2;
}
```
* ```if``` statements in C can have an ```else``` clause. Such ```if``` statements look like this: ```if(expression) statement else statement```.
* The statement following the word ```else``` is executed if the expression enclosed in parentheses is false.
* Because C's syntax is mostly whitespace-agnostic and only uses whitespaces as token separators, the word ```else``` can be placed in different positions (aligned with the word ```if```, on the same line as the word ```if```...). This makes no difference functionally and is only a matter of style.
* C imposes no restrictions on the type of statements in an ```if``` statement.
* ```if``` statements can be nested inside each other to any depth. C programmers will usually align each ```if``` with its matching ```else``` and indent the statements in each to make sure the cascading ```if``` logic is discernible.
* Some C programmers use compound statements with ```if``` and ```else``` clauses even when they're not required. This is a matter of style as well and makes no functional difference.
* An ```if``` statement that has another ```if``` statement nested inside its ```else``` clause (and so on ad infinitum) is called a cascaded ```if``` statement.
* Cascaded ```if``` statements are used to conduct a series of tests. For this reason, C programmers usually don't indent a cascaded ```if``` statement's nested ```if``` statements and align all of them with the original ```if```.
```c
if(expression)
   statement
else if (expression)
   statement
...
else if(expression)
   statement
else
   statement
```
* The last ```else``` clause in a cascaded ```if``` statement is not mandatory.
* The excessive nesting of ```if``` statements can make a program hard to read. Correctly indenting ```if``` and ```else``` clauses could help make it a bit more readable.
* The "dangling else" problem is notorious when it comes to nesting ```if``` statements. This problem arises when a programmer matches an ```else``` clause with the wrong ```if``` clause.
* C abides by a rule stating that an ```else``` clause is always matched with the nearest ```if``` clause that is yet to be paired with an ```else```.
* Using compound statements with all ```if``` and ```else``` clauses can help avoid the dangling else problem.
* Just like C's ```if``` statement allows a program to perform one of two actions depending on the value of a condition, C provides an operator that allows an expression to produce one of two values depending on the value of an expression. This operator is called the "conditional operator".
* C's conditional operator requires two symbols, ```?``` and ```:```, that must be used in tandem.
* Assuming ```expression1```, ```expression2``` and ```expression3``` are three expressions of any type, the conditional operator is used in the following manner:
   * ```expression1 ? expression2 : expression3```.
* C's conditional operator produces a type of expression known as "a conditional expression".
* C's conditional operator requires three operands which makes it the only ternary operator in the entire C programming language.
* A conditional expression like ```expression1 ? expression2 : expression3``` is evaluated in stages.
   * ```expression1``` is evaluated first.
   * If ```expression1``` is true, ```expression2``` is evaluated and its value is the value of the entire conditional expression.
   * If ```expression1``` is false, ```expression3``` is evaluated and its value is the value of the entire conditional expression.
* C's conditional operator has a higher level of precedence than C's assignment operators.
* C's conditional operator has a lower level of precedence compared to all other operators discussed so far (arithmetic operators, increment/decrement operators, relational operators, equality operators and logical operators).
* Conditional expressions are most commonly used in function return statements, ```printf``` calls and macro definitions.
* C89 does not provide a boolean type. C programmers have found several ways to work around this deficiency:
   * Using integer variables instead.
   * Defining preprocessor macros like ```#define TRUE 1``` and ```#define FALSE 0```.
   * Defining a makeshift bool type using preprocessor macros ```#define BOOL int```.
* C99 provides a boolean type ```_Bool```.
* ```_Bool``` is just an unsigned integer type in disguise.
* A ```_Bool``` variable in C99 can only be assigned the values ```0``` and ```1```. Any nonzero value assigned to a ```_Bool``` variable will be considered ```1```.
* Arithmetic can be performed on ```_Bool``` variables.
* C99 extends C's standard library with new headers including ```<stdbool.h>```. This header defines the ```bool``` macro that stands for ```_Bool``` and the ```true``` and ```false``` macros that stand for ```1``` and ```0``` respectively.

## :question: The switch Statement

* Testing an expression against a series of values can be done using a cascaded ```if``` statement, or more conveniently using a ```switch``` statement.
* C's ```switch``` statement is arguably easier to read than a cascaded ```if``` statement and becomes more efficient as the number of test cases increases.
* C's ```switch``` statement in its most common form looks like this:
```c
switch(expression) {
   case constant_expression: statements
   ...
   case constant_expression: statements
   default: statements
}
```
* C's ```switch``` statement contains several components:
   * The controlling expression.
      * This is the expression enclosed in parentheses.
      * C requires it to be an integer expression.
      * Characters in C are treated as integers which makes them eligible.
      * Floating-point numbers, strings and other types are not allowed.
   * Case labels.
      * This is the ```case constant_expression:``` we see in the beginning of each case.
      * A constant expression must not contain variables or function calls, only constants and macros that stand for constants.
      * The constant expression must evaluate to an integer (including characters).
   * Statements.
      * C does not require that a single statement follow a case label so no compound statement is needed.
      * Any number of statements can follow a case label.
   * The ```default``` case.
      * Applied if the controlling statement doesn't match any other case label.
      * Not mandatory.
      * If it's missing and the controlling expression doesn't match any other case label, the whole ```switch``` statement is essentially skipped.
* C's ```switch``` statement essentially performs a conditional jump based on the value of the controlling expression.
* C does not allow duplicate case labels in a ```switch``` statement.
* The order in which case labels appear in a ```switch``` statement is irrelevant.
* C requires that each case label contain exactly one constant expression.
* A group of statements in a ```switch``` statement can be preceded by multiple case labels. This technique is known as "case fall-through".
* C's switch statement cannot test whether the controlling expression falls within a range of values.
* The last statement in a group of statements following a case label is usually the ```break``` statement.
* The ```break``` statement transfers control out of the ```switch``` statement entirely and to the first statement following it. Without it, control will fall through to the first statement in the next case, bypassing its case label entirely.
* The last case in a ```switch``` statement does not need a ```break``` statement.

## :game_die: Miscellaneous

* Some C programmers use a trick to mitigate the risk of inadvertently confusing the assignment ```=``` and equality ```==``` operators in ```if``` statement expressions. Instead of writing ```if(i == 2)```, they would routinely write ```if(2 == i)```. In the event that ```==``` is mistakenly written as ```=``` in the latter case, the compiler will generate an error since C requires the left operand of the assignment operator to be an lvalue. In other words, we can't assign a value to the constant ```2```. This trick has one major deficiency: It can only work when one of the operands is not an lvalue.
* Some compilers are designed to check for dubious uses of the assignment operator in ```if``` statement conditions. GCC for example will perform this check if ```-Wparentheses``` or ```-Wall``` is selected.
* In GCC, adding an extra set of parentheses around an ```if``` statement's condition will suppress warnings caused by the assignment operator.
* There are four common compound statement indentation and brace placement styles among C programmers.
   * The K&R style.
      * Made popular by Kernighan and Ritchie's "The C programming language".
      * The left brace is not placed on its own line.
      * Was adopted by Java programmers and is arguably the most popular style among Java programmers.
      * An ```if``` statement using this style will look something like this:
      ```c
      if(i % 2 == 0) {
         printf("i is even, divide by 2");
         i /= 2;
      }
      ```
   * The Allman style.
      * Named after Eric Allman, author of sendmail and other UNIX utilities.
      * Places each brace on its own line.
      * An ```if``` statement using this style will look something like this:
      ```c
      if(i % 2 == 0)
      {
         printf("i is even, divide by 2");
         i /= 2;
      }
      ```
   * The Whitesmiths style.
      * Made popular by the Whitesmiths C compiler.
      * Places each brace on its own line and indents the pair of them to the same level of the statements they enclose.
      * An ```if``` statement using this style will look something like this:
      ```c
      if(i % 2 == 0)
         {
         printf("i is even, divide by 2");
         i /= 2;
         }
      ```
   * The GNU style.
      * Made popular by the GNU project's software.
      * Places each brace on its own line, indents the pair of them, then further indents the statements they enclose.
      * An ```if``` statement using this style will look something like this:
      ```c
      if(i % 2 == 0)
         {
            printf("i is even, divide by 2");
            i /= 2;
         }
      ```
* Assuming ```i``` and ```f``` are an integer and a floating-point variable respectively, the value of the conditional expression ```expression ? i : f``` is of type float (```f``` if ```expression``` is false and ```i``` after conversion to float if ```expression``` is true).
* The C89 standard states that names beginning with an underscore ```_``` followed by an uppercase letter are reserved for future use and therefore cannot be used by programmers. This explains why the name ```_Bool``` was chosen for C99's boolean type since it's guaranteed not to have been used by previous programs. This ensures these older programs can continue to be compiled using newer C99-compliant compilers.
* The switch statement allows for case labels not to be preceded by the word case (the ```default``` label is a good example of this). For this reason, a programmer must make sure not to include typos when writing the ```default``` label in a switch statement. If they do, the compiler will fail to detect that mistake, interpreting it as just another case label.