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

* A declarator in a C declaration is an identifier that represents the object being declared, whether that's a variable or a function. The identifier can be combined with the ```*```, ```[]``` and ```()``` symbols to form more complex declarators.
   * In its simplest form, a declarator is just an identifier.
      * ```int a;```. ```a``` in this case is a declarator.
   * A declarator containing an identifier preceded by the asterisk ```*``` symbol represents a pointer variable.
      * ```int *p;```. ```p``` in this case is a pointer variable.
   * A declarator containing an identifier followed by the ```[]``` symbol represents an array.
      * ```int array[10];```. ```array``` in this case is an array.
      * The brackets ```[]``` in an array declarator can be left empty in three cases.
         * The array has an initializer, in which case the compiler can deduce the size of the array based on the size of the initializer.
         * The array declarator is a function parameter.
         * The array's storage class is ```extern```, in which case the array is defined elsewhere in the program so the compiler doesn't require the declarator to provide a size for the array.
         * Note that only the first set of brackets can be left empty in a multidimensional array declarator.
      * C99 allows the brackets of an array function parameter to contain two other sets of symbols.
         * The keyword ```static``` followed by an expression that evaluates to the array's minimum length.
         * The asterisk ```*``` symbol in a function prototype which indicates the array parameter is a variable-length array.
   * A declarator containing an identifier followed by the ```()``` symbol represents a function.
      * C allows function declarators to omit parameter names.
      ```c
      void dummy_function(int , int* , int[]);
      ```
      * C even allows function declarators to have an empty set of parentheses.
      ```c
      void dummy_function();
      ```
      * An empty set of parentheses in a function declarator in C does not mean the function takes no arguments (that would warrant the keyword ```void``` to be put between parentheses). Instead, it means that the function can take an unspecified number of parameters of any type.
         * Leaving a function declarator's set of parentheses empty is a dangerous practice that has largely been rendered obsolete. It's perfectly valid syntax and can still be used in modern C programming, but it's strongly discouraged since it doesn't allow the compiler to perform type checking during function invocation.

### :small_blue_diamond: Deciphering Complex Declarators

* Declarators in C can be complex and quite tricky to understand. That being said, there are two rules of thumb that we can use to break down any declarator no matter how complex.
   * Declarators should be read from inside out.
      * We start by locating the identifier in the declarator. The identifier is the name of the object being declared.
      * We start figuring out the declarator from there.
   * The ```[]``` and ```()``` symbols always take precedence over the ```*``` symbol in a declarator.
      * When an identifier is preceded by the ```*``` symbol and followed by the ```[]```, it's an array, not a pointer.
      * When an identifier is preceded by the ```*``` symbol and followed by the ```()```, it's a function, not a pointer.
      * These precedence rules can be overridden by the use of parentheses.
* Applying these rules to the following examples will yield the following results:
   * ```int *p[8];```.
      * First, we locate the identifier in the declarator. In this case, the identifier is ```p```.
      * Then we notice that ```p``` is preceded by the ```*``` symbol (so ```p``` might be a pointer) and followed by the ```[]``` symbol (so ```p``` might be an array). Rules of precedence dictate that ```[]``` always takes precedence over ```*```, so ```p``` is an array of pointers to integer values.
   * ```int *p(float);```.
      * First, we locate the identifier in the declarator. In this case, the identifier is ```p```.
      * Then we notice that ```p``` is preceded by the ```*``` symbol (so ```p``` might be a pointer) and followed by the ```()``` symbol (so ```p``` might be a function). Rules of precedence dictate that ```()``` always takes precedence over ```*```, so ```p``` is a function that takes a floating-point argument and returns a pointer to an integer value.
   * ```void (*p)(int);```.
      * First, we locate the identifier in the declarator. In this case, the identifier is ```p```.
      * Then we notice that ```p``` is preceded by the ```*``` symbol (so ```p``` might be a pointer) and followed by the ```()``` symbol (so ```p``` might be a function). Rules of precedence dictate that ```()``` always takes precedence over ```*```, but these rules are overridden here by parentheses enclosing ```*p```. This means ```p``` is a pointer here. Since ```(*p)``` is followed by a ```()``` symbol, then ```p``` is a pointer to a function that takes an integer argument and returns nothing.
   * ```int *(*p[10])(void);```.
      * First, we locate the identifier in the declarator. In this case, the identifier is ```p```.
      * Then we notice that ```p``` is preceded by the ```*``` symbol (so ```p``` might be a pointer) and followed by the ```[]``` symbol (so ```p``` might be an array). Precedence rules dictate that ```[]``` takes precedence over ```*```, so ```p``` is an array of pointers. Next we notice that ```(*p[10])``` is preceded by the ```*``` symbol and followed by the ```()``` symbol. Again, according to precedence rules, ```()``` takes precedence over ```*``` so ```p``` is an array of pointers to functions that take no arguments and return pointers to integer values.
* Some objects are illegal in C and therefore cannot be declared.
   * Functions that return functions.
      * C forbids a function from returning a function.
      * ```void f(int)(int);``` is illegal in C.
      * To work around this limitation, C allows a function to return a pointer to a function.
   * Functions that return arrays.
      * C forbids a function from returning an array.
      * ```int f(void)[];``` is illegal in C.
      * To work around this limitation, C allows a function to return a pointer to an array.
   * Arrays of functions.
      * ```int a[8](int);``` is illegal in C.
      * To work around this limitation, C allows the creation of arrays of pointers to functions.
* Type definitions are sometimes used to simplify complex declarators.
   * ```void (*p)(int);``` for example is functionally equivalent to the following:
   ```c
   typedef void FCT(int);
   FCT *p;
   ```

## :seedling: Initializers

* C allows specifying initial values for variables while they're being declared. This is called "variable initialization".
* Variable initialization is performed by placing the ```=``` symbol after the declarator, followed by an initializer.
   * The ```=``` symbol in this case is not the assignment operator. Initialization and assignment are not the same thing in C.
* An initializer may vary depending on the object being initialized.
   * A simple variable's initializer is an expression with the same type as the variable.
      * If the initializer does not share the variable's type, assignment type conversion rules are applied to convert the initializer's type.
   * A pointer variable's initializer is either a pointer expression with the same type as the pointer variable being declared, or ```void *```.
   * An array, a structure or a union initializer is usually a set of comma-separated values enclosed in braces.
      * C99's designated initializers offer a slightly different form of brace-enclosed initializers.
* The following are some lesser-known rules related to initializers in C.
   * The initializer for a variable with static storage duration must be a constant expression, otherwise the program would not even compile.
   * The initializer for a variable with automatic storage duration doesn't have to be a constant expression and can be a variable or a function parameter.
   * A brace-enclosed initializer for an array, structure, or union must only contain constant expressions. C99 alleviates this restriction by allowing brace-enclosed initializers to contain variables with automatic storage duration.
   * An automatic structure or union can be initialized using another structure or union.
   ```c
   void dummy_function(struct dummy_struct struct1) {
      struct dummy_struct struct2 = struct1;
   }
   ```
* The initial value of an uninitialized variable depends on its storage duration.
   * If the variable has automatic storage duration, its initial value is unpredictable and may even change every time it comes into existence.
   * If the variable has static storage duration, it's by default initialized to zero.
      * This initialization is type-aware. In other words, a variable with type ```int``` is initialized to ```0```, a variable with type ```float``` is initialized to ```0.0```, a pointer variable is initialized to ```NULL``` and so on.
      * This is in contrast to a function like ```calloc``` which simply sets memory bits to ```0```.

## :zap: Inline Functions

* C99 offers a new category of declaration specifiers that's unique to function declarations.
   * This category includes a single keyword: ```inline```.
* Calling a function in C is not as straightforward as it seems once we look under the hood. At the machine level, several tasks need to be performed for a function to be called.
   * Several instructions might need to be executed in preparation for the call.
   * A jump instruction needs to be executed to transfer control to the start of the function.
   * The function's arguments will need to be copied.
   * The function's stack frame needs to be created.
   * Returning from a function requires executing several other instructions on behalf of the calling function and the one being called.
   * These tasks are collectively referred to as "function call overhead".
* Function overhead can considerably slow a program down especially when a lot of function calls are involved.
* C89’s way of mitigating function call overhead was to use parameterized macros instead of functions.
* C99 offers a different solution: ```inline``` functions.
   * An ```inline``` function is an implementation strategy whereby the compiler can directly replace a function invocation with its body.
   * This avoids the overhead associated with function calls but may cause a slight increase in the size of the compiled program.
   * ```inline``` affects code generation choices, but not linkage or storage.
* The ```inline``` keyword is a suggestion to the compiler to minimize function overhead as much as possible, perhaps by performing an inline expansion when the function is invoked.
   * The compiler is free to honor or ignore this request.

### :small_blue_diamond: Inline Definitions

* Getting a grasp of how the linker handles inline definitions is not as straightforward as it seems. The following points outline the issue C99 designers tried to solve with regard to linking ```inline``` functions:
   * Assuming a function is declared at the outermost level of nesting outside all functions in a program, it will by default have external linkage.
   * If this function is declared ```inline```, then the compiler will be able to expand it inline whenever it's called.
   * Since the function has external linkage, other source files can call it and the compiler will be able to expand those calls inline.
   * Each time it encounters a call of the ```inline``` function, the compiler emits a definition of that function. The idea is to keep that definition in the translation unit where the function was called, if the compiler chooses not to expand it inline.
   * If multiple source files call the ```inline``` function, each of them will have its own copy of the function's definition, which violates one of C's fundamental linkage rules: An externally linked object must have a single definition.
* C programmers have three ways of working around this issue:
   * :small_blue_diamond: Adding ```static``` to the ```inline``` function.
   ```c
   // This definition is in a source file dummy.c
   static inline int dummy_add(int a, int b) {return a + b;}
   ```
   * If the function is defined in a source file, it now has internal linkage thanks to the ```static``` storage class.
   * The function is not visible from other source files. As a result, they can include their own definitions of functions with the same name which may or may not be the identical.
   * At link time, every translation unit will have its own internal copy of the function's definition.
   ```c
   // This definition is in a header file dummy.h
   static inline int dummy_add(int a, int b) {return a + b;}
   ```
   * If the function is defined in a header file, it now has internal linkage as well, thanks to the ```static``` storage class.
   * Every translation unit that includes this header file will have its own internal copy of the function's definition.

   * :small_blue_diamond: Creating one external function definition.
   ```c
   // This goes in a header file dummy.h
   inline int dummy_add(int a, int b) {return a + b;}

   // This goes in a single source file dummy.c
   extern int dummy_add(int a, int b);
   ```
   * This provides a single externally visible definition of the function that the linker can resolve all uninlined calls to.
   * In other words, if the compiler encounters a call to this function in a different source file and chooses not to expand it inline, it will have to resolve that call to this one externally visible definition.

   * :small_blue_diamond: Creating a second identical function definition in a source file.
   ```c
   // This goes in a header file dummy.h
   inline int dummy_add(int a, int b) {return a + b;}

   // This goes in a source file dummy.c
   int dummy_add(int a, int b) {return a + b;}
   ```
   * The second definition has to be external.
   * It must not be ```inline```.
   * The two definitions must be identical.
   * This approach is technically sound but stylistically discouraged because of redundancy and risk of inconsistency.

### :small_blue_diamond: Summary

* The C99 standard states: "If a function is declared with ```inline``` and also with ```extern``` in one translation unit, the definition is an external definition. Otherwise, it’s an inline definition that does not create an external definition."
   * This means an ```inline``` function does not have external linkage unless the ```extern``` storage class is explicitly used.
   * If the ```inline``` function has external linkage by default, its default linkage is overridden.
* C provides three ways of dealing with ```inline``` functions.
   * Using the ```static``` storage class so the function has internal linkage in all translation units that include it.
   * Creating a unique externally visible definition while including the ```inline``` function in multiple source files.
   * Creating a duplicate definition of the ```inline``` function in a separate source file and making sure the two definitions are identical.
* The general rule in C99 can be stated as follows:
   * If all top-level declarations of a function in a file include the keyword ```inline``` but not ```extern```, then the definition of the function in that file is ```inline```.
   * If the function is called anywhere in the program (including the file in which it is defined), an external definition of the function will have to be provided.
   * The two definitions must be consistent.

### :small_blue_diamond: Restrictions On Inline Functions

* C99 enforces some restrictions on ```inline``` functions.
   * An ```inline``` function cannot reference a variable with internal linkage.
   * An ```inline``` function cannot define a modifiable ```static``` variable.
   * An ```inline``` function can define a ```const```, ```static``` variable.

### :small_blue_diamond: Inline Functions With GCC

* GCC supported ```inline``` functions prior to the C99 standard.
* Inlining functions in C99 requires enabling optimization using the ```-O``` compiler flag.
* Older GCC compilers used to support another scheme that allowed sharing an ```inline``` function between multiple source files.
   * The idea is to create a definition of the function in a header file, specifying that the function is both ```inline``` and ```extern```.
   * Include that header file in all source files that need to call the function.
   * Redefine the function in one of the source files without the keywords ```inline``` and ```extern```.
   * This second definition will be used to resolve function invocations if the compiler chooses not to expand the function inline.

## :game_die: Miscellaneous

* C99 treats selection statements and iteration statements, along with their inner statements as entire blocks.
   * This rule was introduced to avoid an undefined behavior trap that might arise as a result of using compound literals within these statements.
   * An ```if``` statement for example has three blocks in C99: The ```if``` clause's statement, the ```else``` clause's statement and the entire ```if``` statement.
* Storage for an automatic variable is allocated when the surrounding block is executed.
   * This rule has one exception: C99's Variable-Length Arrays declared inside blocks.
   * A VLA's size is not yet known when the enclosing block begins to execute.
   * Storage for a VLA declared inside a block is allocated when its declaration is reached.
* When a compiler translates a source file into object code, it keeps track of the different types of linkage associated with each name and stores them in a table in the object code. By the time the linker processes the object code, it will have access to all names along with their linkage.
   * The linker does not see names with no linkage.
* An object having block scope and external linkage at the same time is not very intuitive, so let's take a look at an example:
   * Assuming a variable is declared in a source file, at the outermost level of nesting.
   * This variable will have external linkage by default.
   * Let's assume a function defined in a different source file needs access to that variable.
   * This function can declare that variable with the keyword ```extern```.
   * The result is that the variable declared in the function has block scope and external linkage at the same time.
* C's ```const``` objects not being allowed in contexts that require constant expressions might seem counter-intuitive. The following points explain why this is the case:
   * ```const``` in C is much more appropriately seen as "read-only" rather than "constant".
   * A ```const``` object that's also ```volatile``` cannot be changed by the program, but can still be changed through other mechanisms since it's ```volatile```.
   * If a ```const``` object is declared inside a function and initialized to a value that depends on the function's parameter, the object will effectively have a different value every time the function is called with a different set of arguments.