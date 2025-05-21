/* Takeaways */

/*
1) A variable declared inside the body of a function is said to be local to that function.
2) The storage duration or extent of a variable is the portion of program execution during which storage for the variable exists.
3) Storage for a local variable is automatically allocated when the enclosing function is called and automatically deallocated when the enclosing function returns.
A local variable is therefore said to have automatic storage duration.
4) The previous definition might require a bit more depth: At runtime, when a function call is made, its stack frame (portion of stack where local variables will
be allocated) is created and all declarations made inside that function are already known to the compiler from compile time, even those made halfway down the
function's body. So it's at this exact moment (when the function is called) that space is allocated for all local variables on the stack.
5) A local variable doesn't retain its value when the enclosing function returns (its storage is automatically deallocated). When the function is called again, we
have no guarantee that the variable will still hold its last known value.
6) The scope of a variable is the portion of the program's text where the variable can be referenced.
7) A local variable has block scope which means that it is visible from its point of declaration inside the function until the end of the enclosing function's body.
8) The fact that a local variable's scope doesn't extend beyond the function to which it belongs allows for the same variable name to be used elsewhere for different
purposes.
9) In C99, a variable's scope can be very limited since we're not obligated to declare variables at the beginning of a function.
10) Adding the keyword static in front of the declaration of a local variable causes it to become a static local variable. A static local variable has static storage
duration instead of automatic which means it has a permanent storage location i.e it occupies the same memory location throughout the execution of the program and
therefore will retain its value throughout. Once the enclosing function returns, the static local variable will keep its value.
11) A static local variable still has block scope so it won't be visible by other functions. This makes declaring a static local variable a good way to hide data from
other functions while keeping it for future calls of the same function.
12) The parameters of a function have the same properties as local variables: block scope and automatic storage duration.
13) There's not much to set apart local variables and the parameters of a function. In fact, the only difference is that parameters are automatically initialized
when the function call is made, by being assigned the values of the corresponding arguments.
14) Information can be fed into a function in multiple ways. One way to do that is through arguments that get assigned to the function's parameters when the function
is called. Another way is through external variables.
15) External variables, also known as global variables, are variables declared outside the body of any function.
16) External variables have static storage duration. A value stored in an external variable will stay there indefinitely. They also have file scope, meaning that
an external variable is visible from its point of declaration until the end of the file, which means it can be accessed and modified by all functions that follow
its declaration.
17) Side note: A stack is an abstract concept, a data structure capable of storing data items of the same type exactly like an array. The difference is, the number
of operations that we can perform on a stack is limited: we can either push a data item onto the stack meaning we add an element at one end of the stack called the
stack's top, or we can pop a data item off the stack by removing it from the same end we push to. Examining a data item that's not at the top of the stack is not
allowed.
18) External variables, although tempting to use, come with their fair share of issues and it's usually better to make functions communicate through arguments. The
following 3 points will list some of their problems.
19) If we discover that an external variable has been assigned a wrong value, it might be hard to identify which function is responsible for that assignment since
multiple functions are accessing and potentially modifying it at the same time.
20) A function that relies on external variables is not self-contained and therefore can't be reused elsewhere. If we take it, we'll have to drag along those variables.
21) Any change that might affect an external variable will most likely affect all functions that use it. This will undoubtedly cause a maintenance headache.
22) A common abuse in the use of external variables is using a single external variable in different functions for different purposes. Using a single variable
usually entails that the uses are somehow related, so there's actually no need for an external variable if the uses are not related at all.
23) External variables, unlike local variables, should usually have meaningful names.
24) We know that C allows the use of compound statements of the form { statements }. These compound statements can hold declarations as well {declarations statements}.
These types of compound statements can be called blocks.
25) The storage duration of a variable declared in a block is automatic: storage for it is allocated when the block is entered and deallocated when it's exited. It
can be declared static for it to have static storage duration.
26) A variable declared in a block has block scope: it can't be referenced outside of the block.
27) The body of a function is itself a block.
28) Blocks are useful inside the body of a function especially when we need to declare variables for temporary use. The following 2 points site 2 advantages for this.
29) Using blocks inside the body of a function to declare temp variables avoids cluttering the top of the function with declarations of variables that will only be
used briefly.
30) Using blocks inside the body of a function to declare temp variables reduces name conflict. The same name can be used for other local variables outside the block.
The variable decalred inside the block is strictly local to that block.
31) C99 allows the declaration of a variable anywhere in a block and not necessarily at the top, just as it does for functions.
32) An identifier in a C program may have several different meanings throughout the program. C offers scope rules to determine which meaning is relevant at any given point.
33) The most important scope rule in C is the following: when a declaration inside a block names an identifier that's already visible either because it has file scope
or because it was declared in an enclosing block, the new declaration temporarily hides or shadows the old one, and the identifier takes on a new meaning. Once the
block is exited, the identifier regains its old meaning.
34) Assuming a C program is restricted to a single file (which is usually not the case obviously), th elements that would make it up would roughly be:
preprocessing directives such as #include and #define, declaration of external variables, type definitions, function prototypes and function definitions.
35) C does not impose a lot of rules on the order of these items. The few rules we need to keep in mind are, a preprocessor directive does not take effect until the line
where it appears, a type name can't be used until it's been defined and a variable can't be used until it's been declared. Rules about functions are less rigid, but it's
usually a good idea to declare or define a function before it's first call. This is in fact a requirement for C99.
36) When a function is called recursively, fresh copies of its local automatic variables are made at every call. The same can't be said for its static local variables.
These are shared across calls of the recursive function.
37) If we consider the following example: int i = 1; void f(void) {int j = i; int i = 2;}, the initial value of j would be 1. In fact the second declaration of i doesn't
take effect until after j is declared and initialized. And since the second i is a local variable, it has block scope that starts from where it's been declared. At the
point where j is declared and initialized, only the external i is visible and in scope. Had the second declaration and initialization of i been before that of j inside
the function's body, we would have been able to say that j would be initialized to 2 since the local i would temporarily shadow the external i.
*/

/* Exercises */

/* Exo2: */

/* We are */

/* Exo3: */

/* We are asked how many distinct variables named i can there be in a C program that contains a single function which is the main function.

Well, we can safely assume that this program has a signle file since it has a single function, so the natural thing to do would be to start thinking of the different
types of variables that we can have. External and local would be all. We can't have a parameter named i since this is the main function so it either takes an array
of arguments with their count ot it doesn't take any arguments at all. So the tempting answer then would be 2, we could only have 2 variables named i, an external i
and a local i declared inside main, but that's the wrong answer. The correct answer would be an infinity; we can in theory declare as many variables called i as we
want if we're willing to use nested blocks inside the main function's body. The number of variables that we can declare is only constrained by how deeply and extensively
we nest our blocks, which in practice is only limited by the compiler's limits and readability, and not by C itself. Every block can contain a declaration of a new i
which will shadow the one before it since variables declared in blocks have block scope. */