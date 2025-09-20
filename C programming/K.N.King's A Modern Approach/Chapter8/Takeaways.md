<h1 align="center">💡<strong> Arrays</strong></h1>
<p align="center">
  <a href="#straight_ruler-one-dimensional-arrays">One-Dimensional Arrays</a> •
  <a href="#books-multidimensional-arrays">Multidimensional Arrays</a> •
  <a href="#rainbow-variable-length-arrays">Variable-Length Arrays</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :straight_ruler: One-Dimensional Arrays

* An array is a data structure that groups together multiple values of the same type. These values are called the array's "elements".
* Array elements can be accessed using their position in the array.
* The simplest kind of array in C is a one-dimensional array where elements are arranged in adjacent fashion in a single row.
* Declaring an array in C requires specifying:
   * The type of the array's elements.
   * The array's length (number of elements in the array).
   * Declaring an array of ```10``` integers called ```a``` would look like this:
      * ```int a[10];```.
* An array's length can be specified using any integer constant expression.
* Array elements can be of any type.
* Accessing an array element is done through "array subscripting" also known as "array indexing" using the ```[]``` operator. Assuming ```a``` is an array of ```n``` integers:
   * ```a[i]``` accesses the element at index ```i``` in the array ```a``` provided that ```0 <= i < n```.
   * ```a[i]``` is an lvalue.
   * ```a[i]``` is treated just like any other integer variable. In a broader sense, given an array of type ```T```, its individual elements can be used anywhere a variable of type ```T``` is allowed.
* Arrays in C are 0-indexed. Assuming ```a``` is an array of ```10``` elements, they will be designated as ```a[0]```, ```a[1]```, ... , ```a[9]```.
* C's ```for``` loops are usually the go-to iterative statement for stepping through an array. This could be done for multiple reasons:
   * Clearing all array elements by assigning ```0``` to each of them. This can alternatively be done with a ```memset``` call.
   * Reading user input and storing it in the array's different elements using a ```scanf``` call inside the loop.
   * Performing some kind of arithmetic on the array's elements like computing the sum or product of all elements.
* C does not require subscript bound checking. If a subscript goes beyond the array's range, undefined behavior will result. This is usually caused by the notorious "off-by-one" mistake that some beginner C programmers make. A good rule of thumb to avoid this kind of error is to always use idiomatic controlling expressions when writing loops.
* An array subscript can be any integer expression. It can even have side effects.
* C allows initializing an array when it's declared. The most straightforward way of doing this is using a list of constant expressions enclosed in braces and separated by commas.
   * ```int a[5] = {0, 1, 2, 3, 4};``` Initializes ```a``` by assigning ```0``` to ```a[0]```, ```1``` to ```a[1]``` and so on.
   * The list enclosed in braces is called "array initializer".
* If an array initializer is shorter than the length of the array, the remaining uninitialized elements will be assigned ```0```. What this ```0``` looks like depends on the type of the array's elements:
   * Array of integers: The remaining elements will be assigned ```0```.
   * Array of floating-point numbers: The remaining elements will be assigned ```0.0```.
   * Array of characters: The remaining elements will be assigned ```\0```.
   * Array of structures: The remaining elements will be zero-initialized member by member.
   * Array of pointers: The remaining elements will be assigned ```NULL```.
* An array can be initialized to all zeros in the following manner:
   * ```int a[5] = {0};```.
      * An array initializer can't be empty in C.
      * If we provide an initializer with a single value, the rest of the array's elements will be assigned ```0```.
      * If that single value in the initializer is ```0```, the whole array will be initialized to all zeros.
* C does not allow an array initializer to be longer than the array it initializes.
* If an initializer is provided when an array is declared, the length of the array is allowed to be dropped.
   * ```a[] = {0, 1, 2, 3, 4};```.
      * The array initializer's length is used to determine the length of the array.
      * The array will still have a fixed length.
* C99 allows initializing specific elements of an array using "designated initializers".
   * ```int a[10] = {[1] = 5, [6] = 7, [9] = 46};```.
      * In this example, the second element of the array (subscript ```1```) will be initialized to ```5```.
      * The seventh element of the array (subscript ```6```) will be initialized to ```7```.
      * The tenth element of the array (subscript ```10```) will be initialized to ```46```.
      * All other elements of the array will default to ```0```.
   * Each number between brackets is called a "designator```.
   * The order in which elements are listed inside a designated initializer is irrelevant.
      * ```int a[10] = {[9] = 46, [6] = 7, [1] = 5};``` has the same effect as the previous initializer.
   * A designator can be any integer constant expression.
   * When initializing an array of length ```n``` using a designated initializer, each designator must satisfy ```0 <= designator < n```.
   * If the array's length is dropped from the declaration, it will be inferred from the largest designator in the designated initializer.
      * ```int a[] = {[9] = 46, [6] = 7, [1] = 5};```. This array will have ```10``` as length since ```9``` is the largest designator.
   * C allows the use of a hybrid technique to create an array initializer.
      * ```int a[10] = {1, 1, 2, 3, [6] = 87, 5, [9] = 81};```.
         * In this example, the four first elements of the array will be initialized to ```1```, ```1```, ```2``` and ```3``` respectively.
         * The seventh element (subscript ```6```) will be assigned ```87```.
         * The element following the seventh (i.e, the eighth element) will be assigned ```5```.
         * The tenth element (subscript ```9```) will be assigned 81.
         * The remaining elements (fifth, sixth and ninth) will default to zero.
* C allows the use of the ```sizeof``` operator to determine the size of an array in bytes.
* An array's size in C is equal to the size of a single element of the array multiplied by the number of elements in the array.
   * Some C programmers divide the size of an array by the size of one of its elements to determine the number of elements in the array. Assuming ```a``` is an array:
      * ```sizeof(a) / sizeof(a[0])``` is an idiomatic expression that produces the number of elements in the array ```a```.
      * It's important to bear in mind that the ```sizeof``` operator produces a value of type ```size_t``` which is an unsigned type. As a result, the whole expression ```sizeof(a) / sizeof(a[0])``` will produce a value of type ```size_t```. When compared with a signed value, it's best to cast the expression to a signed type to avoid comparing signed and unsigned values.

## :books: Multidimensional Arrays

## :rainbow: Variable-Length Arrays

## :game_die: Miscellaneous