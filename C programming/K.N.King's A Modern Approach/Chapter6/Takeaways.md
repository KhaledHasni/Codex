<h1 align="center">💡<strong> Loops</strong></h1>
<p align="center">
  <a href="#cyclone-the-while-statement">The while Statement</a> •
  <a href="#repeat_one-the-do-statement">The do Statement</a> •
  <a href="#repeat-the-for-statement">The for Statement</a> •
  <a href="#stop_sign-exiting-from-a-loop"> Exiting From A Loop</a> •
  <a href="#hole-the-null-statement">The NULL Statement</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :cyclone: The while Statement

* C's ```while``` loop in its simplest form looks like this: ```while(expression) statement```.
   * The expression enclosed in parentheses is called "the controlling expression".
   * The statement after the parentheses is called "the loop body".
   * The parentheses around the controlling expression are mandatory and are part of the ```while``` loop's syntax.
   * Some other programming languages add a keyword like ```then``` after the controlling expression. C does not do that.
* When a ```while``` loop is executed, the controlling expression is first evaluated. If its value is ```false```, the loop body is skipped and control is transferred to the first statement after the ```while``` loop. If the controlling expression evaluates to ```true```, the loop body is executed and the expression is evaluated again. This process (evaluating the controlling expression and executing the loop body if it's ```true```) continues until the controlling expression evaluates to ```false```.
* C requires the ```while``` loop's body to be a single statement. We can work around this by enclosing multiple statements in a pair of braces and using that as the loop body. This kind of statement is called a "compound statement".
* When a ```while``` loop terminates, the controlling expression's value is ```false```.
* A ```while``` loop's body may not be executed at all if the controlling expression evaluates to ```false``` when the loop is first entered.
* A ```while``` loop will never terminate if its controlling expression never evaluates to ```false```, unless its body contains a statement that transfers control out of the loop such as ```goto```, ```break``` and ```return``` or calls a function that causes the program to terminate.

## :repeat_one: The do Statement

* C's ```do``` statement is basically a ```while``` statement where the controlling expression is evaluated after the loop body.
* The ```do``` statement has the following form: ```do statement while(expression);```.
   * The expression enclosed in parentheses is called "the controlling expression".
   * The statement after the word ```do``` is called "the loop body".
   * The parentheses around the controlling expression are mandatory and are part of the ```do``` loop's syntax.
* C requires the ```do``` loop's body to be a single statement (possibly a compound statement).
* When a ```do``` statement is executed, the loop body is executed first, then the controlling expression is evaluated. If the controlling expression evaluates to ```true```, the loop body is executed again. This process (executing the loop body then evaluating the controlling expression) continues until the controlling expression evaluates to ```false```, at which point the loop terminates.
* C's ```do``` and ```while``` statements have a lot in common. The main difference between the two is:
   * The ```do``` loop's body is guaranteed to be executed at least once.
   * The ```while``` loop's body may not be executed at all if the controlling expression is ```false``` initially.
* It's often a good idea to enclose the ```do``` loop's body in braces even when they're not strictly necessary, to avoid confusion with a ```while``` loop.

## :repeat: The for Statement

## :stop_sign: Exiting From A Loop

## :hole: The NULL Statement

## :game_die: Miscellaneous
