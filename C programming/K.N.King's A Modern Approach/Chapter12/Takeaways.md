<h1 align="center">💡<strong> Pointers and Arrays</strong></h1>
<p align="center">
  <a href="#abacus-pointer-arithmetic">Pointer Arithmetic</a> •
  <a href="#point_right-using-pointers-for-array-processing">Using Pointers For Array Processing</a> •
  <a href="#name_badge-using-an-array-name-as-a-pointer">Using An Array Name As A Pointer</a> •
  <a href="#point_left-pointers-and-multidimensional-arrays-books">Pointers And Multidimensional Arrays</a> •
  <a href="#point_left-pointers-and-variable-length-arrays-rainbow">Pointers And Variable-Length Arrays</a> •
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

* Pointers and arrays in C are related in more than one way:
   * Pointer arithmetic can be used to process an array.
   * An array's name can be seen as a pointer to the first element in the array. Assuming the array declaration ```int a[5];``` is in effect:
      * ```a``` is equivalent to ```&a[0]```.
      * ```a + 1``` is equivalent to ```&a[1]```.
      * Assuming ```i``` is an integer that satisfies ```0 <= i <= 5```, ```a + i``` is equivalent to ```&a[i]```.
      * ```*a``` is equivalent to ```a[0]```.
      * ```*(a + i)``` is equivalent to ```a[i]```.
   * Array subscripting is just another form of pointer arithmetic.
* Assuming ```a``` is an array of length ```n```, we can use pointer arithmetic to step through the array in the following manner:
```c
for(p = a; p < a + n; p++) {/* Process array element */}
```
* Although an array's name in C behaves like a pointer to its first element, attempting to modify it by making it point elsewhere produces a compile-time error. However, we can still copy it to a different pointer variable and modify that variable.
* Assuming this declaration ```int a[5];``` is in effect:
   * ```a``` itself is not a pointer, it's actually a non-modifiable lvalue whose type is "array of ```5``` integers" (```int[5]```).
   * In many contexts, C will automatically convert ```a``` to a pointer that points to its first element. ```a```'s type becomes ```int *```.
   * In C terminology, when this conversion happens, we say that the array name ```a``` decays to a pointer.
   * An array name will decay to a pointer when:
      * Assigned to a pointer: ```int *p = a;```. ```a``` in this case silently becomes ```&a[0]```.
      * Used in an expression: ```*(a + 2)``` is equivalent to ```a[2]``` because ```a``` decayed.
      * Passed to a function: ```function(a)```. ```a``` decays to a pointer when passed as an argument to ```function```.
      * Anywhere the compiler expects a pointer, an array name will decay.
   * An array name does not decay to a pointer in two major cases:
      * When used with the ```sizeof``` operator. In this case, the array name represents the entire array.
      * When used with the address operator ```&```. ```&a```'s type is ```int (*)[5]```.
* An array name passed as argument to a function will always decay to a pointer. A pointer to the first element of the array is copied into the corresponding parameter.
   * When an array is passed to a function, only a pointer to its first element is copied, not the entire array. This means changes made inside the function affect the original array.
   * If we want to prevent the function from changing the contents of the array, we can add the keyword ```const``` before the array's declaration ```function(const int a[])``` . Any attempt to assign a value to an element of the array will produce an error.
   * Passing a large array to a function does not hurt the system's performance since no copy of the array is made.
   * An array parameter in a function can be declared as a pointer instead. Choosing either one makes no functional difference.
   * A function that expects an array argument can be given a slice of an array.
* It's important to make the distinction between an array decaying to a pointer and a pointer variable.
   * An array name that decayed to a pointer can be used to reference elements in the array. In particular, it can be dereferenced using the indirection ```*``` operator to access elements in the array.
   * A pointer variable cannot be dereferenced without initializing it first.
   * The declaration ```int a[5];``` allocates a block of memory to hold ```5``` integers.
   * The declaration ```int *a;``` allocates just enough space for a pointer variable.
* Just as an array can be used as a pointer, C allows the use of pointers as if they were arrays. In particular, subscripting can be applied to a pointer albeit with some important rules:
   * The pointer must point to a valid block of memory. An element inside an array (up to one past the last element) is usually a safe bet.
   * Assuming ```a``` is an array, ```p``` is a pointer of the same type and this assignment ```p = a;``` is in effect:
      * The subscripting operator ```[]``` in C is just pointer arithmetic in disguise. ```p[i]``` in this case is just shorthand for ```*(p + i)``` (i.e ```*(a + i)```).

## :point_left: Pointers And Multidimensional Arrays :books:

* 2D arrays in C are stored in row-major order.
   * This fact can be used to step through a 2D array using nested ```for``` loops:
   ```c
   for(i = 0; i < NUM_ROWS; i++)
      for(j = 0; j < NUM_COLUMNS; j++)
         /* Process 2D array element */
   ```
   * Using pointer arithmetic instead of array subscripting, we get:
   ```c
   for(p = &a[0][0]; p <= &a[NUM_ROWS - 1][NUM_COLUMNS - 1]; p++)
      /* Process 2D array element */
   ```
   * Treating 2D arrays as one-dimensional works with most compilers and arguably offers a slight increase in efficiency especially with older compilers.
* To process elements in a particular row of a 2D array, we can point to the first element in the row and use pointer arithmetic to access the remaining elements. Assuming ```i``` is an integer and ```a``` is a 2D array of integers:
   * We can declare a pointer variable ```p``` that points to the first element in row ```i```: ```int *p = &a[i][0];```.
   * The previous declaration can be further simplified by writing ```int *p = a[i];```. In fact:
      * Given that ```b[i]``` is just another way of writing ```*(b + i)``` for any one-dimensional array ```b```, ```a[i][0]``` is equivalent to ```*(a[i] + 0)``` since ```a[i]``` is a row in a 2D array and can therefore be seen as a one-dimensional array.
      * ```*(a[i] + 0)``` is equivalent to ```*a[i]```.
      * ```int *p = &a[i][0];``` is therefore equivalent to ```&*a[i]``` which is the same as ```a[i]```.
      * In summary, ```a[i]``` is a pointer to the first element in the row ```i``` of the 2D array ```a```.
      * To step through row ```i``` using a ```for``` loop, we can write:
      ```c
      for(p = a[i]; p < a[i] + NUM_COLUMNS; p++)
         /* Process element from row i */
      ```
* A row or a column from a 2D array is treated exactly as a one-dimensional array. In particular, it can be passed to a function that expects an array.
* Stepping through a column of a 2D array is a little bit more complicated than stepping through a row since arrays are stored in row-major order. Assuming ```i``` is an integer and ```a``` is a 2D array of integers:
   * The trick is to step through the array one row at a time in each loop iteration and access the element in each row corresponding to column ```i```.
   * We can declare a pointer to a "row": ```int (*p)[NUM_COLUMNS];``` and write the loop in this fashion to access all elements of column ```i```:
   ```c
   for(p = &a[0]; p < &a[NUM_ROWS]; p++)
      /* (*p)[i] accesses element from column i */
   ```
   * ```p``` is a pointer to an array so we must declare it as ```int (*p)[NUM_COLUMNS]```. ``` int *p[NUM_COLUMNS]``` would be the declaration of an array of pointers to integers instead.
   * ```p++``` advances to the next row.
   * ```(*p)[i]``` is needed to access the ```i```'th element of a row because the subscripting operator ```[]``` has higher precedence than the indirection operator ```*```. ```*p[i]``` is equivalent to ```*(p[i])``` which is not what we want.
* The name of a 2D array ```a``` is a pointer to the first row ```a[0]```. This is not intuitively clear, but does become so when we remember that C views a 2D array as a one-dimensional array whose elements are one-dimensional arrays.
   * When used as a pointer, the name of a 2D array ```a``` is a pointer of type ```int (*)[NUM_COLUMNS]```.
   * The name of a 2D array ```a``` is not a pointer to ```a[0][0]```.
* We can use the name of a 2D array ```a``` to step through a column of our choice. Assuming the following declaration is in effect ```int (*p)[NUM_COLUMNS];```:
   ```c
   for(p = a; p < a + NUM_ROWS; p++)
      /* (*p)[i] accesses element from column i */
   ```
* We can trick a function that expects a one-dimensional array as an argument into thinking that a 2D array is one-dimensional.
   * We can pass the 2D array by calling ```function(a[0], NUM_ROWS * NUM_COLUMNS)``` where the prototype of ```function``` is ```function(int a[], int n)```.
   * ```function(a, NUM_ROWS * NUM_COLUMNS)``` would not be correct since ```a``` has type ```int (*)[NUM_COLUMNS]```.

## :point_left: Pointers And Variable-Length Arrays :rainbow:

* C99 allows pointers to point to an element of a variable-length array (VLA).
* Assuming ```n``` is an integer variable, and this variable-length array's declaration is in effect ```int a[n];```:
   * We can declare a pointer to an integer and have it point to the first element of ```a```: ```int *p = a;```.
   * ```a``` in this case is a one-dimensional array.
* Assuming ```a``` is a 2D array declared as follows: ```int a[n][m];```, where ```m``` and ```n``` are two integers:
   * We can declare a pointer to a row (one-dimensional array) and have it point to the first row of ```a```: ```int (*p)[m] = a;```
   * The pointer variable ```p```'s type is ```int (*)[m]``` which depends on the variable ```m```. For this reason, ```p``` is said to have a "variably modified type".
   * An initialization such as ```int (*p)[5] = a;``` will pass compilation, but won't make any sense if ```m != 5```. Any subsequent use of ```p``` in this case will cause undefined behavior.
* Pointer arithmetic works with VLAs (both one-dimensional and multidimensional) just as it does with ordinary arrays.
* C99 enforces some restrictions on variably modified types. Most notably, their declaration must occur inside a function body or in a function prototype.

## :game_die: Miscellaneous