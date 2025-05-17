/* Takeaways */

/*
1) An executable program is basically made up of 2 parts: code which equates to machine instructions that correspond to statements
in the original C code, and data which equates to variables in the original C program.
2) A variable in a program is stored in memory over one or more bytes. The address of the first byte it occupies is the address of the
variable itself.
3) Addresses cannot be stored in ordinary integer variables since their range of values isn't necessarily compatible with that of
integer variables --> we store them in pointer variables.
4) A pointer is C's fancy way of saying an address and pointer variables are variables capable of storing addresses.
5) A pointer variable can only point to objects of a particular type only. This type is called the referenced type. C enforces no
restrictions on what the referenced type may be. We can even make a pointer point to another pointer.
6) Declaring a pointer variable sets aside space for it in memory but doesn't make it point to anywhere in particular. It's absolutely
crucial that we initialize a pointer before using it, and one way of doing that for example is to assign it the address of some lvalue.
7) As long as p points to i, *p is an alias for i. *p and i will have the same value and changing the value of *p will change that of i.
8) *p is an lvalue, so assigning values to it is perfectly legal.
9) It's absolutely crucial that we never apply the indirection operator to an uninitialized pointer variable no matter what we're trying
to do. It's particularly dangerous if we do that to assign a value like in this case for instance: int *p; *p = 5;
10) Using the assignment operator with pointer variables is legal in C as long as both ends of the equal sign have the same type. For
example, if int i, *q; is in effect then int *p = &i and int *p = q are both legal examples of pointer assignment. In contrast, *q = *p
is not a pointer assignment, it merely copies the value of the object that p points to into the object that q points to.
11) Any number of different pointer variables can point to the same object.
12) Since C passes arguments to functions by value, a variable supplied to a function as an argument is protected against change. So what
if we want a function to be able to change the value of one of its arguments? Pointers offer a solution to this by passing the address
of a variable to the function (The address will be passed by value). If we declare the corresponding parameter to be a pointer p, *p
will be an alias for the object that the argument pointer points to.
13) Failing to pass a pointer to a function that expects one can have very bad consequences. The function itself will have no way
of telling that the value that's been copied into its pointer parameter isn't an actual address, and it will attempt to consume that value as
if it were an address.
14) scanf is a notoriously error-prone function because failing to pass a pointer to it will usually go undetected by the compiler.
15) Sometimes, we might pass a pointer as an argument to a function without having the intention of changing the value of the object it
points to inside the function. The reason for using a pointer in this case might be efficiency: passing a variable that requires a large
amount of storage by value will eat up a lot of time and space.
16) We can prevent a function from changing the value of an object that a pointer argument is pointing to by adding the const keyword
to the corresponding parameter's declaration: void function(const int *ptr)
17) A function can return a pointer variable. We usually return either: a pointer to an external variable, a pointer to a static local
variable or a pointer that's been passed to the function as an argument.
18) We should never return a pointer to an automatic local variable. Such a variable will cease to exist once the function returns so
a pointer to it will become invalid.
19) A pointer can point to an array element: int Array[10]; int *p = &Array[5];
20) A common source of confusion for beginners: the asterisk symbol * can mean different things depending on where it's used. In declarations
like int *p; it lets the compiler know that p is a pointer variable. In a statement like *p = 5; however, it serves as the indirection
operator. It is a unary operator that dereferences a pointer variable and gives access to the object it's pointing to.
21) We can print a pointer or a variable's address by using printf with the %p conversion specification.
22) If a pointer is passed to a function as an argument, changing the pointer inside the function won't have any effect on the original
pointer since the pointer is passed by value i.e a copy of the actual address is stored into the pointer parameter.
23) We can protect a pointer parameter against change inside a function by adding const in front of the pointer name in the declaration of the
parameter: void function(int * const ptr). However, since ptr only contains a copy of the original pointer i.e the argument, there's rarely
any reason to protect the pointer parameters against change since changing it will actually not affect the argument at all.
24) We can protect both the object a pointer points to and the pointer itself against change when passed to a function by adding const
before and after the pointer's type in the declaration: void function(const int * const ptr). This is very seldom done in C.
25) A pointer usually is a synonym of an address but that's not always the case. That's usually the case if addresses on the specific platform
we're using are unique identifiers for the smallest unit of memory that can hold the value of a variable. For example, in most modern computers,
all variables will occupy at least one byte in memory, meaning that if our memory is byte-addressed, an address and a pointer will be synonyms
in this case. A counter example to this would be a platform that is word-addressed with a word capable for example of holding 36 or 60 bits.
If a variable requires 6 bits only to be stored, we will need to know the address of the word it's stored in and how many bits off the start of
the word it's located which is called the offset within the word. In this case, the pointer becomes an address + offset and not just an address.
*/

#include <stdbool.h>

/* Exercises */

/* Exo1: */

/* If i is a variable and p points to i then: 
(a) *p is an alias for i. This is as straightforward as it gets. As long as p points to i, then applying the indirection operator to p
yields an alias for i.
(b) &p is not an alias for i. &p provides the address of the pointer variable p. In other words, the address in memory of the variable
that stores the address of i.
(c) *&p is not an alias for i. We can break this down in more than one way. &p provides the address of the pointer variable p in memory.
Applying the indirection operator to &p gives us access to the pointer variable p itself. If we want to be pedantically mathematical (:p)
we can think of the indirection and the address operators as 2 operators that will cancel each other out and leave just p. Either way we
get to the same conclusion: *&p is an alias for p not for i.
(d) &*p is not an alias for i. It's not an alias for p either. If we want to get really serious about our pointers here, &*p is an expression
that will evaluate to the value stored in p but it does not represent the object p itself, therefore it's not an alias for it. One more way
of looking at it is that & produces an rvalue while p is an lvalue. so &*p is an rvalue and therefore can't be an alias for an lvalue.
(e) *i is not an alias for i. This use of the indirection operator is particularly dangerous. If i contains a value that corresponds to a
valid memory address at the time of the execution of this statement, we will essentially be trying to access the value stored at that valid
address. What could make this really dangerous is if we try to assign a value to this lvalue (*p).
(f) &i is not an alias for i. This represents the address of i in memory.
(g) *&i is an alias for i. &i provides the address of i in memory which essentially equates to a pointer to i. Applying the indirection
operator to that pointer gives us access to the object the pointer is currently pointing to, which is always going to be i. We can use the
mathematical cancellation trick as well.
(h) &*i is not alias for i. This is actually meaningless since i is a variable so applying the indirection operator to it makes no sense. */

/* Exo2: */

/* If i is an int variable and p and q are pointers to int then:
(a) p = i; is not a legal assignment. We cannot assign an int variable to an int pointer variable.
(b) *p = &i; is not a legal assignment. First of all, *p is an lvalue so we can assign values to it, that's not the issue. The problem is
*p is expecting an int value since p is an int pointer so *p should in theory be an alias for an int variable. So if we try to assign the
address of an int variable to it, that would be a problem.
(c) &p = q; is not a legal assignment. We're trying to assign a pointer to int to a pointer to a pointer to int.
(d) p = &q; is not a legal assignment. We're trying to assign a pointer to a pointer to int to a pointer to int.
(e) p = *&q; is a legal assignment. *&q is an alias for q which is a pointer to int, same as p. The legality is therefore trivial.
(f) p = q; is a legal assignment. We're basically asking both p and q to point to the same object of type int, and this is perfectly fine.
(g) p = *q; is not a legal assignment. *q is an alias for an int value to which q is currently pointing. Trying to assign that value to a
pointer variable p is illegal.
(h) *p = q; is not a legal assignment. *p is an alias for an int variable to which p is currently pointing. We're trying to assign a pointer
to an int variable which is wrong.
(i) *p = *q; is a legal assignment. Assuming both p and q have been initialized already, they are both pointing to variables of type int.
What we're essentially doing is assigning the value contained in the variable being pointed to by q to the variable being pointed to by p.
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
    *largest = (a[0] > a[1]) ? a[0] : a[1];
    *second_largest = (a[0] > a[1]) ? a[1] : a[0]; 

    for(int i = 2; i < n; i++) {
        if(a[i] > *largest){
            *second_largest = *largest;
            *largest = a[i];
        } else if(a[i] > *second_largest) //This will consider any duplicates equal to *largest as second largest
            *second_largest = a[i];
    }
}

/* Exo7: */

/* We are asked to write a function that takes a day_of_year and year arguments and extracts the month and day from that and stores them
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

    for(int i = 1; i < n; i++) {
        if(a[i] > *ptr_to_lgst)
            ptr_to_lgst = &a[i];
    }

    return ptr_to_lgst;
}

/* Programming projetcs: */

/* Project1: */

/* We are asked to write a function that takes a number of dollars and splits that into the smallest number of 20, 10, 5 and 1 dollar bills.
Let's try to do this without referring back to project 7 from Chapter 2 like we're being asked */
void pay_amount(int dollars, int* twenties, int* tens, int* fives, int* ones)
{
    *twenties  = dollars / 20;
    *tens = (dollars % 20) / 10;
    *fives = (dollars % 10) / 5;
    *ones = dollars % 5;
}

/* */