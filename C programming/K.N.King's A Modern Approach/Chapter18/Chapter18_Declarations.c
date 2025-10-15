/* Takeaways */

/*
1) Declarations are used to provide information to the compiler about what identifiers mean. So when we write:
    *) int i; --> we're informing the compiler that in the current scope, the name i represents a variable of type int.
    *) float f(float); --> This is a declaration informing the compiler that f is a function that returns a value of type float and has one argument of
type float.
2) A declaration in C has the following format: declaration-specifiers declarators; where declaration-specifiers provide a description of the properties
of the variables or functions being declared while declarators provide their names and sometimes give out additional information about their properties.
3) Declaration-specifiers fall into three categories:
    *) Storage classes: C provides four storage classes, auto, static, extern and register. A declaration may contain at most one storage class, in which
case, it should appear as the very first specifier in the declaration.
    *) Type qualifiers: C89 provides two type qualifiers, const and volatile. C99 provides an extra type qualifier, restrict. A declaration may contain
zero or more type qualifiers.
    *) Type specifiers: These are keywords like void, char, short, int , long, float, double, signed and unsigned. They can be combined as described
in Chapter 7 of this book. The order they appear in doesn't matter so int unsigned long is the same as long unsigned int. Two small caveats to this are:
--> This flexibility in C's grammar is only valid with built-in type specifiers.
--> The combined type specifiers need to make sense together. So things like unsigned float or long float or int float or unsigned char int don't make sense.
Type specifiers also include specifications of structures, unions and enumerations so things like struct point {int x, y;}, struct {int x, y;} and
struct point are all type specifiers. Type specifiers also include type names created using typedef.
4) There's a fourth category of declaration specifiers introduced in C99 which is the function specifier, used only for function declarations and it has
only one specifier: The inline keyword.
5) In declarations, C enforces that type specifiers and type qualifiers come after storage classes. Apart from this, there's no other restriction on their order.
6) Declarators include identifiers (names of simple variables), identifiers followed by [] (array names), identifiers followed by () (function names) and
identifiers preceded by * (pointer variable names). They are separated by commas if multiple declarations are being made in one go, and they may be followed by
initializers.
7) Some examples of how declaration specifiers and declarators are used:
    *) static float x,y,*z; --> This is a declaration that has a storage class (static), a type specifier (float) and three declarators (x,y,*z).
    *) const char month[] = "January"; --> This declaration has a type qualifier (const), a type specifier (char), a declarator (month[]) and an initializer ("January").
    *) extern const unsigned long int a[10]; --> This declaration has a storage class (extern), a type qualifier (const), three type specifiers whose order doesn't
matter (unsigned long int) and a declarator (a[10]).
    *) extern int square(int); --> This is a function declaration which has a storage class (extern), a type specifier (int) and a declarator (square(int)).
8) Function declarations, like variable declarations may have a storage class, type qualifiers, type specifiers and a declarator.
9) Storage classes can be specified for variables and to a lesser extent for functions and parameters of functions.
10) Reminder: A block refers to the body of a function or the part enclosed in braces {} and can also refer to a compound statement that can potentially contain
declarations. C99 also considers selection statements (if and switch) and iteration statements (for, do and while) and the inner statements they control as blocks.
11) Every variable in a C program has three properties:
    *) Storage duration: Determines when memory is set aside for that variable and when that memory is released for reuse by the program. For example, storage for
a variable with automatic storage duration is allocated when the surrounding block is executed and it's released when the surrounding block terminates, therefore
releasing that allocated memory causing the variable to lose its value. On the other hand, a variable with static storage duration retains its allocated memory
(storage location) as long as the program is running, allowing it therefore to retain its value indefinitely.
    *) Scope: This is the portion of the program text where the variable can be referenced. A variable can either have block scope whereby it's visible within
the enclosing block (from its point of declaration to the end of the enclosing block) or file scope whereby it's visible within the enclosing file (from its point
of declaration to the end of the enclosing file).
    *) Linkage: Determines the extent to which a variable can be shared by different parts of the program. For example, a variable with external linkage can be
shared by several or all files of a program. On the other hand, a variable with internal linkage is restricted to a single file but can be shared by functions in
that file, therefore allowing other files in the program to use the same variable name for entirely different purposes. A variable with no linkage belongs to a
function and cannot be shared whatsoever.
12) C will assign, unless instructed otherwise, default storage durations, scopes and linkages to variables depending on why they are declared:
    *) Variables declared inside a block including a function body have automatic storage duration, block scope and no linkage.
    *) Variables declared outside all blocks at the outermost level of a program have static storage duration, file scope and external linkage. So for example:
Suppose we have the following snippet:
int i;
void f(void)
{
    int j;
}
--> i has static storage duration, file scope and external linkage while j has automatic storage duration, block scope and no linkage.
13) For a lot of C variables, the default storage duration, scope and linkage are good enough. If they aren't however, we can alter them by explicitly specifying
a storage class: auto, static, extern and register.
14) The auto storage class in only legal for variables that belong to a block. An auto variable has automatic storage duration, block scope and no linkage. The auto
storage class is almost never specified in a C program since it's only legal for variables declared in a block, and for such variables, auto is the default storage
class anyway.
15) The static storage class can be used with variables no matter where they're declared, in a block or outside a block. That being said, it's effect on a variable
greatly differs depending on whether that variable is declared inside or outside a block:
    *) When used outside a block, static specifies that a variable has internal linkage.
    *) When used inside a block, static changes a variable's storage duration from automatic to static. So for example:
Suppose we have the following snippet:
static int i;
void f(void)
{
    static int j;
}
--> i has static storage duration, file scope and internal linkage while j has static storage duration, block scope and no linkage.
16) When static is used outside any block, it essentially hides the declared variable within the current file where it's being declared so that it's only visible to
functions in the same file. So for example:
Suppose we have the following snippet:
static int i;
void f1(void)
{
    //This function has access to i
}
void f2(void)
{
    //This function has access to i
}
--> Both functions f1 and f2 have access to the variable i but functions in other files don't. This is a way to implement a technique called "information hiding".
17) When static is used within a block, it essentially allows the associated variable to retain its storage location throughout program execution therefore retaining
its value indefinitely, unlike automatic variables that lose their value when the program leaves the enclosing block.
18) Properties of static variables:
    *) A static variable in a block is initialized only once before program execution, unlike an auto variable which is initialized every time it comes into existence.
(provided that it has an initializer).
    *) A function that gets called recursively will get a new set of its auto variables. Its static variables on the other hand will be shared across all calls.
    *) A function should never return a pointer to an auto variable, but it can return a pointer to a static variable.
19) By declaring one of its variables to be static, a function will essentially be able to use it to retain information between calls in a place that's not accessible
to the rest of the program (not accessible to the rest of the file since the variable still has block scope and neither to other source files since it has no linkage).
In practice however, programmers will usually declare static variables within a block to improve the program's efficiency. So for example:
char digit_to_hex_char(int digit)
{
    const char hex_chars[16] = "0123456789ABCDEF";
    return hex_chars[digit];
}
--> A new hex_chars array will be allocated and the characters 0123456789ABCDEF will be copied into it to initialize it every time the function digit_to_hex_char is
called. By making the hex_chars array static, we can make digit_to_hex_char much faster and much more efficient since static variables (and arrays) only get
initialized once.
20) The extern storage class enables several source files to share the same variable.
21) The declaration extern int i; merely informs the compiler that i is an int variable but it doesn't allocate memory for i yet. In C terminology, we say that
this is not a definition of i. This is only a way to let the compiler know that we need access to such a variable that's defined elsewhere (later in the same file
or in some other file). The only way the declaration of an extern variable can serve as a definition is a declaration that comes with an initializer. Example:
extern int i = 10;
--> For other storage classes, the declaration of a variable is already a definition even without an initializer. The only exception to this rule is the extern storage
class which does not reserve any storage unless there's an initializer. In layman's terms, an extern declaration with no initializer promises the compiler that there
will be a definition of that variable somewhere else, and that it shouldn't do anything about it until it finds that definition.
--> This rule prevents multiple extern declarations from defining the same variable in multiple ways.
22) The declaration extern int i = 10; is effectively the same as int i = 10; assuming this declaration is being made outside of all blocks since i will by default
have external linkage and therefore extern becomes redundant. In practice, we rarely write extern int i = 10; we just write int i = 10; in one file and declare
extern int i; in any other file that needs i.
23) VERY IMPORTANT POINT: A variable can have many declarations in a program but it can only have one definition.
24) A variable in an extern declaration always has static storage duration no matter where it's declared. Its scope depends on whether or not it's declared inside a
block. So for example:
extern int i;
void f(void)
{
    extern int j;
}
--> i has static storage duration and file scope while j has static storage duration and block scope.
25) If a declared extern variable was declared as static earlier in the same file outside of any block then it will inherit its internal linkage, otherwise it will
have external linkage.
26) Using the register storage class in the declaration of a variable asks the compiler to keep it in a register rather than in main memory like other variables.
This however is only a request made to the compiler and not a command. The compiler is free to store that variable in main memory if it wants. Note that a register
is a small storage area in a device's CPU that can be accessed faster than main memory.
27) The register storage class is only legal for variables declared in a block. It has the same storage duration, scope and linkage of a variable with auto storage
class, the only difference between the two is the fact that a variable with register storage class can't be used with the address & operator since registers don't
have an address. This restriction applies to register variables even if the compiler has elected to store such variables in main memory.
28) The register storage class is best used with variables that are accessed or updated frequently. For example: A for loop's control variable:
int sum_array(int a[], int n)
{
    register int i;
    int sum = 0;

    for(i = 0; i < n; i++)
        sum += a[i];
    return sum;
}
29) The register storage class is not as popular as it once was partly due to the fact that compilers have become much more sophisticated and many of them know
what variables will benefit from being stored in registers rather than in main memory without the programmer having to specify that themselves. That being said,
using this storage class can help the compiler optimize the performance of a program. A classic example of this is the fact that the compiler will immediately
know, upon finding the declaration of a register-class variable, that it can't be modified through a pointer since it doesn't have an address. This relates to C99's
restrict keyword.
30) Function declarations and definitions may also include a storage class that can only be static or extern. A function declaration with an extern storage class
has external linkage meaning it can be called from other files. A function declaration with a static storage class has internal linkage meaning it can only be
called from within the file where it's defined (an indirect call to such a function can still be made from another file through a function pointer). The function is
assumed to have external linkage if no storage class is specified.
31) Declaring a function to be extern is like declaring a variable to be auto, it serves no purpose since the default storage class of a function is extern.
32) Declaring a function that's not intended to be called from other files as static is useful and has several advantages:
    *) Since a static function is guaranteed not to be visible by other files, someone reading/modifying the program later knows that changes made to said function
won't affect functions defined in other files. One exception to this is when a function defined in a different file is passed a pointer to a static function defined
elsewhere. Luckily, this case is not that tricky to spot since the function that passed the pointer must be defined in the same file as the static function.
    *) Reducing name space pollution by allowing the same name of a function declared to be static to be reused in different files for different purposes since it
has internal linkage. An excessive number of names declared in different files, each with external linkage conflicting with each other is what C programmers call
"name space pollution".
33) Function parameters have the same properties as auto variables: automatic storage duration, block scope and no linkage. The only storage class that can be
specified to parameters is register.
34) Consider this code snippet that outlines all the ways in which storage classes can be used in variables and parameters:
int a;
extern int b;
static int c;
void f(int d, register int e)
{
    auto int g;
    int h;
    static int i;
    extern int j;
    register int k;
}
-->     Name    |       Storage Duration       |    Scope   |   Linkage     |
         a      |            static            |    file    |    external   |
         b      |            static            |    file    |       ?       |
         c      |            static            |    file    |    internal   |
         d      |           automatic          |    block   |   no linkage  |
         e      |           automatic          |    block   |   no linkage  |
         g      |           automatic          |    block   |   no linkage  |
         h      |           automatic          |    block   |   no linkage  |
         i      |            static            |    block   |   no linkage  |
         j      |            static            |    block   |       ?       |
         k      |           automatic          |    block   |   no linkage  |
Note that b and j's definitions are not shown here so we can't be sure of their linkages. In most cases they will both be defined in different files and will have
external linkage.
35) Static and extern are the two most significant storage classes. Auto has no effect and register has become less impactful when used with modern compilers.
36) C provides two type qualifiers const and volatile. C99 offers a third type qualifier, restrict, used only with pointers.
37) Const is used to declare objects that resemble variables but are read-only meaning that the program may access their values but cannot change them. For example:
    *) The declaration const int n = 10; creates a const object named n of type int whose value is 10.
    *) The declaration const int Fibonacci[10] = {1,1,2,3,5,8,13,21,34,55}; creates a const array named Fibonacci.
38) Declaring an object to be const has several advantages:
    *) It's a form of documentation that alerts anyone who reads the program to the read-only nature of the declared object.
    *) It provides a defense mechanism against unwanted changes by taking advantage of the compiler making sure read-only objects aren't inadvertently changed.
    *) For C programs written for certain applications like embedded systems, the compiler uses read-only objects to identify data to be stored in ROM (Read-Only memory).
39) It might seem like const and the #define directive play similar roles since the latter is also used to create names for constants, but there are differences between
the two:
    *) #define can be used to create a name for a numerical, character or string constant. On the other hand, const can be used to create read-only objects of all types
including arrays, structures, unions and pointers.
    *) Const objects abide by the same scope rules as ordinary variables. Constants created using #define on the other hand don't. For example, we can't create a
constant with block scope using #define.
    *) The value of a const object can be viewed in a debugger, unlike the value of a macro.
    *) Const objects can't be used in constant expressions unlike macros. For example:
const int n = 10;
int a[n]; //Wrong, can't do this in C
--> Note that the previous example is legal in C99 if the array a has automatic storage duration in which case it would be treated as a variable length array. That's
not the case if it has static storage duration though.
    *) A const object has an address and therefore can be used with the address & operator. A macro on the other hand doesn't.
40) There are no rules that outline when to use const objects vs macros. It's usually a good idea to use macros to define numerical and character constants. That way,
they can be used wherever constant expressions are needed (array dimensions, switch statements...)
41) A declarator is an identifier, the name of the variable or function being declared, possibly preceded by * or followed by [] or (). Examples:
    *) int i; --> The simplest case where i is an identifier the represents an integer variable.
    *) int *p; --> A declarator that begins with * represents a pointer.
    *) int a[10]; --> A declarator that ends with [] represents an array. IMPORTANT NOTE: The brackets may be left empty in the declaration of an array if it's a
parameter, if it has an initializer or if its storage class is extern. In fact, since the array is defined elsewhere in the latter case, the compiler doesn't need
to know its length when it's declared. Note that only the first set of brackets can be empty in a multidimensional array.
--> C99 provides two additional options for what can go between the brackets in the declaration of an array parameter:
        1- The keyword static followed by an expression specifying the array's minimum length.
        2- The * symbol which can be used in a function prototype to indicate a variable-length array argument.
    *) int abs(int a); void swap(int *a, int *b); --> A declaration that ends with () represents a function. C allows parameter names to be removed in a function
declaration. So the two previous declarations can be rewritten as int abs(int); and void swap(int *, int *); The parentheses can even be left empty: int abs(); and
void swap(); therefore providing no information about the functions' arguments while still specifying the return type. It has to be said though, that this style of
function declaration has largely disappeared since it's largely inferior to the prototype model introduced by C89 which allows the compiler to verify whether an
invoked function actually has the right arguments in terms of number and type.
42) In function declarations, leaving the parentheses empty isn't the same as putting void between them which would indicate that the function takes no arguments.
43) Declarators in C programs often combine these symbols. For example:
    *) int *ap[10]; --> Declares an array named ap of 10 pointers to integers.
    *) float *fp(float); --> Declares a function called fp with a float argument that returns a pointer to a float.
    *) void (*pf)(int); --> Declares a pointer to a function with an int argument and that returns nothing.
44) Sometimes, a declarator will be convoluted and include multiple symbols like *, [] and () used together. Fortunately, we can rely on the following two rules
to understand any declarator:
    *) Always start reading a declarator from the inside out, meaning start by locating the identifier that's being declared and begin deciphering the declarator
from there.
    *) [] and () both take precedence over * unless normal precedence is overridden. This means if * precedes an identifier and [] follows it, it's an array not
a pointer. If it's preceded by * and followed (), it's a function not a pointer. To override this default precedence, we can use parentheses.
45) Applying the rules from point 44 to the declarations from point 43:
    *) int *ap[10]; --> Start by identifying the identifier which is ap here. Since ap is preceded by * but followed by [], we give precedence to [] therefore ap
is an array of pointers.
    *) float *fp(float); --> The identifier here is fp. () Takes precedence over * so fp is a function that returns a pointer.
    *) void (*pf)(int); --> The identifier here is pf. Had *pf not been enclosed in parentheses, pf would have been a function that returns a pointer. So it's
obvious the parentheses were added to override the default precedence and therefore pf here is a pointer to a function that takes int as argument and returns nothing.
    *) int *(*x[10])(void); --> To understand this declarator we have to use the zigzagging technique which states that we start by locating the identifier being
declared, pick a side (left or right) to go in based on precedence then go the other way each time. So in the example, the identifier being declared is x. It's
preceded by * and followed by [] so we go right based on precedence and say that x is an array. Then we go left to determine the nature of the elements in the array.
Since we run into *, we can say that x is an array of pointers. Then we go right again to see what these pointers point to. We run into (void) which means these
pointers point to functions that take no arguments. Finally, we go left again to find out what these functions return, and we run into int *, which means these
functions return pointers to integers. In conclusion, this declarator declares an array of pointers to functions that each take no arguments and return a pointer
to an integer. This array is called x.
46) Certain things can't be declared in C:
    *) Functions in C can't return arrays --> int f(int)[]; is illegal.
    *) Functions in C can't return functions --> int f(int)(int); is illegal.
    *) Arrays of functions are illegal in C --> int a[10](int); is illegal.
--> We can however use pointers for each of the previous cases: Functions can return pointers to arrays and pointers to functions, and an array of pointers to functions
is perfectly legal.
47) Some programmers use type definitions to simplify complex declarations. In our previous example int *(*x[10])(void); we can use these definitions:
typedef int *Fcn(void);
typedef Fcn *Fcn_Ptr;
typedef Fcn_Ptr Fcn_Ptr_Array[10];
Fcn_Ptr_Array x;
--> If we read these definitions in reverse, we get: x is an object of type Fcn_Ptr_Array, Fcn_Ptr_Array is a 10-element array of Fcn_Ptr values, Fcn_Ptr is a pointer
to type Fcn, and Fcn is a function that takes no arguments and returns a pointer to an integer value.
48) C allows us to specify initial values for variables as we declare them by adding the = symbol after their declarators, and follow those with initializers. We
shouldn't confuse the = symbol in a declaration with the assignment operator. Initialization and assignment are not the same.
49) The initializer for a simple variable is an expression of the same type of the variable. Example: int i = 5 / 2; --> i is initially 2.
If the types don't match, C will convert the initializer using the same rules used for assignment. Example: int j = 5.5; --> will be converted to 5.
50) The initializer for a pointer variable must be a pointer expression of the same type as the variable or of type void*.
51) The initializer for an array, structure or union is usually a series of values enclosed in braces. Example: int a[5] = {1,2,3,4,5};
Note that brace-enclosed initializers can have other forms in C99 thanks to designated initializers.
52) A variable with static storage duration must have a constant initializer. Example:
#define FIRST 1
#define LAST 100

static int i = LAST - FIRST + 1;
--> Since FIRST and LAST are macros, the compiler already knows their values by the time it starts translating this code into machine code. Had they been variables,
this code would be illegal.
53) If a variable has automatic storage duration, its initializer doesn't have to be constant. Example:
void f(int n)
{
    int i = n;
}
54) A brace-enclosed initializer for an array, a structure or a union must contain constant expression, never variables or function calls. Example:
#define N 2
int powers[5] = {1, N, N*N, N*N*N, N*N*N*N};
--> Since N is constant, powers' initializer is legal. It wouldn't have been if N were a variable and the program wouldn't have compiled. Note that this restriction
only applies in C99 if the variable has static storage duration.
55) The initializer for an automatic structure or union can be another structure or union. Example:
void f(struct part part1)
{
    struct part part2 = part1;
}
56) The initializer doesn't have to be a variable or parameter name, but it doesn't need to be an expression that carries the proper type. Example: In the previous
example, part2 could be initialized using *p where p is of type struct part *, or f(?) where f is a function that returns a part structure.
57) Although it might be tempting to think that uninitialized variables have undefined values. That's not always true since a variable's initial value depends on its
storage duration:
    *) Variables with automatic storage duration have no default initial value meaning their initial value is unpredictable and may be different each time the variable
comes into existence.
    *) Variables with static storage duration have the value 0 by default. They are correctly initialized based on their type. static int variables will contain the
value 0, static float variables will contain the value 0.0 and static pointer variables will contain a NULL pointer (in contrast to memory allocated using calloc for
example which simply sets the whole block of memory to 0 bits).
58) It's always a good idea to provide an initializer for a static variable rather than rely on the fact that its default initial value will be 0. In fact, someone
reading the program who stumbles upon a statement accessing such a variable that hasn't yet been initialized won't be able to tell whether its value is assumed to be
0 or if it has already been initialized by an assignment elsewhere in the program, especially if it has external linkage.
59) C99 offers an additional option that may be part of function declarations: the inline keyword, which happens to be a new breed of declaration specifiers distinct
from storage classes, type specifiers and type qualifiers. Understanding the effect of this keyword has to go through understanding the machine instructions that
are generated by the C compiler to handle the process of calling and returning from a function. At the machine level, this process involves:
    *) Several instructions that need to be executed in preparation for the call.
    *) The function call itself will require jumping to the first instruction in the function.
    *) Sometimes, additional instructions will be executed by the function itself when it begins to execute.
    *) Copying the function's arguments since C passes arguments by values.
    *) Returning from the function requires a similar amount of effort from the function being called and the one calling it.
--> The cumulative work required to call a function and then return from it is called "overhead" which implies the meaning of doing extra work beyond what the function
is required to accomplish. This might not slow the program by a considerable amount but it adds up especially when an older, slower processor is used, when the function
gets called a lot of times or when the program is required to meet very strict deadlines such as real-time systems.
60) The only way to avoid the overhead mentioned in the previous point in C89 is to use parameterized macros, which have a lot of drawbacks. C99 offers a better
solution to this by using inline functions which basically allows the compiler to replace each call of the function by the machine instructions for that function. This
avoids the overhead of regular function calls but might slightly increase the size of the compiled program.
61) Declaring a function to be inline doesn't force the compiler to inline it, it's only a suggestion that the compiler should try to make calls to that function as
fast as possible perhaps by performing an inline expansion whenever the function is called. This suggestion could very well be ignored by the compiler, just like
the register and restrict keywords, which could be used to improve the performance of the program or could be ignored.
62) An inline function has the keyword inline as one of its declaration specifiers. Example:
inline double average(double a, double b)
{
    return (a + b) / 2;
}
--> average has external linkage so other files may contain calls of average. However, the definition of average isn't considered to be an external definition by the
compiler, it's an inline definition instead, which means attempting to call average from another file will yield an error.
63) There are two solutions to the error mentioned in the previous point:
    *) Giving the function internal linkage by adding the word static in front of it that way it can't be called by other files anymore. These other files can contain
their own definitions of the "average" function which may or may not be identical to this one.
    *) Provide an external definition for the "average" function so that calls from other files are permitted. One way of doing this is writing a second definition
of the average function without the inline keyword in a second source file --> This solves the problem but it introduces a huge mess and isn't the best idea since
we will end up having to change both functions together whenever one is changed.
64) The best idea to solve the problem discussed in the two previous points is to write the inline definition of the average function in a header file:
inline double average(double a, double b)
{
    return (a + b) / 2;
}
and create a matching source file wherein we declare it with external linkage:
extern double average(double a, double b);
--> A file that needs to call "average" will have to just include the previous header file which contains its inline definition, while the matching source file
contains an extern prototype of average which causes the definition of average included from the header to be treated as an external definition in the matching source
file.
65) A general rule in C99 is this: if all top-level declarations of a function in a file include the keyword "inline" but not "extern", then the definition of that
function in that file is inline. If the function is used anywhere in the program including the file that contains its inline definition, then an external definition
of the function has to be provided by some other file. When the function is called, the compiler will choose to either perform an ordinary call using the function's
external definition or perform inline expansion using the function's inline definition. There's no way to predict which choice the compiler will make so it's crucial
that both definitions be consistent. Point 64 ensures these definitions are the same.
66) Inline functions are subject to different restrictions compared to ordinary functions. In particular, variables with static storage duration are a problem for
inline functions with external linkage, which leads to the following rules being imposed on inline functions with external linkage but not on ones with internal linkage:
    *) The function may not define a modifiable static variable.
    *) The function may not contain references to variables with internal linkage.
    *) The function may define a variable that is both static and const, but each inline definition may create its own copy of the variable.
67) Some compilers, GCC included, supported inline functions prior to the C99 standard and therefore might have rules that slightly deviate from the C99 standard when
using inline functions. For example, the scheme described in point 64 may not work with these compilers.
68) Functions that are both static and inline should work with GCC regardless of the version. It can be used within a single file or placed in a header file and included
into any source file that needs to call it. This strategy is legal in C99.
69) There's another way of sharing an inline function among multiple files that works with older versions of GCC but conflicts with C99. This technique entails putting
a definition of the function in a header file specifying that it's both extern and inline, then including the header file into any source file that includes a call to
the function. A second copy of the definition, without the keywords extern and inline, is placed in one of the source files, which guarantees that if the compiler is
unable to inline the function, it will still have a definition to fall back on.
70) In GCC, functions are inlined only when the -O command-line option is requested.
71) Declarations in C are meant to mimic use. A pointer declarator has the form *p which matches the way the indirection operator * will later be applied to p. An array
declarator has the form a[] which matches the way the array will later be subscripted. A function declarator has the form f(), which matches the syntax of a function call.
Example: If we consider an array a whole elements are pointers to functions, its declarator will have the form (*array[])(void). A call to one of the functions of the
array has the form (*array[n])(). Note that the parentheses, brackets and * are in identical positions.
72) Scope vs Linkage: Scope is for the benefit of the compiler while linkage is for the benefit of the linker:
    *) The compiler will use the scope of an identifier to determine whether or not it's legal to refer to that identifier at any given point in the program.
    *) When the compiler translates a source file into object code, it takes note of which names have external linkage and stores them in a table in the object file. This
way, the linker can have access to names with external linkage, internal linkage and no linkage at all (which are invisible to the linker).
73) It might not be so obvious how a variable can have block scope but external linkage so here's an example: Suppose a file a.c declares a variable int i; outside of all
functions. i therefore will have external linkage by default. Let's assume that a function f defined in another file b.c needs to access i so the body of f will have to
declare i as extern: void f(void){extern int i;....}. In a.c, i has file scope since it's declared outside all functions. In b.c however, i has block scope since it's
declared inside f's body. If another function defined in b.c needs to access i, it will have to declare it in its body as well, or alternatively, we can declare i as extern
in b.c outside of all function bodies. The confusing thing about all of this is the fact that every declaration or definition establishes a different scope, sometimes it's
block scope and other times it's file scope.
74) We've established that storage, for a variable with automatic storage duration, is automatically allocated when the surrounding block is executed. This is not true for
C99's variable-length arrays since the array's length isn't yet known when the surrounding block is executed. The allocation happens instead when the declaration of the
variable-length array is reached during the execution of the block. In this respect, variable-length arrays are different from all other automatic variables.
75) A common misconception in C is that const objects denote objects that hold "constant" values and can therefore be used in constant expressions. This is not true as
const in C means "read-only" and not "constant". In fact, the value of a const object might only be constant during its lifetime and not for the whole execution duration
of the program. Example: Suppose we have a function f inside of which we declare a const int variable m: void f(int n){const int m = n / 2;...}. When f is called, m will
be initialized to n/2 and that value will then remain constant until the function returns. Next time f is called, depending on the argument it will take, m will likely be
initialized to a different value. Now suppose that the rest of the function's body contains a switch statement like this:
void f(int n)
{
    const int m = n / 2;

    switch(//something) {
        case m:
            //do something
            break;
        case default:
            //do something else
            break;
    }
}
--> Since the value of m won't be known until f is called, this is a violation of one of C's rules that states that the values of case labels in a switch statement must be
constant expressions.
76) Another reason why a const object can't be used in constant expressions can be inferred from this example: Suppose we declare a const object in a file outside all
functions. Such an object will have external linkage and can be shared between files. Here's a possible situation we will find ourselves in:
extern const int n;
int a[n]; //WRONG!!!
--> Although n is declared here, it's more than likely defined in another file, which makes it impossible for the compiler to determine the array a's length, assuming of
course that a is an external array so it can't be a variable-length array.
77) Another stonewall reason that proves const objects don't hold constant values per se, is the case of const volatile objects which is discussed in the C standard itself.
Consider the case of a variable called real_time_clock declared as follows: extern const volatile int real_time_clock; This variable cannot be changed by the program since
it's const but it still can be changed through some other mechanism since it's volatile.
78) In C99, selection and iteration statements and their respective inner statements are considered blocks, despite how counter-intuitive that may seem. This is due to a
known problem involving the storage duration of compound literals when compound they're used in selection and iteration statements. In fact, the C99 standard states that
an object represented by a compound literal has static storage duration if the compound literal occurs outside the body of a function, otherwise it has automatic storage
duration. If it's the latter, the memory occupied by the object will be deallocated at the end of the block in which the compound literal appears. So let's consider this
function which returns a structure called point created using a compound literal:
struct point create_point(int x, int y)
{
    return (struct point) {x, y};
}
--> This function will work just fine because the object created by the compound literal will be copied when the function returns. The original object will no longer exist
but the copy will remain. Now suppose we tweak the function to make it return a pointer to a structure instead:
struct point *create_point(int x, int y)
{
    return &(struct point) {x, y};
}
--> This function suffers from an undefined behavior because it returns the address of an object that has automatic storage duration and will therefore not exist by the time
the function has returned.
--> Here's where the problem comes in: Consider the following example that will explain why selection and iteration statements are considered blocks in C99:
double *coefficients, value;
if(polynomial_selected == 1)
    coefficients = (double[3]){1.5, -3.0, 6.0};
else
    coefficients = (double[3]){4.5, 1.0, -3.5};
value = evaluate_polynomial(coefficients);
--> This fragment should behave in the expected manner: coefficients will point to one of two objects created by compound literals, and that object will still exist by the
time evaluate_polynomial is called. Now consider what happens when we add braces to if's inner statements:
double *coefficients, value;
if(polynomial_selected == 1) {
    coefficients = (double[3]){1.5, -3.0, 6.0};
} else {
    coefficients = (double[3]){4.5, 1.0, -3.5};
}
value = evaluate_polynomial(coefficients);
--> Each compound literal causes an object to be created, but that object will have automatic storage duration and will therefore only exist within the block delimited by the
braces. By the time evaluate_polynomial is called, coefficients points to an object that no longer exists which results in undefined behavior.
--------> Foreseeing that adding braces to the inner statements could unexpectedly cause undefined behavior is likely going to confuse a lot of C programmers, the creators
of C99 decided to just consider inner statements of selection and iteration statements as blocks whether they're enclosed in braces or not. This means both our
examples are equivalent in C99, and both will produce undefined behaviors.
79) A similar problem to the one described in point 78 can arise when a compound literal is used in the controlling expression of an iteration or selection statement.
Consequently, each entire selection/iteration statement is considered to be a whole block as though an invisible set of braces surrounds the entire statement. So for example,
an if statement with an else clause consists of three blocks: the two inner statements of if and else, and the entire if statement as well.
*/