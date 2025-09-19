<h1 align="center">💡<strong> Pointers</strong></h1>
<p align="center">
  <a href="#round_pushpin-pointer-variables">Pointer Variables</a> •
  <a href="#compass-the-address-and-indirection-operators">The Address And Indirection Operators</a> •
  <a href="#link-pointer-assignment">Pointer Assignment</a> •
  <a href="#point_right-pointers-as-arguments">Pointers As Arguments</a> •
  <a href="#point_left-pointers-as-return-values">Pointers As Return Values</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :round_pushpin: Pointer Variables

* In most modern computing devices, main memory is divided into bytes, with each byte capable of holding eight bits of data.
* Each byte in main memory has an address that allows it to be referenced and distinguished from other bytes.
* An executable is essentially composed of two parts:
   * Machine instructions that correspond to statements in the original C code.
   * Data stored in main memory that corresponds to variables in the original C code.
* A variable occupies one or more bytes in memory.
* The first address occupied by a variable is said to be that variable's address.
* An address is essentially a number. However, we cannot use ordinary integer variables to store variable addresses since both ranges may not align.
* A special kind of variable, known as "pointer variable", is instead used to store addresses.
* A pointer is just fancy C talk for "address".
* A pointer variable is just a variable that holds an address.
* If a pointer variable ```p``` holds the address of a variable ```a```, we say that ```p``` points to ```a```.
* An asterisk ```*``` must precede the name of a pointer variable when it's declared.
   * ```int *p;```.
      * In this declaration, ```p``` is a pointer variable capable of pointing to objects of type ```int```.
* A pointer variable doesn't necessarily have to point to a block of memory that holds a variable.
* A pointer variable can be declared alongside other ordinary variables and arrays of the same type.
   * ```int a, array[10], *p;```.
      * ```a``` is an integer variable.
      * ```array``` is an array of integers.
      * ```p``` is a pointer variable capable of pointing to integer variables.
* C requires that a pointer variable point to objects of a single type. This type is called "the referenced type".
* C imposes no restrictions on the referenced type. It can be anything, even another pointer.

## :compass: The Address And Indirection Operators

* C provides two operators designed for use with pointers:
   * The address operator ```&```.
      * Requires an object operand.
      * If ```a``` is a variable, ```&a``` produces the address of ```a``` in memory.
   * The indirection operator ```*```.
      * Requires a pointer variable operand.
      * If ```p``` is a pointer variable, ```*p``` represents the object to which ```p``` is currently pointing.
* Declaring a pointer variable allocates space for a pointer but doesn't make it point to any particular object.
* One way to initialize a pointer variable is to assign it the address of a variable. Assuming ```a``` is an integer variable and ```p``` is a pointer variable capable of pointing to objects of type ```int```:
   * ```p = &a;``` initializes ```p``` by assigning it the address of ```a```.
   * ```int *p = &a;``` combines ```p```'s declaration and initialization.
   * ```int a, *p = &a;``` combines ```a```'s declaration and ```p```'s declaration and initialization. ```a``` must be declared first in this case.
* If ```p``` points to an object ```a```:
   * We can apply the indirection operator to p ```*p``` to access ```a```.
   * ```*p``` is an alias for ```a```. In other words, ```*p``` and ```a``` are two ways of referencing the same data.
   * ```*p``` is an lvalue.
   * Modifying ```*p``` will equally modify ```a```.
* Applying the indirection operator to a pointer variable can be seen as the inverse operation of applying the address operator to the object it points to. Assuming ```p``` is a pointer variable that points to ```a```:
   * ```&a``` creates a pointer to ```a``` while ```*p``` gives us access to ```a```.
   * ```*&a``` is equivalent to ```a```. In fact, ```&a``` creates a pointer to ```a``` and ```*&a``` dereferences that pointer to access ```a```.
* Using the value of an uninitialized pointer variable in any way at all causes undefined behavior. Consequently, we should never, under any circumstances, apply the indirection operator ```*``` to an uninitialized pointer variable.
* Assuming ```p``` is an initialized pointer variable, attempting to assign a value to ```*p``` is particularly dangerous.
   * When ```p``` is declared, it's assigned a random address in memory.
   * As long as ```p``` is uninitialized, it will contain whatever bits were already in that random memory address.
   * Applying the indirection operator to ```p``` will attempt to dereference the pointer variable ```p``` assuming it contains a valid object address.
   * Since ```p``` actually contains garbage data, we don't know whether that data happens to coincidentally match a valid address in memory or not.
   * Attempting to assign a value to ```*p``` will essentially overwrite data in a random memory address that we don't know.
   * If that garbage data matches an address that belongs to the program, the program may crash.
   * If that garbage data matches an address that belongs to the operating system, we can expect our application to behave erratically.

## :link: Pointer Assignment

* C's simple assignment operator ```=``` can be used to copy pointers provided that they have the same type.
* Assuming ```a``` and ```b``` are integer variables and ```p``` and ```q``` are pointer variables capable of pointing to objects of type ```int```:
   * ```p = &a;``` is an example of pointer assignment. This copies the address of ```a``` into ```p```, making ```p``` point to ```a```.
   * ```q = p;``` is an example of pointer assignment. This copies the content of ```p``` into ```q```, making ```p``` and ```q``` point to the same object.
   * Once ```p``` and ```q``` point to the same object, assigning a value to ```*p``` or ```*q``` will change the value of the object pointed to by ```p``` and ```q```, which is ```a``` in this case.
* C allows any number of pointer variables to point to the same object.
* The statement ```*q = *p;``` copies the value pointed to by ```p``` into the object pointed to by ```q```.
   * ```q = p;``` makes both ```p``` and ```q``` point to the same object in memory.
   * ```*q = *p;``` makes both ```p``` and ```q``` point to objects in memory containing the same data.

## :point_right: Pointers As Arguments

* Arguments to functions in C are passed by value. In other words, a variable supplied as an argument to a function is protected against change.
* Pointers can be used if we want a function to permanently change the value of a variable passed as an argument. Assuming ```a``` is a variable whose value we want to change using a function ```f```:
   * If we pass ```a``` as an argument to ```f```, ```a``` will be passed by value. In other words, its content will be copied into the corresponding function parameter. The value of ```a``` will remain unchanged.
   * Suppose we pass a pointer to ```a``` (i.e ```&a```) as an argument to ```f```, and declare the corresponding function parameter to be a pointer ```p```.
   Once the function is invoked, ```p``` will contain ```&a``` and ```*p``` will be an alias for ```a```. Any change to ```*p``` will be mirrored in ```a```.
* ```scanf``` is an example of a C function that expects a pointer argument. Assuming ```a``` is an integer variable:
   * ```scanf("%d", &a);``` reads characters from standard input, attempts to convert them to an integer that it stores in ```a```. The address operator ```&``` applied to ```a``` is mandatory here. ```scanf``` needs to know where to store the integer it reads. Without the ```&``` operator, we would be supplying ```scanf``` with the value of ```a``` instead.
* If a function has a pointer parameter, the address operator ```&``` doesn't necessarily have to precede the name of its corresponding argument. Assuming ```f``` is a function that expects a single pointer argument and ```p``` is a pointer variable:
   * ```f(p);``` is a valid call as long as ```p```'s type matches that of ```f```'s parameter.
* Passing a value to a function that expects a pointer is arguably one of the most dangerous things we can do in C.
   * Once such a function is called, it has no way of knowing whether the value passed as argument is a valid pointer or not.
   * Since it can't verify this, the function will "take our word for it" and use the provided value as though it were a pointer.
   * An attempt to dereference this pointer or change the value it points to is particularly dangerous since we don't know the content of the address we're accessing.
   * C compilers will usually detect a mismatch between the type of the passed argument and the expected parameter based on the function's prototype.
   * ```scanf``` is a particularly dangerous function to use since failing to pass a pointer often goes undetected.
* Passing a pointer argument to a function can be done for reasons other than wanting to change the object the pointer is pointing to inside the function. One such reason is efficiency. In fact, a significant amount of time and space are wasted copying sizable arguments.
* C allows passing a pointer argument while still ensuring the function cannot modify the object it points to. This can be done by adding the keyword ```const``` in the corresponding parameter's declaration.
   * ```f(const int *p)```.
      * In this example, ```f``` is a function that expects a pointer to a constant integer.
      * The parameter ```p``` is a pointer to a constant integer.
      * If a pointer to an integer variable ```a``` is passed to ```f```, ```a``` will be protected against change inside ```f```'s body.
      * Any attempt to modify the value of ```a``` will produce a compilation error.
      * The pointer argument itself can still be changed, however. In other words, it can be made to point to a different object.

## :point_left: Pointers As Return Values

## :game_die: Miscellaneous
