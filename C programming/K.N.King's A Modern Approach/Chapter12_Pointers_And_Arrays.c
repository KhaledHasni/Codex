/* Takeaways */

/*
1) Pointer arithmetic also known as address arithmetic allows easy access to different elements of an array.
2) C supports 3 and only 3 forms of pointer arithmetic: Adding an integer to a pointer, subtracting an integer from a pointer and
subtracting a pointer from another pointer.
3) Adding an integer j to a pointer p pointing to an array element yields a pointer to the array element j places after the one p is pointing to.
In other words, if p is pointing to a[i] then p+j will point to a[i+j] provided that a[i+j] exists.
4) Subtracting an integer j from a pointer p pointing to an array element yields a pointer to the array element j places before the one p is
pointing to. In other words, if p is pointing to a[i] then p-j will point to a[i-j] provided that a[i-j] exists.
5) Subtracting a pointer from another pointer yields the signed distance measured in array elements between the two elements that both pointers are
pointing to. In other words, if p points to a[i] and q points to a[j] then p-q is equal to i-j. The type of the difference is ptrdiff_t defined in
<stddef.h> which is a signed integer type.
6) Performing pointer arithmetic on pointers that don't point to array elements yields undefined behaviors.
7) The effect of subtracting one pointer from another is undefined unless they both point to elements of the same array.
8) C allows using relational (<, <=, >, >=) and equality (==, !=) operators with pointers. Comparing pointers with the relational operators is only
meaningful when both pointers point to elements of the same array. The result depeneds of the relative positions of the elements being pointed to in
the array.
9) A compound literal is a C99 feature that allows us to create an array with no name and saves us the trouble of having to declare an array variable
before being able to use it.
10) C allows a pointer to point to an element of an array created using a compound literal: int *p = (int[]){1,2,3,4,5}; this will make p point to
the first element of the 5-element array containing 1,2,3,4,5 that we just created.
11) In an array of N elements, we can use reaching &a[N] as a terminating condition for a loop iterating through the array. Even though the array
is indexed from 0 to N-1 which means a[N] doesn't exist, C allows doing something like for(int *p = &a[0]; p < &a[N]; p++) as long as the program
doesn't try to dereference &a[N]. This can be seen as just a notation that denotes the indexing pointer reaching the first element past the end of
the array. Note that we can use &a[N] anywhere in the code as long as we don't try to dereference it and as long as it's used in pointer comparisons
or to compute a distance, otherwise it will yield an undefined behavior.
12) We can use pointer arithmetic or subscripting to go through an array. Which is better is highly debatable and depends on a lot of factors.
13) The indirection and the increment operators are often mixed and used together when processing arrays. The ++ operator always has precedence over *.
14) *p++ is equal to *(p++). This expression evaluates to *p before any increment takes place i.e the object that p currently points to. Once the
evaluation is done, p is incremented. This is because we're using the postfix increment operator on p.
15) (*p)++ evaluates to *p before any increment takes place. Once the evaluation is done, *p is incremented i.e p will now point to an object that
contains the value it used to contain + 1.
16) *++p is equal to *(++p). This expression will increment p first then it will evaluate to *p. This is because we're now using the prefix increment
operator.
17) ++*p is equal to ++(*p). This expression will increment *p first then it will evaluate to *p.
18) The name of an array in C is a pointer to the first element in the array. If this declaration is in effect: int array[10]; then *array = 5; will
store 5 in array[0].
19) The fact that an array name is a pointer to the first element can be used to step through the array. If int array[10] is an array then
array+i is equal to &array[i] and *(array+i) is equal to array[i].
20) Using array names as pointers results in a C idiom: for(p = array; p < array + N; p++).
21) Even though the name of an array is technically a pointer to its first element, attempting to make the pointer point elsewhere is an error. It's
a constant pointer in that sense.
22) When an array is passed as an argument to a function, a pointer to the first element in the array is assigned to the corresponding parameter. This
is why we say that an array argument is always treated as a pointer in C.
23) An ordinary variable passed as an argument to a function is protected against change inside the function because C passes that argument by value
and therefore merely a copy of the original value in the variable is supplied to the function. The same can't be said for array arguments though. An
array argument is not protected against change because C is supplying a pointer to the first element in the array to the function i.e it's telling
the function where exactly it can find the array in memory.
24) Since an array is treated as a pointer when passed as an argument, there's no penalty of any kind for passing a large array. Remember that the
array won't be copied when passed as an argument.
25) When passing an array as an argument to a function, the corresponding parameter can be declared as an array or as a pointer. The compiler treats
both declarations as though they were identical.
26) Beware! Even though array parameters are basically the same as pointers, the same can't be said for variables. int a[10] will set aside space
for an array but int *a; will only set aside space for a pointer variable that's not initialized by the way. If we attempt to use the latter as an
array, like *a = 0; for example, we might get informed of how wrong that is the hard way.
27) We can pass an array slice to a function that expects an array argument by providing a pointer to the first element in the slice.
28) C allows us to subscript a pointer as though it were an array. For example: int a[N], *p = a; If these declarations are in effect then p[i] is
equal to *(p+i) which is legal pointer arithmetic.
29) In C, multidimensional arrays are stored in row-major order i.e the elements of the first row are all stored first then the elements of the 2nd
rown and so on until the elements of the last row. So a multidimensional array is basically stored in memory as a one-dimensional array.
30) We can step through a multidimensional array using nested for loops, but we can also use the fact that the array is stored in row-major order
and use a single loop with pointer arithmetic: for(int *ptr = &a[0][0]; ptr <= &a[MAX_ROW-1][MAX_COLUMN-1]; ptr++).
31) The previous technique (treating a multidimensional array as a one-dimensional array) may compromise readability but it used to offer a
compensating execution speed advantage with older compilers.
32) Another technique is to declare a pointer: int *end = &a[0][0] + MAX_ROW * MAX_COLUMN; and use that in the stop condition of the loop:
for(int *p = &a[0][0]; p < end; p++).
33) Unlike one-dimensional arrays where it's legal to use the element right past the last one in the array to compute a distance or to compare
with other pointers, multidimensional arrays do not support this as C does not allow going out of bounds of a subarray. So things like
for(int *p = &a[0][0]; p < &a[MAX_ROW-1][MAX_COLUMN]; p++) are not allowed.
34) Stepping through a row of a 2D array is just like stepping through a 1D array i.e a 2D array is an array of 1D arrays.
35) If the declaration int a[MAX_ROW][MAX_COLUMN]; is in effect, int *p = &a[i][0]; is equivalent to writing int *p = a[i]; This initializes p
to point to the first element in the row i of the 2D array a. Quick demonstration: &a[i][0] == &(*(a[i] + 0)) == &*a[i] == a[i].
36) We can use the previous simplification to write for(int *p = a[i]; p < a[i] + MAX_COLUMN; p++).
37) We can pass a row from a 2D array to a function that expects a one-dimensional array as an argument.
38) Stepping through a column of a 2D array is a little bit more complicated than stepping through a row because arrays are row-major-ordered. The
way we do it is we step through the array one row at a time in each iteration of our loop and go to the element in that row corresponding to the
column we want to extract. So if we have a 2D array int a[MAX_ROW][MAX_COLUMN]; and an integer i and we would like to step through the i'th column
of a, we would declare a pointer to a "row": int (*p)[MAX_COLUMN]; and write the loop in this fashion for example to set all elements of column i to 0:
for(p = &a[0]; p < &a[MAX_ROW]; p++) {(*p)[i] = 0;}.
NOTE: *) p is a pointer to an array so we must write (*p)[MAX_COLUMN]. If we write *p[MAX_COLUMN] that would be an array of pointers.
      *) p++ advances to the next row.
      *) (*p)[i] is needed to access the i'th element of a row because the subscripting operator [] takes precedence over the indirection *.
      If we write *p[i] that would be equivalent to *(p[i]) which is not what we want.
39) The name of a 2D array is a pointer to the first row a[0] so in that sense a is a pointer of type int (*)[MAX_COLUMN]. It is not a pointer to
a[0][0]!
40) We can use the name of a 2D array to step through a column of our choice by writing a for loop in the following fashion: int (*p)[MAX_COLUMN];
for(p = a; p < a + MAX_ROW; p++)
41) We can trick a function that expects a one-dimensional array as an argument into thinking that a 2D array that we pass to it is one-dimensional.
We can pass the 2D array by writing function(a[0], MAX_ROW * MAX_COLUMN); where function's prototype is function(int a[], int n);
42) Recall that a variable length array VLA is a C99 feature that allows the creation of arrays of variable length. An ordinary pointer can be used
to point to an element of a VLA: example: function(int n){int a[n], *p; p = a;}. In the case of a nD array, the pointer type will depend on
all dimensions of the array except the first. Example 2D: function(int m, int n){int a[m][n]; (*p)[n]; p = a;}.
43) In the previous example, p is said to have a variably modified type because it depends on the variable n supplied to the function.
43) Beware! The compiler can't always guarantee the validity of an assignment in the context of VLAs. For example: int a[m][n]; int (*p)[m]; p = a;
This code will compile but won't be correct unless m == n otherwise it will yield undefined behavior.
44) The declaration of variably modified types is linked to certain restrictions, the most important of which are the fact that they can only be
declared inside the body of a function or in the function's prototype.
45) Pointer arithmetic can be used with VLAs. For example: if we want to clear the i'th column of a VLA we would do something like this:
function(int m, int n){int a[m][n]; int (*p)[n]; for(p = a; p < a + m; p++) (*p)[i] = 0;}.
46) Integers used in pointer arithmetic are scaled to the size of the pointer. This means that if p is a pointer to a type whose size is x bytes,
then p+j will add j*x to the address value stored in p. For example, if p is of type int *, p+j will add j*4 to the address in p since integers
are usually stored over 4 bytes.
47) Pointer arithmetic vs array subscripting in array processing is a uselss debate. Neither can be proven to be more advantageous. Learn
both and use whichever is more natural.
48) Suppose that we have int a[N], i = x; with x < N. Funnily enough, i[a] == a[i]. Quick demonstration: i[a] == *(i+a), this is because
the subscripting operator is actually using pointer arithmetic under the hood. And since *(i+a) == *(a+i) because pointer addition is commutative,
and *(a+i) == a[i], we have our result.
49) C allows the use of array names as constant pointers, but that's not the case for array parameter names which can actually be made to point
elsewhere.
50) Array parameters and pointers are interchangeable but that's not the case for array variables and pointers. An array name is not even a pointer,
rather the compiler will convert it to a pointer when necessary. Applying the sizeof operator to both an array and a pointer will showcase the
difference between the two: sizeof(array) yields the size of a single element in the array multiplied by the number of elements it has, while
sizeof(ptr) yields the size necessary to store a pointer variable.
51) Some bounds-checking compilers will not allow us to treat multidimensional arrays as one-dimensional since they will see stepping past the last
element in the first row as illegal (stepping out the bounds of a one-dimensional array).
52) If a is a 2D array, then a and a[0] are both pointers to a[0][0]. The difference is that a is of type int (*)[MAX_COLUMN] and a[0] is of type
int *. This means, even though they both hold the same address, the former is actually pointing to a 1D array while the latter is pointing to an int. 
*/

#include <stdbool.h>

/* Exercises */

/* Exo1: */

/* We are given three declarations:
int a[] = {5, 15, 34, 54, 14, 2, 52, 72};
int *p = &a[1], *q = &a[5];

a) The value of *(p+3) is 14
b) The value if *(q-3) is 34
c) The value of q-p is 4
d) The condition p < q is true
e) The condition *p < *q is false */

/* Exo2: */

/* We are given a statement that appears to be an attempt to perform pointer arithmetic on two pointers low and high that point to elements of
the same array in order to extract a pointer to an element of the array that sits right in the middle of them: medium = (low + high) / 2; with
low, medium and high all pointer variables of the same type. We are asked to identify what makes this statement illegal in C and try to fix it.

--> So what makes the statement illegal is the fact that we're trying to add 2 pointers. The only forms of pointer arithmetic that C allows are
adding an integer to a pointer, subtracting an integer from a pointer and subtracting a pointer from a pointer. low + high is none of those.
What we could do however is this: medium = low + (high - low) / 2; This statement will make medium point to the element that sits in the middle
between the ones pointed to by low and high respectively. If an odd number of elements sits in between *low and *high then medium will point
to the element bang in the middle, otherwise it will point to the first element from among the pair of elements in the middle. */

/* Exo3: */

/* We are given a program fragment where an integer array is being declared and manipulated and asked to determine what will its content be
at the end of the execution: */

/* #define N 10

int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int *p = &a[0], *q = &a[N-1], temp;

while(p < q) {
    temp = *p;
    *p++ = *q;
    *q-- = temp;
}

--> This program goes through the array swapping its symmetrical elements (with regards to the middle of the array) in every iteration. The
swapping is done using a classic method that relies on a temporary storage variable. At the end of this execution, the array will contain
the same elements as before in a reversed order: a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1} */

/* Exo4: Comeback to this after reading chapter 10 */

/* Exo5: */

/* We are asked to assume that we have a one-dimensional array a and a pointer p and that the assignment p = a; is in effect. We are then asked
to identify which from among a group of expressions are illegal due to a type mismatch and which from among the rest have a non zero value:
a) p == a[0]; is illegal. We are comparing a value of type X to a pointer variable of type *X.
b) p == &a[0]; is legal. Since p = a, this means p is now a pointer to the first element of the array a (since the array name is technically
a pointer to its first element). Which means p is equal to &a[0]. Another way to look at this is to remember that &a[i] is equal to a+i.
so &a[0] is equal to a+0 == a ==> since p == a then p == &a[0]. ====> This expression is true.
c) *p == a[0]; is legal. Since p = a is in effect, this means p points to a[0] which also means *p == a[0]. ====> This expression is true.
d) p[0] == a[0]; is legal. We know that p = a. We also know that C allows pointers to be subscripted just like arrays as long as they point
to array elements. This means p[0] is a perfectly fine use of the pointer p and it is an alias for a[0] indeed ====> This expression is true.

/* Exo6: */

/* We are given a function that sums the elements of an array passed as an argument and asked to change the logic being used to step through
the array from subscripting to pointer arithmetic. The goal is to make as few changes as possible:

int sum_array(const int[], int n)
{
    int i, sum;

    sum = 0;
    for(i = 0; i < n, i++)
        sum += a[i];
    return sum;
} */
int sum_array(const int *ptr, int n)
{
    int sum = 0;
    const int *temp_ptr; 

    for(temp_ptr = ptr; temp_ptr < ptr + n; temp_ptr++)
        sum += *temp_ptr;
    return sum;
}

/* Exo7: */

/* We are asked to write a function that takes 3 arguments, a constant integer array, its number of elements and an integer key value. This function
should return true if the key matches one of the elements of the array and it should return false otherwise. The only condition is to use pointer
arithmetic and not array subscripting to step through the array. */
bool search(const int a[], int n, int key)
{
    const int *ptr = a;

    while(ptr < (a + n)) {
        if(*ptr++ == key)
            return true;
    }

    return false;
}

/* Exo8: */

/* We are given a function that takes 2 arguments: an integer array and the number of its elements. This function zeroes all elements in the array.
We are asked to make as few changes as possible to make the function use pointer arithmetic instead of array subscripting to step through the array:

void store_zeros(int a[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        a[i] = 0;
} */
void store_zeros(int a[], int n)
{
    for(int *ptr = a; ptr < a + n; ptr++)
        *ptr = 0;
}

/* Exo9: */

/* We are asked to write a function that takes 2 double arrays as arguments and their common length as a third argument to compute and return their
inner product i.e the sum of the respective products of all their same-ranked element pairs. As usual, we are required to use pointer arithmetic. */
double inner_product(const double *a, const double *b, int n)
{
    const double *ptr_b = b;
    double inner_product = 0;

    for(const double *ptr_a = a; ptr_a < a + n; ptr_a++)
        inner_product += *ptr_a * *ptr_b++;
    
    return inner_product;
}

/* Exo10: */

/* We are asked to alter the function find_middle of section 5 in chapter 11 so that it uses pointer arithmetic to calculate the return value. Just as
a reminder, the function find_middle takes 2 arguments: an array of integers and the number of its elements and returns a pointer to the element that
sits bang in the middle of the array:

int *find_middle(int a[], int n)
{
    return &a[n/2];
} */
int *find_middle(int a[], int n)
{
    int *ptr = a;
    while(ptr != &a[n/2])
    	ptr++;

    return ptr;
}

/* Exo11: */

/* We are asked to modify the find_largest function of section 3 of chapter 12 so that it uses pointer arithmetic instead of array subscripting:
int find_largest(int a[], int n)
{
    int i, max;

    max = a[0];
    for(i = 0; i < n; i++)
        if(a[i] > max)
            max = a[i];
    return max;
} */
int find_largest(int a[], int n)
{
    int max = a[0];

    for(int *ptr = a; ptr < a + n; ptr++)
        if(*ptr > max)
            max = *ptr;
    return max;
}

/* Exo12: */

/* We are asked to write a function that takes an integer array as an argument along with the number of its elements and step through it
using pointer arithmetic and not array subscripting to find the largest and second largest from among its elements and store them in pointer
parameters */
void find_two_largest(const int a[], int n, int *largest, int *second_largest)
{
    *largest = a[0] > a[1] ? a[0] : a[1];
    *second_largest = a[0] > a[1] ? a[1] : a[0];

    for(const int *ptr = a+2; ptr < a + n; ptr++){
        if(*ptr > *largest){
            *second_largest = *largest;
            *largest = *ptr;
        } else if(*ptr > *second_largest)
            *second_largest = *ptr;
    }
}

/* */
