/* Takeaways */

/*
1) Multiple statements in C, including the if statement must test whether an expression is true or false. Example: An if statement might need to test the expression
i < j with a true value indicating that i is less than j. Many programming languages have a dedicated boolean or logical type for expressions such as i < j. Such a
type will usually have two possible values: true and false. In C however, evaluating whether the expression i < j will yield an integer: 0 for false and 1 for true.
2) C provides relational operators that correspond to the <, >, <= and >= operators of mathematics. They are <, >, <= and >= and they mean less than, greater than,
less than or equal to and greater than or equal to respectively. These operators produce the values 0 for false and 1 for true when used in expressions.
3) C's relational operators can be used to compare numeric values of different types, integers and floating-point numbers, with operands of mixed types allowed.
Example: 1.2 < 5 has the value 1 while 3.7 < 2 has the value 0.
4) C's relational operators have lower precedence than the arithmetic operators. Example: i + j < k - 1 is equivalent to (i + j) < (k - 1).
5) C's relational operators are left associative. This is especially noteworthy as it helps avoid some common pitfalls. Example: The expression i < j < k is perfectly
legal in C but more than likely won't mean what the mathematically-inclined would think it means at first glance. In fact, since C's relational operators are left
associative, i < j < k is equivalent to (i < j) < k. In other words, the expression i < j < k first evaluates i < j, testing whether i is less than j, producing 1 or 0,
which will then be compared to k. It does not test whether j lies between i and k, the correct way to do that would be i < j && j < k.
6) C provides two equality operators that look quite distinctive, unlike its relational operators that are denoted by the same symbols used in many other programming
languages as well as in mathematics. These two equality operators are the "equal to" operator denoted by two adjacent '=' symbols not just one, since "=" denotes the
assignment operator, and the "not equal to" operator "!=".
7) C's equality operators are also left associative and produce 0 for false or 1 for true as their result.
8) C's equality operators have lower precedence than the relational operators. Example: The expression i < j == j < k is equivalent to (i < j) == (j < k) which is true
if both i < j and j < k are both either true or false.
9) Some programmers like to take advantage of the fact that C's relational and equality operators return integer values when applied to operands. Example: The
expression (i >=j ) + (i == j) is equal to 0, 1 or 2 depending on whether i is less than, greater than or equal to j respectively. This however is usually not a good
idea since tricks like this make a program hard to read and understand.
10) We can build complex logical expressions based on simpler ones by taking advantage of C's logical operators: and, or and not, denoted &&, || and ! respectively.
The "not" ! operator is unary while the other two are binary.
11) C's logical operators produce either 0 or 1 as their result. Their operands will usually have the value 0 or 1 as well, although that's not a strict requirement.
The logical operators treat any non zero value as a true value and any zero value as a false value.
12) This is a brief rundown of how the logical operators behave in C:
    *) !expression has the value 1 if expression has the value 0.
    *) expression1 && expression2 has the value 1 if both expression1 and expression2 has non zero values.
    *) expression1 || expression2 has the value 1 if either expression1 or expression2 (or both) has a non zero value.
    *) In all other cases, these operators produce the value 0.
13) The && and || operators perform short-circuit evaluation of their operands. What this means is that they'll first evaluate the left operand then the right operand.
If the value of the whole expression can be deduced from the value of the left operand alone, then the right operand isn't evaluated at all. Example: Consider the
following expression: i != 0 && (j / i > 0). Evaluating this expression goes through evaluating the subexpression i != 0 first. If indeed i is not equal to 0 then the
second subexpression (j / i > 0) has to be evaluated to determine whether the entire expression is true or false. However, if i is equal to 0 then there's no need to
evaluate (j / i > 0) since the entire expression is false regardless of its value. The advantage of short-circuit evaluation here is to avoid a division by zero.
14) Short-circuit evaluation of expressions containing the && and || operands may cause some side effects not to occur. Example: In the following expression:
i > 0 && ++j > 0, j is apparently incremented as a side effect of evaluating the whole expression, but that's not always the case. In fact, if i > 0 is false, then
++j > 0 is not evaluated at all and j is therefore not incremented. This problem can be fixed by swapping both subexpressions: ++j > 0 && i > 0, or by incrementing j
separately.
15) The ! operator has the same level of precedence as the unary plus and minus operators. It's also right associative.
16) The && and || operators have a lower level of precedence compared to the relational and equality operators. Example: i < j && k == m is equivalent to
(i < j) && (k == m). && and || are left associative.
17) The if statement allows a program to choose between two alternatives by testing the value of an expression. In its simplest form, it looks something like this:
if (expression) statement. It's important to point out the parentheses in the if statement that surround the expression. These are mandatory, they're part of the if
statement, not part of the expression. It's also worth pointing out that if statements in C don't keywords like "then" to introduce the statement like some other
programming languages would do.
18) When an if statement is executed, the expression enclosed in parentheses in evaluated. If its value is non zero which C interprets as true, the statement after
the parentheses is executed. Example:
if(lines_num == MAX_LINES)
    lines_num = 0;
--> The statement lines_num = 0; is executed if the expression lines_num == MAX_LINES is true.
19) A classic C mistake can happen as a result of inadvertently using the = operator instead of == in an if condition. Example:
    *) if(i == 0) tests whether i is equal to zero.
    *) if(i = 0) assigns zero to i then tests whether the result is non zero. In this case, the test always fails.
--> This confusion is perhaps C's most common error, probably because the = operator means "is equal to" in mathematics and in some other programming languages. Some
compilers will issue a warning when they encounter a = where a == is normally expected.
20) Sometimes, an expression in a if statement will have to test whether a numeric variable falls within a particular range of values. Example: If we want to test whether
0 <= i < n, we could write the following: if(0 <= i && i < n). To test the opposite condition i.e is i outside the range [0,n[, we could write: if(0 > i || i >= n).
21) The if statement template outlined in point 17 makes use of a singular statement. If we want an if statement to control two or more statements, we would have to use
a compound statement. A compound statement has the form {statements}. By enclosing a group of statements in braces, we can force the compiler to treat them as a single
statement. Example: {lines_num = 0; page_num++;}. It's worth pointing out that each inner statement in a compound statement still has to end with a semicolon but the
compound statement itself doesn't. Example: This is what a compound statement would look like when used with an if statement:
if(lines_num == MAX_LINES) {
    lines_num = 0;
    page_num++;
}
--> Compound statements are also common in loops and other places where the C syntax requires a single statement but we want more than one.
22) An if statement may also have an else clause which will be executed if the expression in parentheses evaluates to zero. An if statement with an else clause has the
following template: if (expression) statement else statement. Example:
if(i > j)
    max = i;
else
    max = j;
--> Notice the semicolons at the end of both inner statements.
23) When an if statement has an else clause, many C programmers will align it with the if at the beginning and will indent the statements inside both if and else clauses.
However, if the inner statements are short, they can be put on the same line as the if and else. Example:
if(i > j) max = i;
else max = j;
24) There are no restrictions on the kinds of statements that can appear inside an if statement. In fact, multiple if statements can even be nested inside each other.
Example: The following example fetches the largest value from among the three variables i, j and k and stores it in max:
if(i > j)
    if(i > k)
        max = i;
    else
        max = k;
else
    if(j > k)
        max = j;
    else
        max = k;
--> If statement can be nested to any depth. This is where aligning each else with its matching if becomes ever so valuable to make the nesting stand out and render the
code easier to read. If the nesting is still confusing, we can add braces to remove all doubt:
if(i > j) {
    if(i > k)
        max = i;
    else
        max = k;
} else {
    if(j > k)
        max = j;
    else
        max = k;
}
25) Adding braces to statements even when they're not strictly needed, is analogous to using parentheses in expressions. They both make a program more readable and lower
the risk of the compiler interpreting it in ways different than we thought.
26) Some programmers use as many braces as possible inside if and iteration statements by including a pair of braces for every if and else clause:
if(i > j) {
    if(i > k) {
        max = i;
    } else {
        max = k;
    }
} else {
    if(j > k) {
        max = j;
    } else {
        max = k;
    }
}
--> This technique makes a program easier to modify because a statement can easily be added to if and else clauses inside the set of enclosing braces. It also helps mitigate
the risk of errors that can result from forgetting to enclose statements in a set of braces when adding a statement to an if or an else clause.
27) A cascaded if statement is one way to test a series of conditions and stop as soon as one of them is true. Example: The following cascaded if statement tests whether n
is less than, equal to or greater than 0:
if(n < 0)
    printf("n is less than 0\n");
else
    if(n == 0)
        printf("n is equal to 0\n");
    else
        printf("n is greater than 0\n");
--> In this example, the second if statement is nested inside the first. That being said, C programmers don't usually indent it, opting instead for aligning each else with
the original if:
if(n < 0)
    printf("n is less than 0\n");
else if(n == 0)
    printf("n is equal to 0\n");
else
    printf("n is greater than 0\n");
--> This gives the distinctive appearance of the cascaded if statement that's well known and idiomatic:
if(expression)
    statement
else if(expression)
    statement
else if(expression)
...
else
    statement
28) In the cascaded if statement template from point 27, the last else clause is not always present. The indentation structure in the cascaded statement's template avoids
the excessive number of indentations when the number of expressions to evaluate is large. It also gives visual reassurance that the processing of the if statement is nothing
more than a series of tests.
29) The cascaded if statement is not a new kind of if statement. It's just an ordinary if statement that has another if statement as its else clause and so on.
30) Cascading if statements can cause a notorious problem known as the dangling else problem. Example:
if(x != 0)
    if(y != 0)
        res = x / y;
else
    printf("Error: y is equal to 0\n");
--> The problem here relates to the else clause. It's not at first obvious to which if clause it belongs. The indentation suggests that it belongs to the outer if clause,
but C has a rule that states that an else clause belongs to the nearest if clause that's not already paired with an else. So in the previous example, the else clause
actually belongs to the inner if clause. A more appropriate indentation structure would look something like this:
if(x != 0)
    if(y != 0)
        res = x / y;
    else
        printf("Error: y is equal to 0\n");
--> To pair the else clause in the previous example with the outer if clause, we could enclose the inner if statement in braces:
if(x != 0) {
    if(y != 0)
        res = x / y;
} else
    printf("Error: y is equal to 0\n");
31) C's if statement allows a program to perform one of two actions depending on the value of a condition. C also provides an operator that allows an expression to produce
one of two values depending on the value of a condition. This is called the conditional operator and it consists of two symbols ? and : that must be used together in the
following manner: expression1 ? expression2 : expression3 where expression1, expression2 and expression3 can be expressions of any type. The resulting expression is said to
be a conditional expression.
32) The conditional operator is unique among C operators in the number of operands it takes. It takes three operands as opposed to one or two which explains why it's often
called a ternary operator.
33) The expression expression1 ? expression2 : expression3 can be read as follows: "If expression1 then expression2 else expression3". The whole expression is evaluated in
stages. expression1 is evaluated first. If its value is not zero, then expression2 is evaluated and its resulting value is the value of the entire conditional expression.
If expression1's value is zero however, then expression3 is evaluated and its value is the value of the whole conditional. Example:
int i, j, k;
i = 1;
j = 2;
k = i > j ? i : j;       //k is now 2
k = (i > 0 ? i : 0) + j; //k is now 3
--> In the previous example, the conditional expression i > j ? i : j returns the value of either i or j and it gets assigned to k depending on which one among i and j is
larger. Since j is larger than i when the conditional is evaluated, i > j will fail and the value of the whole conditional is the value of j, 2 which gets assigned to k. In
the second assignment to k, i > 0 succeeds so the whole conditional evaluates to the value of i which happens to be 1, then j is added and the resulting value, 3 gets
assigned to k.
34) The precedence of the conditional operator is lower than that of arithmetic operators and higher than that of the assignment operator. This makes the parentheses in the
previous example in point 33 mandatory.
35) Conditional expressions make programs harder to read and understand so some programmers would usually advise against using them. However, there are places where it's hard
to argue against using them. Examples:
    *) Instead of writing:
if(i > j)
    return i;
else
    return j;
we would write: return i > j ? i : j;
    *) Instead of writing:
if(i > j)
    printf("%d\n", i);
else
    printf("%d\n", j);
we would write: printf("%d\n", i > j ? i : j);
36) Conditional expressions are common in certain kinds of macro definitions.
37) C lacked a proper boolean type for years and there is none defined in the C89 standard. Many programs need variables that can store either true or false which makes for
a major drawback. One way to work around this C89 limitation is to declare an int variable and assign it 0 and 1 for false and true respectively. This however doesn't help
with program readability since it's not obvious that 0 and 1 stand for false and true respectively and there's nothing preventing us from using the declared int variable to
store other values. For this reason, it's common for C89 programmers to define macros with names such as TRUE and FALSE:
#define TRUE  1
#define FALSE 0
int flag;
flag = TRUE;
if(flag  == TRUE)...
38) Based on the previous example, to test whether the variable flag is true or false, some programmers would write if(flag) instead of if(flag == TRUE). This newer version
is better since it's more concise and it will still work correctly if flag has a value other than 0 or 1. Conversely, to test whether flag is false we can write
if(flag == FALSE) or if(!flag).
39) Some C89 programmers will go as far as creating a macro that will serve as a type:
#define BOOL int
--> BOOL can be used instead of int when declaring Boolean variables: BOOL flag; This makes it clear for whoever reads the program that flag isn't an ordinary int variable
and instead represents a Boolean condition. The compiler will still treat it as an integer variable under the hood though. That being said, there are better ways to simulate
Boolean types in C89 using type definitions and enumerations.
40) C99 remedies the lack of a Boolean type issue by providing the _Bool type. In this C version, a Boolean variable can be declared by writing: _Bool flag;
41) _Bool is an unsigned integer type so a _Bool variable is just an integer variable in disguise. Unlike an ordinary integer variable though, a _Bool variable can only be
assigned 0 or 1. Attempting to store a non zero value into a variable of type _Bool will cause the variable to be assigned 1. Example:
_Bool flag;
flag = 5; //flag is assigned 1
42) A _Bool variable can be printed. It's also legal to perform arithmetic on _Bool variables, although that's usually not a good idea. It's also common practice to test
_Bool variables in if statements. Example: if(flag) will test whether flag is 1.
43) C99 also provides a new header <stdbool.h> that makes it easier to work with Boolean values. This header defines a macro called bool that stands for _Bool. If <stdbool.h>
is included, we can write: bool flag; which is equivalent to writing _Bool flag;
44) The <stdbool.h> header also supplies macros called true and false that expand to 1 and 0 respectively making it possible to write:
bool flag;
flag = true;
flag = false;
45) When trying to compare an expression against a series of values to see which one it currently matches, a cascaded if statement can be appropriate. As an alternative though,
C provides the switch statement. Example:
switch (grade) {
    case 4:  print("Excellent");
             break;
    case 3:  print("Good");
             break;
    case 2:  print("Average");
             break;
    case 1:  print("Poor");
             break;
    case 0:  print("Failing");
             break;
    default: print("Illegal grade");
             break;
}
--> When this statement is executed, the value of grade is tested against 4, 3, 2, 1 and 0. If grade evaluates to 4 for example, "Excellent" will be printed and the break
statement will be executed, therefore transferring control to the statement right after the switch. If grade doesn't evaluate to any of the listed values, the default case
applies and "Illegal grade" is printed.
46) A switch statement is usually easier to read than a cascaded if statement, and it's often faster to execute as well, especially when the number of values to test against
is substantial.
47) In its most common form, the switch statement has the following template:
switch (expression) {
    case constant_expression : statements
    ...
    case constant_expression : statements
    default: statements
}
48) The switch statement is made of several components:
    *) Controlling expression: The word switch is to be followed by an integer expression enclosed in parentheses. Characters can be used here since they're treated as
integers in C. Strings and floating-point numbers don't qualify however.
    *) Case labels: Each case begins with a label of the form "case constant_expression :". A constant expression is much like any other ordinary expression except that
it must not contain variables and function calls. 5 for example is a constant expression, and so is 5 + 3. On the other hand, n + 2 is not a constant expression if n is
a variable. If n is a macro that expands to an integer constant, then that's a different story. The constant expression in a case label must evaluate to an integer. Characters
are also acceptable.
    *) Statements: After each case labels comes a set of statements. Any number of statements can be used, and there's no requirement to enclose them in a set of braces
either. The last statement in each group is usually, but not necessarily, the break statement.
49) Duplicate case labels in a switch statement are not allowed.
50) The order of case labels in a switch statement is not important. In particular, the default case label doesn't have to come last.
51) Only one constant expression may follow the keyword case. Conversely, more than one case label can precede the same group of statements. Example:
switch (grade) {
    case 4:
    case 3:
    case 2:
    case 1: printf("Passing");
            break;
    case 0: printf("Failing");
            break;
    default: printf("Illegal grade");
            break;
}
52) Some programmers put several case labels on the same line when performing a case fall-through:
switch (grade) {
    case 4: case 3: case 2: case 1:
            printf("Passing");
            break;
    case 0: printf("Failing");
            break;
    default: printf("Illegal grade");
            break;
}
53) C doesn't offer a way of writing a case label that denotes a range of values in a switch statement.
54) A switch statement is not required to have a default case. If the default case is omitted and the controlling expression doesn't evaluate to any of the case labels,
control is simply passed to the next statement after the switch.
55) Executing a break statement causes the program to break out of the switch statement and resume execution at the first statement after the switch. The reason this
statement is needed boils down to the fact that the switch statement is really just a form of computed jump. When the controlling expression is evaluated, control jumps to
the case label that matches the computed value. In this sense, a case label is nothing more than a marker indicating a position within the switch statement. Once the last
statement in a case has been executed, control falls through to the first statement in the next case and the case label is completely ignored. In the absence of break or
some other jump statement, control will keep flowing from one case to the next. Example:
switch (grade) {
    case 4:  print("Excellent");
    case 3:  print("Good");
    case 2:  print("Average");
    case 1:  print("Poor");
    case 0:  print("Failing");
    default: print("Illegal grade");
}
--> If grade evaluates to 3, the message printed will be "GoodAveragePoorFailingIllegal grade".
56) Forgetting to use break in a switch statement can be done intentionally, but it's usually done out of forgetfulness. This is actually one of C programmers' most common
mistakes.
57) It's usually a good idea to point out any deliberate omission of break in a switch statement and signal in a comment that we are falling through on purpose. Example:
switch (grade) {
    case 4: case 3: case 2: case 1:
            num_passing++;
            //Fallthrough
    case 0: total_grades++;
            break;
}
--> Had we not added the comment, someone else might think this was an oversight and will try to fix it by adding an actually unwanted break.
58) The last case in a switch statement never needs a break, but it's common practice to add one nevertheless to make sure no missing break issues happen in the future if we
are to add other cases.
59) Some programmers like to be defensive by habitually writing something like if(0 == i) instead of if(i == 0). Suppose that == was inadvertently written as = in one of
these instances, the compiler will produce an error since it's not possible to assign a value to 0. This trick has two disadvantages though:
    *) It makes programs look unnatural.
    *) It can only be valuable if one of the two operands of the equality operator is not an lvalue.
60) Many compilers are capable of detecting dubious uses of the assignment operator inside if conditions. The GCC compiler for example will perform this check if -Wall (all
warnings is selected) or if the -Wparentheses option is selected. GCC allows the programmer to suppress the warning by enclosing the if condition in a second set of
parentheses. Example: if((i == j))...
61) There are mainly four styles of indentation and brace placement in if statements:
    *) The K&R style used in Kernighan and Ritchie's the C programming language: The left brace appears at the end of a line. Example:
if(num_lines == MAX_LINES) {
    lines_num = 0;
    page_num++;
}
--> This style keeps a program's text relatively compact by not putting the left brace on a line by itself. Some say that this is disadvantageous since the left brace doesn't
stand out and cannot be easily spotted. Others will counter argue that the indentation of the inner statements makes it clear where the left brace should be. The K&R style is
also popular in Java, not just C.
    *) The Allman style named after Eric Allman the author of sendmail and other UNIX utilities: Puts the left brace on a line by itself which makes it easier to visually
check that braces come in pairs. Example:
if(num_lines == MAX_LINES)
{
    lines_num = 0;
    page_num++;
}
    *) The Whitesmiths style made popular by the Whitesmiths C compiler: Dictates that braces should be indented. Example:
if(num_lines == MAX_LINES)
    {
    lines_num = 0;
    page_num++;
    }
    *) The GNU style used in software developed by the GNU project: Dictates that braces should be indented, and inner statements should be further indented. Example:
if(num_lines == MAX_LINES)
    {
        lines_num = 0;
        page_num++;
    }
--> Which style to use when writing C code is purely a matter of taste. Which style to pick is of much less importance than applying it consistently.
62) When int and float types are mixed in a conditional expression, the result of the whole expression will be of type float. Example: i > 0 ? i : f; Assuming that i and f
are int and float variables, if i > 0 is true, the value of the entire expression will be the value of i after conversion to float type.
63) The _Bool type name was chosen in C99 instead of other more obvious names such as bool or boolean because existing C programs might have already defined those names
which will cause these older programs not to compile anymore. _Bool makes sense since the C89 standard dictates that names beginning with an underscore followed by an
uppercase letter are reserved for future use and shouldn't be used.
64) A switch statement may contain labels that aren't preceded by the word case which might lead to a somewhat common pitfall. Example: Consider the case where we might
misspell the word default inside a switch statement:
switch(...) {
...
defualt:...
}
--> The compiler might not detect the error assuming that defualt is a regular label.
65) There are two common indentation structures in switch statements:
    *) Putting the statements in each case after the case label. Example:
switch (grade) {
    case 4:  print("Excellent");
             break;
    case 3:  print("Good");
             break;
    case 2:  print("Average");
             break;
    case 1:  print("Poor");
             break;
    case 0:  print("Failing");
             break;
    default: print("Illegal grade");
             break;
}
--> If each statement consists of a single action, the break statement can even be added on the same line as the action. Example:
switch (grade) {
    case 4:  print("Excellent"); break;
    case 3:  print("Good"); break;
    case 2:  print("Average"); break;
    case 1:  print("Poor"); break;
    case 0:  print("Failing"); break;
    default: print("Illegal grade"); break;
}
--> This indentation scheme is good for statements that are relatively short and few in number.
    *) Putting the statements under the case label and making sure to indent the statements to make the case label stand out. Example:
switch (grade) {
    case 4:
        print("Excellent");
        break;
    case 3:
        print("Good");
        break;
    case 2:
        print("Average");
        break;
    case 1:
        print("Poor");
        break;
    case 0:
        print("Failing");
        break;
    default:
        print("Illegal grade");
        break;
}
--> This indentation scheme is good for statements that are complex and numerous.
*/