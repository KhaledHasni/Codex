/* Takeaways */

/*
1) C provides six bitwise operators that operate on integer data at the bit level: Bitwise left shift, bitwise right shift, bitwise complement, bitwise and, bitwise exclusive or and bitwise inclusive or.
2) The bitwise shift operators can transform the binary representation of an integer by shifting its bits to the left (left shift <<) or to the right (right shift >>).
3) The bitwise shift operators' operands may be of any integer type including char. Integer promotions are performed on both operands and the result of the operation will have the type of the left
operand after promotion.
4) Assuming i and j are both variables of integer types, the value of i << j is the result when the bits in i are shifted left by j places. As a result of this shifting, for every bit that gets shifted
off the left side of i, a zero bit gets introduced to the right side of i.
5) The value of i >> j is the result when the bits in i are shifted right by j places. If i is of an unsigned type or if the value of i is equal to or greater than zero, then zeros are added at the left
as needed, as right shifts are performed. If on the other hand, i is a negative number, the result of right-shifting i is implementation-defined: Some implementations add zeros at the left end while
others try to preserve the sign by adding ones. Therefore, to ensure portability, it's always a good idea to perform bitwise shifts on unsigned numbers exclusively.
6) Let's explore a couple of examples:
unsigned short i, j;
i = 13;     //i is now 13 (0000000000001101)
j = i << 2; //j is now 52 (0000000000110100)
j = i >> 2; //j is now 3  (0000000000000011)
--> The bitwise shift operators do not modify their operands. To shift the bits of a variable, we can use the compound assignment operators <<= and >>=. Example:
i = 13;  //i is now 13 (0000000000001101)
i <<= 2; //i is now 52 (0000000000110100)
i >>= 2; //i is now 13 (0000000000001101)
7) Bitwise shift operators have lower precedence compared to arithmetic operators. Example: i << 2 + 1 is equivalent to i << (2 + 1).
8) The bitwise complement operator ~ is a unary operator. Integer promotions are performed on its operand. The bitwise and operator &, the bitwise inclusive or operator | and the bitwise exclusive or
operator ^ are binary. The usual arithmetic conversions are performed on their operands. All four of these operators perform boolean operations on all bits in their operands:
    *) The bitwise complement operator ~ is unary and it produces the complement of its operand by replacing zeros with ones and ones with zeros.
    *) The bitwise and operator & performs a boolean and operation on all corresponding bits in its two operands.
    *) The bitwise inclusive or operator | performs a boolean or operation on all corresponding bits in its two operands and produces 1 when both operands have a 1 bit.
    *) The bitwise inclusive or operator ^ performs a boolean or operation on all corresponding bits in its two operands and produces 0 when both operands have a 1 bit.
9) We shouldn't confuse the bitwise operators & and | with the logical operators && and ||. Although they sometimes produce the same results when applied to the same sets of operands, they aren't
equivalent.
10) Let's explore a couple of examples:
unsigned short i, j, k;
i = 21;    //i is now 21    (0000000000010101)
j = 56;    //j is now 56    (0000000000111000)
k = ~i;    //k is now 65514 (1111111111101010) assuming unsigned short values occupy 16 bits
k = i & j; //k is now 16    (0000000000010000)
k = i ^ j; //k is now 45    (0000000000101101)
k = i | j; //k is now 61    (0000000000111101)
11) The bitwise complement operator ~ can be used to make low-level programs more portable. Suppose that we need an integer whose bits are all 1 irrespective of the number of bits in the integer. A good
idea would be to rely on the bitwise complement of 0 (~0). Similarly, suppose we need an integer whose bits are all 1 except for the last five irrespective of its size. A good idea would be to use ~0x1f.
12) The ~, &, ^ and | operators have different levels of precedence that go from highest to lowest in that order. Consequently, we can combine them in expressions without having to use parentheses.
Example: For example, we could write:
    *) i & ~j | k instead of (i & (~j)) | k
    *) i ^ j & ~k instead of i ^ (j & (~k))
13) The &, ^ and | operators have lower precedence than the equality and relational operators. Example: The following statement won't have the desired effect: if(status & 0x400 != 0). Since != takes
precedence over &, this statement will first evaluate 0x400 != 0 which is 1, then it will check if status & 1 is not zero.
14) The compound assignment operators &=, ^= and |= correspond to the bitwise operators &, ^ and | respectively. Example:
unsigned short i, j;
i = 21;    //i is now 21 (0000000000010101)
j = 56;    //j is now 56 (0000000000111000)
i &= j;    //i is now 16 (0000000000010000)
i ^= j;    //i is now 40 (0000000000101000)
i |= j;    //i is now 56 (0000000000111000)
15) Low-level programming will often require storing information as single bits or collections of bits. Using bitwise operators, we can extract and modify data that's stored in a small number of bits.
16) Assuming i is a 16-bit unsigned short variable, we can perform the following single-bit operations on i:
    *) Set a bit: Let's assume the 16 bits in i are numbered 0 to 15 starting from the least significant bit (the rightmost bit) to the most significant bit (the leftmost bit). If we want to set the
4th bit for example, the easiest way to achieve that is to or the value of i with the constant 0x0010 which is a bit mask that contains 1 in the position 4:
i = 0x0000;  //i is now 0  (0000000000000000)
i |= 0x0010; //i is now 16 (0000000000010000)
--> More generally, if the position of the bit we want to set is stored in a variable j, we can use a shift operator to create the mask:
i |= 1 << j; // sets the jth bit assuming the bits are 0-indexed starting from the right
    *) Clear a bit: Bearing in mind the same assumptions we already established when setting a bit, if we want to clear the 4th bit for example, we can and the value of i with the constant obtained by
clearing the 4th bit and setting every other bit. This constant is called the bit mask:
i = 0x00ff;   //i is now 255 (0000000011111111)
i &= ~0x0010; //i is now 239 (0000000011101111)
--> More generally, if the position of the bit we want to clear is stored in a variable j, we can use a shift operator to create the mask:
i &= ~(1 << j); // clears the jth bit assuming the bits are 0-indexed starting from the right
    *) Test a bit: To test whether bit 4 of i is set we can use the following statement:
if(i & 0x0010)
--> More generally, To test whether bit j of i is set, we can use the following statement:
if(i & 1 << j)
17) To make working with bits easier, we'll often give them names. Suppose for example that we want the first, second and third bits (starting from the least significant bit) to represent the colors
blue, green and red respectively. We can start by defining meaningful names for the three bits:
#define BLUE  1 << 0
#define GREEN 1 << 1
#define RED   1 << 2
--> We can then proceed to performing the following operations using those names we defined:
    *) Setting the BLUE bit: i |= BLUE;
    *) Clearing the BLUE bit: i &= ~BLUE;
    *) Testing the BLUE bit: if(i & BLUE)
--> We can also set, clear and tests multiple bits at a time:
    *) Setting the BLUE and GREEN bits: i |= BLUE | GREEN;
    *) Clearing the BLUE and GREEN bits: i &= ~(BLUE | GREEN);
    *) Testing the BLUE and GREEN bits: if(i & (BLUE | GREEN)); //tests whether the BLUE or GREEN bit is set
18) Handling a group of several consecutive bits known as a bit-field is slightly more complicated than dealing with single bits. We can perform the following operations on a bit-fields:
    *) Modify a bit-field: Modifying a bit-field requires a bitwise and to clear the bit-field followed by a bitwise or to store new bits in the bit-field. Example: Suppose we wanted to store the bits 101
in bits 4-6 of the variable i, we might do the following:
i = i & ~0x0070 | 0x0050; //stores 101 in bits 4-6
--> The & operation will clear the bit-field ranging from bit position 4 to 6 in the variable i, then the | operation will set bits 4 and 6. Take notice of the fact that i |= 0x0050; wouldn't always work
if our goal is to store the bits 101 in bits 4-6. In fact, i |= 0x0050 will indeed set bits 4 and 6 but it won't clear bit 5.
--> More generally, if we assume that a variable j contains the value that we want to store in bits 4-6 of i, we'll need to shift j into position first then perform a bitwise or:
i = (i & ~0x0070) | (j << 4); //stores j in bits 4-6
--> The previous statement can be further simplified since | has lower precedence compared to & and <<
i = i & ~0x0070 | j << 4;
    *) Retrieve a bit-field: When a bit-field sits at the right end of a number (in the least significant bits), retrieving its value is fairly easy. Example: Suppose we wanted to retrieve bits 0-2 in the
variable i, we might do the following:
j = i & 0x0007; //retrieves bits 0-2 of i and stores them in j
--> If however, the bit-field we want to retrieve does not sit at the right end of a number, we can first shift the bit-field until it is then extract it using the & operator. Example: Suppose we wanted
to retrieve the bits 4-6 of the variable i, we might do the following:
j = (i >> 4) & 0x0007; //retrieves bits 4-6
19) Encrypting a message can be achieved relatively easily by XOR-ing every character with a secret character called "the key". For example, if we suppose that we're using an XOR encryption scheme whose
key character is '&'. Encrypting the 'z' (ASCII 01111010) character for example would be as easy as XOR-ing it with '&' (ASCII 00100110). The outcome in this case is '\' (ASCII 01011100). Decrypting the
message involves XOR-ing all characters from the encrypted message with the same secret key. In other words, encrypting an already encrypted message using the same key actually decrypts it and restores
the original message. This is by virtue of the XOR operation being an involution.
20) C provides an alternative to managing bit-fields in the manner discussed in point 18, in the form of structures whose members are bit-fields themselves. A good real-world example of such structures
being used is the manner in which the MS-DOS operating system stores the date at which a file was created or last modified. DOS allocates 16 bits for such dates, five of which are allotted to the day,
four to the month and seven to the year. This is mainly done because days, months and years are relatively small numbers, so they wouldn't require an integer variable each. We can define a C structure
that relies on bit-fields with the same layout:
struct file_date {
    unsigned int day: 5;
    unsigned int month: 4;
    unsigned int year: 7;
};
--> The number following each member indicates its length in bits. Since all members have the same type, the structure's declaration can be condensed even further:
struct file_date {
    unsigned int day: 5, month: 4, year: 7;
};
21) A bit-field's type in a structure should be either int, unsigned int or signed int. Using the int type is ambiguous since some compilers will treat the field's high-order bit as a sign bit and some
won't. Therefore, to ensure portability, it's always a good idea to declare bit-fields to be either signed or unsigned.
22) In C99, bit-fields may have the type _Bool. C99 compilers may also allow additional bit-field types.
23) Bit-fields are mostly used just like any other member of a structure (with one exception mentioned further down). Example: Based on the structure declaration from point 20, we can declare the
following file_date instance:
struct file_date fd;
fd.day = 28;
fd.month = 12;
fd.year = 8;
--> Note the year member is stored relative to 1980 (A significant and milestone year for Microsoft that marked the beginning of their partnership with IBM). The fd variable in the previous example will
have the following appearance in memory: || 0 | 0 | 0 | 1 | 0 | 0 | 0 || 1 | 1 | 0 | 0 || 1 | 1 | 1 | 0 | 0 | with the most significant bit being the leftmost bit.
--> The bitwise operators could have been used to achieve the same feat and might have even made the program slightly faster. That being said, using bit-fields makes the program much more readable which
is usually more valuable than a few microseconds gained.
24) Bit-fields in structures can generally be treated as any other structure member with just one exception: C doesn't allow applying the address operator to a bit-field since bit-fields don't really have
addresses in the traditional sense. This has many consequences, like the fact that the scanf function can't read data and store it directly in a bit-field:
scanf("%d", fd.day); //wrong
--> We can still use the scanf function to read data into an ordinary variable that we can then assign to a bit-field though.
25) The C standard allows compilers a considerable freedom margin in choosing how they store bit-fields when they encounter the declaration of a bit-field-containing-structure. The way a compiler goes
about this is largely influenced by the notion of storage units, whose sizes are implementation-defined. Typical storage unit sizes are 8, 16 and 32 bits.
26) As it processes the declaration of a structure that has bit-fields, the compiler will pack those bit-fields one by one into a storage unit with no gaps between the fields until there's no more room
left for the next field. Once that happens, some compilers will leave the rest of the bits in the current storage unit empty and skip to the next storage unit, while others will split a bit-field across
storage units. Which one happens, and the order in which bit-fields are stored (left to right or right to left) are implementation-defined. Example: In the file_date example discussed in point 23, we
assumed that a storage unit is 16-bits long. We could also look at it as two adjacent 8-bit long storage units as long as the compiler splits the month field acorss storage units. It's also assumed that
bit-fields are stored from right to left.
27) C allows the omission of a bit-field's name. Such unnamed fields are useful as paddings to ensure that other fields are correctly positioned in memory. Example: The time associated with a DOS file
is stored in the following manner:
struct file_time {
    unsigned int seconds: 5;
    unsigned int minutes: 6;
    unsigned int hours: 5;
};
--> One question that might come to mind is how would DOS be able to store seconds ranging from 0 to 59 over 5 bits. Well, DOS actually divides the number of seconds by two making it range from 0 to 29
and thereby effectively a 2-second resolution and not storing odd-numbered seconds at all. This compromise was made at the time (remember that this in the early 80s) because saving valuable bits of memory
was deemed more important than having a to-the-second accurate timing.
--> If the seconds field is of no importance to us, we can leave out its name:
struct file_time {
    unsigned int : 5;        //not used
    unsigned int minutes: 6;
    unsigned int hours: 5;
};
--> The remaining bit-fields will be aligned as if the seconds bit-field were still there.
28) The length of an unnamed bit-field can be set to 0. This is a sign to let the compiler know that the following bit-field should be aligned at the start of a storage unit. Example:
struct str {
    unsigned int a: 4;
    unsigned int : 0;  //0-length bit-field
    unsigned int b: 8;
};
--> In the previous example, if the size of a storage unit is:
    *) 8 bits: The compiler will allocate 4 bits for the a member, skip the next 4 in the storage unit, then allocate 8 bits (an entire storage unit) for the b member.
    *) 16 bits: The compiler will allocate 4 bits for the a member, skip the next 12 in the storage unit, then allocate 8 bits from the next storage unit for the b member.
29) It's sometimes a good idea to define machine-dependent types. Examples include the char type which by definition occupies one byte and is therefore used extensively to store data that's not
necessarily in character form. When that is done, C programmers will typically define a BYTE type: typedef unsigned char BYTE; Other examples include 16-bit words which are used a lot in the x86
architecture, so it would make sense to have such a definition when using that platform: typedef unsigned short WORD;
30) Unions in C are a great way of ensuring portability, but they're actually mostly used to be able to interpret the same data in more than one way which is called "type punning". Example: Based on the
file_date structure declaration from point 20, we can think of any two-byte value as a file_date structure since the latter can fit into two bytes. So assuming that a short integer is 16 bits long on a
given platform, we can think of any unsigned short value as a file_date structure. That being said, we can use the following to union to easily convert a short integer to a file_date and vice versa:
union int_date {
    unsigned short i;
    struct file_date fd;
};
--> Using this union, we can fetch a file date from memory as two bytes and extract its day, month and year fields in a single operation. Conversely,we can build a file_date structure then store it in
memory as two bytes. Example: The following is a function that takes an unsigned short integer as an argument and prints it as a file date:
void print_date(unsigned short input) {
    union int_date u;

    u.i = input;
    printf("%d/%d/%d\n", u.fd.month, u.fd.day, u.fd.year + 1980);
}
31) Using unions to view data in multiple ways is especially useful when working with registers which are often divided into smaller units. x86 processors for example have 16-bit registers called AX, BX,
CX and DX which can be further divided into 2 8-bit registers each. The AX register for example is divided into registers called AH and AL that stand for high and low respectively. When writing
applications for x86-based computers, we may need variables that hold the contents of the AX, BX, CX and DX registers but with a caveat: we need to be able to access the contents of the 16-bit and 8-bit
registers at the same time, while taking into account that changing either AH or AL will affect AX, and changing AX will impact both values in AH and AL. The solution here is to set up two structures,
one whose members represent the 16-bit registers and the other with members that match the 8-bit registers, and finally enclose both structures in a union:
union {
    struct {
        WORD ax, bx, cx, dx;
    } word;
    struct {
        BYTE al, ah, bl, bh, cl, ch, dl, dh;
    } byte;
} registers;
--> The members of the word structure will be overlaid by the members of the byte structure and both will overlap in memory in such a way that ax will occupy the same memory as ah and al combined and so
on, which is exactly what we wanted. Example:
registers.byte.ah = 0x12;
registers.byte.al = 0x34;
printf("AX %hx\n", registers.word.ax); //The output in this case will be 1234.
--> It's worth pointing out that al is declared before ah in the byte structure for a reason, even though intuitively al is the low half and ah is the high half of the AX register. The reason for this
boils down to the concept of endianness. Once a data item consists of more than one byte, there are two logical ways to store it in memory, either with the bytes in their natural order with the leftmost
most significant byte stored first otherwise known as big-endian or in the reverse order with the rightmost least significant byte stored first also known as little-endian. C has no say whatsoever and
does not require any specific byte ordering, that's completely up to the CPU on which the code will be executed. Some CPUs will use big-endian while others will use little-endian. Since x86 processors
assume that data is stored in little-endian order, we declared the al byte first since the first byte of registers.word.ax is the low byte.
32) A C programmer doesn't usually have to worry about byte ordering. However, programs that deal with memory at a low level must be aware of how bytes are ordered as illustrated by the registers example
from point 31. This information can also be useful when working with files that contain non-character data.
33) We must be extra careful when using unions to provide multiple views of the same data. Data that's valid in its original format may sometimes not be valid when viewed as a different type which may
lead to unexpected problems.
34) A memory address often has the same number of bits as an integer or a long integer. Creating a pointer that contains a specific address is easy by casting an integer that represents the address value
into a pointer . Example: If wa wanted to store the hex address 1000 in a pointer variable p, we might do something like the following:
BYTE *p;
p = (BYTE *) 0x1000; //p will now contain the address 0x1000
35) Certain memory locations on some computers are volatile, in other words the values stored in said locations can change at runtime even though the program itself isn't storing new data in those
locations. A common example of this taking place is memory locations that hold data coming directly from input devices. C provides the volatile type qualifier used to inform the compiler if any of the
data used in a program is volatile. This qualifier typically appears in the declaration of a pointer variable that is intended to point to a volatile memory location. Example:
volatile BYTE *p; //p will point to a volatile byte
--> Suppose that p points to a memory location that contains the most recent character typed at the user's keyboard. This memory location is by definition volatile since its value will change every time
the user types a new character at the keyboard. The following loop might be used to obtain characters from the user's keyboard and store them in a buffer array:
while(//buffer not yet full) {
    //wait for input
    buffer[i] = *p;
    if(buffer[i++] == '\n')
        break;
}
--> A sophisticated compiler processing this while loop might notice that neither p nor *p are being changed inside of it, so it might optimize the program by altering it just a bit in such a manner that
*p is fetched only once:
//store *p in a register;
while(//buffer not yet full) {
    //wait for input
    buffer[i] = value_stored_in_register;
    if(buffer[i++] == '\n')
        break;
}
--> We can clearly see that this program will not do what was originally intended, rather it will fill the entire buffer with copies of the same character. Adding the volatile type qualifier to declare
that p points to volatile data avoids this problem by letting the compiler know that *p must be fetched from memory each time it's needed.
36) Let's examine how the & and && operators sometimes produce the same result and sometimes don't. Let's compare the simple operations i & j and i && j: As long as i and j have the values 0 and 1 in any
combination, the two operations will yield similar outcomes. In fact:
|---------------------|
|    i   | 0  1  0  1 |
|--------|------------|
|    j   | 0  0  1  1 |
|--------|------------|
| i & j  | 0  0  0  1 |
|--------|------------|
| i && j | 0  0  0  1 |
|---------------------|
However, if i and j have values other than 0 and 1, the two operations may not always yield the same result. For example, if i is 1 and j is 2, then i & j will yield 0 while i && j will yield 1. If i is
3 and j is 2, then i & j will yield 2 while i && j will yield 1.
--> The & and && operators may also differ in terms of side effects. For example, evaluating i & j++ will always increment j as a side effect of the evaluation while i && j++ will only sometimes increment
j as a side effect (only when i has a non-zero value).
--> Similar conclusions can be drawn when it comes to | and ||.
37) The terms big-endian and little-endian originate from Jonathan Swift's novel "Gulliver's Travels". In the novel, the fictional islands of Lilliput and Blefuscu are in a perpetual disagreement over
whether to open an egg from the big end or the little end. This situation closely resembles byte ordering when storing data in memory since the choice is completely arbitrary and both ways are valid.
38) TODO: Add summary of viewmemory.c program

*/