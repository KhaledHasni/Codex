/* Takeaways */

/*
1) The preprocessor is controlled by preprocessing directives which are commands that begin with the # character in a C program. #define and #include are 2 examples.
2) The #define directive defines what is called a macro: a name that represents something else like a constant or a frequently used expression. When the preprocessor
encounters a #define directive, it responds by storing the macro name along with its definition. When the macro is later used in the program, the preprocessor replaces
it by its defined value. This replacing act is called expanding a macro.
3) The #include directive tells the preprocessor to open a particular file and include its contents as part of the file currently being compiled.
4) The preprocessor's role in the compilation process: Original C program --> Preprocessor --> Modified C program --> Compiler --> Object code.
5) The input to the preprocessor is a C program that might contain directives. The preprocessor executes those directives and removes them from the program in the
process. It then produces an edited version of the original C program that does not contain any directives and feeds it into the compiler which checks it for errors
and translates it to object code (machine instructions).
6) When editing the original C program to produce its output, the preprocessor doesn't remove lines containing directives, it instead makes them empty. It also
replaces comments with a single space character and sometimes even goes further to remove unnecessary white-space characters at the beginning of indented lines including
spaces and tabs.
7) Back in the early days of C, the preprocessor used to be a separate program that would work its magic then feed its output into the compiler. But nowadays, the
preprocessor is often part of the compiler and some of its output may not necessarily be C code. An example of that would be the #include directive in modern day
integrated preprocessors that might not literally copy the contents of the included header file into the current source file, it might nowadays be a case of just
making the functions whose prototypes for example are declared in the included header file available for the current source file in some way or another.
8) Most compilers with integrated preprocessors offer a way to view the output of the preprocessor. Some of them will even generate the preprocessor output when a certain
option is specified (for example GCC will do that when the -E option is used). Other compilers come with a separate program that behaves like a preprocessor. Each
compiler implementation will have its way of handling the preprocessor's role in the compilation process so it's best to check the compiler's documentation for more
information.
9) Beware! The preprocessor has only a limited knowledge of C so it's capable of creating illegal programs as it executes directives. To make matters worse, these errors
are hard to spot and might require generating the output of the preprocessor separately to be able to identify them.
10) #define directives are said to be "expanded" when the preprocessor executes them, #include directives are said to be "expanded inline", meaning the content of the
included header files is copied right where the original #include directive was in the program, exactly as though we copied and pasted that content in that place, and
conditional directives like #ifdef and #ifndef are said to be "resolved".
11) Most preprocessor directives fall into one of three categories: *) Macro definition: the #define directive defines a macro and the #undef directive removes a macro
definition. *) File inclusion: the #include directive causes the content of a specified file to be included in a program. *) Conditional compilation: The #if, #ifdef,
#ifndef, #elif, #else and #endif directives cause a block of text to be either included in or excluded from a program depending on a condition that can be tested by the
compiler.
12) Directives always begin with the # symbol. The # symbol doesn't necessarily have to be at the beginning of the line as long as it's only preceded by white spaces.
After the # symbol comes the name of the directive followed by any other information required by the directive.
13) It doesn't matter how many spaces and/or horizontal tab characters separate the tokens of a directive. For example this directive is perfectly legal:
#    define     MAX_VALUE                           10
14) Directives always end at the first encounter of a newline character unless explicitly continued through splicing (the use of \ to continue a directive on the next line).
Example: The following directive computes the volume of a cuboid:
#define CUBOID_VOLUME (LENGTH * \
                       WIDTH *  \
                       HEIGHT)
15) Directives can appear anywhere in a program. Although we usually put the #include and #define directives at the beginning of a program, other directives are likely
to show up later, sometimes in the middle of function definitions.
16) Comments may appear on the same line with a directive.
17) The definition of a simple macro or object-like macro as it's called in the C standard has the form: #define identifier replacement_list, with replacement_list being
any sequence of preprocessing tokens.
18) A macro's replacement list may include identifiers (example: #define BOOL_VAR is_true), keywords (example: #define RETURN_KEYWORD return, #define WHILE_KEYWORD while,
#define INTEGER_TYPE int), numeric constants (example: #define MAX_NBR 50, #define PI 3.14159), character constants (example: #define NEWLINE '\n',
#define ESCAPE_CHAR '\x1B'), string literals (example: #define GREETING "Hello, world!"), punctuation (example: #define END_BLOCK }), operators (example: #define ADD +,
#define MULTIPLY *).
19) We must pay close attention not to put any extra symbols in a macro's definition as they'll become part of the replacement list. A common example of this mistake
being made is ending a macro definition with a ; Example: #define N 10; later this macro is expanded to 10; and will more than likely cause the compiler to complain
if used in instances like for example: int array[N] --> gets expanded to int array[10;] --> compiler error. Another common example is using the equal sign in a macro
definition of a constant value. Example #define PI = 3.14159 --> gets expanded to = 3.14159. In both these examples, we have mistakenly defined our macro to be a pair
of tokens instead of just one. A compiler will usually flag the expansions of such erroneous macro definitions but it will fail to identify the real culprit, which,
by the time the compiler makes its complaint, the macro definitions will have been removed from the program by the preprocessor.
20) Simple macros are primarily used for defining "manifest constants" as they're called by the creators of C. Using macros we can give names to numeric, character and
string values.
21) Using #define macros to assign names to constants has several advantages that will be enumerated in the following 3 points.
22) It makes the program easier to read especially when the macro identifier is a meaningful and well-chosen name. Without these macro definitions, our program could
easily end up being full of numbers and symbols that could confuse even the most avid C programmer.
23) It makes the program easier to maintain and modify by changing a single value in the macro's replacement list instead of changing all of its occurrences in the code.
The alternative would be a code full of hardcoded values that are hard to track down especially since they sometimes show up in a slightly altered form. Example:
Stepping through a 0-indexed array of 100 elements will require incrementing an index from 0 to 99, so trying to locate the occurrences of the value 100 in the program
to change won't help us much here.
24) It helps avoid typographical errors.
25) definition macros are not only used to define names for constants. They can serve several other purposes 3 of which are enumerated in the following 3 points.
26) They allow us to create alternate names for C symbols which would visually alter the syntax of C. For example we can use these two macros #define BEGIN { and
#define END } to simulate Pascal's syntax or we can even create new statements like #define LOOP for(;;) which would create an infinite loop. This is usually not a good
idea however, since it would make our C programs very hard to read for others.
27) They allow us to rename types like for example #define BOOL int. This is fairly used by some programmers but type definitions are a better way of doing it.
28) They allow us to control conditional compilation like for example #define DEBUG which would indicate that this program is to be compiled in debugging mode and
consequently would have to produce extra logs or debugging output.
29) A macro's replacement list is allowed to be empty.
30) It's a C custom to capitalize all letters in the names of macros that are used as constants. However, there's no consensus on how to write names of macros used for
other purposes. Some programmers argue that it's best to draw attention to macros by capitalizing their letters since they're high up there on the list of sources of
bugs in C (especially parameterized macros), while others like to stick to the style of Ritchie and Kernighan's the C programming language by keeping them lower-cased.
31) The definition of a parameterized macro or function-like macro has the form: #define identifier(x1, x2, x3,...,xn) replacement_list, where xk are identifiers and
serve as the macro's parameters and can appear as many times as we want in the replacement list.
32) If a space is left between the macro's name and the left parenthesis, the preprocessor will consider this an object-like macro and (x1,x2,x3,...xn) will be seen
as part of its replacement list.
33) When the preprocessor encounters a parameterized macro, it stores its definition for later use. When it finds a macro invocation later in the program in the form
identifier(y1, y2, y3,...yn) where yk are tokens, it replaces it with the replacement list substituting y1 for x1, y2 for x2 and so on.
34) Parameterized macros behave like simple functions. Example: #define TOUPPER(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 'a' + 'A' : (c)). This macro checks if a character
is a lower-case letter and produces its upper-case equivalent otherwise it leaves it as is. <ctype.h> provides a similar function with the same name that's more portable.
Another example: #define IS_EVEN(x) ((x) % 2 == 0). This macro produces 1 if x is even and 0 if it's odd. A third example: MAX(a,b) ((a) > (b) ? (a) : (b)).
35) A parameterized macro may have an empty parameter list. Example: #define getchar() getc(stdin). Here, the empty parameter list isn't really needed but it aesthetically
makes the macro resemble a function. In fact, this is the same getchar from <stdio.h>, which can be implemented both as a macro and a function.
36) Using a parameterized macro instead of a function has a couple of advantages that will be cited in the following 2 points.
37) The program may become slightly faster as function calls usually require some overhead during program execution due to context information being stored and arguments
having to be copied and so on. Macros on the other hand require no runtime overhead at all. This however is undercut by C99's inline functions feature which allows
function calls to avoid overhead completely without the need for macros.
38) Macros are generic in that they can accept parameters of any type as long as the resulting, post-preprocessing program is valid, unlike functions which require
parameters to be typed.
39) However, parameterized macros also have drawbacks that will be enumerated in the following 4 points.
40) They often cause the program to become larger in size. In fact, each macro invocation causes the macro's replacement list to be inserted in its place therefore
increasing the size of the source program and the compiled code. The problem is even more pronounced when macro invocations are nested. For example, using the MAX
macro from earlier to determine the largest number from among 3 arguments like this MAX(i, MAX(j,k)) will be expanded into the following:
((i) > (((j) > (k) ? (j) : (k))) ? (i) : (((j) > (k) ? (j) : (k)))). Look at that mess!
41) They do not perform type checks for arguments. A function will require its arguments to be of specific types and the compiler will check whether that is indeed
the case when a function call is performed. If it's not, the argument's type will either be silently converted to the appropriate type or the compiler will throw a
mismatch error. For macros, that is not the case and arguments are neither type checked nor are they converted.
42) They can't be pointed to unlike functions. Since macros are removed during preprocessing, they won't have any relevance at runtime and therefore we can't use pointers
to point to them.
43) They can evaluate their arguments more than once leading to unexpected behavior especially if the argument has side effects. A function however will evaluate its
arguments only once. Here's an example where this unexpected behavior plays out: n = MAX(i++, j);. This macro will get expanded into n = ((i++) > (j) ? (i++) : (j));
After this expression is evaluated, i will be incremented twice, so if i is initially larger than j, then n will be assigned an incorrect value.
44) Errors due to macro arguments being evaluated more than once are notoriously difficult to find, especially since the macro will work fine for most arguments but
will only fail for arguments with side effects. That's why it's generally a good idea to avoid side effects in arguments altogether.
45) We can use parameterized macros not just for simulating functions but also to avoid having to write redundant patterns of code. Example:
#define PRINT_INT(n) printf("%d\n", n) can be helpful to display an integer on a single line every time it's called.
46) The # and ## operators may be contained in a macro definition. They are not in any way recognized by the compiler and are only used by the preprocessor.
47) The # operator performs what the C standard calls "stringization". It's used in parameterized macros and applies to the macro's arguments and can only show up
in the replacement list. In effect, it converts a macro's argument into a string literal. Example: #define PRINT_INT(n) printf(#n " = %d\n", n). The preprocessor will
create a string literal from PRINT_INT's argument and the fact that the compiler automatically concatenates string literals separated by white spaces will produce out of
an argument i/j what is equivalent to the following statement printf("i/j = %d\n", i/j).
48) The ## operator is called the token-pasting operator. It's used to paste two tokens (for example identifiers) together to form a single token. Example:
#define MK_ID(n) i##n. When invoked as follows int MK_ID(1), MK_ID(2), MK_ID(3); --> after preprocessing this declaration becomes int i1, i2, i3;
49) The ## operator is rarely used but here's a good example of how it can be used. The MAX macro of earlier has one issue: it's arguments mustn't have any side effects.
So suppose we want to mitigate that without having to define a function instead since functions will require a different one for every numeric type (integer, float...).
We can therefore create a macro that expands into a function like this:
#define GENERIC_MAX(type,x,y)     \
type type##_max(type #x, type #y) \
{                                 \
    return x > y ? x : y;         \
}
--> So when this macro is invoked, we'd get something like this: GENERIC_MAX(float, 3.14, 4.86); which will expand to:
float float_max(float x, float y) {return x > y ? x : y;}. This way, we have essentially used the macro to define a function whose name depends on the type of its
arguments. Had we failed to make the function name type-dependant and called it max no matter the type, we wouldn't have been able to invoke GENERIC_MAX twice in the same
file with two distinct type arguments because C doesn't allow defining two distinct functions with the same name in the same file.
50) A macro's (simple or parameterized) replacement list may contain an invocation of another macro. Once an invocation of such a macro is encountered, the preprocessor
will expand it to its replacement list which will still contain another macro's name in this case. It will then rescan the replacement list for macro names and expand those.
It will continue to do so until all macro names are eliminated from the expansion.
51) For a macro to be invoked in the replacement list of another, it doesn't even have to be defined before the calling macro. In fact, macro expansion is handled at a
later stage altogether compared to macro definition so as long as both macros are defined before they get called in the code, their order of definition relative to each
other doesn't matter.
52) A macro invocation can't appear in the replacement list of itself. In other words, recursive macros are disallowed in C and there's a safeguard established to prevent
infinite recursion. Example: #define FOO (FOO+1) will get expanded only once so int i = FOO; will get expanded to int i = FOO+1; which doesn't make any sense.
53) The preprocessor replaces only entire tokens and token portions. This means macro names that are embedded in string literals or identifiers or character constants...
aren't expanded by the preprocessor. Example: if #define SIZE 10 is a macro we have, then int BUFFER_SIZE; and printf("THE SIZE IS %d", i) won't be affected by the
preprocessor.
54) Since macros are handled by the preprocessor, they don't abide by normal scope rules. A macro definition remains in effect from its point of definition until the end
of the file no matter where its definition takes place. For example, a macro defined inside a function isn't local to that function.
55) The same macro can't be defined twice in the same translation unit unless the definitions are identical. Differences in spacing are allowed but definitely not to
tokens in the replacement list and the parameters if any. A translation unit is a .c source file along with all headers included into it and macro expansions. So basically,
a .c file after the preprocessor is done with it.
56) Macros can be undefined using the undef directive which has the form: #undef identifier. If applied to a macro name, it will remove that macro's definition so that it
can for example be given a new definition. If applied to a macro name that wasn't previously defined, it will have no effect.
57) Two rules to keep in mind when deciding where to put parentheses in a macro definition: *) If the replacement list contains an operator, always enclose the whole list
in parentheses. *) If the macro has parameters, enclose each parameter in the replacement list in parentheses. Without these parentheses, we have no guarantee that the
compiler will treat the replacement list and the arguments as whole expressions and might end up applying the rules of operator precedence and associativity in ways we did
not see coming.
58) Missing parentheses in a macro definition will cause some of the most frustrating errors we can see. The code will compile and the macro will usually behave as expected
but will sometimes fail in mysterious ways when provided with the right sneaky arguments.
59) To write more sophisticated macros, we can use the , operator in the replacement list. Example: #define ECHO(s) (gets(s),puts(s)) will read a string from stdin and
print it. gets and puts are expressions so we can use them as operands of the , operator. We can even do #define ECHO(s) {gets(s); puts(s);} to form a compound statement.
60) Using compound statements as macro replacement lists is particularly problematic especially when the macro gets invoked in a conditional clause. Example:
#define ECHO(s) {gets(s); puts(s);} and then we have:
if(is_true)
    ECHO(s);
else
    //do something else
--> The compiler will treat the if clause as a complete if statement. The ; after ECHO(s) will be seen as a null statement and the else clause will be left dangling and will
therefore produce a compilation error. We can work around this by removing the ; after ECHO(s) but that opens the door to a heap of visual irregularities in the program.
61) The previous problem can be solved by the , operator if the macro needs to glue together a series of expressions like gets and puts for example, so no need for compound
statements in that case. But the , operator doesn't solve the issue if a macro wants to glue together a series of statements. The solution in that case is to use a do..while(0)
Example: #define ECHO(s) \
         do              \
         {               \
            gets(s);     \
            puts(s);     \
         } while(0)
--> When called, ECHO must be followed by a ; to complete the do while statement.
62) C offers several predefined macros. They each represent an integer constant or a string literal. Example: __DATE__ and __TIME__ identify when a program was compiled in the
respective formats: "Mmm dd yyyy" (example: Dec 25 2020) and "hh:mm:ss" (example: 22:10:45). Both these replacement lists are string literals. This information can be helpful
in telling apart different versions of the same program compiled at different times.
63) Other examples of predefined macros include __LINE__ and __FILE__ which can help in debugging to locate erros. Example, if we invoke the following macro right before all
instances in our program where a division is taking place, we can get a heads-up as to where exactly (file and line) in the code, the problematic division is happening:
#define DIVIDE_BY_ZERO_WARNING(divisor)                                     \
if(divisor == 0)                                                            \
    printf("Division by zero in file %s at line %s\n", __FILE__, __LINE__)
64) Another example of a predefined macro is __STDC__ which has the value 1 if the compiler conforms to the C standard (C89 and C99). By testing this macro, a program can adjust
to a compiler that predates the C89 standard.
65) A C implementation is the compiler + any other software necessary to execute a C program. C99 makes a distinction between two types of implementations:
    *) Hosted: these are implementations that must accept any C program that conforms to the C99 standard.
    *) Freestanding: these are implementations that don't have to compile programs that use complex types or some standard headers beyond a few of the most basic ones (<stdio.h>
for example doesn't have to supported by a freestanding implementation.)
66) C99 offers additional predefined macros: __STDC__HOSTED__ represents the constant value 1 if the compiler is a hosted implementation and 0 if it's freestanding.
67) Another predefined macro is __STDC__VERSION__ which provides a way to tell which version of the C standard is supported by the compiler. This macro first appeared in the
first Amendment to the C89 standard (also known as C95) and its value was equal to the long integer constant 199409L (since the amendment dates back to September 1994).
A compiler conforming to the C99 standard will see this macro having the value 199901L. Subsequent versions of the C standard and amendments made to them will carry different
values for this macro.
68) Other examples that a C99 compiler may or may not define depending on whether or not certain requirements are met include:
    *) __STDC_IEC_559__: is defined and evaluates to 1 if the compiler performs floating-point arithmetic according to the IEC 60559 standard (IEEE 754 standard).
    *) __STDC_IEC_559_COMPLEX__: is defined and evaluates to 1 if the compiler performs complex arithmetic according to the IEC 60559 standard (IEEE 754 standard).
    *) __STDC_ISO_10646__: is defined as an integer constant of the form yyyymmL if values of type wchar_t are represented by the codes in the ISO/IEC 10646 standard with revisions
as of the specified year and month.
69) C99 allows one or more of the arguments in a macro call to be empty. This must happen while keeping the same number of commas in the macro call as though there has been no
omissions though. When such a macro is expanded, the parameter in the macro's replacement list corresponding to the empty argument will be replaced by nothing. Example:
#define ADD(x, y) (x+y)
int i = ADD(,b); will expand to (after preprocessing) int i = +b;
70) Special rules apply when the empty argument is an operand of the # or ## operators:
--> For example if an empty argument is stringized by the # operator, the result is an empty
string "". Example:
#define MAKE_STR(x) #x
char str[] = MAKE_STR(); will expand to (after preprocessing) char str[] = "";
--> If an empty argument of a macro call is supposed to be the operand of the ## operator, it gets replaced by a "placemarker" token. Concatenating an ordinary token with a
placemarker token yields the original token, with the placemarker being effectively phased out (in other words, the placemarker token is seen as the idle operand of the ## operator).
If two placemarker tokens are concatenated, the result is a single placemarker token. The idea is for placemarker tokens to disappear entirely from the program by the time macro
expansion is done. Example:
#define JOIN(x,y,z) x##y##z
int JOIN(a,b,c), JOIN(a,b,), JOIN(a,,c), JOIN(,,c); will expand to (after preprocessing) int abc, ab, ac, c;
Calling the JOIN macro with empty arguments like this JOIN(,,) is legal as well and will yield an empty result.
71) C89 only allows macros to have a fixed number of arguments, or no arguments at all. C99 on the other hand allows macros to have an unlimited number of arguments to mirror the way
functions have always been in C. The primary reason for adding this feature in C99 is to allow for macros to pass a variable number of arguments to functions that require a variable
number of arguments like printf and scanf. Example:
#define TEST(condition, ...) ((condition) ? printf("Test passed: %s\n", #condition) : printf(__VA_ARGS__))
72) From the previous example: the ... token is called ellipsis. It goes at the end of a macro's parameter list preceded by ordinary parameters if there are any. __VA_ARGS__ is a
special identifier that can only appear in the replacement list of a macro with a variable number of arguments and it represents all the arguments that correspond to the ellipsis.
This means that there must be at least one argument that corresponds to the ellipsis that will be represented by __VA_ARGS__, although that argument can be empty.
73) In the example above, the TEST macro requires at least two arguments when called, one corresponding to the "condition" parameter and the other corresponds to the ellipsis.
74) Example of how the TEST macro might be used:
TEST(voltage <= max_voltage, "Current voltage %d exceeds limit %d\n", voltage, max_voltage); --> After preprocessing, this will expand to the following:
    *) If voltage <= max_voltage: printf("Test passed: %s\n", "voltage <= max_voltage");
    *) If voltage > max_voltage: printf("Current voltage %d exceeds limit %d\n", voltage, max_voltage);
75) Another new C99 feature is the __func__ identifier which behaves exactly like a string variable which stores the name of the currently executing function. Every function has access
to the __func__ identifier. Its as if every function contains a declaration of a string variable called __func__ at the beginning of its body: static const char __func__[] = "name";
where name is the actual name of the function being executed. This allows us to write macros such as these:
#define FUNCTION_CALLED() printf("The function being executed is %s\n", __func__)
#define FUNCTION_RETURNING() printf("The function now returning is %s\n", __func__)
--> Calls of these two macros can be placed at the start and end respectively of all functions in a program to track its call stack. We can also pass __func__ to a function as an argument
so it knows the name of the function that called it.
76) Conditional compilation is the process of including or excluding portions of the program's text depending on the outcome of a test performed by the preprocessor.
77) A classic case where conditional compilation is needed is when debugging a program. We can define a macro and give it a non-zero value. Then we can add printf call in our program and
have them print the values of certain values that we need for debugging. Example:
#define DEBUG 1
#if DEBUG
printf("The value of i: %d\n", i);
printf("The value of j: %d\n", j);
#endif
--> During preprocessing, the value of DEBUG will be tested. Since it's not equal to zero, the preprocessor will leave the printf calls in the program but the #if and #endif lines will
disappear. If we change the value of DEBUG to zero and recompile the program, the preprocessor will remove all four lines from the program. Once removed, the compiler won't even see
the printf calls and they won't occupy any space in the object code, nor will they cost any time when the program is run. It's as if they weren't written at all. We can also leave the
#if and #endif directives in the final program to allow diagnostic information to be produced later by recompiling the program with DEBUG equal to 1 if we need to debug again.
78) The general forms of the #if and #endif directives are the following respectively: #if constant_expression and #endif. When the preprocessor encounters the #if directive in a program,
it evaluates the constant-expression, if its value is equal to zero, it removes the lines of text sandwiched between the #if and #endif directives. Otherwise, those lines will survive
the preprocessing phase to then be processed by the compiler.
79) The #if directive treats undefined identifiers as identifiers that have the value zero. In the above example, if we do not define the DEBUG macro, the #if DEBUG test will fail (as
though DEBUG were equal to zero) and the test #if !DEBUG will succeed.
80) The preprocessor supports three operators: # and ## which we've already seen and the defined operator. The defined operator is applied to an identifier operand and produces 1 if the
identifier is a currently defined macro and produces 0 otherwise. It's usually used with the #if directive. Example:
#if (DEBUG)
//do something
#endif
--> The lines between the #if and #endif directives will be included in the program if DEBUG is defined as a macro. Note that the parentheses around DEBUG are not necessary.
81) The defined operator only tests whether its operand is a defined identifier or not. This means, it's not necessary to give the DEBUG identifier (from the previous example) a value:
#define DEBUG
Even if DEBUG is given a value, the defined operator will still produce 1 when applied to DEBUG, even if that value is zero!
82) The #ifdef directive tests whether an identifier is currently defined as a macro. Its general form is the following:
#ifdef identifier
//lines to be included if identifier is defined as a macro
#endif
83) The defined operator combined with the #if directive has the exact same effect as the #ifdef directive so technically there's no need for the #ifdef directive at all.
84) The #ifndef directive is similar to the #ifdef directive but instead it tests whether an identifier is not defined as a macro. So #ifndef identifier is the same as writing
#if !defined identifier
85) The #if, #ifdef and #ifndef blocks can be nested just like ordinary if statements. Some techniques to make the nesting depth pop out include:
    *) Using indentations inside these conditional blocks with a growing indentation the deeper the nesting goes.
    *) Adding a comment when closing a conditional block with an #endif referencing the condition the matching #if is actually testing (Example: #endif //DEBUG)
86) The #elif and #else directives can be used with #if, #ifdef and #ifndef to test a series of conditions. Their general forms are respectively: #elif constant-expression and #else. Example:
#if expr1
//lines to be included if expr1 is non-zero
#elif expr2
//lines to be included if expr1 is zero and expr2 is non-zero
#elif expr3
//lines to be included if expr1 and expr2 are zero and expr3 is non-zero
#else
//lines to be included if expr1, expr2 and expr3 are zero
#endif
--> The previous example could have used the #ifdef or #ifndef directives instead of #if. Any number of #elif directives but at most one #else directive can show up between #if and #endif.
87) There are several reasons why conditional compilation could be used in a program:
    *) Debugging.
    *) Writing programs that are portable to several machines or operating systems. Example:
#ifdef WIN32
#elif MAC_OS
#elif LINUX
#endif
    --> At the beginning of the program, only one of these identifiers would be defined thereby selecting a particular operating system.
    *) Writing programs that can be compiled with different compilers. In fact, different compilers often recognize slightly different versions of C; some accept a standard version of C while
some don't, some provide machine-specific language extensions while some don't. A common example of this is when we want to write a program that might need to be compiled using an older
non-standard compiler. Using the __STDC__ macro, the preprocessor will be able to tell whether a compiler conforms to the standard, if it doesn't the program can adjust itself for example by
using older style function declarations that predate C89 instead of function prototypes. So at each point in the program where we have to write a function declaration, we would write:
#if __STDC__
//function prototypes
#else
//old-style declarations
#endif
    *) Checking if a macro is currently defined and if not giving it a default definition. Example:
#ifndef STACK_SIZE
#define STACK_SIZE 256
#endif
    *) Temporarily disabling code that contains comments, since we can't nest multi-line comments in C. This kind of disabling of code is called "conditioning out".
    *) Protecting header files against multiple inclusions.
88) The #error directive has the form: #error message where message is any sequence of tokens. If the preprocessor encounters an #error directive, it prints an error message which must include
"message" (i.e the sequence of tokens provided to the #error directive). The exact form of the error message produced can vary from one compiler to another. It might be something like:
Error directive: message or sometimes #error message. Encountering an #error directive usually means a serious flaw with the program, and some compilers consider this enough reason to abort
compilation and not continue looking for other errors.
89) #error directives are usually used with conditional compilation to produce errors when certain situations shouldn't arise during compilation. An example of this is if our program requires
that the int type can hold values up to 6 digits long. What we do in this case is we define a macro called MAX_INT to hold the maximum value int types can hold and check that against 100000:
#if MAX_INT < 100000
#error int type is too small
#endif
--> Attempting to compile this program on a machine whose integers are stored over 16 bits at most will produce the "int type is too small" error.
90) The #error directive often shows up in the #else part of an #if #elif #else series.
91) Lines in a program are numbered 1,2,3... but we can use the #line directive to alter the way a program is numbered. This directive can also be used to trick the compiler into thinking that
it's reading the program from a file with a different name. The following two points will outline the two forms of the #line directive:
    *) #line n: where n is a sequence of digits representing a signed 16-bit (signed 32-bit) integer between 1 and 32767 (1 and 2147483647) for C89 (for C99). This will cause subsequent lines
in the program to be numbered n,n+1,n+2... (watch out!! line number n is assigned to the line right after the directive. The directive line is not taken into account).
    *) #line n "file": where file is a file name. The lines following the use of this directive are assumed to have come from "file" with line numbering starting at n. We can even use macros to
define the values of n and file.
92) The line macro can be used to change the value of the __LINE__ and __FILE__ macros. But most importantly, the compilers will use the #line macro to alter the information in their error
messages. Example: If we have a file called foo.c that contains the following directive: #line 10 "bar.c" on its very first line. Suppose the compiler detects an error on line 5 of foo.c,
the error message it will produce will refer to line 13 of bar.c instead of line 5 of foo.c. In fact, the very first line in foo.c after the directive will now become line 11. So we will have
this equivalence:
foo.c lines:    before using directive   |   after using directive
                       line 1                       line 1
                       line 2                       line 10
                       line 3                       line 11
                       line 4                       line 12
                       line 5                       line 13
93) Why would the #line directive be needed? It's primarily used by programs that generate C code as output, the most famous example of which is yacc (Yet Another Compiler-Compiler) whose GNU
version is called bison. This is a UNIX utility that automatically generates part of a compiler. When using yacc, the programmer will have to provide a file that contains information needed by
yacc along with fragments of C code as input to yacc. yacc then uses that input to generate a C program y.tab.c in that incorporates the code supplied by the programmer in that input file. It's
then the programmer's responsibility to compile that program in the usual manner. The idea here is to embed #line directives in the input file that will end up in the y.tab.c file so that we can
trick yacc into thinking that this program being compiled actually originates from the file written by the programmer and not the one produced by yacc halfway through the compilation process.
This way we can use line numbers as debugging indicators without having to worry about whether the lines produced by error messages refer to different lines in the y.tab.c file.
94) The #pragma directive is used to request special behavior from the compiler and it's usually used by programs that are either very large or that need to take advantage of capabilities of
a particular compiler. It has the general form: #pragma tokens: where tokens are arbitrary tokens that can be very simple like a single token or very elaborate. Example:
#pragma data(stack_size >= 2000, heap size >= 1000).
95) The set of commands that can appear in pragma directives are different for each compiler. The list of commands a compiler allows in pragma directives and what they actually do can be found
in the compiler's documentation.
96) The preprocessor will ignore any pragma directive that contains an unrecognized command. It won't produce any error and won't call our attention to it. It will be ignored silently.
97) C89 defines no standard pragmas. They're all implementation-defined. C99 however has three standard pragmas: FP_CONTRACT, CX_LIMITED_RANGE and FENV_ACCESS.
98) C99 also introduces the _Pragma operator which is used with the #pragma directive and has the following general form: _Pragma (string_literal). When it finds such a directive, the preprocessor
destringizes the string literal by removing the double quotes around it and replacing the escape sequences \" and \\ by " and \ respectively which results in a series of tokens instead of the
string literal that will be treated as though they appear in a #pragma directive. So for example, writing _Pragma ("data(stack_size >= 2000, heap size >= 1000)") is the same as writing
#pragma data(stack_size >= 2000, heap size >= 1000).
99) Since _Pragma is an operator and not a directive, it can technically appear in a macro definition therefore working around one of the preprocessor's biggest shortcomings: the fact that a 
preprocessing directive can't generate another directive --> We can use the _Pragma operator to leave behind a pragma directive after macro expansion.
100) An example from the GCC manual for using the _Pragma operator:
#define DO_PRAGMA(x) _Pragma(#x)
DO_PRAGMA(GCC dependency "parse.y") --> after expansion will yield: #pragma GCC dependency "parse.y" which is one of GCC's pragma commands that issues a warning if the date of "parse.y" is more
recent than the date of the file being compiled.
101) In the example above, the argument to DO_PRAGMA is a series of tokens which gets stringized into "GCC dependency \"parse.y \"", which is then passed to the _Pragma operator which destringizes
it and produces a pragma directive containing the original tokens.
102) Some programmers use # on a line by itself. This is called the null directive and it serves no purpose whatsoever. It's basically an empty line as far as the preprocessor is concerned. But
it's mostly used for spacing within conditional compilation blocks because it helps the reader visually discern the extent of the block. Example:
#if MAX_INT < 100000
#
#error int type is too small
#
#endif
103) Some programmers follow some rules as to what constants in a program should be defined as macros. For integers, some would say that every numeric constant other than 0 and 1 should be a macro.
For character constants and string literals however, defining them as a macro doesn't always improve readability so some would say it's a good idea to define them as macros if they are used more
than once in the program and if there's a possibility their values might change in the future. Some programmers for example use the macro: #define NUL '\0', but since it's not likely to change at
all, some would argue that this is not necessary.
104) If the argument of the # operator contains " or \, it converts them to \" and \\ respectively. Example:
#define STRINGIZE(x) #x
STRINGIZE("foo") after expansion will yield "\"foo\"".
105) Macros whose replacement list uses the ## concat operator can't be called in a nested fashion. The reason why becomes clear when we look at this example:
#define CONCAT(x,y) x##y
CONCAT(a,CONCAT(b,c))
--> This macro call isn't expanded in a normal fashion with CONCAT(b,c) expanding to bc and then CONCAT(a,bc) expanding to abc. It rather expands to aCONCAT(b,c) which can't be further expanded
since there's no macro called aCONCAT. The root of the issue comes from a rule that Dennis Ritchie calls bizarre which states that "macro parameters followed or preceded by the ## operator can't
be expanded at the time of substitution".
--> There's an ugly workaround to this problem that involves defining another macro that simple calls the first one:
#define CONCAT2(x,y) CONCAT(x,y). The difference is that CONCAT2's replacement list doesn't contain the ## operator and therefore won't be subjected to the weirdness Dennis Ritchie is referring to.
106) The # operator behaves similarly to ## when it comes to macro expansion. If #x appears in a macro's replacement list where x is a macro parameter, then once that macro is called, the
corresponding argument is not expanded. Example:
#define N 5
#define STRINGIZE(x) #x
STRINGIZE(N) --> after expansion will yield "N" and not "5". The same workaround stated above can be used here as well.
107) Rescanning is a process that the preprocessor goes through after expanding a macro to check whether the first expansion introduced any other macros that themselves need expanding.
108) If the preprocessor encounters the original macro name during rescanning, it shouldn't go into an infinite loop, although older preprocessors used to do that. According to the C standard, if
the original name of a macro reappears in an expanded macro, it won't be expanded again. This opens the door to a technique that defines macros whose names match certain reserved words or functions
in the standard library. For example, the sqrt library function computes the square root of its argument and returns an implementation-defined value if the argument is negative. Suppose we want to
rewrite the sqrt function so that it returns 0 if the argument is negative. We can in that case define a macro called sqrt like this:
#undef sqrt
#define sqrt(x) (x >= 0 ? sqrt(x) : 0).
--> Any subsequent calls to sqrt will be expanded by the preprocessor (since sqrt is now seen as a macro and not a function) to the previous conditional expression. If the argument is negative, it
will therefore result in 0, otherwise, the macro will be expanded to sqrt(x) which won't be further expanded as per the standard's rule and will be left for the compiler to handle.
109) In the previous example, we used the #undef sqrt as a defensive measure just in case the standard library does indeed have a macro whose name is sqrt, although it's worth noting that the
standard library is allowed to have a macro and a function which share the same name.
110) __FILE__ and __LINE__ are automatically recognized by the preprocessor and don't require any headers to be included. Note the double dashes at the beginning and end of these identifiers!
111) A hosted implementation is needed by programs that rely on the underlying operating system for input/output and other essential services. A freestanding implementation on the other hand would
be used by C programs that require no (or only a minimal) underlying operating system. A common example of when a freestanding implementation might be needed is for writing the kernel of an operating
system. This is a feat that doesn't require traditional input/output and therefore doesn't need <stdio.h>. A freestanding implementation can also be used when writing software for embedded systems.
112) The preprocessor knows enough about C to be able to evaluate constant expressions, although it doesn't do it in the same manner as the compiler (for example, it treats any undefined identifier
as though it has the value 0). In practice, preprocessor constant expressions (in the #if directive for example) contain either a constant, a macro that expands to a constant or an application of
the defined operator.
113) The #ifdef and #ifndef directives were part of the C language since the 70s while the defined operator was added to the language in the 80s during standardization. It was added for extra
flexibility since it allows us to test whether multiple identifiers are defined or not in one go instead of having to test one at a time using the #ifdef directive. Example:
#if defined(FOO) && defined(BAR) && !defined(BAZ) will check whether FOO and BAR are defined and BAZ isn't in one go.
114) The preprocessor works in 4 phases:
    1- Break the code into lines.
    2- Remove comments.
    3- Break the code into tokens.
    4- Execute directives.
This means that an unterminated multi-line comment or an unpaired single or double quote will be tokenized as bad input and will therefore be passed on to the compiler who will in turn detect and
report that bad token. So even though these issues might be in a block of code that's conditioned out, they still will get detected by the compiler.
*/