<h1 align="center">💡<strong> Structures Unions And Enumerations</strong></h1>
<p align="center">
  <a href="#package-structure-variables">Structure Variables</a> •
  <a href="#label-structure-types">Structure Types</a> •
  <a href="#nesting_dolls-nested-arrays-and-structures">Nested Arrays And Structures</a> •
  <a href="#balance_scale-unions">Unions</a> •
  <a href="#1234-enumerations">Enumerations</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :package: Structure Variables

* Structures and arrays form the building blocks for data structures in the C programming language.
* An array in C has two inherent properties:
   * All of its elements share the same type.
   * All of its elements can be individually accessed using array subscripting.
* A structure in C has slightly different properties compared to an array:
   * Its elements don't have to share the same type.
   * Every structure element has a name that can be used to access it.
* A structure element is called a "member" in C terminology.
* The idea of structures is not unique to the C programming language. Other languages may provide a similar feature.
* Structures in C are commonly used to store a set of related data items.
   * These items are usually conceptually related and serve a common business logic.
* The following example declares two structure variables called ```var1``` and ```var2```.
```c
struct {
  int number;
  char char_array[ARRAY_SIZE];
  int another_number;
} var1, var2;
```
* In the previous example, ```var1``` and ```var2``` are two variables that contain three members each: an integer called ```number```, a character array called ```char_array``` and a second integer called ```another_number```.
* Structure variable declaration in C is syntactically similar to other declarations.
   * ```struct {int number; char char_array[ARRAY_SIZE]; int another_number;}``` is equivalent to the variable type in any other declaration.
   * ```var1``` and ```var2``` are the variables of that type.
* Structure members are stored in memory in the same order they're declared. This is required by the C standard.
   * The address of the structure variable is the address at which the first member in the structure is stored.
   * Each data type in C has an alignment requirement. This dictates the memory addresses where an item of each data type may be stored.
      * On a 32-bit system:
         * ```char``` requires a ```1```-byte alignment.
         * ```short``` requires a ```2```-byte alignment.
         * ```int``` requires a ```4```-byte alignment.
         * ```double``` requires an ```8```-byte alignment.
      * The address of a structure member must be a multiple of that member's alignment requirement.
      * If a structure member ends at an address that doesn't meet the next member's alignment, the compiler fills the gap with padding bytes.
      * The size of a structure variable is not the sum of the individual sizes of each of its elements.
         * Padding bytes are accounted for when computing the size of a structure.
         * As a result, the size of a structure might depend on the order of its members. In other words, rearranging the members inside a structure might impact its size.
      * Each structure member is stored at an address that’s a multiple of the structure’s maximum alignment requirement.
      * The overall size of a structure is a multiple of its maximum alignment requirement.
         * As a result, if a structure variable contains a member of type ```int``` on a 32-bit system, its overall size will be a multiple of ```4```.
* Each structure in C has its own namespace for member names.
   * Members of two different structure variables that share the same name won't conflict.
* A structure variable can be initialized at the time of its declaration.
   * This is done by providing a value for each of the structure's members and enclosing them in braces.
   * The values in the initializer must be provided in the same order the corresponding members are declared in the structure.
   * A structure initializer adheres to much of the same rules as an array initializer.
      * An initializer must not contain variables of any kind, although this restriction is slightly alleviated in C99.
      * If the initializer contains expressions, these expressions must be constant.
      * An initializer can have fewer values than the number of its corresponding structure's members.
         * The leftover members are initialized to zero by default.
```c
struct {
  int number;
  char char_array[ARRAY_SIZE];
  int another_number;
} var1 = {5, "dummy_var1", 10},
  var2 = {3, "dummy_var2", 6};
```
* Just like with arrays, structures can be initialized using C99's designated initializers.
   * Each value in the initializer is labeled by the name of the corresponding member.
   ```c
   struct {
    int number;
    char char_array[ARRAY_SIZE];
    int another_number;
   } var1 = {.number = 5, .char_array = "dummy_var1", .another_number = 10},
     var2 = {.number = 3, .char_array = "dummy_var2", .another_number = 6};
   ```
   * The dot ```.``` and the following member name are together called a ```designator```.
* Designated initializers provide several advantages compared to traditional initializers.
   * Designated initializers are easier to read.
      * Since every value in the initializer is labeled by the name of the corresponding structure member, it's easy to see what value corresponds to what member without having to remember the order in which the different structure members were declared.
   * The values in a designated initializer don't have to appear in the same order their corresponding members were declared in the structure.
   * A designated initializer is flexible. It does not require all of its values to have a designator.
      * The compiler assumes that a value with no designator corresponds to the "next" member.
      ```c
      struct {
        int number;
        char char_array[ARRAY_SIZE];
        int another_number;
      } var1 = {.number = 5, "dummy_var1", .another_number = 10};
      ```
      * In this example, ```"dummy_var1"``` doesn't have a designator so the compiler assumes it corresponds to the next member after ```number```.
* To access a structure member, C provides the ```.``` operator.
   * ```var1.number``` for example, accesses the ```number``` member of the ```var1``` structure variable.
   * The ```.``` operator has the same precedence as the postfix increment ```++``` and decrement ```--``` operators.
      * Since the postfix increment and decrement operators have one of the highest precedence levels in C, the ```.``` operator takes precedence over almost all other C operators.
   * A structure member is an lvalue.
      * It can appear on the left side of an assignment operator.
      * It can be used as the operand of an increment/decrement operator.
         * ```.``` and postfix ```++/--``` have the same precedence.
         * ```.``` and ```++/--``` are all left-associative.
         * ```var1.number++``` increments the ```number``` member in the ```var1``` structure variable.
      * It can be used as the operand of the indirection operator ```&```.
         * ```&var1.another_number``` provides the address in memory of the ```another_number``` member since ```&``` has lower precedence compared to ```.```.
* A structure variable can be copied using the assignment operator ```=```.
   * ```var1 = var2;``` is a perfectly legal statement in C.
      * It copies the values stored in ```var2```'s members into their corresponding ```var1``` members.
   * Array elements can't be copied using the assignment operator. This is an aspect that is unique to structures in C.
      * An array embedded within a structure is copied when the enclosing structure is copied using the assignment operator.
      * Some C programmers use this quirk to their advantage by wrapping an array declaration in a dummy structure to be able to copy it using the assignment operator later.
   * The assignment operator can only be used with structures of compatible types.
      * Two structures declared simultaneously are compatible.
      * Two structures declared using the same structure tag are compatible (structure tags will be discussed further down).
      * Two structures declared using the same typedef name are compatible.
   * C's equality operators can't be used to compare the members of two structures.

## :label: Structure Types

## :nesting_dolls: Nested Arrays And Structures

## :balance_scale: Unions

## :1234: Enumerations

## :game_die: Miscellaneous