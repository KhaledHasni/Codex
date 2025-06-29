/* Takeaways */

/*
1) The only data structure that has been discussed up until this point is the array which has two important properties:
    *) All elements in an array have the same data type.
    *) To select an array element, we use its position in the array as an integer subscript.
2) C provides another data structure called structure that comes with a different set of properties:
    *) Elements of a structure, called members in C jargon, are not required to have the same data type.
    *) Structure members have names. To select a member, we use its name and not its position.
3) Most programming languages provide a similar feature to C's structures. In some of them, structures are known as records and their members as fields.
4) Structures are most suited for when we need to store a set of related data items. Example: Suppose we need to keep track of parts in a warehouse. For each part, we'll need
to store a part number (integer), a part name (a string of characters) and the number of parts on hand (integer). To create variables able to store all three items of data,
we can use a declaration like this:
struct {
    int number;
    char name [NAME_LENGTH + 1];
    int on_hand;
} part1, part2;
--> Each of the two structure variables declared in the previous example (part1, part2) has three members. The declaration itself has a similar form to other variable
declarations in C: struct{...} is equivalent to the data_type in any other declaration while part1 and part2 are the variables of that type.
5) The members of a structure are stored in memory in the same order that they're declared. If we take the structure part1 from the previous example, and assuming that
part1 is located at address 2000, integers are stored over 4 bytes, NAME_LENGTH has the value 20 and there are no memory gaps between the members, the memory layout will
look something like this:
    *) The "number" member is stored over 4 bytes starting at the address 2000, so 2000, 2001, 2002, 2003.
    *) The "name" member is stored over 26 bytes starting at the address 2004, i.e ranging from 2004 to 2029.
    *) The "on_hand" member is stored over 4 bytes starting at the address 2030, so 2030, 2031, 2032, 2033.
6) Each structure represents a new scope. Any names declared in that scope won't conflict with other names in the program. In C terms, we say that every structure has a
distinct and separate namespace for its members. Example: The following declarations can appear in the same program:
struct {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
} part1, part2;

struct {
    char name[NAME_LENGTH + 1];
    int number;
    char gender;
} employee1, employee2;
--> number and name in part1 and part2 don't conflict with number and name in employee1 and employee2.
7) A structure can be initialized at the time of its declaration. To do so, we must provide a list of values to be stored in the structure and enclose them in braces.
Example:
struct {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
} part1 = {528, "Disk Drive", 10},
  part2 = {914, "Printer cable", 5};
--> The values in the initializer must appear in the same order as the members of the structure. So in the previous example, the number member of part1 will have the value
528, the name member will be "Disk Drive" and on_hand will be 10.
8) Structure initializers follow similar rules to array initializers. Expressions used in a structure initializer must be constant, meaning that we couldn't have used a
variable for example to initialize the on_hand member of the part1 structure. This rule is alleviated in C99 though.
9) A structure initializer can have fewer members than the structure it's initializing. Just like with arrays, any leftover members will be initialized to zero by default.
In particular, the bytes in a leftover character array will all be initialized to zero making the character array represent the empty string.
10) C99's designated initializers can be used to initialize a structure. If we consider the example used in point 7, part1's initializer {528, "Disk Drive", 10} would look
similar if we were to use a designated initializer, but with each value labeled by the name of the member it initializes: {.number = 528, .name = "Disk Drive", .on_hand = 10}.
The combination of the period and the member name is called a designator which looks quite different compared to designators of array elements.
11) C99's designated initializer has several advantages:
    *) They're easier to read and check for correctness since the reader can clearly see the structure members and the corresponding values in the initializer.
    *) The values in the initializer don't have to be listed in the same order as the members in the structure. For example, the designated initializer used in point 10
can be rewritten as follows: {.on_hand = 10, .number = 528, .name = "Disk Drive"}. Since the order doesn't really matter, the programmer doesn't have to remember the order
in which the structure members were declared to write a designated initializer for it. The order of the members can also be changed in the future without affecting its
designated initializer.
12) As is the case with arrays, not all values listed in a designated initializer need a designator prefix. Again, using the previous example:
{.number = 528, "Disk Drive", .on_hand = 10}. The value "Disk Drive" doesn't have a designator, so the compiler just assumes that it initializes the member after number in
the structure being initialized. Members that the initializer fails to account for are set to zero by default.
13) To access a member within a structure, we write the structure's name followed by a period then the member's name. For example, if we use the part1 structure from point 6,
the following statements can be used to display the values of its members:
printf("Part number: %d\n", part1.number);
printf("Part name: %s\n", part1.name);
printf("Quantity on hand: %d\n", part1.on_hand);
14) The members of a structure are lvalues which means they can appear on the left side of an assignment operator and can also be used as operands of increment and decrement
expressions: part1.number = 258; will change part1's number and part1.on_hand++ will increment part1's quantity on hand.
15) The period that we use to access a structure member is a C operator. It has the same precedence as the postfix ++ and -- operators which means it has precedence over
almost all operators. Let's consider the following example: scanf("%d", &part1.on_hand); The expression &part1.on_hand contains two operators (& and .). The . operator takes
precedence over the & operator which means the expression &part1.on_hand will compute the address of part.on_hand
16) The assignment operator can also be applied to structures. For example, the assignment part1 = part2; will copy part2.number into part1.number, part2.name into
part1.name and part2.on_hand into part1.on_hand.
17) It may come as a surprise that a structure can be copied into another structure using the assignment operator since this feature doesn't apply to arrays. It's even more
surprising that an array embedded within a structure as one of its members gets copied when the enclosing structure is copied using the assignment operator. Some programmers
even go as far as exploiting this property by creating dummy structures to hold arrays that will be copied later. Example: struct{ a[10];} a1, a2; a1 = a2;
--> The assignment a1 = a2; is perfectly legal since a1 and a2 are both structures.
18) When used with structures, the = operator can only be used with structures of compatible types. For example, two structures declared at the same time are compatible.
Structures declared with the same "structure tag" or the same type name are also compatible. These concepts will be discussed further on.
19) C provides no other operators besides = that apply to full structure operands. In particular, we can't use the == and != to test whether or not two structures are equal.
20) If we suppose that a program needs to declare several structure variables with identical members, then two possibilities are in play: We can either declare all variables
at once using the technique already discussed, in which case there's no issue, or we have to declare the variables at different points in the program. For example: Writing
struct { int number; char[NAME_LENGTH + 1]; int on_hand; } part1; and in one place in the program and struct { int number; char[NAME_LENGTH + 1]; int on_hand; } part2; in
another will cause several issues:
    *) Repeating the structure information will quickly bloat the program.
    *) Maintaining the program will not be straightforward since we can't guarantee that the declarations will remain consistent.
    *) According to the rules of C, part1 and part2 won't have compatible types therefore part1 can't be assigned to part2 and vice versa.
    *) Part1 and part2 can't be used as arguments in function calls since they don't have a type name.
--> To avoid all these issues, we need to be able to define a name that represents a type of structure and not just a structure variable. C provides two ways to name
structures: we can either declare a structure tag or use typedef to define a type name.
21) A structure tag is a name used to identify a particular kind of structure. For example, we can declare a structure tag called part like this:
struct part {
    int name;
    char name[NAME_LENGTH + 1];
    int on_hand;
};
--> The ; at the end is crucial and must be present to terminate the declaration. Failing to set the ; at the end of a structure tag declaration can have unpredictable
consequences. For example, if we consider the following example:
struct part {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
}

f(void)
{
    //do something
    return 0;
}
--> Notice that the function doesn't have a return type. Since the preceding structure declaration isn't terminated properly, the compiler will assume that the function f
returns a value of type struct part. The error won't be detected until the compiler reaches the first return statement in the function.
22) Once a structure tag is created, we can use it to declare structure variables. For example, having declared the part tag in point 21, we can use as follows:
struct part part1, part2; to declare the part1 and part2 structure variables. Note that we can't omit the word "struct" in this declaration since part is not a type name
per se, without the word "struct", it's meaningless.
23) Since structure tags aren't recognized unless preceded by the word "struct", they don't conflict with other names in the program. In other words, it would be perfectly
fine to have a variable called part in the program having declared a structure called part as we have done in point 21.
24) The declaration of a structure tag can be combined with the declaration of a structure variable: Example: We can declare a structure tag named part which allows us
to later on declare structure variables of type struct part, as well as structure variables named part1 and part2 in one go as the following example shows:
struct part {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
} part1, part2;
25) All structures declared to have type struct part (part being a structure tag already declared; to keep using the same example) are compatible with one another:
struct part part1 = {528, "Disk Drive", 10};
struct part part2;
part2 = part1; //perfectly legal since both structures have the same type.
26) Alternatively, if we don't want to declare a structure tag, we can use typedef to define a structure type. For example, we can define a type named part like this:
typedef struct {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
} part;
--> The name of the type must come at the end and not after the word struct. Once we've defined the structure type part, we can use it to declare structure types just like
we would with any other built-in type: Example: part part1, part2;
--> Since part is a typedef name, we're not allowed to write struct part;
--> All part variables, regardless of where they're declared are compatible.
27) It's up to the programmer to choose whether to declare a structure tag or define a structure type when it comes time to declare a structure variable. However, a small
caveat here is that declaring a structure tag is mandatory when the structure will be used in a linked list.
28) Functions may have structures as arguments and return values. For example:
--> The following function takes a structure as an argument and prints the values of its different members:
void print_part(struct part p)
{
    printf("Part number %d\n", p.number);
    printf("Part name %s\n", p.name);
    printf("Quantity on hand %d\n", p.on_hand);
}
and here's how print_part might be invoked: print_part(part1);
--> The following function returns a part structure that it constructs from its arguments:
struct part build_part(int number, const char *name, int on_hand)
{
    struct part p;

    p.number = number;
    strcpy(p.name, name);
    p.on_hand = on_hand;

    return p;
}
and here's how build_part might be invoked: build_part(528, "Disk Drive", 10);
Also notice how build_part is allowed to have parameter names that match the names of members of the part structure. This is because the structure has its own namespace.
29) Passing a structure to a function and returning a structure from a function both require making a copy of all members of the structure, which imposes a fair amount of
overhead on the program especially if the structure is large. For this reason, it's sometimes better to pass a pointer to astructure to a function instead of passing the
structure itself. Similarly, it's sometimes advisable to return a pointer to a structure from a function instead of returning the actual structure.
30) There are other reasons apart from efficiency that might require us to avoid passing and returning a structure by value. For example, the <stdio.h> header defines a type
named FILE which is typically a structure used to store information about the state of an open file and must therefore be unique in a program. This uniqueness enforces the
passing/returning by address of these FILE structures to all functions that require them to be passed as arguments/returned. This is indeed the case since every function in
<stdio.h> that opens a file returns a pointer to a FILE structure and every function that performs an operation on an open file requires a pointer to a FILE structure.
31) Sometimes, we might want to initialize a structure variable inside a function using another structure variable, possibly supplied as an argument to the function:
void f(struct part part1)
{
    struct part part2 = part1;
    //do something
}
--> C allows initializers of this kind provided that the structure variable being initialized, which is part2 in this case, has automatic storage duration i.e its' local
to a function and hasn't been declared static. The initializer can be any expression of the proper type, including a function call that returns a structure.
32) C99 introduces the concept of compound literals that can be used to create unnamed arrays primarily for the purpose of passing the array to a function. A compound
literal can also be used to create a structure on the fly without having to first store it in a variable. A structure created by a compound literal can be passed as an
argument, returned by a function or even assigned to a structure variable. For example:
--> We can use a compound literal to create a structure that will be passed to a function: So using the print_part function from earlier for example:
print_part((struct part) {528, "Disk Drive", 10}); The compound literal here creates a part structure containing the members 528, "Disk Drive" and 10 in that order.
--> We can use a compound literal to assign a structure to another structure variable:
part1 = (struct part) {528, "Dirk Drive", 10}; This statement resembles a declaration containing an initializer but it's not the same. In fact, an initializer can only
appear in a declaration and not in a statement like this.
33) In general, a compound literal consists of a type name within parentheses followed by a set of values enclosed by braces. If the compound literal represents a structure,
the type name can be a structure tag preceded by the word "struct" or a typedef name.
34) A compound literal may contain designators just like a designated initializer. Example:
print_part((struct part) {.number = 10, .name = "Disk Drive", .on_hand = 10});
35) A compound literal that creates a structure can fail to provide full initialization, in which case any uninitialized member will default to zero.
36) Structures and arrays can be combined without restriction. In other words, an array can have structures as elements and a structure can have structures and arrays as its
members. The part structure we've been using as an example has an array as one of its members (the name array).
37) Nesting one kind of structure inside another can often be useful. Example: Suppose we create a structure that will hold a person's first and last name, along with the
initial from their middle name. We can then use that structure as part of a larger structure:
struct person_name {
    char first_name[FIRST_NAME_LENGTH + 1];
    char middle_name_initial;
    char last_name[LAST_NAME_LENGTH];
};
struct student {
    struct person_name name;
    int id, age;
    char gender;
} student1, student2;
--> To access student1's first name, middle initial and last name, we need to make use of two applications of the . operator. Example: strcpy(student1.name.first_name, "Khaled");
38) Based on the example from the last point, using a structure for names as opposed to making first_name, last_name and middle_name_initial be members of the student structure
has several advantages:
    *) Names can be treated as units of data.
    *) If we were for example to write a function that would display a student's name, we could pass it a person_name structure as just one argument instead of three:
display_name(student1.name);
    *) Copying the information from a person_name structure into the name member of a student structure would take just one assignment:
struct person_name new_name;
student1.name = new_name;
39) One of the most common combinations of arrays and structures is an array whose elements are structures which is sometimes used to serve as a simple database. Example: If we
use the part structure from point 21, we can create an array called inventory capable of storing 100 parts: struct part inventory[100];
--> To access one of the parts stored in the array for example, we'd use subscripting. For example, If we were to print the part stored in position i of the inventory array, we
would write: print_part(inventory[i]);
--> Accessing a member within a part stored in the array will require a combination of array subscripting and member selection: Example: inventory[i].number = 883;
--> Accessing a particular character in a part's name will require subscripting to select the part we need, member selection to select the name member then subscripting again
to select a character within the part name. Example: To change the name stored in inventory[i] to an empty string, we could write inventory[i].[0] = '\0';
40) Initializing an array of structures is very similar to the way multidimensional arrays are initialized. Each structure in the array has its own brace-enclosed initializer,
and an extra set of braces is wrapped around all structure initializers to top off the array initializer.
41) One of the reasons why we would initialize an array of structures is when we need a database of information that is not going to change during the execution of the program.
Suppose for example that we're working on a project that needs access to the country codes needed to make international calls. The first thing we might do is set up a structure
to hold the name of a country alongside its country code:
struct dialing_code {
    char *country;
    int code;
};
--> Note here that country is a pointer to a character and not an array of characters. Had we been planning to use the dialing_code structures as variables, that would have been
problematic, but we're not. Once these structures are initialized, the country pointer will end up pointing to a string literal.
--> We can now declare an array of such structures and initialize it to contain some countries' dialing codes:
const struct dialing_code country_codes[] =
{{"Argentina", 54}, {"Bangladesh", 880}, {"Brazil",  55}, {"Burma", 95},
 {"China",     86}, {"Colombia",    57}, {"Congo",  243}, {"Egypt", 20},
 {"Ethiopia", 251}, {"France",      33}, {"Germany", 49}, {"India", 91}};
--> Note that the inner braces around each structure value are optional and are only kept as a matter of style.
42) Since arrays of structures and structures containing arrays are so common in C, C99's designated initializers allow one item to have more than one designator. Example:
Using the inventory array from point 39, suppose we want to initialize it to contain a single part for now, whose number is 528, the quantity on hand is 10 and the name is empty:
struct part inventory[100] =
{[0].number = 528, [0].on_hand = 10, [0].name[0] = '\0'};
--> The first two items use two designators: one to select array member 0 which is a part structure and one to select a member within the structure. The last item uses three
designators: one to select array element 0, one to select the name member from within that element and one to select element 0 of name which is a character.
43) Suppose we wanted to declare an array of part structures in one go, here's what we would do:
#define NAME_LENGTH 25
#define MAX_PARTS   100

struct part {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
} inventory[MAX_PARTS];
44) If we were to write a program that would manage a database of parts in a warehouse using the inventory array declared in the previous point, we would use the typical layout
of a menu-driven program and would use a main loop in the main function. Inside the main loop we would prompt the user to input a command, read the command and make sure it's
valid and process the command.
45) To read the command, assuming it's a one character command, we could do something like this:
char cmd;
scanf(" %c", &cmd);
while(getchar() != '\n');
--> The format string in scanf(" %c", &cmd) allows scanf to skip over any whitespaces before reading the command character. Notice the space in the format string " %c". This
space is crucial since without it, scanf will sometimes read the newline character from previous lines of input. On the other hand, while(getchar() != '\0') allows us to
discard all characters remaining in the line of input (once the command character has been read using scanf) until the end of line character is reached signaling the end of
the line of input.
46) A helper function, also known as a utility function, is a small function designed to perform subtask that supports the main functionality of a program or another function.
47) A union, like a structure consists of one or more members possibly of different types. The difference however is that the compiler will allocate only enough space for the
largest in size from among these members, which will therefore overlay each other in the allocated space. As a result, assigning a new value to one member alters the values
in the other members as well.
48) The declaration of a union very closely resembles that of a structure:
struct {
    int i;
    double d;
} s;
union {
    int i;
    double d;
} u;
--> The structure s and the union u differ in just one way: the members of the structure s are stored in different addresses while the members of the union u are stored at the
same address. So assuming int values require four bytes of storage and double values require eight bytes of storage, in the s structure, i and d occupy different addresses in
memory and the total size of the structure is 12 bytes. In the u union however, i and d occupy the same memory address and the total size of the union is only eight bytes.
This is achieved by i and d overlapping, with i taking over the first four bytes of d.
49) Members of a union are accessed in the same way we access members of a structure using the . operator. Example: If we were to store 82 in the i member of the u union, we
would write: u.i = 82; If we were to store 75.6 in the d member of the u union, we would write u.d = 75.6;
50) Since the compiler overlays storage for the members of a union, changing one member will alter any value previously stored in all other members. Using the previous example,
if we change the value stored in u.i, any value previously stored in u.d will be corrupted and vice versa. Because of this property of unions, they are looked at as a place
where we can store only one value for of the union's members and not all of them (that would be a structure).
51) Unions have a very similar set of properties to that of structures:
    *) We can declare union tags and union types just like we declare structure tags and types.
    *) Unions can be copied using the = operator just like structures.
    *) Unions can be passed to functions and returned by functions just like structures.
52) Unions can be initialized using a similar syntax to that of the initialization of a structure with one important caveat: only the first member of a union can be given an
initial value. Example: We can initialize the i member of the u union to 0 in the following manner:
union {
    int i;
    double d;
} u = {0};
--> Notice the presence of the braces which are required. The expression inside the braces must be constant, with slight rule changes in C99.
53) C99's designated initializers can be used with unions. A designated initializer allows us to specify which member of the union should be initialized: Example: We can
initialize the d member of u as follows:
union {
    int i;
    double d;
} u = {.d = 4.2};
--> Only one member can be initialized using a designated initializer and it doesn't necessarily have to be the first one.
54) Unions can be used to achieve mainly three goals:
    *) Save space.
    *) Build mixed data structures.
    *) Viewing storage in different ways.
55) Let's examine how a union can be used to save space in structures. Suppose we want to design a structure that will contain information about an item sold at a gift shop.
Here are the rules:
    *) The shop sells only three kinds of merchandise: books, shirts and mugs.
    *) An item will have a stock number and a price no matter what type it is.
    *) An item will have other type-specific information:
        1. A book will have a title, author and a number of pages.
        2. A mug will have a design.
        3. A shirt will have a design, available colors and available sizes.
--> We might be tempted to design the structure in the following manner:
struct gift_item {
    int stock_number;
    double price;
    int item_type;
    char title[TITLE_LENGTH + 1];
    char author[AUTHOR_LENGTH + 1];
    int num_pages;
    char design[DESIGN_LENGTH + 1];
    int colors;
    int sizes;
};
--> The item_type member would have one of the following values: BOOK, SHIRT and MUG. The members colors and sizes would have encoded combinations of colors and sizes.
56) If we consider the example in the previous point, the structure we wrote is perfectly usable but it has one major flaw: it wastes a lot of space since only part of the
information in the structure is common between all types of items. For example, if an item is a book, there's no need to have a design, colors or a sizes member. By using
a union inside the structure, we can reduce the amount of space needed to store each structure instance. The idea is to make the members of the union structures themselves
that will hold item-specific data:
struct gift_item {
    int stock_number;
    double price;
    int item_type;
    union {
        struct {
            char title[TITLE_LENGTH + 1];
            char author[AUTHOR_LENGTH + 1];
            int num_pages;
        } book;
        struct {
            char design[DESIGN_LENGTH + 1];
        } mug;
        struct {
            char design[DESIGN_LENGTH + 1];
            int colors;
            int sizes;
        } shirt;
    } item;
};
--> Notice that the union called item is a member of the gift_item structure, while book, mug and shirt are all members of the item union.
--> Suppose that g is a gift_item structure instance that represents a book. We can print the book's title using: printf("%s", g.item.book.title);
57) It's generally not a good idea to store a value in one member of a union and then access that data through a different member. This is due to a rule in the C standard that
states: Assigning to a member of a union causes that other members to be undefined. However, this rule has one exception that the C standard mentions: When two or more of the
union's members are structures and these structures begin with one or more matching members (these members need to be in the same order and have compatible types but they don't
need to have the same name). In this case, if one of the structures is currently valid, then the matching members in the other structures are also valid. Example: Consider
the item union embedded in the gift_item structure used in the example in point 56. The unions has three structures as members, two of which, mug and shirt have a matching
first member called design. If we assign a value to one of the design members: strcpy(g.item.mug.design, "Cat"); the design member in the other structure will also be defined
and have the same value: printf("%s", g.item.shirt.design); will print "Cat".
58) Let's examine how a union can be used to build mixed data structures. Suppose we need to create an array whose elements are a mixture of int and double values. At first
glance, it might seem impossible to create such a data structure since the elements of an array must be of the same type. However, this can be achieved relatively easily using
unions. We start by defining a union type whose members are the different kinds of data to be stored in the array:
typedef union {
    int i;
    double d;
} Number;
Next, we create an array whose elements are Number values: Number array[100]; Each element in the array is a Number value which can hold either an int value or a double value,
which makes it possible to store a mixture of int and double values in the array: Example of assignments we can perform:
array[0].i = 10;
array[0].d = 1.2;
59) Unions have a major deficiency, there's no way to tell which member of a union was last changed and therefore contains meaningful data. So suppose we wanted to write a
function that would take a Number union (based on the example from point 58), and display the value currently stored in it. This function might look something like this:
void print_number(Number n) {
    if(//n contains an integer)
        printf("%d", n.i);
    else
        printf("%g", n.d);
}
--> There's no way for print_number to tell whether n contains an integer or a floating-point number. So in order to keep track of this information i.e be able to tell at any
given moment whether a certain Number union contains an integer or a floating-point number, we can embed the union in a structure that contains an extra member called a "tag
field" or a "discriminant" whose purpose is to remind us what's currently stored in the union. In the gift_item discussed in point 56, the member item_type served this purpose.
If we try to apply that to the Number type, we would get something similar to this:
#define INT_KIND    0
#define DOUBLE_KIND 1
typedef struct {
    int kind; //tag field
    union {
        int i;
        double d;
    } u;
} Number;
--> Number has two members, kind and u. The possible values of kind are INT_KIND and DOUBLE_KIND. The idea is to change the value of kind every time we assign a value to u to
remind us which member of u we modified. Example: If n is a number variable, an assignment to the i member of u would need to involve two steps:
n.kind = INT_KIND;
n.u.i = 15;
--> When we need to retrieve data stored in a Number variable, the kind member will tell us which member of the union was last assigned a value. The print_number function
discussed earlier can take advantage of this information:
void print_number(Number n) {
    if(n.kind == INT_KIND)
        printf("%d", n.i);
    else
        printf("%g", n.d);
}
--> IMPORTANT REMINDER: When using unions with a tag field, it's up to the programmer to update it every time an assignment is made to a member of the union.
60) C programs will often need variables that hold a small set of meaningful values. For example, a boolean variable will hold one of two possible values, true and false. A
variable that stores the suit of a playing card should have only four potential values: Spades, Hearts, Diamonds and Clubs. One way to handle such a variable is to declare it
as an int variable and have a set of codes to represent the different possible values:
int suit;
suit = 2; //2 is code for Diamonds in this case
--> Although this method will work, it has some glaring deficiencies:
    *) Someone reading the program can't tell that suit has only four possible values.
    *) The significance of 2 assigned to suit isn't immediately apparent.
61) To fix the issues with the previous example, we can use macros to define a suit type and names for the various suits:
#define SUIT     int
#define SPADES   0
#define HEARTS   1
#define DIAMONDS 2
#define CLUBS    3
//do something
SUIT suit;
suit = DIAMONDS;
--> This technique is an improvement, but it still has flaws:
    *) There's no indication to someone reading the program that the macros represent values of the same type.
    *) If the total number of possible values is large, writing out macros for all possible values will be tedious to say the least.
    *) The macro names will be expanded and removed by the preprocessor and consequently won't be available during debugging.
62) C provides a special kind of type designed specifically for variables with a limited number of possible values. An enumerated type is a type whose values are listed or
enumerated by the programmer. The latter must create a name otherwise known as an enumeration constant for each of the values. Example: We can enumerate the different suit
values that can be assigned to variables s1 and s2: enum {SPADES, HEARTS, DIAMONDS, CLUBS} s1, s2;
63) Enumerations might appear to be similar to structures and unions because their declarations are fairly similar looking, but they actually have little in common. It's
also important to remember that unlike the members of structures and unions, enumeration constants must be different from other identifiers declared in the enclosing scope.
64) Enumeration constants are similar to constants declared with the #define directive but the two are not equivalent. For instance, enumeration constants are subject to
C's scope rules, so when an enumeration is deckared inside a function, its constants won't be visible outside of it.
65) We sometimes need to create names for enumerations just like we do for structures and unions. And just like structures and unions, there are twp ways to name an
enumeration: by declaring a tag or by using typedef to create a genuine type name.
66) Enumeration tags are like structure and union tags. To keep using the playing card suit example, we could define the tag suit in the following manner:
enum suit {SPADES, HEARTS, DIAMONDS, CLUBS}; and suit variables would be declared in the following manner: enum suit s1, s2;
67) Making Suit a type name and declaring variables s1 and s2 of that type would look something like this:
typedef enum {SPADES, HEARTS, DIAMONDS, CLUBS} Suit;
Suit s1, s2;
68) In C89, using typedef to name an enumeration is a good way to create a boolean type:
typedef enum {FALSE, TRUE} Bool;
--> C99 has a built-in boolean type though, so this technique is not necessary.
69) C treats enumeration variables and constants as integers. In fact, the compiler will assign the values 0,1,2...by default to the constants in a particular enumeration.
In our suit enumeration for example, SPADES, HEARTS, DIAMONDS, CLUBS represent the values 0, 1, 2 and three respectively.
70) We can choose different values to be assigned to our enumeration constants if we want. Example: enum suit {SPADES = 1, HEARTS = 2, DIAMONDS = 3, CLUBS = 4};
71) The values of our enumeration constants can even be arbitrary integers listed in no particular order. Example:
enum suit {SPADES = 10, HEARTS = 205, DIAMONDS = 3, CLUBS = 47};
72) Different enumeration constants in the same enumeration can have the same value.
73) When no value is specified for an enumeration constant, its value will by default be one greater than the value of the previous constant, with the first constant's value
being zero by default. Example: in the following enum, BLACK has the value 0 and DK_GRAY has the value 8:
enum EGA_colors {BLACK, LT_GRAY = 7, DK_GRAY, WHITE = 15};
74) In a sense, enumeration values are nothing but thinly disguised integers, which is why C allows us to freely mix them with ordinary integers:
int i;
enum {SPADES, HEARTS, DIAMONDS, CLUBS} s;
i = DIAMONDS; //i is now 2
s = 0; //s is now SPADES
s++; //s is now HEARTS
i = s + 2; //i is now 3
--> The compiler treats the variable s as some type of integer. SPADES, HEARTS, DIAMONDS, CLUBS are merely names for 0, 1, 2 and 3.
75) It's convenient to use an enumeration value as an integer but using an integer as an enumeration value is hazardous. For example, we might inadvertently store the number
5 in s which doesn't correspond to any suit.
76) Enumerations can be used to declare a tag field in a union. In the Number structure discussed in point 59 for example, we can make the kind member an enumeration
instead of an int:
typedef struct {
    enum {INT_KIND, DOUBLE_KIND} kind;
    union {
        int i;
        double d;
    } u;
} Number;
--> This structure is used in exactly the same way as the other version (using int for the kind member). The advantage here is that we no longer have macros for INT_KIND and
DOUBLE_KIND and we have instead replaced them with enumeration constants, and we have clarified the meaning of the kind member since it's now very obvious that it only has
two possible values.
77) Using the sizeof operator on structures might sometimes reveal a seemingly startling reality at first, but it makes sense once we know the underlying reasons behind it.
In fact, the size of a structure in terms of number of bytes it occupies in memory might be greater than the sum of its members' sizes. Example:
struct {
    char a;
    int b;
} s;
--> If char values occupy one byte and int values occupy four bytes then the size of s may surprisingly not be 5 (1 + 4). In fact, some computers require that the address
of certain data items be a multiple of some number of bytes (typically two, four or eight depending on the item's type). To satisfy this requirement, a compiler will align the
members of a structure by leaving unused bytes (paddings) between adjacent members. So in our example, assuming that data items are stored at addresses that are multiples of
four bytes, the a member will be followed by 3 unused bytes. As a result, sizeof(s) will be 8 and not 5. Note that a structure can have holes or unused bytes at the end as
well as between adjacent members. Example:
struct {
    int a;
    char b;
} s;
--> The structure s in this case might have a three-bytes hole at the end i.e after the b member.
78) The C standard explicitly states that holes in structures can only be either at the end or in the middle. They categorically can't at the start. A direct consequence of this
is that a pointer to the first member of a structure is always guaranteed to be the same as a pointer to the entire structure. The two pointers will more than likely not have the
same type though.
79) Comparing two structures using the == operator was probably left out of C because there's no way of implementing this operation all while staying true to C's philosophy.
Comparing members one by one would be too inefficient. Comparing all bytes in both structures is better, and some computers do have special instructions that perform such a
comparison. However, if the structures have holes in them, this form of comparison might not yield the expected result since the structures could have identical member values
but the leftover data stored in the holes is not the same. In theory, this could be mitigated by ensuring the compiler always stores the same value in those holes. This however
is not feasible since it would impose a performance penalty on all programs that use structures.
80) C originally lacked typedef, so tags were the only technique available for naming structure types. When typedef was introduced to the language, it was already too late to
remove tags, so now we have two ways of naming structure types. Besides, a tag is still necessary when a structure member points to a structure of the same type as is the case
with most linked list implementations.
81) A structure can have both a tag and a typedef name and the two can even be the same although that's not required:
typedef struct part {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
} part;
82) To share a structure type among several files in a program, we can put a declaration of a structure tag or typedef in a header file and include that file anywhere the
structure is needed. Example: To share the part structure between multiple files, we would write this in a header file:
struct part {
    int number;
    char name[NAME_LENGTH + 1];
    int on_hand;
};
--> Notice that we only declared the structure tag, not variables of this type.
83) A header file that contains a declaration of a structure tag or structure type may need protection against multiple inclusion since declaring a tag or a typedef name twice
in the same file is an error. This also applies to unions and enumerations.
84) If we declare a structure in a header file and include that file in two source files, the variables of that structure type in both files will technically not be of the same
type, however, the C standard states that both sets of variables will have compatible types. And since variables of compatibles types can be assigned to each other, there's
little practical difference between two types being "compatible" and "the same".
85) The rules for structure compatibility in C89 and C99 are slightly different. In C89, two structures defined in different files are compatible if their members have the same
names and appear in the same order, with corresponding members having compatible types. C99 takes this a step further by requiring that either both structures have the same tag
or neither has a tag. Note: Compatibility rules mentioned in this point and in point 84 also apply to unions and enumerations with the same differences between C89 and C99.
86) C99 allows having pointers to compound literals. Example: If we consider the print_part function from point 28 which takes a part structure as an argument. The function would
be much more efficient if it were modified to take a pointer to a part structure instead. We can then use call the function with the address of a compound literal as an argument:
print_part(&(struct part) {528, "Disk Drive", 10});
87) Compound literals are lvalues and can be modified, although doing so is rare. This explains the fact that pointers to compound literals are legal.
88) C99, as well as some pre-C99 compilers allow commas after the final constant in an enumeration. In fact, allowing this trailing comma makes enumerations easier to modify since
constants can be added without having to change any existing lines of code. Perhaps one reason for introducing this in C99 is the fact that C89 allowed trailing commas in
initializers so it seemed inconsistent not to allow the same flexibility in enumerations. To further prove this point, C99 also allows trailing commas in compound literals.
89) Enumerations constants can be used as subscripts since they're technically aliases for integers.
90) In C99, enumeration constants can be used as subscripts in designated initializers. Example:
enum weekdays {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY};
const char *daily_specials[] = {
    [MONDAY] = "Pasta",
    [TUESDAY] = "Pizza",
    [WEDNESDAY] = "Salad",
    [THURSDAY] = "Ravioli",
    [FRIDAY] = "Chicken"
};
*/