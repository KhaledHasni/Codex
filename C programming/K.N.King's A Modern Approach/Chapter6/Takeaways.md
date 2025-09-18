<h1 align="center">💡<strong> Loops</strong></h1>
<p align="center">
  <a href="#cyclone-the-while-statement">The while Statement</a> •
  <a href="#repeat_one-the-do-statement">The do Statement</a> •
  <a href="#repeat-the-for-statement">The for Statement</a> •
  <a href="#stop_sign-exiting-from-a-loop"> Exiting From A Loop</a> •
  <a href="#hole-the-null-statement">The null Statement</a> •
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

* C's ```for``` statement has the following form: ```for(expression1; expression2; expression3) statement```.
   * ```expression1```, ```expression2``` and ```expression3``` are three expressions.
   * ```statement``` is called the loop body.
* When a ```for``` statement is executed, ```expression1``` is first evaluated, followed by ```expression2```. If ```expression2``` evaluates to ```false```, the loop body is skipped and control is transferred to the first statement after the ```for``` loop. If ```expression2``` evaluates to ```true```, the loop body is executed, ```expression3``` is evaluated, then ```expression2``` is evaluated again. This process (evaluating ```expression2```, executing the loop body then evaluating ```expression3``` continues until ```expression2``` evaluates to ```false```).
* In most cases, a ```for``` loop can be rewritten using a ```while``` loop using the following pattern:
```c
expression1;
while(expression2){
   statement;
   expression3;
}
```
   * ```expression1``` is an initialization step that occurs once before entering the loop.
   * ```expression2``` controls the loop's termination.
   * ```expression3``` is executed at the end of each loop iteration.
* Examining a ```for``` loop's equivalent ```while``` statement reveals several facts:
   * ```expression1``` and ```expression3``` are executed as expression statements in the equivalent ```while``` loop.
   * This means ```expression1``` and ```expression3``` are only useful for their side effects.
   * For this reason, ```expression1``` and ```expression3``` are usually assignments and increment/decrement expressions respectively.
* C's ```for``` loop is usually the go-to choice when writing loops that count up or down.
   * ```for(i = 0; i < n; i++)``` counts up from ```0``` to ```n - 1```.
   * ```for(i = 1; i <= n; i++)``` counts up from ```1``` to ```n```.
   * ```for(i = n; i > 0; i--)``` counts down from ```n``` to ```1```.
   * ```for(i = n - 1; i >= 0; i--)``` counts down from ```n - 1``` to ```0```.
* Common mistakes beginner C programmers make when writing ```for``` statements include:
   * "Off-by-one" errors.
   * Writing ```i == n``` as the controlling expression which could lead to the immediate termination of the loop as soon as it starts executing.
* ```for``` loops do not require all three controlling expressions to be used. In fact, we can even write a ```for``` loop with none of the three controlling expressions.
* The two semicolons inside the for loop's parentheses are mandatory and must always be present, even if one or more expressions are omitted. They are part of the ```for``` loop's syntax.
* ```expression1``` can be omitted if we don't need to execute an expression statement before the loop is entered.
* If ```expression3``` is omitted, it becomes the loop body's responsibility to ensure the controlling expression eventually evaluates to ```false```.
* If ```expression1``` and ```expression3``` are both omitted, the resulting ```for ``` loop is just a ```while``` loop in disguise.
* If ```expression2``` is omitted, its value will default to ```true```, and as a result, the loop will never terminate unless its body contains a statement that transfers control out of the loop, or calls a function that terminates the program.
* Some C programmers use the following idiomatic for loop to create an infinite loop: ```for(;;)```.
* C99 offers the possibility to use the first expression in a ```for``` loop to declare and initialize a variable.
   * ```for(int i = 0; i < n; i++)```
      * ```i``` doesn't need to be declared prior to this.
      * If another variable called ```i``` is still within scope, ```i``` declared in the loop will supersede it.
      * ```i``` is only visible inside the loop's body and can't be referenced anymore once control is transferred outside the loop.
* C99 allows declaring more than one variable in a ```for``` loop's first expression, provided that all variables have the same type.
   * ```for(int i = 0, j = 1; i < n; i++)```.
* C99 also allows incrementing/decrementing more than one variable in a ```for``` loop's third expression.
   * ```for(int i = 0; i < n; i++, j++)```.
* C's comma operator ```,``` can be used to chain together a sequence of expressions to form what is called a "comma expression".
   * ```expression1, expression2```.
      * ```expression1``` and ```expression2``` are any two expressions.
      * This comma expression is evaluated in two stages:
         * ```expression1``` is evaluated first, and its value is discarded.
         * ```expression2``` is then evaluated, and its value is the value of the whole comma expression.
      * Since ```expression1```'s value is discarded, it should always have a side effect, otherwise it will essentially be useless.
* C's comma operator ```,``` has the lowest level of precedence among all operators in the entire C programming language.
* C's comma operator ```,``` is left associative.
   * ```++i, ++j, ++k``` is equivalent to ```(++i, ++j), ++k```.
      * ```i``` will be incremented and its value discarded. The change to ```i``` is permanent, however.
      * ```j``` will then be incremented, and its new value will be the value of the entire comma expression enclosed in parentheses.
      * ```k``` will be incremented next, and its new value will be the value of the entire expression.
* The comma operator allows us to have more than one expression anywhere a single expression is required. From this standpoint, it is much like the compound statement which allows us to have multiple statements anywhere a single statement is required.
* The comma operator has been part of the C programming language since the C89 ANSI standard.
* The three controlling expressions in a ```for``` loop are customarily used to initialize, test and update the same variable. However, C does not require this. The three expressions can be unrelated and even involve three different variables.

## :stop_sign: Exiting From A Loop

* The ```while``` and ```for``` loops' exit points come before their bodies.
* The ```do``` loop's exit point comes after its body.
* The ```break``` statement can be used to establish an exit point in the middle of a loop's body.
* The ```break``` statement can be used to create a loop with more than one exit point.
* The ```break``` statement transfers control out of the innermost enclosing ```for```, ```do```, ```while``` and ```switch``` statement. If more than one of these statements are nested, the ```break``` statement can only escape a single level of nesting.
* In contrast to the ```break``` statement which transfers control to a point right past the end of the enclosing loop or ```switch``` statement, the ```continue``` statement transfers control to a point right before the end of the enclosing loop body, keeping control within the loop.
* The ```continue``` statement can only be used with loops.
* ```break``` and ```continue``` are two examples of restricted jump statements that transfer control from one point in the program to another particular target point.
* The ```goto``` statement is a jump statement that allows a program to transfer control from one point in the program to any other statement in the program provided that:
   * The target statement has a ```label```.
   * The source and target points are contained in the same function.
* A ```label``` is just an identifier at the beginning of the statement followed by a colon ```:```.
   * ```label: statement```.
* A statement may have more than one label.
* C99 requires a ```goto``` statement not to skip the declaration of a variable-length array (a concept that will be discussed in later chapters).
* The ```goto``` statement has the following format: ```goto label```.
* The ```goto``` statement is not frequently used in modern C programming. The ```break```, ```continue```, ```return``` statements and the ```exit``` function are in most cases more than enough to handle situations where control transfer is needed. That being said, there are situations where the ```goto``` statement can still be useful:
   * Early function exit, commonly known as "guard clause".
   * Leaving nested loops.
   * Leaving ```switch``` statements nested in loops or vice versa.

## :hole: The null Statement

* A C statement that doesn't contain any symbols apart from the trailing semicolon is called the null statement.
* The null statement does nothing and is typically used in loops whose bodies are empty.
   * ```for(i = 0; i < n; i++);```. The trailing semicolon here is the null statement which indicates in this case that the loop body is empty.
* C programmers will usually place the null statement on a line by itself to make it obvious.
* Inadvertently placing a semicolon after the parentheses in an ```if```, ```for``` or ```while``` statement creates a null statement, leading to unexpected behavior.
   * The ```if``` statement's "body" is executed irrespective of the value of its controlling expression.
   * The ```for``` and ```while``` loops "bodies" may never be executed if an infinite loop was inadvertently created, or they may only be executed once if the loops eventually terminate.

## :game_die: Miscellaneous
