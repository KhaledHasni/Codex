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
* To access a structure member, C provides the ```.``` operator, also known as "member selection".
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
      * Two structures declared using the same ```typedef``` name are compatible.
   * C's equality operators can't be used to compare the members of two structures.

## :label: Structure Types

* Declaring individual structure variables can be handy for one-off declarations, but a problem arises as soon as we need to declare multiple variables with the same structure members.
   * The technique discussed in the first section can still be useful if all structure variables need to be declared at the same time in the program.
   * Declaring the different structure variables individually in different places in the program has several issues:
      * It introduces a considerable amount of redundancy.
      * The resulting structure variables are not compatible despite having the same members.
         * Recall that, for two structure variables to be compatible, they need to satisfy one of the following:
            * Declared at the same time in the program.
            * Declared using the same structure tag.
            * Declared using the same ```typedef``` name.
         * They can't be copied using the assignment operator.
      * The resulting program can be hard to maintain, with every change affecting a structure variable declaration needing to be duplicated several times.
      * The resulting structure variables can't be used as function arguments since they don't have a type.
* C provides two ways to name a "class" of structures.
   * Declaring structure tags.
   * Defining a type name using ```typedef```.

### :small_blue_diamond: Declaring A Structure Tag

* A structure tag in C is a name assigned to a "class" of structures that share the same members.
```c
struct var {
  int number;
  char char_array[ARRAY_SIZE];
  int another_number;
};
```
* The previous example declares a structure tag called ```var``` that can be used to declare other structure variables with the same set of members.
* The semicolon ```;``` at the end of the declaration is mandatory and part of the structure tag declaration's syntax.
* A structure tag can be used to declare structure variables individually or in groups.
   * ```struct var var1;``` declares a structure variable called ```var1``` that has three members: ```number```, ```char_array``` and ```another_number```.
   * ```struct var var1, var2;``` declares two structure variables, ```var1``` and ```var2``` that both have the same three members.
   * The ```struct``` keyword cannot be omitted from either declaration since ```var``` is just a structure tag and not a type name.
* A structure tag does not conflict with any other name in the program.
   * In other words, a structure tag can share a name with a variable or any other object in a program.
* A structure tag declaration can simultaneously declare structure variables.
```c
struct var {
  int number;
  char char_array[ARRAY_SIZE];
  int another_number;
} var1, var2;
```
* The previous example combines the declaration of two structure variables with the declaration of a structure tag named ```var```. This structure tag can be used later in the program to declare more structure variables of type ```struct var```.
* All structure variables declared using the same structure tag are compatible.

### :small_blue_diamond: Defining A Structure Type

* C allows us to declare a type name for a "class" of structures.
```c
typedef struct {
  int number;
  char char_array[ARRAY_SIZE];
  int another_number;
} var;
```
* In the previous example, ```var``` is a type name for structures that have the same three members discussed previously.
* The type name should appear at the end of the declaration unlike structure tags which appear at the beginning after the ```struct``` keyword.
* Structure types declared in this fashion are used in much the same way as any of C's built-in types.
   * We can declare structure variables using the ```var``` type as follows: ```var var1, var2;```.
   * Unlike a structure tag, ```var``` is a type name and can't be preceded by the keyword ```struct```.
* All structure variables declared using the same structure type are compatible.

### :small_blue_diamond: Structures As Arguments And Return Values

* C allows using structures as arguments and return values when working with functions.
* A structure can be passed as an argument to a function using a structure tag or a structure type depending on how it was declared.
   * Structure tag: ```void dummy_function(struct var var1)```.
   * Structure type: ```void dummy_function(var var1)```.
* Similarly, a structure can be returned from a function using a structure tag or a structure type depending on how it was declared.
   * Structure tag: ```struct var dummy_function(void)```.
   * Structure type: ```var dummy_function(void)```.
* Although it's perfectly legal to pass a structure by value in C, it's usually not a good idea.
   * Passing a structure by value requires copying all members of the structure while creating the function's stack frame.
   * This might not be an issue if the structure is not very sizeable, but it certainly imposes a fair amount of overhead that degrades the program's performance the larger it gets.
   * Returning a structure from a function involves a similar amount of overhead.
   * C programmers usually prefer to use pointers to structures when passing arguments, or returning from functions.
* A structure variable declared inside a function is allowed to be initialized with two important caveats:
   * If the structure variable has static storage duration, its initializer needs to contain constant values.
   * If the structure variable has automatic storage duration, its initializer can be anything, including another compatible structure variable.
* C99 introduces a new feature that's common to both structures and arrays: "Compound literals".
   * A compound literal can be used to create arrays without having to declare them first, usually to be able to pass them as arguments to functions.
   * A compound literal can serve the same purpose when used with structures.
   * A compound literal can also be used to return a structure from a function or to assign one to a structure variable.
   ```c
   // Compound literal using a structure tag
   struct var var1 = (struct var) {5, "dummy_var1", 10};

   // Compound literal using a structure type
   var var2 = (var) {3, "dummy_var2", 6};
   ```
   * Using a compound literal to assign values to the members of a structure variable should not be seen as an initialization. Initializers can only appear in declarations which are distinct from statements in C grammar.
   * Compound literals follow a general formal pattern: A type name enclosed in parentheses followed by a set of values enclosed in braces.
   * When used with structures, compound literals can use designators like in designated initializers.
   ```c
   struct var var1 = (struct var) {.number = 5, .char_array = "dummy_var1", .another_number = 10};
   ```
   * If the compound literal fails to assign a value to any of the structure variable's members, it will be assigned zero by default.

## :nesting_dolls: Nested Arrays And Structures

* C allows nesting arrays in structures, structures in arrays and structures in other structures.

### :small_blue_diamond: Nested Structures

* A structure can be nested inside another structure of a different type.
```c
// Name structure declaration
struct name {
  char first_name[MAX_NAME + 1];
  char last_name[MAX_NAME + 1];
};

// Employee structure declaration
struct employee {
   struct name employee_name;
   int age;
   char gender;
} employee1, employee2;
```
* In the previous example, accessing the ```first_name``` member of the ```name``` member of the ```employee``` structure requires the use of the dot operator ```.``` twice.
* Using nested structures in this manner is a way of treating semantically related information as a data unit.
   * This helps reduce the number of data abstraction layers.
   * This also reduces the number of dot operators ```.``` required to access data.

### :small_blue_diamond: Arrays Of Structures

* Arrays of structures are one of the most common combinations of arrays and structures used in C.
* Accessing a structure stored in an array is done through array subscripting.
* Accessing a member of a structure stored in an array is done through a combination of array subscripting and member selection.
* Assuming the structures stored in the array contain an array themselves, accessing an element in that array requires subscripting, followed by member selection, followed by another subscripting operation.
```c
// var structure declaration
struct var {
   int number;
   char char_array[ARRAY_SIZE];
   int another_number;
};

// declaration of an array of structures
struct var var_array[100];

struct var var1 = var_array[0];      // array subscripting to access the first structure in the array.
int i = var_array[0].number;         // array subscripting + member selection to access the "number" member in the first structure in the array.
char c = var_array[0].char_array[0]; // array subscripting + member selection + array subscripting to access the first character in "char_array"
                                     // as a member of the first structure of the array.
```

### :small_blue_diamond: Initializing An Array Of Structures

* Initializing an array of structures in C is done by simply providing a list of comma-separated, brace-enclosed sets of initial values for each member of each structure element in the array, and wrapping the list in an extra set of braces to provide the array initializer.
* In most cases, an array of structures in C is used as a database or a lookup table containing information that shouldn't be changed.
```c
// person struct declaration
struct person {
   char *name;
   int age;
};

// declaration of an array of structures
const struct person list_of_employees[] = {{"Alice", 21}, {"Bob", 25}, {"Eve", 30}};
```
* In the previous example, the ```name``` structure member was declared as a pointer.
   * This would not have worked had we been planning to use ```person``` structure instances as variables.
   * Since ```person``` structures are only being initialized with constant values, using a pointer is not an issue.
   * When a ```person``` structure is initialized, its ```name``` member points to an immutable string literal.
* The inner braces used to initialize each structure in the array initializer are not mandatory.
* C99's designated initializers can be used to initialize structures within arrays.
```c
struct var var_array[100] = {[0].number = 5, [0].another_number = 6, [0].char_array[0] = '\0'};
```
* C99 allows one item in a designated initializer to have more than one designator.
   * The first item in the previous example has two designators: one to access the first element in the array (the ```0``` subscript), and one to access the ```number``` member in the first structure.
   * The third item in the previous example has three designators: one to access the first element in the array, one to access the ```char_array``` member in the structure, and one to access the first character in that character array.
   * Only the first structure in the array is being initialized in the previous example. The rest of the structures are initialized to zero by default.

## :balance_scale: Unions

* A union is another one of C's built-in data structures, that much like structures, can contain one or more members.
* Unlike a structure, when the compiler encounters a union, it does not allocate space for each of its members.
   * The compiler allocates only enough space for the largest member of the union.
   * All union members will have to share that storage space, and overlay on top of each other as a result.
   * Changing one union member will alter the values of all other members.
   * The members of a structure are all stored at different memory addresses. On the other hand, the members of a union all have the same address in memory.
* Union declarations in C are very similar to structure declarations.
```c
// one-off union variable declaration
union {
  int i;
  double d;
} u0;

// union tag and union variable declaration
union dummy_union{
  int i;
  double d;
} u1;

// union type and union variable declaration
typedef union {
  int i;
  double d;
} u2;
```
* Accessing union members can be done using the same "member selection" operator ```.``` used for accessing structure members.
   * ```u0.i = 2;``` assigns ```2``` to the ```i``` member of the ```u0``` union.
   * ```u0.d = 2.5;``` assigns ```2.5``` to the ```d``` member of the ```u0``` union.
* Assigning a value to a union member immediately alters values stored in all other members. For this reason, a union is a data structure that groups members of potentially different types, only one of which may have a meaningful value stored in memory at any point in a program's lifetime.
* Unions and structures in C share a lot of properties.
   * They can both be declared using tags and types.
   * They can both be passed to functions as arguments.
   * They can both be returned from functions.
   * They can both be copied using the ```=``` operator.
* A union can be initialized at the time of its declaration.
   * A union's initializer has a caveat: Only the first member of the union can be initialized.
   ```c
   union {
     int i;
     double d;
   } u = {0};
   ```
   * The braces enclosing the initializer are required.
   * The initializer must be a constant expression, although this rule is slightly alleviated in C99.
   * C99's designated initializers can be used with unions.
      * A designated initializer allows us to specify which member of the union is to be initialized.
      * Only one union member can be initialized using designated initializers, but it doesn't have to be the first member.
   ```c
   union {
     int i;
     double d;
   } u = {.d = 2.5};
   ```
* C does not enforce any restrictions on the type of a union member. It can be a structure, an array or even another union.
* When a value is assigned to a union member, all other members are undefined.
   * Consequently, it's usually best to avoid accessing data stored in a union through an undefined member.
   * The C standard has one exception to that rule.
      * If two or more members of the union are structures.
      * The structures embedded in the union begin with one or more matching members.
      * Matching members are members that appear in the same order and have compatible types.
      * In this case, if one of the structures is currently valid, its matching members in the other structures are also valid.
* Unions can be used to save space that would otherwise be wasted if structures are used.
* Unions can also be used to create data structures of mixed types.
   * Arrays are a good example of a C data structure whose elements must be of the same type.
   * C programmers sometimes use unions to work around this limitation.
   ```c
   // union type declaration
   typedef union {
     int i;
     double d;
   } entry;

   // mixed type array declaration
   entry dummy_array[100];

   // store values of different types in the array
   dummy_array[0].i = 5;
   dummy_array[1].d = 2.3;
   ```
   * In the previous example, each element of the array is an ```entry``` union that can store either an integer or a double value.
* Unions in C have an inherent shortcoming. Since only one union member can have a meaningful value at a given point in time, there's no easy way to tell which member it is.
   * To work around this problem, C programmers habitually embed their unions in structures that contain an extra "tag field" also known as a "discriminant".
   * This tag field is used to keep track of the union member that currently has a meaningful value.
   ```c
   #define INT 0
   #define DOUBLE 1

   // union embedded in a structure with a tag field
   typedef struct {
     int discriminant; // tag field
     union {
       int i;
       double d;
     } entry;
   } regulated_entry;
   ```
   * Each time a union member is modified, the tag field should also be changed to track the union's meaningful member.
   ```c
   regulated_entry s;

   // entry's i member is assigned a value
   s.entry.i = 5;
   s.discriminant = INT;

   // entry's d member is assigned a value
   s.entry.d = 5.2;
   s.discriminant = DOUBLE;
   ```
   * Retrieving the value stored in a union variable can take advantage of the tag field to determine the union member to access.
   ```c
   // print value stored in union
   if(s.discriminant == INT)
     printf("%d", s.entry.i);
   else
     printf("%g", s.entry.d);
   ```
   * It's important to keep in mind that it's the program's responsibility to update the tag field every time a value is assigned to one of the union's members.

## :1234: Enumerations

## :game_die: Miscellaneous