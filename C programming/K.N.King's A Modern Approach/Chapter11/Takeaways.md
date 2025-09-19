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

## :point_right: Pointers As Arguments

## :point_left: Pointers As Return Values

## :game_die: Miscellaneous
