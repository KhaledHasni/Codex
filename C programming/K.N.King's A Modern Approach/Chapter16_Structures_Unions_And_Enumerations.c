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
35) A compound literal that creates a structure can fail to provide full initialization, in which case any initialized member will default to zero.
*/