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
the same array in order to extract a pointer to an element of the array that sits right in the middle of them: medium = (low + high) / 2;
We are asked to identify what makes this statement illegal in C and try to fix it.

--> So what makes the statement illegal is the fact that we're trying to add 2 pointers. The only forms of pointer arithmetic that C allows are
adding an integer to a pointer, subtracting an integer from a pointer and subtracting a pointer from a pointer. low + medium is none of those.
What we could do however is this: medium = low + (high - low) / 2; This statement will make medium point to the element that sits in the middle
between the ones pointed to by low and high respectively. If an odd number of elements sits in between *low and *high then medium will point
to the element bang in the middle, otherwise it will point to the first element from among the pair of elements in the middle. */

/* Exo3: */

/* We are given a progral fragment where an integer array is being declared and manipulated and asked to determine what will its content be
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

/* We are asked to assume that we have a one-dimensional array and a pointer and that the assignment p = a; is in effect. We are then asked
to identify which from among a group of expressions are illegal due to a type mismatch and which from among the rest have a non zero value:
a) p == a[0]; is illegal. We are comparing a value of type X to a pointer variable of type *X.
b) p == &a[0]; is legal. Since p = a, this means p is now a pointer to the first element of the array a (since the array name is technically
a pointer to its first element). Which means p is equal to &a[0]. Another way to look at this is to remember that &a[i] is equal to a+i.
so &a[0] is equal to a+0 = a ==> since p == a then p == &a[0]. ====> This expression is true.
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

/* We are asked to write a function that takes 3 arguements, a constant integer array, its number of elements and an integer key value. This function
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

/* We are given a function that takes 2 arguments: an integer array and the number of its elements. This function zeroes all elements in the arrays.
We are asked to make as few changes as possible to make the function use pointer arithmetic instead of array subscripting to step through the array:

void store_zeros(int a[], int n)
{
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
