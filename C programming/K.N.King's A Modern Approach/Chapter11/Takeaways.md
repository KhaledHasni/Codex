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

## :link: Pointer Assignment

## :point_right: Pointers As Arguments

## :point_left: Pointers As Return Values

## :game_die: Miscellaneous
