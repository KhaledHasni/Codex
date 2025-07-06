/* Takeaways */

/*
1) A string literal is a sequence of characters enclosed within double quotes. Example: "This is a string literal". They often appear as format strings in calls of printf and scanf.
2) A string literal may contain the same escape sequences as character constants. Recall that character escapes can be used in printf and scanf format strings. Example: Each \n
in a string literal is a character escape that causes the cursor to advance to the next line.
3) Octal and hexadecimal escapes are also legal in string literals but they're not as common as character escapes.
4) Using octal and hexadecimal escape sequences in string literals is error-prone so we should pay close attention when doing so:
    *) An octal escape sequence ends after three digits or with the first non-octal character, the set of octal characters being 0,1,2,3,4,5,6,7.
Example: The string "\1234" contains two characters, \123 and 4. In this case, \123 is an octal escape that ended after three characters. The string "\189" on the other hand has
three characters, \1, 8 and 9. In this case, 8 is not an octal character so the escape sequence in this case is reduced to \1.
    *) A hexadecimal escape sequence ends at the first non-hexadecimal character and isn't limited to any number of characters. Example: The escape sequence \xfc represents the
character ü in the Latin1 character set, a common extension of ASCII. The string "Z\xfcrich" has six characters Z,\xfc,r,i,c,h and stands for "Zürich". The string "\xfcber" on the
other hand is an attempt at writing "über" but it actually only contains two characters \xfcbe and r. Notice how the hexadecimal escape didn't end until the first non-hexadecimal
character which in this case is r. Luckily, most compilers will object to the "\xfcber" string since hexadecimal escapes are usually limited to the range \x0 - \xff.
--> An escape sequence that begins with a \ and an octal character is an octal escape.
--> An escape sequence that begins with a \x is a hexadecimal escape.
5) If a string literal in a C program is too long to fit conveniently on a single line, we can continue it on the next line provided that we end the first line with a backslash \
character. No other character may follow the backslash character on the same line apart from the invisible new line character at the end.
6) In general, the backslash character can be used to join two or more lines of a program into a single line, a process which the C standard calls splicing. Splicing a string
literal has one drawback though which is the fact that the string must start at the beginning of the second line, therefore ruining the program's indented structure. This can be
mitigated however using the following C rule: When two or more string literals are adjacent i.e separated only by white space, the compiler joins them together into a single string.
This rule allows us to split a string literal over two or more lines. Example: printf("These two lines will be joined into "
                                                                                      "a single line once the program is compiled.");
7) C treats string literals as character arrays. When the compiler encounters a string literal of length n in a program, it sets aside n+1 bytes of memory for that string. This area
of memory will contain the n characters of the string plus an extra character called the null character whose bits are all zero which C uses to mark the end of the string. This
null character is represented by the escape sequence \0. The null character '\0' shouldn't be confused with the zero character '0'. The former has the code 0 while the latter has
a different code which happens to be 48 in ASCII. Example: The string literal "abc" is stored as an array of four characters 'a','b','c' and '\0'.
8) The string "" is an empty string literal and is stored as a single null character.
9) Since string literals are stored as character arrays, the compiler treats them as pointers of type char*. For example, both printf and scanf expect an argument of type char* as
their first argument. Example: When this call is invoked printf("abc"); printf is passed a pointer to where the letter a is stored in memory otherwise known as the address of "abc".
10) In general, string literals can be used wherever pointers to characters are used:
    *) String literals can appear on the right side of assignment operations. Example: char *p; p = "abc"; The last assignment doesn't copy the characters in the string literal to
where the pointer is currently pointing, it merely makes the pointer p point to the first character in the string literal "abc".
    *) String literals can be subscripted since C allows pointers to be subscripted. Example: char ch; ch = "abc"[1]; The last assignment will assign the character 'b' to the
variable ch. The other possible subscripts are 0, 2 and 3 which would respectively assign 'a', 'c' and '\0' to the variable ch. It's worth noting that string literal subscripting
isn't a property that's widely used, but it can occasionally prove to be useful. Example: Consider the following function which converts an integer in the 0 to 15 range into
a character that represents the equivalent hexadecimal digit: char digit_to_hex_char(int digit) {return "012345789ABCDEF"[digit];}
11) Attempting to modify a string literal causes undefined behavior. Example:
char *p = "abc";
*p = 'd'; //This will cause the program to crash or behave erratically.
12) A string literal containing a single character isn't the same as a character constant. The former is represented by a pointer to an address in memory where the character in the
string is stored followed by the null character while the latter is represented by an integer which is the numerical code for the character. We should therefore never use a
single-character string literal when a character is needed and never use a character when a single-character string literal is needed. Example: printf("\n"); is a perfectly legal
call since printf expects an argument of type char*, but printf('\n'); is not a legal call.
13) Unlike other programming languages that define a string type for declaring string variables, C takes a different approach by allowing any one-dimensional character array to be
used as a string, as long as that string is terminated by the null character. This approach seems simple, but has several difficulties:
    *) If we write our own string handling functions, we have to make sure that we correctly handle the null character.
    *) It's not always straightforward to be able to tell whether an array is being used as a string or not.
    *) The only way to determine the length of a string is a character-by-character search for the null character. There's unfortunately no faster way of achieving that.
Example: Suppose we need a variable to store a string containing up to 80 characters. Since the string will require a terminating null character, we can declare the variable to be
an array of 81 characters:
#define STR_LENGTH 80
char str[STR_LENGTH + 1];
--> Notice how we declared STR_LENGTH to specifically be 80 characters, thereby emphasizing the fact that the string can hold up to 80 characters, then we added one in the
declaration to allow extra room for the null character. This is idiomatic among C programmers.
14) When declaring an array that will be used to hold a string, we should always make sure to leave extra room for the null character by making the array one byte larger than the
maximum length of the string. Failing to do so may result in unpredictable behavior once the program is executed since functions in the C library assume that strings are
null-terminated.
15) Declaring a character array to be of length STR_LENGTH + 1 doesn't mean that the string it contains will always be of length STR_LENGTH. In fact, the length of a string is
hinges entirely on the position of the null character in the array and not on the size of the array where the string is stored. In other words, an array of length STR_LENGTH + 1
can store strings of various lengths ranging from the empty string to strings of length STR_LENGTH.
16) A string variable can be initialized at the same time it's declared. Example: char date1[8] = "June 14"; The compiler will put the characters from "June 14" in the date1 array
then add the null character to make sure date1 can be used as a string.
17) In the declaration used in the previous point, even though "June 14" looks like a string literal, it's not. Instead, the compiler views it as an abbreviation for an array
initializer which would have looked like this: char date1[8] = {'J','u','n','e',' ','1','4','\0'}; and would have been a completely valid way of initializing the string, although
it's clear that the original syntax is easier to read.
18) If we declare a string variable and provide an initializer for it that's too short to fill the whole string, the compiler will pad the rest of the allocated space in the
character array with null characters. Example: char date2[9] = "June 14"; This will be stored as 'J'|'u'|'n'|'e'|' '|'1'|'4'|'\0'|'\0' in memory. This behavior is in fact consistent
with the way C handles array initializers in general by initializing the remaining elements in an array to zero if the initializer is smaller than the size of the array.
19) A string initializer cannot be greater in length than the string variable it's supposed to initialize which is exactly the case for array initializers as well.
20) C allows a string variable initializer (excluding the null character) to be of the exact same length as the string variable: Example: char date3[7] = "June 14"; In this case,
the compiler will make no attempt to store a null character since there's no room left.
--> Rule of thumb: If we try to initialize a character array to be used as a string, we should make the array strictly greater in size than the length of the initializer otherwise
the null character will be quietly omitted making the array unusable as a string.
21) The declaration of a string variable may omit its length in which case it will be computed by the compiler. Example: char date4[] = "June 14"; In this case, the compiler will
set aside 8 characters for date4, just enough to store the characters in the initializer and the extra null character. The fact that date4's length isn't specified does not mean
it can be changed later. Once the program is compiled, date4's length is fixed at eight. Choosing to omit the length of a string variable initializer is especially useful if the
initializer is long since computing the length of an initializer by hand is error-prone.
22) Thanks to the close relationship between arrays and pointers in C, we can use either char date[] = "June 14"; or char *date = "June 14"; as a string. The former declares date as
an array while the latter declares it as a pointer to a character. A function that's expecting a character array or a pointer to a character as an argument will accept either
version of date. That being said, the two versions of date are not interchangeable and have significant differences between them:
    *) If date is an array, the characters stored in it are modifiable just like the elements of any array. If date is a pointer to a character however, then date points to a string
literal and we know that a string literal cannot be modified.
    *) In the array version of the declaration, date is an array name. In the pointer version on the other hand, date is the name of a pointer variable that can be made to point to
other strings during program execution.
23) If a program requires a modifiable string, it's our responsibility to set up a character array in which to store the string. Setting up a pointer variable in this case is just
not enough.
24) The declaration char *p; sets aside just enough memory for a pointer variable but doesn't allocate space for a string. In fact, this declaration doesn't even tell the compiler
how much memory to allocate. If we want to use the pointer p as a string, it needs to point to a character array. One way of doing that is to make p point to a string variable.
Example: char str[STR_LENGTH + 1], *p; p = str; This will make p point to the first character in the str string which would make it usable as a string. Another possibility that
would allow us to use p as a string is to make it point to a dynamically allocated string.
25) Using an uninitialized pointer variable as a string is a serious error. Example:
char *p;
p[0] = 'a';  //wrong
p[1] = 'b';  //wrong
p[2] = 'c';  //wrong
p[3] = '\0'; //wrong
--> All assignments in the previous example are wrong. Since p in uninitialized, we have no clue where it's pointing. Trying to access the data it's pointing to is a major mistake.
26) Writing a string is easy using either the printf or puts functions. Reading a string on the other hand is a bit tougher primarily because we have to account for the possibility
that the string we read might be longer than the string variable into which it's being stored. To read a string in a single go, we can use either scanf or gets. Alternatively, we
can read string character by character.
27) The %s conversion specification allows the printf function to write a string. Example:
char str[] = "This is an example string";
printf("%s\n", str);
--> The output of the printf statement will be: "This is an example string".
28) The printf function prints the characters in a string one by one until it encounters the null character. If the null character is missing, printf will continue writing
characters past the end of the string until it eventually runs into a null character somewhere in memory.
29) To partially print a string, we can use the conversion specification %.ps where p is the number of characters that we want displayed. Example:
char str[] = "This is an example string";
printf("%.7s\n", str);
--> The output of the printf statement will be: "This is"
30) A string can be printed within a field just like a number can. The %ms conversion specification will display a string in a field of size m. If the string is longer than m, it will
be printed in full and won't be truncated. If the string has fewer characters than m, it will be right-justified within the field. A minus sign can be added in front of m in the
conversion specification to force left-justification instead.
31) The %ms and %.ps can be used in combination in the following manner: %m.ps which will cause the first p characters of the string to be displayed in an m-sized field.
32) printf isn't the only option when it comes to writing strings. The C library provides another function that can do that job: puts. The puts function takes one argument only which
is the string to be printed and always inserts an additional new-line character after writing the string, thus advancing the cursor to the next output line.
33) The %s conversion specification allows the scanf function to read a string into a character array. Example: scanf("%s", str); Since str is an array name, it's automatically treated
as a pointer and there's therefore no need for the & operator.
34) When scanf is called, it skips all leading white spaces then reads characters into the str character array until it encounters a white space. Any other characters past the first
white space are left in the input buffer. It always stores a null character at the end of the string.
35) A string read using scanf will never contain a white space. In fact, scanf will never read a full line of input since a new-line character will cause it to stop reading, just as
a space or a tab character will.
36) To read an entire line of input at once we can use the gets function which is similar to scanf in that it also reads characters into a character array and stores a null character
at the end of the read string. However, unlike scanf:
    *) gets doesn't skip white spaces before starting to read the string (scanf does).
    *) gets reads until it finds a new-line character (scanf stops at the first encounter of a white space). gets will discard that new-line character once it finds it and replaces it
with the null character that gets stored at the end of the read string. Example:
char str[STR_LENGTH + 1];
printf("Enter a sentence:\n");
scanf("%s",str);
--> If the user enters the following sentence once they're prompted to do so: "  Silly puns are out of date." then scanf will store "Silly" in str.
char str[STR_LENGTH + 1];
printf("Enter a sentence:\n");
gets("%s",str);
--> If the user enters the following sentence once they're prompted to do so: "  Silly puns are out of date." then gets will store "  Silly puns are out of date." in str.
37) scanf and gets have no way of telling if they've gone past the end of the array in which they're storing a string they're reading as they're reading it. Therefore, they may store
characters past the end of the array causing undefined behavior. scanf can be made safer by using the %ns conversion specification instead of %s, with n being an integer indicating the
maximum number of characters to be stored in the destination character array. gets on the other hand is inherently unsafe, which makes fgets a much better alternative.
38) Since scanf and gets are dangerous and not flexible enough for many applications, a lot of C programmers choose to write their own input functions that read strings one character at
a time, therefore offering a greater degree of control compared to the standard input functions. This undertaking comes with a set of questions that we have to answer though:
    *) Will this read function skip white space before beginning to store the string?
    *) What causes this function to stop reading? Is it a new-line character, a white space character or something else? And should it be stored or discarded.
    *) What should this function do if the input is too long to be stored all at once? Should the excess be discarded or should it be left for the next input operation?
Example: Let's suppose a program requires a one-character-at-a-time read function that doesn't skip leading white spaces, stops reading at the first new-line character and discards it
along with any extra characters that can't be stored in the destination character array. This function might have the following prototype: int read_line(char str[], int n);
where str represents the character array in which the input will be stored and n is the maximum number of characters that can be read. If the input line contains more characters than n,
read_line should discard the additional characters. The function will also return the number of characters it actually stores in str, which will range from 0 to n, although it might not
always be needed.
--> The implementation of such a function will rely on a loop that calls getchar to read a character then stores it in str as long as there's room left. The loop should terminate when
the new-line character is read. If we want to be pedantic, the loop should also terminate if getchar fails to read for whatever reason but we'll overlook this complication for the sake
of this example. The complete definition of such a function will be as follows:
int read_line(char str[], int n) {
    int ch, i = 0;

    while((ch = getchar()) != '\n')
        if(i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}
--> Take note of the fact that ch has int as a type instead of char since the getchar function returns the character that it reads as an int value. Also notice how read_line adds a
null character to the end of the string before returning. Standard input functions like scanf and gets will do this automatically but if we write our own input function, it's up to us
to handle that.
39) Since strings are stored as arrays in C, subscripting can be used to access the characters in a string. For example, we can set up a loop that increments a counter i and selects
characters using the expression str[i] to loop over all characters in the string str. Example: Suppose that we need a function that counts the number of spaces in a provided string.
Using string subscripting, we can write such a function in the following manner:
int count_spaces(const char str[]) {
    int count = 0, i;

    for(i = 0; str[i] != '\0'; i++)
        if(str[i] == ' ')
            count++;
    return count;
}
--> A couple of observations are worth mentioning:
    *) Notice that the str parameter is const to indicate that the function count_spaces doesn't change the array that str represents.
    *) Had str not been a string, the function would have required a second argument indicating the length of the array. The fact that it's a string however allows the function to test
for the null character to determine its length.
40) A lot of C programmers would have preferred to use a pointer to keep track of our position in the string as we move along through it. Subscripting and pointer arithmetic are both
valid ways of stepping through the string, though pointer arithmetic is considered to be particularly convenient when working with strings. Here's how the function would look if we use
pointer arithmetic instead of array subscripting:
int count_spaces(const char *str) {
    int count = 0;

    for(; *str != '\0'; str++)
        if(*str == ' ')
            count++;
    return count;
}
--> Note that const doesn't prevent count_spaces from modifying the pointer str. It's there to prevent the function from modifying what str points to. And since str is a copy of the
pointer passed to count_spaces (C passes arguments by value), the original pointer is not affected by the increments that take place inside the function.
41) We are free to use either pointer operations (pointer arithmetic) or array operations (array subscripting) to access the characters in a string. We can even mix the two. In the
count_spaces example from the previous point, using pointer arithmetic slightly simplifies the implementation by eliminating the need for the incrementing variable i. C programmers
usually lean towards using pointer arithmetic when dealing with strings.
42) A string parameter can either be declared as an array or as a pointer. There's no difference whatsoever between the two. In fact, the compiler treats an array parameter as though
it were a pointer. This goes for any array, not just strings.
43) Whether a string parameter is declared as an array or a pointer, when the function is called, the argument passed to it could be an array name, a pointer variable or a string
literal. The function being called can't tell the difference.
44) Unlike other programming languages that offer operators that can be used on strings to copy, concatenate, compare or even select substrings, C's operator set is effectively
useless when it comes to strings. Recall that strings are essentially arrays in C, so they are subject to the same array restrictions, particularly the fact they can't be copied or
compared using operators. Examples:
    *) Suppose that str1 and str2 are two strings that have been declared as follows:
char str1[10], str2[10]; copying a string literal into a character array using the = operator is not possible:
str1 = "abc"; //wrong
str2 = str1; //wrong
--> Recall that using an array name as the left operand of the = operator is illegal.
Initializing a character array using = is legal though. Example: char str1[10] = "abc"; since in the context of a declaration, = is not the assignment operator.
    *) Attempting to compare two strings using the relational and equality operators is legal but won't produce the desired result. In fact the statement if(str1 == str2) compares
str1 and str2 as pointers, it doesn't compare the contents of the two arrays. Since str1 and str2 have different addresses, the expression str1 == str2 will evaluate to 0.
45) The C library provides a rich set of functions for performing operations on strings. The prototypes for these functions reside in <string.h> header file. So programs that need
string operations should include it. Most functions declared in this header file require at least of string as an argument. The associated string parameters are declared to have type
char*, allowing the argument to be a character array, a char* variable or a string literal which are all suitable as strings. We should watch out for string parameters that aren't
declared const though. Such parameters allow the associated arguments to be modified inside the function and therefore these arguments cannot be string literals.
46) Assuming that str1 and str2 are two character arrays used as strings, the following are some of the most basic functions found in <string.h>:
    *) String copy (strcpy): It has the following prototype in <string.h>: char *strcpy(char *s1, const char *s2); It copies the string pointed to by s2 into the array pointed to by
s1. In other words, it copies characters up until and including the first null character from s2 into s1. It returns a pointer to s1, the destination string. The source string s2 is
not modified so it's declared const.
--> This function compensates for the fact that we can't use the assignment operator to copy strings. Example:
str2 = "abcd"; //wrong because str2 is an array name and therefore can't appear on the left side of the assignment operator.
strcpy(str2, "abcd"); //correct, str2 now contains "abcd".
str2 = str1; //wrong
strcpy(str2, str1); //correct, str2 and str1's contents are now identical.
--> The return value of the strcpy function is usually discarded. However, it sometimes can be useful especially if we want to nest an strcpy call inside other calls. Example:
strcpy(str2, strcpy(str1, "abcd")); //both str1 and str2 now contain "abcd".
--> IMPORTANT: In the call strcpy(str1, str2); the strcpy function has no way of checking whether the string pointed to by str2 can fit in the array pointed to by str1. Suppose that
str1 points to an array of length n, if the string pointed to by str2 has at most n - 1 characters, then the copy will succeed. If however the string pointed to by str2 is n
characters-long or more, then undefined behavior will be the result of this call. strcpy always copies until the first null character, so in this case it will keep copying characters
into the array pointed to by str1 past the end of the array.
--> Copying a string into a character array can be done much more safely, albeit slower using the strncpy function. This function takes the same arguments as strcpy but requires a
third argument that limits the number of characters to be copied from str2 to str1. Example: To copy characters from str2 to str1 we can use the following call:
strncpy(str1, str2, sizeof(str1));
--> As long as str1 is large enough to hold the entirety of the string pointed to by str2, including the null character, the copying will be done successfully. That being said, strncpy
has its own sticky points. In fact, it will leave the string in str1 without a terminating null character if the length of the string pointed to by str2 is equal to or greater than
the size of the array pointed to by str1. A safer way of using strncpy would be:
strncpy(str1, str2, sizeof(str1) - 1);
str1[sizeof(str1) - 1] = '\0';
--> The second statement guarantees that the string in str1 will be null-terminated even if strncpy doesn't copy a null character from str2.
    *) String length (strlen): It has the following prototype in <string.h>: size_t strlen(const char *s); size_t defined in the C library, is a typedef name that represents one of C's
unsigned integer types. This function's return values can be treated as integers though as long as we're not dealing with strings whose lengths are extremely long. What this function
does is it returns the length of a string s i.e the number of characters in the string up until but not including the first null character. Example:
size_t len;
len = strlen("abc"); //len is now equal to 3
len = strlen(""); //len is now equal to 0
strcpy(str1, "abc");
len = strlen(str1); //len is now equal to 3
--> Take note of a very interesting fact highlighted by the last statement. When provided with an array as an argument, the strlen function doesn't return the length of the array itself,
instead it returns the length of the string stored in the array.
    *) String concatenation (strcat): It has the following prototype in <string.h>: char *strcat(char *s1, const char *s2); It appends the contents of the string pointed to by s2 to the
end of the string pointed to by s1. It returns s1 (a pointer to the resulting string). Example:
strcpy(str1, "abc");
strcpy(str2, "def");
strcat(str1, str2); //str1 now has "abcdef"
--> Just like strcpy, the return value from strcat is usually discarded. Here's an example though of how it might be used:
strcpy(str1, "abc");
strcpy(str2, "def");
strcat(str1, strcat(str2, "ghi")); //str1 now has "abcdefghi" while str2 has "defghi"
--> The effect of calling strcat(str1, str2); is undefined if the array point to by str1 isn't long enough to accommodate the extra characters from str2. Example:
char str[6] = "abc";
strcat(str, "def"); //wrong
--> In the previous example, strcat will attempt to add the characters 'd', 'e', 'f' and '\0' to the end of the string already stored in str. But since str is limited to six characters,
strcat will write past the end of the array.
--> strncat is a safer but slower version of strcat. Like strncpy, it takes a third argument that limits the number of characters to be copied from the source string. Example:
strncat(str1, str2, sizeof(str1) - strlen(str1) - 1); strncat will terminate str1 with a null character so we account for that in the third argument by computing the amount of space left
in the array pointed to by str1 and subtracting one to ensure there will be room left for the null character.
    *) String compare (strcmp): It has the following prototype in <string.h>: int strcmp(const char *s1, const char *s2); It compares the two strings pointed to by s1 and s2 and returns
an integer value less than, equal to greater than zero depending on whether or not the string pointed to by s1 is less than, equal to or greater than the string pointed to by s2. Example:
if(strcmp(str1, str2) < 0); //is str1 less than str2
if(strcmp(str1, str2) <= 0); //is str1 less than or equal to str2
--> By choosing the proper relational (<, >, <=, >=) or equality (==, !=) operator, we can test any possible relationship between str1 and str2.
--> strcmp compares strings based on their lexicographic ordering, which resembles the way words are arranged in a dictionary. In other words, strcmp will consider str1 to be less than
str2 if either of the two following conditions is satisfied:
        1- The first i characters of str1 and str2 match but the (i+1)st character of str1 is less than the (i+1)st character of str2 for all 0 <= i <= min(strlen(str1), strlen(str2) - 1).
Example: "abc" < "bcd", "abd" < "abe".
        2- All characters from s1 match s2 but s1 is shorter than s2. Example: "abc" is shorter than "abcd".
--> strcmp relies on characters' numerical codes to compare them amongst each other. Therefore, some knowledge of the underlying character set is always helpful to be able to use strcmp
efficiently. A few of the most important properties of the ASCII character set are:
        1- The characters is each of the sequences a-z, A-Z and 0-9 have consecutive codes.
        2- All upper-case letters (ASCII code range 65-90) are less than all lower-case letters (ASCII code range 97-122).
        3- Digits (ASCII code range 48-57) are less than letters.
        4- Spaces are less than all printing characters. In particular, the space's ASCII code is 32.
47) sprintf is a library function similar to printf, except that it writes output into a string. Example: the call sprintf(day_str, "%2d", day); writes the value of day into day_str and
automatically adds a null character at the end of the destination string when it's done writing.
48) We're not allowed to write our own functions that have the same name as a standard library function even if we don't include the header file to which those standard functions belong.
In particular, we can't write string processing functions that have the same name as functions from <string.h>. In fact, all names that begin with str plus a lowercase letter are
reserved to allow functions to be added to the <string.h> header in future versions of the C standard.
49) Suppose we wanted to write our own strlen functions in an idiomatic manner. We could write something like this:
size_t compute_str_len(const char *s) {
    size_t n = 0;

    while(*s++)
        n++;
    return n;
}
--> Here's a version of the same function that runs a bit faster on some compilers:
size_t compute_str_len(const char *s) {
    const char *p = s;

    while(*s)
        s++;
    return s-p;
}
--> This version of the function computes the length of the string by locating the position of the null character then subtracting from it the position of the first character in the
string. The slight improvement in speed comes from not having to increment n inside the while loop. The usage of const in the declaration of the p pointer is worth noting. Without
it the compiler would notice that the string pointed to by s is at risk of being changed.
--> The statements while(*s) s++; and the related while(*s++) are idioms that search for the null character at the end of a string pointed to by s. The former leaves s pointing to the
null character once done, while the latter leaves s pointing just past the null character.
50) Suppose we wanted to write our own strcat function in an idiomatic manner. We could write something like this:
char *concatenate_strings(char *s1, const char *s2) {
    char *p = s1;

    while(*p != '\0')
        p++;
    while(*s2 != '\0') {
        *p = *s2;
        p++;
        s2++;
    }
    *p = '\0';

    return s1;
}
--> This version of the function uses the first while loop to locate the null character in the first string s1 and point to it using p, then a second loop to copy characters from the second
string s2 to where p is now pointing, then adds a null character at the end once it copies all characters.
--> Here's a more concise version of the same function:
char *concatenate_strings(char *s1, const char *s2) {
    char *p = s1;

    while(*p)
        p++;
    while(*p++ = *s2++)
        ;
    return s1;
}
--> This while(*p++ = *s2++) is called the string copy idiom. The expression inside the parentheses copies a character from where s2 points to where p points then both pointers are
incremented once the assignment is done thanks to the postfix increment operator. Repeatedly executing this in a while loop has the effect of copying characters from where s2 points to where
p points. Since the primary operator inside expression in parentheses is the assignment operator, the while statement tests the value of the assignment i.e the character being copied. All
characters except the null character will evaluate to true, so the loop won't in fact terminate until the null character has been copied. And since the loop terminates after the assignment,
we don't need a separate statement to add a null character at the end of the string pointed to by s1.
51) When we want to store an array of strings, the most intuitive way is to create a two-dimensional array of characters and store the strings one per row. Example:
char planets[][8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
--> Note in the previous example that we're allowed to omit the number of rows in the declaration of a two-dimensional array since that's obvious from the number of strings in the initializer,
however, C still requires that we provide the number of columns. The resulting array will look something like this:
   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
---|---|---|---|---|---|---|---|---|
 0 | M | e | r | c | u | r | y | \0|
---|---|---|---|---|---|---|---|---|
 1 | V | e | n | u | s | \0| \0| \0|
---|---|---|---|---|---|---|---|---|
 2 | E | a | r | t | h | \0| \0| \0|
---|---|---|---|---|---|---|---|---|
 3 | M | a | r | s | \0| \0| \0| \0|
---|---|---|---|---|---|---|---|---|
 4 | J | u | p | i | t | e | r | \0|
---|---|---|---|---|---|---|---|---|
 5 | S | a | t | u | r | n | \0| \0|
---|---|---|---|---|---|---|---|---|
 6 | U | r | a | n | u | s | \0| \0|
---|---|---|---|---|---|---|---|---|
 7 | N | e | p | t | u | n | e | \0|
---|---|---|---|---|---|---|---|---|
 8 | P | l | u | t | o | \0| \0| \0|
---|---|---|---|---|---|---|---|---|
--> Not all strings were long enough to fill an entire row of the array so we see a lot of null character paddings introduced to fill in the blank spaces. There's some wasted space in this array
since only three planets have names long enough to require 8 characters including the null character. This kind of inefficiency is common when working with collections of strings since some of
those strings will be long and some others will be short.
52) To mitigate the waste of space highlighted by the previous example in point 51, we need a ragged array: a two-dimensional array whose rows can have different lengths. C doesn't provide a
ragged array type but it does provide all the necessary tools to create. The secret here is to create an array of pointers to strings. Example: Here's the planets array again, only this time,
it's an array of pointers to strings:
char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
--> Each element of planets in this case is a null-terminated string. There are no longer any wasted characters in the strings but we've had to allocate space for the pointers in the array. To
access one of the planets' names, we can subscript the planets array. Accessing a character in a planet name is done in the same way we access an element in a two-dimensional array. Example:
If we wanted to write a loop that would search the planets array for planet names that start with the letter M, we could do the following:
for(int i = 0; i < 9; i++)
    if(planets[i][0] == 'M')
        printf("%sbegins with M\n", planet[i]);
53) When a program is run, it often needs to be supplied with some information. If we consider the example of the ls UNIX command. When we run the ls command, it will list all files that exist in
the current directory. But if we run it with the -l argument (ls -l), it will display a long, detailed listing of each file showing who the owner of the file is, its size, the date and time it was
last modified and a bunch of other information. We can even have the ls command display information about a single file: ls -l file.c.
54) Command-line information is available to all programs not just operating system commands. To be able to use these command-line arguments called program parameters in the C standard, we must
define the main function with two parameters that are usually called argc and argv: int main(int argc, char *argv[]){//content of main}.
    *) argc stands for argument count and denotes the number of command-line arguments including the name of the program itself.
    *) argv stands for argument vector and is an array of pointers to the actual command-line arguments stored in the form of strings. argv[0] points to the name of the program while argv[1] to
argv[argc - 1] point to the remaining command-line arguments. argv has one extra element argv[argc] which is the null pointer, a pointer that points to nothing.
--> Example: If the user enters the command line: ls -l file.c, then argc is 3, argv[0] would point to the name of the program, argv[1] would point to the string "-l", argv[2] would point to the
string "file.c", and argv[3] would contain the null pointer. The program name might include a path or other information that depends on the operating system. If the program name is not available,
then argv[0] would point to an empty string.
55) Typically, a program that expects command-line arguments will write a loop that steps through the argv array to examine the arguments one at a time. Example: the following loop prints the
commands one per each line:
for(int i = 0; i < argc; i++)
    printf("%s\n", argv[i]);
--> We can also set up a pointer to argv[1] then repeatedly increment the pointer to step through the rest of the vector and we reach the null pointer. Example:
char **p;
for(p = &argv[1]; *p; p++)
    printf("%s\n", *p);
56) According to the C89 standard, compilers must allow string literals to be at least 509 characters long. C99 increases that minimum to 4095 characters. This means compilers adhering to the
respective standards are free to support string literals longer than the respective limits, but they must at least support the given limits.
57) String literals are not called string constants because they're not necessarily constant. In fact, since they're accessed through pointers, there's nothing to really prevent us from
attempting to modify the characters in a string literal. This might seem like a contradiction when read side by side with a previous point we mentioned that states that we should never
attempt to modify a string literal since that would result in undefined behavior. To understand this seemingly perplexing paradox, the fact that a string literal is accessed through a pointer,
there's really nothing preventing us from changing the characters in that string literal, and this is syntactically the case since something like *p = 'd' will more than likely be accepted by
the compiler. Semantically however, this is not the case, and attempting to modify a string literal will result in undefined behavior since the C standard states that string literals have static
storage and may reside in read-only memory. If that's the case, a program that attempts to modify it will simply crash. Another reason why modifying string literals causes undefined behaviors is
the fact that some compilers try to reduce memory footprint by storing single copies of identical string literals. Example: If we consider the following: char *p = "abc", *q = "abc"; A compiler
might choose to store "abc" just once and make both p and q point to it. If we change "abc" through the pointer p, the string that q points to will also be affected which would lead to all sorts
of problems.
--> To conclude, string literals are theoretically not constant. We just avoid modifying them to avoid undefined behaviors.
58) Point 4 mentions that \xfcber is a failed attempt at writing "über". The trick to writing it is to use two adjacent string literals "\xfc" and "ber" and let the compiler concatenate them.
59) Not every character array should include room for a null character since not every character array will be used as a string. For example, we do not need a null character in our character
array if we only plan on performing operations on individual characters in the array. A common example of this would be a character array that will be used to translate from one character set to
another. Such an array declared like this: char translation_array[128]; will only be subjected to subscripting operations where translation_array[ch] will be the translated value of ch.
translation_array is not a string in this case, no string operations will be performed on it and it therefore doesn't require a null character.
60) Since printf and scanf expect a char* argument, we can in theory supply them with a string variable instead of the usual string literal. Example:
char fmt[] = "%d\n";
int i;
//do something
printf(fmt, i);
--> We can also read a format string as input.
61) If we want printf to write the contents of a string variable str, we can in theory provide str to printf as the format string but it comes with a fair share of risk. If str contains the "%"
character, the printf call won't produce the desired result since it will assume the "%" character is the beginning of a conversion specification.
62) Point 38 discusses the read_line function that uses getchar(). If the latter fails to read a character because of an error or because of end-of-file, it returns EOF which has type int. If we
were to write a revised version of the read_line function that tests whether getchar returns EOF, it would look something like this:
int read_line(char str[], int n) {
    int ch, i = 0;

    while((ch = getchar()) != '\n' && ch != EOF)
        if(i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}
63) The return value of the strcmp function probably stems from the way it was traditionally written. For example, the version in Kernighan and Ritchie's "The C programming language" is as follows:
int strcmp(char *s, char *t) {
    int i;

    for(i = 0; s[i] == t[i]; i++)
        if(s[i] == '\0')
            return 0;
    return s[i] - t[i];
}
--> The return value is the difference between the first mismatched characters between the s and t strings which will be negative if s is smaller than t and positive if s is larger than t. There's
no guarantee however that strcmp is written this way, so it's best not to assume that the magnitude of the return value has any particular meaning. The sign however, that's a different story.
64) Some compilers might issue a warning for the while statement while(*p++ = *s2++) since a lot of compilers will issue a warning when = is used in places where == is usually expected. Although
this is a valuable warning that can save us a lot of debugging time if we ever make this mistake, it is not relevant in this particular case since we do need the assignment operator and not the
equality operator. We can suppress the warning by rewriting the statement while((*p++ = *s2++) != 0) since the statement now tests a condition not an assignment. With the GCC compiler, enclosing
the assignment in parentheses is another way of suppressing the warning: while((*p++ = *s2++)).
65) It's very common for compiler vendors to write string-processing functions in assembly instead of C. In fact, the string functions need to be as fast as possible since they're used often and
have to deal with strings of arbitrary length. Writing such functions in assembly makes it possible to achieve great efficiency by taking advantage of any special string-handling instructions
provided by the CPU.
66) The C standard calls command-line arguments "program parameters" since programs aren't necessarily run from the command line. Some programs that use a graphical user interface for example can
be run with a mouse click. In some other environments, there's no traditional command line, although there may be other channels through which information can be passed to the program. The term
"program parameters" adopted by the C standard leaves the door open for all these possibilities.
67) Using the names argc and argv for the main function's parameters is just a convention and not a language requirement. Any names can be used instead.
68) The argument vector in the main function can be declared as **argv instead of *argv[]. In fact, when declaring a parameter, writing *a is always the same as writing a[] regardless of the type of
a's elements.
69) Arrays of pointers are particularly useful with dynamic storage allocation.
*/