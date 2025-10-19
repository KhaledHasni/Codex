/* Takeaways */

/*
1) There are several ways to set up loops in C. The simplest and most fundamental of these is the while statement. It has the following general form:
while(expression) statement. The expression inside the parentheses is called the controlling expression. The statement after the parentheses is called the loop
body. Example:
while(i < n)   //controlling expression
    i = i * 2; //loop body
--> It's worth noting that the parentheses are mandatory and that nothing goes between the right parenthesis and the loop body unlike some other programming
languages that require the word do for example.
2) When a while statement is executed, the controlling expression is evaluated first. If its value is non-zero or true, the loop body is executed and the
controlling expression is evaluated again. The process keeps going on in loops, first testing the controlling expression, then executing the loop body until the
expression eventually becomes false i.e acquires the value zero. Example: Suppose we wanted to write a while loop that computes the smallest power of 2 that's
equal to or greater than a given number n, we could write something that looks like this:
int i = 1;
while(i < n)
    i = i * 2;
--> If we suppose that n has the value 10, this is roughly how the execution flow will happen once the while statement is executed: First the i variable is
declared and initialized to 1 and that value is carried into the while loop. Then the controlling expression is evaluated: is i < n? Since i is 1 then yes.
Therefore the loop body is executed and i becomes 2. The expression is then evaluated again with i being 2 so i is still smaller than n and the loop body is
executed again and i becomes 4. The expression is then evaluated again and it is true so the loop body is executed and i becomes 8. The expression is tested
again and i is still indeed smaller then n so the loop body is executed again and i becomes 16. The expression is then tested once more and this time it's
false since 16 is greater than 10 so we exit from the loop. The idea here is that the loop will keep going as long as the controlling expression is true. As soon
as it becomes false, the loop terminates.
3) C requires that the loop body be a single statement. In practice though, that's merely a technicality since we can enclose multiple statements in braces
essentially turning them into a single compound statement. Example:
while(i > 0) {
    printf("T minus %d and counting\n", i);
    i--;
}
--> Some C programmers always use braces for while loop bodies even when they're not necessary. Example:
while(i < n) {
    i = i * 2;
}
4) Several observations can be made about while loops:
    *) The controlling expression of a while loop is false when the loop terminates. In other words, the controlling expression evaluates to false as the first
statement straight out of the loop is executed.
    *) The body of a while loop may not be executed at all. Since the controlling expression is tested first before entering the loop body for the first time,
it's possible that the latter isn't executed even once.
    *) A while statement can often be written in a variety of ways. Example: The following two while loops are equivalent:
1- while(i > 0) {
       printf("T minus %d and counting\n", i);
       i--;
   }
2- while(i > 0)
       printf("T minus %d and counting\n", i--);
5) A while loop will never terminate if the controlling expression always has a non-zero value. In fact, we sometimes deliberately create infinite loops by using
a non-zero constant as the controlling expression. Example: while(1)...
--> A while statement of this form will continue to execute forever unless its body contains a call to a function that causes the program to terminate or a
statement that transfers control out of the loop like goto, break or return.
6) Recall that the printf function always right-justifies numbers when a field width is specified in the conversion specification. Example:
printf("%10d%10d\n", i, i * i);
7) The second way of setting up loops in C is the do statement which is closely related to the while statement. In fact, a do statement is essentially a while
statement whose controlling expression is tested after each execution of the loop body, not before. It has the following general form:
do statement while (expression);
--> As with while statements, the body of a do loop must be a single statement (possibly compound) and the controlling expression must be enclosed in parentheses.
8) When a do statement is executed, the loop body is executed first then the controlling expression is evaluated for the first time. If the expression has a
non-zero value, the loop body is executed again and then the expression is evaluated once more. The do statement terminates when the controlling expression is
evaluated and has the value zero after the loop body has been executed.
9) A logic implemented using a while loop can always be rewritten, mutatis mutandis, using a do statement. Example: Let's rewrite the countdown while loop from
point 3 using a do statement. So this is the original loop:
while(i > 0) {
    printf("T minus %d and counting\n", i);
    i--;
}
And this is the equivalent do loop:
i = 10;
do {
    printf("T minus %d and counting\n", i);
    --i;
} while(i > 0);
--> The do statement is often indistinguishable from the while statement. The difference between the two is the fact that the body of a do statement is always
executed at least once. The body of a while loop on the other hand is skipped entirely if the controlling expression is initially false. For this reason, it's
always a good idea to use braces for the body of a do statement whether or not they're needed, because a do statement can easily be mistaken for a while statement
in the absence of the braces. Example:
do
    printf("T minus %d and counting\n", i--);
while(i > 0);
--> A reader might think that the word while in this case is the beginning of a new while statement.
10) while statements appear in C programs much more often compared to do statements, but the latter are more appropriate when the body of the loop needs to be
executed at least once. A common example is a loop that computes the number of digits in an integer n. The idea here is to repeatedly divide the integer n by 10
and store the result in n and increment a digit counter inside the loop, as long as n is strictly greater than zero. When the loop terminates, the total number
of divisions performed which would be equal to the value of the digit counter is the result we're looking for. Since every integer has at least one digit, even
0, the do statement has a case for being the more appropriate statement to use here, and this is what it would look like:
int n, digit_counter = 0;
printf("Enter an integer:\n");
scanf("%d", &n);
do {
    n /= 10;
    digit_counter++;
} while(n > 0);
--> If we were to replace this do statement with a while statement, this is what we'd get:
while(n > 0) {
    n /= 10;
    digit_counter++;
}
--> The problem with this statement is that unlike the previous do statement, if n is initially 0, the loop body will never be executed and digit_counter would
end up being 0. Of course we can mitigate that by adding a conditional statement before the loop but that only adds complexity compared to the do statement.
11) The for statement is the last of C's loops. Despite its apparent complexity, it's actually one of the best ways to write loops in many cases. It's ideal for
loops that have a counting variable, but it's versatile enough that it can be made to work in all sorts of cases. It has the following general form:
for(expression1; expression2; expression3) statement; with expression1, expression2 and expression3 being expressions. Example: Suppose we want to rewrite the
countdown loop that we've already written using a while and a do statement, but this time using a for statement:
int i;
for(i = 10; i > 0; i--)
    printf("T minus %d and counting\n", i);
--> When this for statement is executed, the variable i is initialized to 10, then i is tested to see if it's greater than 0. Since it is, the loop's body is
executed and the message is printed then i is decremented. The condition i > 0 is then tested again. The loop body will end up being executed 10 times in total
with i varying from 10 to 1.
12) The for statement is closely related to the while statement. In fact, a for loop can always be replaced with an equivalent while loop except in a few rare
cases:
expression1;
while(expression2) {
    statement
    expression3;
}
--> Based on this equivalence, we can deduce that expression1 in a for statement is an initialization step that's performed only once before the loop begins to
execute, expression2 controls loop termination, in other words the loop continues to execute as long as expression2 has a non-zero value, and expression3 is an
operation to be performed at the end of every iteration.
13) To understand the fine points and edge cases of a for statement, it's always helpful to write an equivalent while loop. For example, in the for loop
mentioned in point 11: int i; for(i = 10; i > 0; i--) printf("T minus %d and counting\n", i);
if we replace i-- by --i, this will have no impact on the behavior of the loop and this becomes very clear once we look at the equivalent while loop:
int i;
while(i > 0) {
    printf("T minus %d and counting\n", i);
    --i;
}
14) Since the first and third expressions in a for statement are executed as statements, their values are irrelevant and they're essentially only useful for
their side effects. As a result, these two expressions are usually assignments and increment/decrement expressions.
15) The for statement is usually the best choice for loops that count up or down. Suppose we want to write a for loop that counts up/down a total of n times, it
will usually have one of the following forms:
    *) Count up from 0 to n-1: for(i = 0; i < n; i++)
    *) Count up from 0 to n: for(i = 1; i <= n; i++)
    *) Count down from n-1 to 0: for(i = n-1; i >= 0; i--)
    *) Count down from n to 1: for(i = n; i > 0; i--)
16) The following is a compilation of some of the most common mistakes beginner C programmers make when writing for loops:
    *) Using < instead of > or vice versa in the controlling expression of the for statement. Based on the idiomatic forms outlined in point 15, it's worth noting
that counting up loops use < or <= while counting down loops use > or >=.
    *) Using == in the controlling expression instead of < , <=, > or >=. A controlling expression needs to be true initially for the loop body to be executed at
least once, then become false eventually for the loop to terminate. A test such as i == n doesn't make sense because it won't be true initially.
    *) Off-by-one errors that happen as a result of writing the controlling expression as i < n instead of i <= n.
17) The for loop is surprisingly even more flexible. Some loops may not need all three expressions that normally control for statements, so C allows us to omit
any or all of them. If the first expression is omitted, no initialization is performed before the loop is executed. Example:
int i = 10;
for(; i > 0; i--)
    printf("T minus %d and counting\n", i);
--> In this example, i has been initialized by a separate assignment, so we can safely omit the first expression in the for statement. It's worth pointing out
that both semicolons should remain enclosed in the parentheses even if we remove some or all of the expressions.
--> If the third expression in a for statement is omitted, it's the loop body's responsibility to ensure that the controlling expression eventually becomes false
for the loop to terminate. Example: We could have written our countdown example in the following manner:
int i;
for(i = 10; i > 0;)
    printf("T minus %d and counting\n", i--);
--> Notice how we compensated for the lack of third statement in the for statement by making sure the counter i is decremented in the loop's body.
--> When the first and third expressions are both omitted, the resulting statement is a while statement in disguise. Example: The following two loops are
equivalent:
1- for(;i < 10;)
       printf("T minus %d and counting\n", i--);
2- while(i < 10)
    printf("T minus %d and counting\n", i--);
--> The while version is obviously clearer and more straightforward and therefore preferable.
--> If the second expression is missing, it defaults to a true value which consequently means the loop will never terminate unless stopped in some other fashion.
Some programmers use this fact to establish an infinite loop: for(;;).
18) In C99, the first expression in a for statement can be replaced by a declaration. This allows us to declare a variable to be used inside the loop body.
Example: for(int i = 0; i < n; i++). The variable i in this case need not be declared prior to this for statement. In fact, even if i has already been declared,
this declaration of i in the first expression of the for statement creates a new version of i that will be used solely inside the loop body.
19) A variable declared by a for statement can't be accessed outside the body of the loop, in other words, it's only visible within the confines of the loop
body.
20) Having a for loop declare its own variable is usually a good idea since it makes programs easier to read and understand. However, if the program needs to be
able to access that variable after loop termination then it's necessary to revert back to the older form of the for statement.
21) A for statement may declare more than one variable, provided that they all have the same type. Example:
for(int i = 0, j = 0; i < n; i++)
22) Sometimes, we might want to write a for statement with two or more initialization expressions or one that increments several variables each time through the
loop. This can be achieved by using a comma expression as the first and third expressions in the for statement. A comma expression has the following general form:
expression1, expression2
where expression1 and expression2 are any two expressions.
--> A comma expression is evaluated in two steps. First, expression1 is evaluated and its value gets discarded. Then expression2 is evaluated and its value is the
value of the whole expression. Since expression1's value will eventually be discarded, it should always have a side effect, otherwise, it will serve no purpose.
Example: Suppose we have two variables i and j that have the values 1 and 5 respectively. When the comma expression ++i, i + j is evaluated, first i is
incremented, then i + j is evaluated resulting in a value of 7 which is the value of the whole comma expression, and of course i now has the value 2.
23) The precedence of the comma operator is less than that of all other operators. Consequently, in the following comma expression: ++i, i + j there's no need
to enclose ++i or i + j in parentheses.
24) Occasionally, we'll need to chain together a series of comma expressions just as we sometimes chain assignments together. It's worth pointing out in this
case that the comma operator is left associative. This means that in the following example: i = 1, j = 2, k = i + j
The compiler will interpret that expression as: ((i = 1), (j = 2)), (k = i + j). Since the left operand in a comma expression is evaluated before the right
operand, the assignments will be performed from left to right.
25) The comma operator is provided for situations where C requires a single expression but we would like to have two or more expressions. In other words, it
allows us to glue together two or more expressions to form a single expression. In this regard, the comma operator is comparable to the concept of compound
statements which allows us to treat a group of statements as a single statement. That being said, the need to glue expressions together doesn't arise that often.
In fact, macro definitions and for loops are the only two places in a C program where we're likely to encounter the comma operator. Example: Suppose that we
want to initialize two variables before entering the body of a for loop. Instead of writing:
sum = 0;
for(i = 1; i < n; i++)
    sum += i;
We can write:
for(sum = 0, i = 1; i < n; i++)
    sum += i;
--> The expression sum = 0, i = 1 first assigns 0 to sum then 1 to i. We can even add more commas to initialize more than two variables.
26) C places no restrictions on the three expressions that control the behavior of a for statement. Although these three expressions usually initialize, test and
update the same variable, there's actually no requirement that they be related in any way. Example: Suppose we want to write a for statement that prints all
integers from 1 up to a given n and their squares, but with a caveat. All three expressions of the for statement must not use the same variable. Here's what we
would do:
int n, i = 1, square, odd = 3;
printf("Enter an integer greater than 1\n");
scanf("%d", &n);
for(square = 1; i <= n; odd += 2) {
    printf("The square of %d is %d", i, square);
    i++;
    square += odd;
}
--> In this example, the for statement initializes one variable (square), tests another (i) and increments a third (odd). The trick here really stems from the
algorithm used to find the squares which relies on avoiding multiplication to find the next square.
27) Loops in C can have an exit point before the loop body (for and while loops for example), an exit point after the loop body (do loops for example) and can
even have exit points in the middle or multiple exit points even. The break statements allow us to achieve just that. The continue statement makes it possible to
skip part of a loop iteration without jumping out of the loop. The goto statement on the other hand allows a program to jump from one statement to another. The
goto statement is rarely used since it can easily be replaced by the break and continue statements.
28) Just as the break statement can be used to transfer control out of a switch statement, it can also be used to jump out of a while, do or for loop. Example:
Suppose we wanted to write a for loop that checks whether a given integer n is prime. The plan might be to repeatedly try dividing n by integers ranging from 2
to n - 1. To optimize our loop even more, it's a good idea to terminate it as soon as a divisor is found since there's really no need for us to try the remaining
possibilities. Once out of the loop, we can use an if statement to determine whether it terminated prematurely, which would mean that n is in fact not prime, or
that it is otherwise. Here's what that program fragment would look like:
int d;
for(d = 2; d < n; d++)
    if(n % d == 0)
        break;
if(d < n)
    printf("%d is divisible by %d\n", n, d);
else
    printf("%d is prime\n", n);
29) The break statement is particularly useful for writing loops whose exit point is in the middle of the loop body rather than at the beginning or the end. A
common example of such loops is loops that read user input and terminate if a particular value is entered. Example:
int n;
for(;;) {
    printf("Enter an integer. Enter 0 to stop\n");
    scanf("%d", &n);
    if(n == 0)
        break;
    printf("%d cubed is equal to %d\n", n, n * n * n);
}
30) The break statement transfers control out of the innermost enclosing while, do, for and switch statement. In other words, if these statements are nested,
the break statement can only escape one level of nesting. Example: Consider the case of a switch statement nested inside a while statement:
while(condition) {
    switch(//something) {
        //something
        break;
        //something
    }
}
--> The break statement in this case transfers control out of the switch statement but not out of the while loop.
31) We can list the following differences between the break and continue statements:
    *) Unlike the break statement which transfers control just past the end of a loop, the continue statement transfers control to a point just before the end
of the loop body.
    *) With break, control leaves the loop altogether, with continue however, it remains within the loop.
    *) The break statement can be used in switch statements and all three forms of loops. The continue statement however is only limited to loops.
32) The continue statement is used to skip past the rest of a loop iteration. Example: Suppose we wanted to write a while loop that would repeatedly read integer
user input and compute the resulting sum. The loop should terminate once we have read 10 non-zero integers. The loop would look something like this:
int i, n = 0, sum = 0;
while(n < 10) {
    scanf("%d", &i);
    if(i == 0)
        continue;
    sum += i;
    n++;
    //the continue statement will jump to here
}
--> Had continue not been available, we would have written the loop as follows:
int i, n = 0, sum = 0;
while(n < 10) {
    scanf("%d", &i);
    if(i != 0) {
        sum += i;
        n++;
    }
}
33) The break and continue statements are both jump statements that transfer control from one point in the program to another. Both are restricted in that the
target of a break is a point just beyond the end of the enclosing loop, while the target of a continue is a point just before the end of the loop body. The
goto statement however is capable of jumping to any statement in a function provided that the statement has a label. A label is just an identifier placed at the
beginning of a statement:
identifier : statement
--> Note that a statement may have more than one label. It's also worth pointing out that C99 places an additional restriction on the goto statement: it can't
be used to bypass the declaration of a variable-length array.
34) The goto statement has the following general form:
goto identifier;
--> Executing the statement goto L; transfers control to the statement following the label L which must be in the same function as the goto statement itself.
Example: Suppose C didn't have a break statement, we could have written the loop from point 28 using a goto statement in the following manner:
int d;
for(d = 2; d < n; d++)
    if(n % d == 0)
        goto done;
done:
if(d < n)
    printf("%d is divisible by %d\n", n, d);
else
    printf("%d is prime\n", n);
35) The goto statement used to be a staple of older programming languages but it's rarely needed nowadays in everyday C programming. The break, continue and
return statements which are essentially restricted goto statements, as well as the exit function are usually enough to handle most situations that might require
a goto in other languages. That being said, the goto statement can still be useful in some cases, especially when trying to exit from nested loops or a switch
statement nested inside a loop for example, or for early function exit commonly known as "guard clause".
36) A break statement immediately following a return statement can never be executed and most compilers will issue a warning when such a mistake is encountered.
37) A statement can be null. In other words, it's completely devoid of symbols except for the semicolon at the end. Example: The following line of code contains
three statements, an assignment to i, a null statement and an assignment to j:
i = 0;  ; j = 1;
38) Null statements are primarily good for one thing which is writing loops whose bodies are empty. Example:
for(d = 2; d < n && n % d != 0; d++)
    ; //empty loop body
--> At the start of each iteration, the condition d < n is tested, if it's false the loop terminates, otherwise the next condition n % d != 0 is tested and if
that's false the loop terminates. It's worth noting that we have put the null statement on a line by itself instead of writing
for(d = 2; d < n && n % d != 0; d++); This is in fact a good habit to have as a C programmer lest someone reading the code gets confused about whether the
statement after the for is in fact its body, when in fact its body is supposed to be empty.
39) It's usually not worth it to try converting an ordinary loop into a loop with an empty body. The new loop will end up being more concise but not more
efficient. In some other cases however, a loop with an empty body is head and shoulders above the alternatives especially when writing loops to read character
data.
40) Inadvertently putting a semicolon after the parentheses in an if, while or for statement creates a null statement therefore ending the if, while or for
statement prematurely:
    *) In the case of an if statement, putting a semicolon after the parentheses creates an if statement that has the same behavior regardless of the value
of its controlling expression. Example:
if(d == 0); //wrong
    printf("Error: division by zero\n");
--> The printf call is performed outside the if statement and will therefore happen regardless of the value of d.
    *) In the case of a while statement, putting a semicolon after the parentheses may create an infinite loop. Example:
i = 10;
while(i > 0); //wrong
{
    printf("T minus %d and counting\n", i);
    --i;
}
It might also result in the loop terminating but the statement that was supposed to be the loop body being executed only once after the loop's termination:
i = 11;
while(--i > 0); //wrong
    printf("T minus %d and counting\n", i);
--> This mistake will cause this program to print "T minus 0 and counting" once.
    *) In the case of a for statement, putting a semicolon after the parentheses causes the statement that should be the loop body to be executed only once.
for(i = 10; i > 0; i--); //wrong
    printf("T minus %d and counting\n", i);
--> This mistake will again cause this program to print "T minus 0 and counting" once.
41) In a loop like the following:
while(i > 0)
    printf("T minus %d and counting\n", i--);
We might be tempted to write the controlling expression as just i, since that will also cause the loop to terminate when i reaches 0. However, that does have
some drawbacks:
    *) It makes the loop harder to read. It particularly makes it difficult to tell whether the i counter is counting up or down. In the original version, that
information can be easily deduced from the i > 0 expression, which makes it clear that we're counting down.
    *) The new loop will behave differently than the original if i initially has negative value. The original will terminate immediately if that's the case while
the new one wouldn't.
42) Point 12 states that a for loop can always be converted into a while loop using a standard pattern except if very rare cases. The most common of these is
when the body of the original for loop contains a continue statement. Example:
n = 0;
sum = 0;
while(n < 10) {
    scanf("%d", &i);
    if(i == 0)
        continue;
    sum += i;
    n++;
}
--> If we try to convert this while loop into a for loop, we might end up with:
n = 0;
sum = 0;
for(n = 0; n < 10; n++) {
    scanf("%d", &i);
    if(i == 0)
        continue;
    sum += i;
}
--> Both loops are not equivalent. Note that when i is equal to 0, the original loop does not increment n while the second one still does.
43) C programmers have traditionally preferred to write for(;;) over while(1) to create an infinite loop since older compilers would force the program to test
the 1 condition at the start of every iteration of the while loop. This is no longer the case with modern compilers however, and there should in theory be no
difference in performance between the two forms.
44) Continue statements are rare in C programming, but they're sometimes very handy. Suppose for example that we wanted to write a loop that would read input
data, make sure that it's valid, and if so apply some processing to it. In this case, continue will turn out to be especially helpful if the validity tests
are complex or numerous. The loop would look roughly like the following:
for(;;) {
    if(test1_fails)
        continue;
    if(test2_fails)
        continue;
    ...
    if(testn_fails)
        continue;
    process_data;
}
45) The goto statement, if used abundantly, can quickly cause code to degenerate into spaghetti code that's hard to understand and a nightmare to modify, since
control will keep jumping all over the place. Goto statements can make a program hard to read because they can jump both forward and backward unlike break and
continue which can only jump forward. A reader will have to attempt to keep track of the control of flow in a program riddled with goto statements which can quickly
turn into chaos. It's also unpleasant to read a code with a lot of goto statements since they have the ability to make a section of code serve more than one
purpose. In fact, a statement that's preceded by a label can be reached either by executing a goto statement or by falling through from the previous statement.
46) The null statement has very few uses other than indicating that the body of a loop is empty. In theory, a null statement can appear anywhere a statement
is allowed. In practice though, there's only one other rare use of the null statement: Since a label can't stand alone and must be followed by a statement, in the
rare event that we want to put a label at the end of a compound statement, we might follow it by a null statement. Example:
{
    ...
    goto end_of_statement;
    ...
    end_of_statement:; //null statement after end_of_statement label
}
47) To draw attention to the fact that a loop has an empty body without using the null statement, some programmers use a dummy continue statement. Example:
for(d = 2; d < n && n % d != 0; d++)
    continue;
while others use an empty compound statement. Example:
for(d = 2; d < n && n % d != 0; d++)
    {}
*/