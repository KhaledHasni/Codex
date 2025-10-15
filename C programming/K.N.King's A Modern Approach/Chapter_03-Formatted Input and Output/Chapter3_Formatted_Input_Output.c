/* Takeaways */

/*
1) The printf function is designed to print the contents of a string known as the format string. It offers the possibility of inserting values at specified points
in the string. When it's called, it must be supplied with the format string along with any values that are to be inserted into it during printing.
2) The general format of a printf call looks like this: printf(string, expression1, expression2, expression3,...);
--> There's no limit on the number of values that can be printed by a single printf call. The values printed can be constants, variables or more complicated
expressions.
3) A printf format string can contain regular characters and conversion specifications that start with the % character. The latter serve as placeholders for values
to be inserted during printing.
4) The information that follows a conversion specification in a printf format string indicates how the value to be inserted during printing is converted from
its internal binary form to its printed character form. This explains why these placeholders are called conversion specifications. Example: The %d conversion
specification instructs printf to convert an int value from binary form to a string of decimal digits. The %f conversion specification does the same for float
values.
5) Ordinary characters in a printf format string are printed exactly the way they show up in the format string while conversion specifications are replaced by
the values to be printed. Example:
int i, j;
float x, y;
i = 10;
j = 20;
x = 2.457f;
y = 7.264f;
printf("i = %d, j = %d, x = %f, y = %f\n", i, j, x, y);
--> This printf call will produce the following output: i = 10, j = 20, x = 2.457000, y = 7.264000. The ordinary characters in the format string are simply copied
to the output line while the four conversion specifications are replaced by the values of the variables i, j, x and y in that order.
6) C compilers are not required to check that the number of conversion specifications in a format string matches the number of output items. Example: The following
printf call has more conversion specifications than actual values to be inserted in the string:
printf("%d %d\n", i); //wrong
--> In this case, printf will print the value of i correctly then replace the second conversion specification with a meaningless integer value. A printf call with
too few conversion specifications will exhibit similar issues. Example:
printf("%d\n", i, j); //wrong
--> In this case, printf will print the value of i correctly but won't print the value of j at all.
7) C compilers are not required to check that a conversion specification in a format string is appropriate for the type of value that we're trying to insert in
its place. If a conversion specification is misused in that sense, the printf call will simply produce meaningless output. Example: The following printf call
tries to print an integer and a float value in the wrong order:
int i;
float x;
printf("%f %d\n", i, x); //wrong
--> printf will faithfully display the format string, so it will print a float followed by an integer. In this case, both values will be meaningless.
8) Conversion specifications give the programmer control over the appearance of output by allowing the use of formatting information. For example, the %.1f
conversion specification can be used to display a float value with one digit after the decimal point.
9) A more generalized form of conversion specifications would look like %m.px or %-m.px where m and p are integer constants and x is a letter. Both m and p are
optional. If p is missing, then the period separating m and p is also dropped. Example: Try identifying m and p in the following conversion specifications:
%10.2f --> m is 10, p is 2 and x is f
%10f --> m is 10, p is omitted and x is f
%.2f --> p is 2, m is omitted and x is f
10) m in the generalized form of a conversion specification outlined in point 9 is called the "minimum field width". It specifies the number of characters to
print. If the value to be printed requires fewer than m characters, the value is right-justified within the m-sized output field. This is achieved thanks to
additional spaces added before the value that actually fill out the m-sized field by padding it. Example: The specification %4d would display the number "123" as " 123".
If on the other hand, the value to be printed requires more than m characters, the field width automatically expands to the required size. Example:
The specification %4d would display the value "12345" as exactly that and no digits are lost. By putting a minus sign in front of the minimum field width m, output
will be left-justified inside the output field. Example: The specification %-4d would display the value "123" as "123 ".
11) x in the generalized form of a conversion specification outlined in point 9 is called the "conversion specifier". It indicates which conversion should be
applied to the value before it's printed. The most common conversion specifiers for numbers are:
    *) d: Displays an integer in decimal, base 10 form. In this case, p also known as the precision, indicates the minimum number of digits to display. If the
integer value being displayed contains fewer digits than the precision value, zeros are added at the start. If the precision value is omitted in this case, it's
assumed to have the value 1 which basically means %d is the same as %.1d.
    *) e: Displays a floating-point number in exponential format also known as scientific notation. The precision p in this case indicates how many digits
should appear after the decimal point with 6 being the default value. If p is zero, the decimal point is not displayed at all.
    *) f: Displays a floating-point number in fixed decimal format without an exponent. The precision p in this case has the same meaning as with the e specifier.
    *) g: Displays a floating-point number in either an exponential or fixed decimal format depending on the number's size. The precision p in this case indicates
the maximum number of significant digits (digits before the decimal point) to be displayed. In contrast to the f conversion, the g conversion won't show trailing
zeros. If the value to be printed has no digits after the decimal point, g doesn't display the decimal point.
12) The g floating-point specifier is especially useful for displaying numbers whose sizes can't be predicted when the program is being written or which have a
tendency to vary widely in size. In fact, when used to display a moderately large or moderately small number, the g specifier will use the fixed decimal format.
On the other hand, when it's used to display a very large or very small number, it will switch to the exponential format so that the output will require fewer
characters.
13) There are many specifiers besides %d, %e, %f and %g.
14) Escape sequences allow strings to contain characters that would otherwise cause issues for the compiler including non-printing control characters and characters
that have a special meaning to the compiler such as " for example. Examples of escape sequences include:
\a --> Alert (bell)
\b --> Backspace
\n --> New line
\t --> Horizontal tab
--> These escape sequences are designed to represent actions to be performed upon printing, when used in printf format strings:
    *) \a causes an audible beep on most machines.
    *) \b causes the cursor to move back one position.
    *) \n advances the cursor to the beginning of the next line.
    *) \t causes the cursor to move to the next tab stop.
15) A string may contain any number of escape sequences. Example: The following string contains six escape sequences:
printf("Item\tUnit\tPurchase\n\tPrice\tDate\n");
--> This printf call produces the following output:
Item    Unit    Purchase
        Price   Date
16) A common escape sequence is \" which represents the " character. The " character usually delimits the beginning and end of a string, which means it can't be
used in the middle of a string without the use of this escape sequence. Example: The following statement: printf("\"Hello\""); produces the following output:
"Hello".
17) The \ character can't be used on its own in a string since the compiler will assume that it's the beginning of an escape sequence. To print a single \
character, we have to use two \ characters. Example: printf("\\"); will produce the following output: "\".
18) scanf reads input in a specified format just as printf prints output in a specified format. scanf also uses format strings that can contain regular characters
and conversion specifications just as printf format strings. The conversions allowed with scanf are essentially the same as those allowed with printf.
19) In many cases, a scanf format string will contain conversion specifications only. Example:
int i, j;
float x, y;
scanf("%d%d%f%f", &i, &j, &x, &y);
--> The user will be prompted to provide input. Suppose they enter the following line: 1 -20 .3 -4.0e3, the scanf function will read the whole line, converting
its characters to the numbers they represent then assign 1, -20, 0.3 and -4000.0 to i, j, x and y respectively.
--> It's worth noting that tightly packed format strings like the one in the previous example "%d%d%f%f" are common with scanf calls but less so with printf calls.
20) scanf contains two inherent built-in traps:
    *) Just like printf, it's the programmer's responsibility to check that the number of conversion specifications in a scanf format string matches the number of
input variables and that each conversion is appropriate for the corresponding variable. The compiler is under no obligation to check for any possible mismatch.
    *) There's a & operand that usually precedes variables in a scanf call. This operator is usually required and it's up to the programmer to remember to use it.
Failing to use it in front of a variable name in a scanf call will have unpredictable results, the most common among which is a program crash. The very least of
our worries in that case will be the fact that the input value won't be stored in the variable. The latter will retain its old value which may be meaningless if
it was never initialized. Omitting the & operator is a very common mistake which can be detected and pointed out by some compilers that might produce a warning
message along the lines of "format argument is not a pointer".
21) Calling scanf is a powerful way to read data, but it comes with a fair amount of risk if used incorrectly. Some C programmers avoid using it altogether instead
opting for more indirect ways of reading input such as reading data in character form and converting it to numeric form later.
22) scanf is in a way a pattern-matching function that tries to match up groups of input characters with conversion specifications.
23) Just like printf, scanf is controlled by the format string. When it's called, scanf begins processing the information in the string starting at the left. For
each conversion specification encountered in the format string, scanf tries to locate an item of the appropriate type in the input data, skipping black space if
necessary. It then reads the item found and stops when it rencounters a character that can't possibly belong to the item. If the item was read successfully, scanf
will continue to process the format string. However, if an item is not successfully read, scanf will return immediately without looking at the rest of the format
string or the remaining input data.
24) As it searches for the beginning of a number, scanf skips over white-space characters (space, horizontal and vertical tab, form-feed and new-line characters).
Consequently, input numbers can be put on a single line or spread out over several lines. Example: Consider the following scanf call:
scanf("%d%d%f%f", &i, &j, &x, &y);
--> Suppose that the user inputs three lines like this:
  1
-20    .3
 -4.0e3
scanf will see one continuous stream of characters:"  1*-20    .3* -4.0e3" with * denoting the new line character in this case. Since scanf skips over white-space
characters as it looks for the beginning of each number, scanf will manage to read the numbers successfully. In the stream of characters scanf will read based on
the previous example, we can help drive the point home by writing s under skipped characters and r under read characters:
  1*-20    .3* -4.0e3
ssrsrrrssssrrssrrrrrr
25) When reading an input line, scanf will actually peek at the final new line character without reading it. This character will be the first character read by the
next scanf call.
26) When asked to read an integer, scanf first searches for a digit, a plus or a minus sign, it then continues reading digits until it reaches a nondigit. When
asked to read a floating-point number, scanf first searches for:
    *) a plus or minus sign. This is optional.
    *) a series of digits possibly containing a decimal point followed by an exponent (this is optional as well). An exponent consists of the letter e or E, an
optional sign and one or more digits.
27) The %f, %e and %g conversions are interchangeable when used with scanf. All three abide by the same rules for recognizing a floating-point number.
28) When scanf encounters a character that can't be part of the current item, the character gets put back to be read during the scanning of the next input item or
during the next scanf call. Example: If we consider the following scanf call: scanf("%d%d%f%f", &i, &j, &x, &y); If the user enters the following input:
1-20.3-4.0e3* (* is the new line character), here's how it would be processed:
    *) The first conversion specification %d instructs scanf to read an integer. scanf will skip over white space characters. The first nonblank input character
is 1. scanf recongnizes that integers can begin with 1, so it reads the next character -. Recognizing that a minus sign can't appear in the middle of an integer,
scanf stores 1 in i and puts back the minus sign character.
    *) The second conversion specification %d instructs scanf to read an integer. scanf will then read - (that was put back already), 2, 0 and the decimal point.
Since an integer can't contain a decimal point, scanf will store -20 in j and will put the . character back.
    *) The third conversion specification %f instructs scanf to read a floating-point number. scanf will then read '.', '3' and '-'. Since a floating-point number
can't contain a minus sign after a digit, scanf will store 0.3 in x and put the - character back.
    *) The fourth conversion specification %f instructs scanf to read a floating-point number. scanf will then read -, 4, ., 0, e, 3 and the new line character.
Since a floating-point number can't contain a new line character, scanf will store -4000.0 in y and puts the new line character back.
--> In this example, scanf was able to match every conversion specification in the format string with an input item. Since the new line character wasn't read, it
will be left for the next scanf call.
29) The pattern-matching aspect of the scanf function can be pushed even more to the limit by writing format strings that contain ordinary characters as well as
conversion specifications. The action taken by scanf when it encounters an ordinary character in a format string depends on whether or not that character is a
white-space character.
    *) When scanf encounters one or more white-space characters in a format string, it will repeatedly read white-space characters from the input until it reaches
a non white-space character which gets put back. It's important to point out that the number of white-space characters in the format string is irrelevant. In other
words, a single white-space character in the format string will match any number of white-space characters in the input. Similarly, a white-space character in the
format string doesn't force the input to actually have white-space characters. A white-space character in the format string will match any number of white-space
characters in the input, including none.
    *) When scanf encounters a non white-space character in a format string, it will compare it to the next input character. If there's a match between the two,
scanf discards the input character and continues processing the format string. If there's no match, scanf will put the input character back and abort without
further processing the format string or reading input. Example: Suppose we have this scanf call: scanf("%d/%d"); and the user enters the following inputs:
        1] " 5/ 96" --> scanf skips the first space looking for an integer, matches %d with 5, matches / with /, skips the next space looking for a second integer
    then matches the second %d with 96.
        2] " 5 / 96" --> scanf skips the first space looking for an integer, matches %d with 5 then attempts to match the / in the format string with the space in
    the input. Since there's no match, scanf will put the space character back and the " / 96" character stream will remain to be read by the next scanf call.
    scanf will then abort the whole scan operation. If we wanted to allow a space after the first integer to be accepted by scanf, we should have used the "%d /%d"
    format string instead.
30) Despite calls of printf and scanf appearing similar, there are significant differences between the two functions.
    *) One common mistake is to use the & operator in front of variables in a printf call. Example:
printf("%d", &i); //wrong
--> This is usually not a big deal since it will be easy to spot. printf will print an unexpected number instead of the actual value of i.
    *) Since scanf skips white-space characters when looking for data items, there's usually no need for a scanf format string to include characters other than
conversion specifications. Assuming that scanf format strings should look like printf format strings could lead to serious mistakes. Example: In the following
scanf call: scanf("%d, %d", &i, &j); scanf will first try to match the %d conversion to an integer in the input, which it will store in the variable i. It then
tries to match the next character in the format string which is a comma with the next input character. If the latter doesn't happen to be a comma, scanf will
abort the scan operation and terminate without reading the value corresponding to the j variable.
31) Putting a new-line character at the end of a scanf format string is usually a bad idea, despite them being common in printf format strings. To scanf, a
new-line character in a format string is equivalent to a space and they both cause scanf to advance to the next non white-space character. Example: For the
following scanf call: scanf("%d\n"); scanf will skip all white-space characters, read an integer then skip to the next non white-space character. This can cause
some interactive programs for example to hang until a non white-space character is entered.
31) The %i conversion is used for similarly to the %d conversion when reading and writing integers. In a printf format string, there's actually no difference
between the two whatsoever. In a scanf format string however, the %d conversion can only match an integer written in decimal base 10 form while the %i conversion
can match integers written in octal, decimal or even hexadecimal forms. If an input number has a 0 prefix like 056, the %i conversion will treat it as an octal
number. If it has 0x or 0X as a prefix like 0x56, the %i conversion will treat it as a hexadecimal number. Using %i instead of %d can lead to surprising results
especially if the user enters a 0 prefix by error thereby giving license to the %i conversion to inadvertently treat the input as an octal number. It's good to
use these conversions carefully.
32) printf will print a % character when it encounters two % consecutive characters. Since % is used to identify the beginning of a conversion specification,
some might ask how to be able to print it. Example: printf("Success rate: %d%%\n", rate); will print "Success rate: 70%".
33) The \t escape advances printf to the next tab stop. That being said, the effect of typing \t is not defined in C and it depends entirely on what the operating
system running the program does when asked to print a tab character. Tab stops are typically eight characters apart but C makes zero guarantees about this.
34) To understand how scanf puts back characters and read again at a later stage, we must understand that programs don't read user input as it's being typed. What
instead happens is input is stored in a buffer to which scanf has access, and it can easily put characters back into for later access.
35) Suppose we have the following scanf call: scanf("%d%d", &i, &j); and the user enters the following: 4,28. scanf will read the 4 then it will read the comma.
Recognizing the comma has no place in an integer, it will put it back and store the 4 in i. The second conversion specification in the format string instructs
scanf to look for an integer which it tries to do but encounters the comma, at which point it will return immediately and leave the comma and the 28 for the next
scanf call. This could easily be fixed by adding a comma between the conversion specifications in the format string, assuming that we're certain user input will
always have that general format: scanf("%d,%d", &i, &j);
36) Suppose we have the following scanf call: scanf("%d", &i); and the user enters the following: 23foo. scanf will read the 23 and store it in i. The remaining
characters are left to be read by the next scanf call. If the user had entered foo23 instead, then scanf won't be able to match anything, the value of i will be
left undefined and the whole input character stream is left to be read by subsequent scanf calls. There are ways in which we can test whether a scanf call has
succeeded. If it hasn't, we can have the program either terminate or try to recover perhaps by discarding the input that caused the issue and prompting the user
to try again.
*/