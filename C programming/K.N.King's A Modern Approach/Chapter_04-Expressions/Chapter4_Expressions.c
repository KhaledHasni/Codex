/* Takeaways */

/*
1) The arithmetic operators, i.e operators that perform addition, subtraction, multiplication and division are some of the most important operators in many programming
languages including C. These operators can be divided into two major groups:
    *) Unary operators:
        --> '+' the unary plus operator.
        --> '-' the unary minus operator.
    *) Binary operators: These operators can be further broken down into two groups;
        --> Additive operators:
            **) '+' the addition operator.
            **) '-' the subtraction operator.
        --> Multiplicative operators:
            **) '*' the multiplication operator.
            **) '/' the division operator.
            **) '%' the remainder operator.
2) The additive and multiplicative operators are said to be binary because they require two operands. The unary operators in the other hand require only one operand.
Example:
i = +1; //+ is used here as a unary operator
j = -1; //- is used here as a unary operator
3) The unary + operator does nothing. It's worth pointing out that it didn't even exist in K&R C. It's used primarily to emphasize that a numeric constant is positive.
4) The value of i%j is the remainder when i is divided by j. Example: 10%3 is 1 and 12%4 is 0.
5) The binary arithmetic operators with the exception of the remainder operator allow integer and floating-point operands with mixing allowed. When integer and
floating-point operands are mixed, the result is a floating-point. Example: 9 + 2.5f is 11.5 and 6.7f / 2 is 3.35.
6) The / and % operators require special care:
    *) when both of the / operator's operands are integers, the result is truncated by dropping the fractional part. Example: The value of 1/2 is 0 not 0.5.
    *) The % operator requires integer operands. When either of its operands is not an integer, the program won't compile.
    *) Using zero as the right operand of either / or % yields undefined behavior.
    *) Outlining the result of a / or % operation when used with negative operands is not as straightforward as it may seem.
        --> The C89 standard states that if either operand of a division operation is negative, the result can be rounded either up or down. Example: The value of
    -9 / 7 is either -1 or -2. Also, if i or j is negative, the value of i % j is implementation-dependent. Example: The value of -9 % 7 is either -2 or 5.
        --> The C99 standard states that the result of a division is always truncated towards zero. So the value of -9 / 7 would be -1. It also states that the value
    of i % j is always of the same sign as i. So -9 % 7 would be -2.
7) The C standard deliberately leaves parts of the language unspecified, with the understanding that an implementation which is another way of saying the software used
to compile, link and execute programs on a particular platform, will fill in the gaps. Consequently, a program's behavior may vary from one implementation to another.
The behavior of the / and % operators when applied to negative operands in C89 is an example of such implementation-defined behavior. It might seem odd or dangerous to
leave parts of the language unspecified in the standard, but that's actually one of C's claims to fame and it reflects its philosophy. One of the language's goals is
efficiency which often means matching the way hardware works. Since some CPUs yield -1 and others yield -2 when -9 is divided by 7, the C89 standard simply reflects
this fact.
8) It's usually a good idea to avoid writing programs that rely on implementation-defined behavior. If there's no way around doing so, it might be a good idea to check
the manual since the C standard requires that implementation-defined behavior be at least documented.
9) As a general rule, C allows the use of parentheses for grouping in all expressions. If we don't use parentheses in expressions involving the use of more than one
arithmetic operators, this highlights the concept of operator precedence. Example: Will the compiler interpret i + j * k as i + (j * k) or (i + j) * k. C, like many
other languages uses operator precedence rules to resolve this ambiguity.
10) The arithmetic operator have the following relative precedence level:
    *) The unary + and - operators have the highest level of precedence among all arithmetic operators.
    *) The binary multiplicative operators *, / and % are next on the list in terms of highest level of precedence among the arithmetic operators.
    *) The binary + and - operators have the lowest precedence among all arithmetic operators.
--> Note: The arithmetic operators have three distinct levels of precedence with multiple operators being able to share the same precedence level.
11) When two or more arithmetic operators appear in the same expression, we can determine how the compiler will interpret said expression by repeatedly enclosing
subexpressions in parentheses starting with the highest precedence operators and working our way down to the lowest-precedence operators. Example:
    *) i + j * k is equivalent to i + (j * k)
    *) -i * -j is equivalent to (-i) * (-j)
    *) +i + j / k is equivalent to (+i) + (j / k)
12) When an expression contains two or more arithmetic operators that have the same level of precedence, precedence rules aren't enough to resolve the ambiguity that
may arise. In this case, the associativity of the operators comes into play.
13) *) An operator is said to be left-associative if it groups from left to right. The binary arithmetic operators (*, /, %, + and -) are all left-associative. Example:
        --> i - j - k is equivalent to (i - j) - k.
        --> i * j / k is equivalent to (i * j) / k.
    *) An operator is said to be right-associative if it groups from right to left. The unary arithmetic operators (+ and -) are both right-associative. Example:
        --> -+i is equivalent to -(+i).
14) Precedence and associativity rules are important in a lot of programming languages but especially so in C. Given that C has so many operators though, it can be
a headache to memorize all precedence and associativity rules. Most C programmers just consult a table of operators when doubtful or simply use a lot of parentheses.
15) Some older compilers limit the maximum value of an int variable to 32767.
16) Once the value of an expression has been computed, it's often helpful to store it in a variable for later use. C provides the simple assignment operator '=' for
that purpose. To update a value already stored in a variable, C provides a set of compound assignment operators.
17) The effect of the assignment v = e is to evaluate the expression e and copy its value into v. Example: The following examples highlight the fact that e can be a
constant, a variable or a more complex expression:
i = 5;          //i is now 5
j = i;          //j is now 5
k = 10 * j + i; //k is now 55
--> It's crucial to point out that if v and e don't have the same type, then the value of e is converted to the type of v as the assignment is taking place. Example:
int i;
float f;
i = 72.99f; //i is now 72
f = 15;     //f is now 15.0
18) VERY IMPORTANT! In many programming languages, assignment is a statement. In C however, assignment is an operator just like + and -. In other words, the assignment
operation produces a result just like adding two numbers or subtracting a number from another produces a result. The value of an assignment v = e is the value of v
after the assignment has taken place. Example: The value of i in the following example is 72 and not 72.99:
int i;
i = 72.99f;
19) Intuitively, we wouldn't expect operators to act on their operands or modify them since mathematical operators don't. Writing i + j doesn't modify either i or j.
It simply computes the result of adding the two values together. In that regard, most C operators don't modify their operands but some do. Such operators are said to
have side effects since they do more than just compute a value. The simple assignment operator is an example of a C operator that does have side effects. In fact,
it acts on its left operand and modifies it. Example: Evaluating the expression i = 0 produces the value 0 and assigns 0 to i as a side effect.
20) Since assignment is an operator, several assignments can be chained together. Example: i = j = k = 0;
Note that the = operator is right-associative. This means i = j = k = 0 is equivalent to i = (j = (k = 0)); The effect is to assign 0 to k first, then to j then to i.
--> Extra attention needs to be paid to potentially unexpected results in chained assignments due to type conversion. Example:
int i;
float f;
f = i = 33.3f;
--> In this example, i is assigned the value 33 since i is of type int, then 33 is assigned to f which will end up containing 33.0 instead of 33.3.
21) In general, an expression of the form v = e is allowed in C wherever a value of type v is permitted. Example:
i = 1;
k = 1 + (j = i);
printf("%d %d %d\n", i, j, k); //prints "1 1 2"
--> As a general rule of thumb, it's usually best to avoid using the assignment operator in this manner since it can be a source of subtle bugs and makes programs hard
to read.
22) Most C operators allow their operands to be constants, variables or even expressions containing other operators. The simple assignment operator however requires an
lvalue as its left operand. An lvalue is an object stored in computer memory, not a constant or the result of a computation. Variables are lvalues. Expressions such as
10 and 2 * i are not. Variables are not the only type of lvalues in C.
23) Since the assignment operator requires an lvalue as its left operator, it's illegal to use any other kind of expression on the left side of an assignment
expression. Example:
12 = 0;    //illegal
i + j = 0; //illegal
-i = j;    //illegal
--> The compiler will detect these kinds of errors and will produce error messages such as "invalid lvalue in assignment".
24) It's common for C programs to use the old value of a variable to compute its new value. Example: The following statement adds 2 to the value stored in i:
i = i + 2;
--> We can shorten this statement and others like it by using C's compound assignment operators. The previous example can be rewritten as:
i += 2; //equivalent to i = i + 2
25) The += compound operator adds the value of the right operand to the variable on the left.
26) C provides ten compound assignment operators including +=, -=, *=, /= and %=.
27) All compound assignment operators work in much the same way:
    *) v += e adds v to e and stores the result in v.
    *) v -= e subtracts e from v and stores the result in v.
    *) v *= e multiplies v by e and stores the result in v.
    *) v /= e divides v by e and stores the result in v.
    *) v %= e computes the remainder when v is divided by e and stores the result in v.
28) v += e is not necessarily equivalent to v = v + e. One problem is operator precedence. i *= j + k is not the same as i = i * j + k. There are also cases where
v += e isn't the same as v = v + e because v itself has a side effect. Similar remarks apply to other compound assignment operators.
29) Inadvertently swapping the two characters that make up a compound operator may yield an expression that the compiler accepts but that doesn't have the intended
meaning. Example: If we wanted to write i += j but wrote i =+ j, the program will still compile, but will only copy the value of j into i (i += j is equivalent to
i = +j) instead of adding the value of j to the value of i and copying the result into i.
30) The compound assignment operators have the same properties as the = operator, in particular, they're right-associative. Example: The statement i += j += k is
equivalent to i += (j += k).
31) Two of the most common operations we can subject a variable to are incrementing (adding one) and decrementing (subtracting one). This can be accomplished by
respectively writing: i = i + 1 and i = i - 1. Compound assignment operators allow us to condense these statements by writing: i += 1 and i -= 1. That being said, C
allows these operations to be shrunk even further by using the ++ and -- operators called the increment and decrement operators respectively.
32) The increment and decrement operators can be tricky to use.
    *) One complication that comes with using these operators is the fact that they come in two sets:
        --> prefix operators --i and ++i.
        --> postfix operators i-- and i++.
    The proper version of the increment/decrement has to be picked depending on the use case.
    *) Another complication is the fact that the increment and decrement operators (both prefix and postfix) have side effects (since they modify the values of their
    operands) just like the simple assignment operator.
        --> Evaluating the expression ++i called a pre-increment yields i + 1 and increments i as a side effect.
        i = 1;
        printf("i is %d\n", ++i); //prints "i is 2"
        printf("i is %d\n", i);   //prints "i is 2"
        --> Evaluating the expression i++ called a post-increment yields i and increments i afterwards.
        i = 1;
        printf("i is %d\n", i++); //prints "i is 1"
        printf("i is %d\n", i);   //prints "i is 2"
33) ++i means increment i now while i++ means use the old value of i now and increment it later. The C standard doesn't specify how much later i will be incremented
when the postfix ++ operator is used but it's always safe to assume that it will be incremented before the next statement is executed.
34) The -- operator has similar properties to the ++ operator. Example:
i = 1;
printf("i is %d\n", --i); //prints "i is 0"
printf("i is %d\n", i);   //prints "i is 0"
i = 1;
printf("i is %d\n", i--); //prints "i is 1"
printf("i is %d\n", i);   //prints "i is 0"
35) When more than one ++ or -- operator is used in the same expression, the result can often be hard to understand. Example:
i = 1;
j = 2;
k = ++i + j++;
--> The question here is, what are the values of i, j and k after these statements are executed. Since i is being pre-incremented and j is being post-incremented, the
last statement is equivalent to:
i = i + 1;
k = i + j;
j = j + 1;
so the final values of i, j and k are 2, 3 and 4 respectively. Had the last expression been: k = i++ + j++; the final values of the three variables would have
respectively been 2, 3 and 3.
36) The postfix versions of ++ and -- have higher precedence than the unary + and - operators and are left-associative.
37) The prefix versions of ++ and -- have the same precedence as the unary + and - operators and are right-associative.
38) The following table summarizes the arithmetic operators discussed, their level of precedence relative to each other and their associativity. The precedence levels
evolve in descending order.
|------------|------------------------------------|-------------------------------------------|-------------------|
| Precedence |                Name                |                  Symbols                  |   Associativity   |
|------------|------------------------------------|-------------------------------------------|-------------------|
|     1      |  Increment / Decrement (postfix)   |                   ++/--                   |       left        |
|------------|------------------------------------|-------------------------------------------|-------------------|
|     2      |        Increment (prefix)          |                     ++                    |       right       |
|            |        Decrement (prefix)          |                     --                    |                   |
|            |            unary plus              |                     +                     |                   |
|            |            unary minus             |                     -                     |                   |
|------------|------------------------------------|-------------------------------------------|-------------------|
|     3      |          multiplicative            |                   * / %                   |       left        |
|------------|------------------------------------|-------------------------------------------|-------------------|
|     4      |             additive               |                    + -                    |       left        |
|------------|------------------------------------|-------------------------------------------|-------------------|
|     5      |            assignment              |              = *= /= %= += -=             |       right       |
|------------|------------------------------------|-------------------------------------------|-------------------|
39) Suppose that we run across a complex expression that doesn't have any parentheses to show how it's constructed from subexpressions. In this case, we can use the
table mentioned in point 38 to figure out which operator in the expression has the highest precedence and enclose it along with its operands in parentheses. This would
indicate that this new unit enclosed in parentheses should be treated as a single operand moving forward. We can then repeat the process until the expression is fully
parenthesized. Example: a = b += c++ - d + --e / -f. In this example, the operator with the highest precedence is ++ used here as a postfix operator, so we can enclose
the ++ and its operand c in parentheses a = b += (c++) - d + --e / -f. Next is the prefix -- operator and the unary - operators: a = b += (c++) - d + (--e) / (-f).
The other - operator in the expression has an operand to its immediate left which makes it a binary subtraction operator not a unary minus operator. Next is the /
operator, the only multiplicative operator in the expression: a = b += (c++) - d + ((--e) / (-f)). Next, we have the additive + and - operators that have the same level
of precedence. Whenever two operators of the same precedence are adjacent to an operand, associativity rules apply. We know that  additive + and - operators group from
left to right so we enclose the subtraction in parentheses first then the addition: a = b += (((c++) - d) + ((--e) / (-f))). The only remaining operators are = and +=
which have the same precedence and are adjacent to the same operand b so associativity rules will have to apply. Assignment operators group from right to left so we
get the final result: (a = (b += (((c++) - d) + ((--e) / (-f))))).
40) The rules of operator precedence and associativity allow us to break an expression into subexpressions, by determining uniquely where the parentheses would go had
the expression been fully parenthesized. That being said, once an expression is broken down into subexpressions, these rules don't always determine the order in which
these subexpressions are evaluated which may influence the value of the whole expression overall.
41) C doesn't define the order in which subexpressions are evaluated (with the exception of subexpressions involving the logical and, logical or, conditional and comma
operators). Example: In the expression (a + b) * (c - d), we don't know whether a + b or c - d will be evaluated first. Luckily, most expressions have the same value
regardless of the order in which their subexpressions are evaluated. However, that may not be the case when a subexpression modifies the value of one of its operands.
Example: In the following two statements, the effect of the second statement is undefined. That is, the C standard doesn't state what will happen in such a case:
a = 5;
c = (b = a + 2) - (a = 1);
--> The problem boils down to which of the two subexpressions (b = a + 2) and (a = 1) will be evaluated first. With most compilers, the value of c will be either 6 or
2. If the subexpression (b = a + 2) is evaluated first, b will be assigned 7 and c will be assigned 6. If the subexpression (a = 1) is evaluated first, b will be
assigned 3 and c will be assigned 2.
42) As a general rule of thumb, it's a good idea to avoid writing expressions that access the value of a variable and modify the same variable elsewhere in the
expression. The expression (b = a + 2) - (a = 1) accesses the value of a to be able to compute a + 2 and modifies the value of a by assigning 1 to it. Some compilers
may complain when encountering such an expression and produce a warning message along the lines of "operation on 'a' may be undefined".
43) To stay clear of any potential issues, it's a good idea to avoid using the assignment operators in subexpressions and instead use a series of assignments.
Example:
a = 5;
c = (b = a + 2) - (a = 1);
The statements above could be rewritten as:
a = 5;
b = a + 2;
a = 1;
c = b - a;
--> This ensures that the value of c will always be 6.
44) The only operators that modify their operands are the assignment, the increment and the decrement operators.
45) When using operators that modify their operands, it's important to make sure that they're not used in expressions that depend on a particular order of evaluation.
Example: As a result of executing the following two statements, j could be assigned either one of two values:
i = 2;
j = i * i++;
    --> j could be assigned 4: The second operand which is the original value of i is fetched. Next, the first operand which is i is fetched. The two operands are
multiplied yielding 4. Finally, i is incremented.
    --> j could be assigned 6: The second operand which is the original value of i is fetched then i is incremented. Next, the first operand which would be the new
value of i is fetched. Finally, the new and old values of i are fetched yielding 6.
46) Fetching a variable means to retrieve the value of the variable from memory. A later change to the variable doesn't affect the fetched value which is typically
stored in a CPU register.
47) The C standard considers statements like j = i * i++; and c = (b = a + 2) - (a = 1); problematic in that they cause undefined behavior which is not the same as
implementation-defined behavior. When a program contains undefined behaviors, it's tough to predict how it will behave under different circumstances. It might behave
differently when compiled with different compilers. It may not compile at all. If it does compile, it might not run. And if it does run, it might crash, produce
meaningless results or behave erratically.
48) One of C's peculiarities is that any expression can be used as a statement by merely appending a semicolon, regardless of the expression's type or what it
computes. Example: The expression ++i can be turned into a statement by appending a semicolon: ++i; When this latter statement is executed, i is first incremented,
then the new value of i is fetched as though it was going to be used in an enclosing expression. However, since the expression ++i in this case isn't part of a larger
expression, its value is discarded and the next statement is executed. The change impacting the value of i is of course permanent.
49) Since the value of an expression statement is discarded, there's usually no point in using one unless it has a side effect. Example:
i = 1; --> 1 is stored in i then the new value of i is fetched but not used. The side effect here is the value assignment that happened.
i--;   --> The value of i is fetched but not used and i is decremented afterwards. The side effect here is the decrementation that happened.
i*j-1; --> Since i and j are not modified, this statement has no side effects and therefore serves no purpose.
50) Typos can easily lead to "do-nothing" expression statements. A common example is the + instead of = typo which happens frequently since these two characters
occupy the same key on most keyboards. This can lead to a programmer inadvertently writing i + j; instead of i = j; Some compilers can detect meaningless expression
statements and produce warning messages along the lines of "statement with no effect".
51) Since there's no exponentiation operator in C, raising an integer to a small positive integer power is ideally done through repeated multiplication. Example:
i * i * i is equivalent to i raised to the power of 3. Raising a number to a non-integer power should be done through the pow function.
52) The % operator requires integer operands. If we want to apply it to a floating-point number, we should use the fmod function instead.
53) The rules laid out by the C standard to use the / and % operators with negative operands may look complicated on the surface, but they're actually not that hard
to keep up with. In both C89 and C99, the goal of these rules is to ensure that the value of (a/b)*b + a%b is always equal to a, and this is indeed the case for both
standards provided that the value of a/b is representable. The problem arises from the fact that there are two ways for a / b and a % b to satisfy that equality if
either a or b is negative. Example: C89 presents the following case: -9 / 7 could be -1 and -9 % 7 is -2 or -9 / 7 could be -2 and -9 % 7 is 5. In the former case,
(-9/7)*7 + -9%7 is equal to -1*7 + -2 which yields -9. In the latter case, (-9/7)*7 + -9%7 is equal to -2*7 + 5 which yields -9 as well. By the time C99 was introduced,
most CPUs were designed to truncate the result of a division toward 0, so this was written into the standard as the only allowable outcome.
54) An lvalue is an expression that can appear on the left side of an assignment, an rvalue is an expression that can appear on the right. Thus, an rvalue could be a
variable, a constant or a more complex expression.
55) It's safe to assume that v += e is equivalent to v = v + e unless v has a side effect. In fact, evaluating v += e causes v to be evaluated once. Evaluating
v = v + e on the other hand causes v to be evaluated twice. Any side effect caused by the evaluation of v will occur twice in the latter case as opposed to once in the
former case. Example: In the following statement, i is incremented once:
a[i++] += 2;
If we use = instead of +=, we get:
a[i++] = a[i++] + 2;
--> The value of i is now being modified as well as used elsewhere in the statement, so the effect of executing this statement is now undefined. A likely outcome is
that i will be incremented twice but that's not guaranteed.
56) C inherited the ++ and -- operators from Ken Thompson's earlier language B. These operators were created because B's compiler at the time could generate a more
compact translation of ++i than i = i + 1. These two operators have become a deeply ingrained part of C and many of the language's idioms rely on them. With most modern
compilers however, using these operators won't make a compiled program any smaller or faster, they just continue to be popular thanks to their convenience.
57) The increment and decrement operators can be applied to floating-point numbers as well as integers. In practice however, it's fairly rare to increment or decrement
a float variable.
58) We might be tempted to ask when exactly does the increment/decrement happen when the postfix version of ++/-- is used. This is a tough one to answer since it relies
on of the most murky concepts introduced by the C standard: sequence points. The C standard states that "updating the stored value of the operand shall occur between
the previous and the next sequence points. There are many kinds of sequence points in C. The end of an expression statement is one example. This means that by the end
of an expression statement, all increments and decrements within the expression statement must have been performed, the next statement can't begin to execute until this
condition has been met.
59) The logical and, logical or, conditional and comma operators all impose sequence points.
60) Function calls impose sequence points. This means that all arguments of a function must be fully evaluated before the call can be performed. If a function argument
happens to be an expression that uses either the ++ or -- operators, the increment/decrement must occur before the call can take place.
61) An expression represents a value by definition. Example: If i has the value 5, then evaluating i + 1 produces the value 6. If i + 1 is turned into a statement by
appending a semicolon: i + 1; the value of i + 1 will be computed but will be discarded since we have failed to save the value produced by the expression and haven't
used it in a meaningful way.
62) = is an operator in C and produces a value just like any other operator. Example: i = 1; assigns 1 to i and the value of the entire expression is 1. This value gets
discarded though. That's no loss however since the reason for writing the statement in the first place was to modify i which has indeed happened by way of the =
operator's side effect.
*/