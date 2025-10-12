<h1 align="center">💡<strong> Declarations</strong></h1>
<p align="center">
  <a href="#writing_hand-declaration-syntax">Declaration Syntax</a> •
  <a href="#file_cabinet-storage-classes">Storage Classes</a> •
  <a href="#bookmark-type-qualifiers">Type Qualifiers</a> •
  <a href="#pencil2-declarators">Declarators</a> •
  <a href="#seedling-initializers">Initializers</a> •
  <a href="#zap-inline-functions">Inline Functions</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :writing_hand: Declaration Syntax

* Declarations in C are used to explain the meaning of identifiers to the compiler.
* A declaration in C has the following general form: ```declaration_specifiers declarators```.
   * ```declaration_specifiers``` provide information about the properties of the identifiers being declared.
   * ```declarators``` provide the names of the identifiers being declared. They may provide additional information about some of their properties as well.
   * C89 recognizes three categories of declaration specifiers.
      * ```Storage classes```.
         * C has four storage classes: ```auto```, ```static```, ```extern``` and ```register```.
         * A declaration cannot have more than one storage class.
         * A declaration may have no storage class at all.
         * Storage classes must always be mentioned before anything else in a declaration. This is one of very few rules C enforces on the order of declaration specifiers.
      * ```Type qualifiers```.
         * C89 has two type qualifiers only: ```const``` and ```volatile```.
         * C99 adds a third type qualifier: ```restrict```.
         * A declaration can have multiple different type qualifiers.
         * A declaration may have no type qualifiers at all.
      * ```Type specifiers```.
         * C's type specifiers come in multiple forms.
         * Keywords like ```void```, ```char```, ```short```, ```int```, ```long```, ```float```, ```double```, ```signed``` and ```unsigned``` are all type specifiers.
            * These keywords can be combined (some combinations are invalid).
            * When combined, the order in which these keywords appear is irrelevant.
         * Structure, union and enumeration specifications are also type specifiers.
         * Custom types created using ```typedef``` are type specifiers as well.
   * C99 adds a fourth declaration specifier category.
      * ```Function specifiers```.
         * This category includes a single keyword: ```inline```.
         * ```inline``` can only be used with function declarations, hence the name of the category.
   * Type specifiers' and type qualifiers' relative positions in a declaration are interchangeable as long as they come after the storage class.
   * Declarators have several rules:
      * They come in different forms.
         * Identifiers like the names of simple variables.
         * Identifiers followed by ```[]```. These identifiers are names of arrays.
         * Identifiers preceded by ```*```. These identifiers are names of pointer variables.
         * Identifiers followed by ```()```. These identifiers are names of functions.
      * Several declarators can be grouped together and associated to a single set of declaration specifiers. In this case, these declarators are separated by commas.
      * A declarator that represents a variable may be followed by an initializer.

## :file_cabinet: Storage Classes

* C allows specifying storage classes for variables, functions and function parameters.
* Every variable in C has three properties.
   * Storage duration.
      * A variable's storage duration dictates when memory gets allocated for that variable and when it gets released.
      * C offers two types of storage duration for variables: "automatic" storage duration and "static" storage duration.
      * Storage for a variable with automatic storage duration is allocated when control enters the enclosing block.
      * Storage for a variable with automatic storage duration is released when the enclosing block terminates.
         * Consequently, a variable with automatic storage duration will lose its value when the enclosing block terminates.
      * A variable with static storage duration is allocated when the program starts executing (even before control enters the main function).
      * Variables with static storage duration keep the same storage location for as long as the program is executing.
         * Consequently, a variable with static storage duration retains its value indefinitely.
      * C also provides the "allocated" (dynamic) storage duration.
         * This kind of storage is allocated on the heap as opposed to the stack.
         * It requires the use of C's memory management functions ```malloc```, ```calloc```, ```realloc``` and ```free```.
      * C11 offers the "thread" storage duration which won't be discussed here.
   * Scope.
      * A variable's scope is the portion of the program text in which the variable can be referenced.
      * C offers two types of scope for variables.
         * Block scope.
            * A variable with block scope can be referenced from its point of declaration to the end of the enclosing block.
         * File scope.
            * A variable with file scope can be referenced from its point of declaration to the end of the enclosing file.
   * Linkage.
      * A variable's linkage dictates the extent to which a variable can be shared by different files in a program.
      * C offers three types of linkage for variables.
         * External linkage.
            * A variable with external linkage can be shared by different files in a program.
            * A variable with internal linkage cannot be shared by different files, and is restricted to the file in which it's declared. It can be shared by functions in that file.
            * A variable with no linkage is a variable declared inside a function block. It cannot be shared with other files nor can it be shared with other functions defined in the same file. It strictly belongs to the function inside of which it is declared.
* C associates a set of default properties to variables depending on where they're declared in a program.
   * A variable declared inside a block (function, compound statement, selection and iteration statement in C99) has the following default properties:
      * Automatic storage duration.
      * Block scope.
      * No linkage.
   * A variable declared outside all functions, at the outermost level of nesting in a program, has the following default properties:
      * Static storage duration.
      * File scope.
      * External linkage.
* C provides four storage classes that can be assigned to a variable when it's declared, if the programmer wants to override its default set of properties. These four storage classes are ```auto```, ```static```, ```extern``` and ```register```.

### :small_blue_diamond: The auto Storage Class

* The ```auto``` storage class can only be used with variables declared inside a block.
* An ```auto``` variable has automatic storage duration, block scope and no linkage.
* An ```auto``` variable's properties exactly match the default properties assigned to a variable declared inside a block. Therefore, the ```auto``` storage class is rarely, if ever, explicitly specified by C programmers.
   * In the old days of C, programmers used to explicitly specify the ```auto``` storage class to shadow another variable that shares the same name but has a different storage class.
   ```c
   void dummy_function(void) {
      static int i = 5;
      {
        auto int i = 30;   // explicitly says "this is a local automatic variable"
        printf("%d\n", i); // prints 30
      }
   }
   ```

### :small_blue_diamond: The static Storage Class

* The ```static``` storage class can be used on all variables irrespective of their place of declaration in a program.
* A ```static``` variable will have a different set of properties depending on where it's declared.
   * A ```static``` variable declared inside a block will have block scope and no linkage as we would expect, but it will have static storage duration, thereby overriding its default automatic storage duration.
      * As a result, a ```static``` variable declared inside a block retains its value after control leaves the enclosing block.
   * A ```static``` variable declared outside a block will have static storage duration and file scope as we would expect, but it will have internal linkage, thereby overriding its default external linkage. This essentially hides the variable inside the file in which it is declared.
* A ```static``` variable is initialized only once before the program begins executing.
   * This is in contrast to an ```auto``` which is initialized every time it comes into existence.
   * The C runtime (the part of the program that runs before the main function) performs static initialization of all objects with static storage duration.
   * If an explicit initializer is not provided for an object with static storage duration, it's by default initialized to zero.
* A function called recursively gets new copies of its ```auto``` variables every time it's called. The same can't be said for its ```static``` variables. These are shared across all calls of the recursive function.
* A function returning a pointer to an ```auto``` variable is highly problematic. Conversely, a function returning a pointer to one of its ```static``` variables is perfectly fine.
* ```static``` variables declared inside functions are used to store information across calls to that function. This information cannot be accessed from outside the function since the variable still has block scope.
* ```static``` variables declared inside functions can be used to improve the efficiency of a program.
   * Some C programmers assign static storage duration to ```const``` objects declared inside functions.
   * This prevents the program from having to initialize these objects every time the function is called, which works in our favor since the objects are invariable by virtue of them being ```const```.

### :small_blue_diamond: The extern Storage Class

* The ```extern``` storage class allows an object to be shared across multiple source files.
* When an ```extern``` variable is declared, storage is not allocated for it.
   * ```extern int a;``` informs the compiler that we will need access to a variable of type ```int``` called ```a```.
   * Storage for ```a``` is not immediately allocated.
   * Storage for ```a``` will be allocated later in the file or in another file entirely.
   * In C terminology, we say that ```a``` is "declared" but not yet "defined".
* According to the C standard, a variable may have several declarations in a program but may only have one definition.
   * This rule is designed to prevent a program from initializing a single variable with multiple different values.
   * This rule comes with one exception: A variable declaration that has an initializer is both a declaration and a definition of that variable.
   * ```extern int a = 0;``` and ```int a = 0;``` are functionally equivalent.
* An ```extern``` variable has the following properties:
   * Static storage duration.
   * Block scope if it's declared inside a block, and file scope if it's declared outside of any block.
   * Internal linkage if it was declared previously in the file as ```static``` outside all functions, and external linkage otherwise.

### :small_blue_diamond: The register Storage Class

* The ```register``` storage class can only be used with variables declared inside a block.
* A ```register``` variable declaration is essentially a request to the compiler to store the variable in a CPU register as opposed to main memory.
* The compiler is not obligated to honor this request and may still choose to store a ```register``` variable in main memory.
   * The compiler is more likely to honor the request if:
      * There are free registers available.
      * The variable is relatively small in size.
      * The variable is accessed frequently.
         * A ```for``` loop control variable is a good example.
   * The compiler is more likely to ignore the request if:
      * There aren't enough physical registers available.
      * The variable is complex or large in size like an array or a structure.
      * The compiler's optimizer deems that other variables need the registers more.
* A ```register``` variable has automatic storage duration, block scope and no linkage. In that regard, it's exactly like an ```auto``` variable.
* C prohibits using the indirection operator ```&``` with a ```register``` variable since it's not stored in main memory so it doesn't actually reside at specific physical address. This restriction still applies even if the compiler's optimizer chooses not to honor the register request.
* The ```register``` storage class is mostly obsolete in modern C programming. It used to be a good way to get better performance back when C compilers were much more primitive. Compilers nowadays are much more sophisticated and can usually autonomously tell which variables would benefit the most from being stored in registers.
   * Some modern compilers go as far as unconditionally ignoring the ```register``` storage class. The GCC compiler's documentation for example states verbatim: "The register storage class specifier has no effect. It is ignored, even when compiling without optimization."
   * Even if the ```register``` storage class is ignored, the language semantics still apply. In particular, the indirection operator still can't be used.

### :small_blue_diamond: The Storage Class Of A Function

* A function's declaration and definition may include a storage class.
* A function in C may have one of two possible storage classes: ```static``` or ```extern```.
* An ```extern``` function has external linkage which allows it to be called from different source files.
* A ```static``` function has internal linkage and can only be called from within the source file in which it's defined.
   * Indirect calls to a ```static``` function can still be made from outside the source file in which it's defined using function pointers.
* A function with no explicit mention of a storage class, has external linkage by default.
* Explicitly declaring a function to be ```extern``` is just like explicitly declaring a local variable to be ```auto```. They're both redundant.
* A function that's not intended to be used outside the file in which it's defined doesn't necessarily have to be declared ```static```, although that's usually not a good idea for many reasons.
   * Declaring such functions to be ```static``` enhances program maintainability by providing an obvious visual cue that indicates changes to this function will not affect any other source file. If a pointer to a static function is passed to a function defined in a different source file, then changes to the static function are no longer contained within the confines of the file in which it's defined.
   * A ```static``` function is not visible to other source files. Consequently, its name can be used in other source files for entirely different purposes.
      * This mitigates the risk of what's colloquially known as "namespace pollution".
      * Namespace pollution happens as a result of the excessive use of names with external linkage to a point where they start conflicting with each other.
* Function parameters have the same default properties as ```auto``` variables.
   * Automatic storage duration.
   * Block scope.
   * No linkage.
* The only storage class that can be explicitly specified for a function parameter is the ```register``` storage class.

### :small_blue_diamond: Summary

* C's ```auto``` storage class has no effect.
* C's ```register``` storage class is obsolete.
* C's ```static``` and ```extern``` storage classes are frequently used.
* The following snippet showcases all possible ways in which storage classes can be used with variables and function parameters along with their different sets of properties.
```c
int a;
extern int b;
static int c;

void dummy_function(int d, register int e) {
   auto int f;
   int g;
   static int h;
   extern int i;
   register int j;
}
```
| Name       | Storage Duration                                 | Scope                             | Linkage                |
| :--------: | :----------------------------------------------: | :-------------------------------: | :--------------------: |
| a          | static                                           | file                              | external               |
| b          | static                                           | file                              | not enough information |
| c          | static                                           | file                              | internal               |
| d          | automatic                                        | block                             | no linkage             |
| e          | automatic                                        | block                             | no linkage             |
| f          | automatic                                        | block                             | no linkage             |
| g          | automatic                                        | block                             | no linkage             |
| h          | static                                           | block                             | no linkage             |
| i          | static                                           | block                             | not enough information |
| j          | automatic                                        | block                             | no linkage             |

## :bookmark: Type Qualifiers

* C provides two type qualifiers: ```const``` and ```volatile```.
* C99 provides a third type qualifier that can only be used with pointers: ```restrict```.
* ```const``` can be used to declare variable-like objects that are read-only.
   * The program can access the value of a ```const``` object but is not allowed to change it.
* C programmers habitually declare objects to be ```const``` for several reasons:
   * A ```const``` object provides a good hint for anyone reading the program that the object in question is not supposed to be changed by the program. In that sense, the ```const``` type qualifier serves as a form of documentation.
   * Declaring an object that's not supposed to be changed to be ```const``` is a good defense mechanism since the compiler will catch any attempt to change the value of the object and produce an error.
   * In many cases, especially when executing a program on a resource-constrained device (which is common when writing code for embedded systems), the ```const``` qualifier is a hint to the compiler to store data in read-only memory (ROM).
* Since the ```const``` type qualifier is used to create read-only "constant" objects, it might be tempting to view it in the same light as the ```#define``` preprocessing directive, which is customarily used to create names for constants. This however is not a good way of looking at it, since there are significant differences between the two.
   * The ```#define``` directive is used to create names for numeric, character and string constants. The ```const``` qualifier on the other hand can be used to create read-only objects of any type, including pointers, structures, unions and arrays.
   * The same set of variable scope rules apply to ```const``` objects. The same can't be said for constants created using the ```#define``` directive.
   * Debuggers cannot access the value of a constant created using the ```#define``` directive, unlike the value of a ```const``` object.
   * A ```const``` object has an address in memory and can therefore be used as the operand of the indirection operator ```&```. The same does not apply to a constant created using the ```#define``` directive. 
   * ```const``` objects cannot be used where constant expressions are expected. Macros created using the ```#define``` directive can.
      * Common examples include array bounds and switch statement case labels.
      ```c
      const int n = 10;
      int array[n]; // Illegal

      switch(/* dummy_expression */) {
         case n: // Illegal
      }
      ```
   * Note that using a ```const``` integer object as the size of an array in its declaration is legal in C99 if the array has automatic storage duration (in which case it will be treated as a variable-length array), but not if it has static storage duration.

## :pencil2: Declarators

## :seedling: Initializers

## :zap: Inline Functions

## :game_die: Miscellaneous