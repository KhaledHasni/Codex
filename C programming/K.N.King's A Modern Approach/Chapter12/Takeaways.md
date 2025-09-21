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

* Pointer arithmetic can be used to process data stored in an array.
* Assuming ```a``` is an array of length ```n``` and ```p``` points to ```a[0]```:
   * We can perform pointer arithmetic on ```p``` by repeatedly incrementing it to step through the entire array.
   * Pointer arithmetic coupled with ```for``` loops is a particularly efficient combination for array processing.
   ```c
   for(p = &a[0]; p < &a[n]; p++) {/* Process array element */}
   ```
   * C allows using ```&a[n]``` to mark the position just past the end of the array.
   * Even though the array is indexed from ```0``` to ```n-1``` (so ```a[n]``` itself doesn't exist), it's perfectly legal to write ```p < &a[n]``` as long as the program doesn't try to dereference ```&a[n]```. This simply represents the position just past the last element of the array.
   * C allows using ```&a[n]``` in this manner anywhere in the code with some guidelines:
      * Trying to dereference ```&a[n]``` is undefined behavior.
      * ```&a[n]``` should be used in pointer comparisons or to compute a distance.
      * Any other attempt to use ```&a[n]``` is undefined behavior.
* C's indirection ```*``` and increment/decrement ```++/--``` operators go hand in hand when processing arrays using pointer arithmetic.
* Since the increment ```++``` operator, both prefix and postfix, has higher precedence compared to the indirection ```*``` operator, and assuming ```p``` is a pointer, we get the following combinations:
   * ```*p++```: Equivalent to ```*(p++)```. Produces ```*p``` then increments ```p``` afterwards.
   * ```(*p)++```: Produces ```*p``` before increment, then increments ```*p```. ```p``` is left unchanged.
   * ```*++p```: Equivalent to ```*(++p)```. Increments ```p``` first then produces ```*p``` after increment.
   * ```++*p```: Increments ```*p``` first then produces ```*p```.
* ```*p++``` is the most common form used when processing arrays with pointer arithmetic.
   ```c
   for(p = &a[0]; p < &a[n]; p++)
      sum += *p++;
   ```
* The decrement operator ```--``` is used in the exact same way as the increment operator ```++``` when combined with the indirection operator ```*```.

## :name_badge: Using An Array Name As A Pointer

## :point_left: Pointers And Multidimensional Arrays :books:

## :game_die: Miscellaneous