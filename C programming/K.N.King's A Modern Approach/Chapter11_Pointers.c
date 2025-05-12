#include <stdbool.h>

/* Exercises */

/* Exo1: */

/* If i is a variable and p points to i then: 
(a) *p is an alias for i. This is as straightforward as it gets. As long as p points to i, then applying the indirection operator to p
yields an alias for i.
(b) &p is not an alias for i. &p provides the address of the pointer variable p. In other words, the address in memory of the variable
that stores the address of i.
(c) *&p is not an alias for i. We can break this down in more than one way. &p provides the address of the pointer variable p in memory.
Applying the indirection operator to &p gives us access to the pointer variable p itself. If we want
to be pedantically mathematical (:p) we can think of the indirection and the address operators as 2 operators that will cancel each other
out and leave just p. Either way we get to the same conclusion: *&p is an alias for p not for i.
(d) &*p is not an alias for i. It's an alias for p again. (Same logic as before)
(e) *i is not an alias for i. This use of the indirection operator is particularly dangerous. If i contains a value that corresponds to a
valid memory address at the time of the execution of this statement, we will essentially be trying to access the value stored at that valid
address. What could make this really dangerous is if we try to assign a value to this lvalue (*p).
(f) &i is not an alias for i. This represents the address of i in memory.
(g) *&i is an alias for i. &i provides the address of i in memory which essentially equates to a pointer to i. Applying the indirection
operator to that pointer gives us access to the object the pointer is currently pointing to, which is always going to be i. We can use the
mathematical cancelation trick as well.
(h) &*i is an alias for i. (Same logic as before). */

/* Exo2: */

/* If i is an int variable and p and q are pointers to int then:
(a) p = i; is not a legal assignment. We cannot assign an int variable to an int pointer variable.
(b) *p = &i; is not a legal assignment. First of all, *p is an lvalue so we can assign values to it, that's not the issue. The problem is
*p is expecting an int value since p is an int pointer so *p should in theory be an alias for an int variable. So if we try to assign the
address of an int variable to it, that would be a problem.
(c) &p = q; is not a legal assignment. We're trying to assign a pointer to int to a pointer to a pointer to int.
(d) p = &q; is not a legal assignment. We're trying to assign a pointer to a pointer to int to a pointer to int.
(e) p = *&q; is a legal assignment. *&q is an alias for q which is a pointer to int, same as p. The legality is therefore trivial. 
(f) p = q; is a legal assignment. We're basically asking both p and q to point to the same object of type int, and this perfectly fine.
(g) p = *q; is not a legal assignment. *q is an alias for an int value to which q is currently pointing. Trying to assign that value to a
pointer variable p is illegal.
(h) *p = q; is not a legal assignment. *p is an alias for an int variable to which p is currently pointing. We're trying to assign a pointer
to an int variable which is wrong.
(i) *p = *q; is a legal assignment. Assuming both p and q have been initialized already, they are both pointing to variables of type int.
What we're essentially doing is assigning the value contained in the variable being pointed to by q to the variable being pointed by p.
Once this statement is executed, p and q will be pointing to 2 variables (could be distinct depending on how they were initialized) that contain
the same value. */

/* Exo3: */

/* We are given this function that should in theory compute the sum and average of numbers in a double array and asked to identify and fix
the mistakes it contains: 
void avg_sum(double a[], int n, double *avg, double *sum)
{
    int i;

    sum = 0.0;
    for(i = 0; i < n; i++)
        sum += a[i];
    avg = sum / n;
}

--> So before investigating what's wrong with the function, we can see that the whole logic is not erroneous and there's nothing that stands out
as weird or unexpected. So this can only mean we have syntax issues or bad usage of pointers. The next thing to do is to try compiling this code.
The compilation produces 3 errors:
1) sum = 0.0; is problematic. sum is a pointer parameter and we're trying to assign a double value to it. This is illegal.
2) sum += a[i]; is problematic. sum is again a pointer and we're trying to assign double values to it. This illegal.
3) avg = sum / n; is problematic. sum and avg are pointers and should be treated as such. 
--> To fix this function, we could do the following: */
static void avg_sum(double a[], int n, double *avg, double *sum)
{
    int i;

    *sum = 0.0;
    for(i = 0; i < n; i++)
        *sum += a[i];
    *avg = *sum / n;
}

/* Exo4: */

/* We are asked to write a swap function that exchanges the values of 2 variables i and j when given their addresses as arguments */
void swap(int *p, int *q)
{
    int temp;

    temp = *p;
    *p = *q;
    *q = temp;
}

/* Exo5: */

/* We are asked to write a function that takes a total amount of seconds since midnight as an argument and splits that into hours, minutes
and seconds: */
void split_time(long total_sec, int *hr, int *min, int *sec)
{
    *hr = total_sec / 3600;
    *min = (total_sec % 3600) / 60;
    *sec = (total_sec % 3600) % 60;
}

/* Exo6: */

/* We are asked to write a function that goes through an array of integers and finds the largest and second largest elements in it and returns
them in pointer parameters: */
void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    *largest = a[0];
    *second_largest = a[0] - 1;

    for(int i = 1; i < n; i++) {
        if(a[i] > *largest){
            *second_largest = *largest;
            *largest = a[i];
        } else if(a[i] > *second_largest)
            *second_largest = a[i];
    }
}

/* Exo7: */

/* We are asked to write a function that takes a day_of_year and year arguments and extracts the month and day from that and returns stores them
in pointer parameters: */
void split_date(int day_of_year, int year, int *month, int *day)
{
    if(day_of_year <= 366)
    {
        int days_by_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        bool is_leap = (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
        *month = 1;
        *day = day_of_year;

        while(*day > 31) {
            if(*month == 2 && is_leap)
                *day -= days_by_month[(*month)++ - 1] + 1;
            else
                *day -= days_by_month[(*month)++ - 1];
        }
    }
}

/* Exo8: */

/* We are asked to write a function that takes an array as an argument and returns a pointer to the array's largest element */
int *find_largest(int a[], int n)
{
    int *ptr_to_lgst = &a[0];

    for(int i = 0; i < n; i++) {
        if(a[i] > *ptr_to_lgst)
            ptr_to_lgst = &a[i];
    }

    return ptr_to_lgst;
}

/* Programming projetcs: */

/* Project1: */

/* We are asked to write a function that takes a number of dollars and split that into the smallest number of 20, 10, 5 and 1 dollar bills.
Let's try to do this without referring back to project 7 from Chapter 2 like we're being asked */
void pay_amount(int dollars, int* twenties, int* tens, int* fives, int* ones)
{
    *twenties  = dollars / 20;
    *tens = (dollars % 20) / 10;
    *fives = (dollars % 10) / 5;
    *ones = dollars % 5;
}

/* */