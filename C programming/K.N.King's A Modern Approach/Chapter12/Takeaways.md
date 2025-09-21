<h1 align="center">💡<strong> Pointers and Arrays</strong></h1>
<p align="center">
  <a href="#abacus-pointer-arithmetic">Pointer Arithmetic</a> •
  <a href="#point_right-using-pointers-for-array-processing">Using Pointers For Array Processing</a> •
  <a href="#name_badge-using-an-array-name-as-a-pointer">Using An Array Name As A Pointer</a> •
  <a href="#point_left-pointers-and-multidimensional-arrays-books">Pointers And Multidimensional Arrays</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :abacus: Pointer Arithmetic

* Pointer arithmetic, also known as address arithmetic, allows easy access to different elements of an array.
* C supports three forms of pointer arithmetic:
   * Adding an integer to a pointer.
   * Subtracting an integer from a pointer.
   * Subtracting a pointer from another pointer.
* Assuming ```i``` and ```j``` are integers, ```a``` is an array, ```p``` points to ```a[i]``` and ```q``` points to ```a[j]```:
   * ```p + j``` produces a pointer pointing to ```a[i + j]``` provided that it exists.
   * ```p - j``` produces a pointer pointing to ```a[i - j]``` provided that it exists.
   * ```p - q``` produces the distance, in number of array elements, between the two (```i - j```). The type of the result is ```ptrdiff_t``` defined in ```<stddef.h>``` which is a signed integer type.
* C requires that pointer arithmetic be done only on pointers that point to array elements. Trying to perform arithmetic on pointers that don't, produces undefined behavior.
* Performing arithmetic on a NULL pointer is undefined behavior, even though adding zero to it is sometimes supported by compilers.
* Trying to compute the difference between two pointers that don't point to elements of the same array is undefined behavior as well.
* C allows comparing pointers using equality operators ```==``` and ```!=```.
* C allows comparing pointers using relational operators ```<```, ```>```, ```<=``` and ```>=```.
   * Comparing two pointers using relational operators only has meaning if they both point to elements in the same array.
   * Assuming ```a``` is an array, ```i``` and ```j``` are integers and ```p``` and ```q``` are two pointers that point to ```a[i]``` and ```a[j]``` respectively:
      * ```p > q``` produces ```true``` if ```i > j```.
      * ```p >= q``` produces ```true``` if ```i >= j```.
* C99 allows pointers to point to elements within an array created using a compound literal.
   * ```int *p = (int[]){1, 2, 3, 4, 5};```.
      * This example showcases the declaration of a pointer variable ```p``` made to point to the first element of an array created using a compound literal.
      * Compound literals are a feature of C99 that allows the creation of an array with no name.
      * Without a compound literal, we would first need to declare the array, initialize it, declare a pointer variable, and then make it point to the first element of the array.

## :point_right: Using Pointers For Array Processing

## :name_badge: Using An Array Name As A Pointer

## :point_left: Pointers And Multidimensional Arrays :books:

## :game_die: Miscellaneous