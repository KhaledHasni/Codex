<h1 align="center">💡<strong> Program Organization</strong></h1>
<p align="center">
  <a href="#house-local-variables">Local Variables</a> •
  <a href="#earth_africa-external-variables">External Variables</a> •
  <a href="#package-blocks">Blocks</a> •
  <a href="#telescope-scope">Scope</a> •
  <a href="#card_index_dividers-organizing-a-c-program">Organizing A C Program</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :house: Local Variables

* A variable declared inside the body of a function is said to be ```local``` to that function.
* Local variables in C have several default properties:
   * They have ```automatic storage duration```.
      * The storage duration (also called extent) of a variable is the portion of program execution during which storage for the variable exists.
      * A local variable's storage is automatically allocated when the enclosing function is called and deallocated once it returns.
      * Since its storage is deallocated when its enclosing function returns, a local variable does not retain its value once control is transferred outside the function.
      * If the function is called again, C does not guarantee that the local variable will have the same value.
      * A local variable's storage exists from the moment the enclosing function is called, just long enough for it to return.
   * They have ```block scope```.
      * The scope of a variable is the portion of the program's text in which the variable can be referenced.
      * A local variable can be referenced from its point of declaration to the end of the enclosing function's body. In C terminology, we say it has "block scope".
      * Once control is transferred outside the enclosing function, a local variable can no longer be referenced. Consequently, its name can be used for other purposes.
* Storage for an automatic local variable exists from the moment the enclosing function is called, even if the variable hasn't yet been declared in the function's body.
   * The compiler knows all the local variables at compile time and reserves one contiguous block of stack space for them as part of the function’s activation record also known as its ```stack frame```.
* C99 doesn't require local variable declarations to be at the beginning of the function.
   * As a result, a local variable can have very limited scope if its declaration happens near the end of the function's body.
* Adding the word ```static``` in front of a local variable's declaration gives it ```static storage duration``` instead of automatic storage duration.
   * Variables with static storage have a permanent storage location in memory.
   * They retain their value when the enclosing function returns.
   * They still have block scope and therefore can't be referenced once control is transferred outside of the enclosing function.
* It might be tempting to ask: If a static local variable can't be referenced outside of the enclosing function, what's the purpose of it retaining its value once the function returns?
   * Static local variables are used to preserve data across calls to the same function while keeping it hidden from the rest of the program.
* Function parameters have the same properties as automatic local variables:
   * Automatic storage duration.
   * Block scope.
   * The only difference between the two is that parameters are automatically initialized with the value of the corresponding argument when the function is called.

## :earth_africa: External Variables

* C offers multiple ways to transfer information between different functions. Two of the most frequently used are:
   * Passing arguments.
   * ```External variables```, also known as global variables.
* An external variable is a variable declared outside of all functions.
* External variables in C have the following default properties:
   * They have static storage duration.
      * A value stored in a global variable will remain there for the lifetime of the program unless intentionally changed.
   * They have ```file scope```.
      * An external variable can be referenced anywhere from its point of declaration until the end of the enclosing file.
      * An external variable is visible inside all functions defined in the same file, provided those functions appear after its declaration.
* It's important not to abuse external variables since their excessive use can quickly degrade the quality of a program in multiple ways:
   * It hurts program maintainability: Changing an external variable must be done carefully since it impacts multiple functions.
   * It makes programs harder to debug: If an external variable contains an unexpected value during program execution, it becomes difficult to trace its root cause because multiple functions may access and modify it.
   * It hurts program portability: A function that uses an external variable is not self-contained and cannot be reused for other purposes.

## :package: Blocks

* A compound statement is any group of statements enclosed in a pair of braces: ```{statements}```.
* A compound statement can be used anywhere a statement is allowed.
* C allows a compound statement to contain declarations: ```{declarations statements}```. Such a statement is called a ```block```.
* Variables declared inside blocks have several default properties:
   * They have automatic storage duration.
      * Storage for a variable declared in a block is allocated when the block is entered and deallocated when the block is exited.
   * They have block scope.
      * A variable declared inside a block is visible from the point of its declaration until the end of the enclosing block.
   * Adding the keyword ```static``` in front of its declaration will give such a variable static storage duration.
* A function's body is a block.
* Some C programmers use blocks inside functions for different reasons:
   * To avoid dumping a load of variables at the beginning of the function, especially if some of them won't be needed until further down in the function body.
   * To reduce name conflict especially for variables with generic names like ```i``` and ```temp```.
* C99 does not require variables to be declared at the beginning of a block.
   * As a result, a variable declared inside a block may have very limited scope if its declaration happens near the end of the block.

## :telescope: Scope

* An identifier in a C program may have several different meanings. The compiler relies on C's ```scope rules``` to determine the relevant meaning at different stages in the program.
* C's most important scope rule is the following:
   * If an identifier is declared inside a block where it's already visible, the new declaration overrides the old one and the identifier takes on a new role until the enclosing block is exited, at which point, it regains its old meaning.
   * Two common scenarios may lead to this situation:
      * The original identifier has file scope.
      * The current block is nested inside another one, and the original identifier was already declared inside the outer block.

## :card_index_dividers: Organizing A C Program

## :game_die: Miscellaneous