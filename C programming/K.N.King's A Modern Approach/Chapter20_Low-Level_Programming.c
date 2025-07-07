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
    *) Set a bit: Let's assume the 16 bits in i are numbered 0 to 15 starting from the least significant bit (the right-most bit) to the most significant bit (the left-most bit). If we want to set the
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
18) Handling a group of several consecutive bits known as a bit field is slightly more complicated than dealing with single bits. We can perform the following operations on a bit field:
    *) Modify a bit field: Modifying a bit field requires a bitwise and to clear the bit field followed by a bitwise or to store new bits in the bit field. Example: Suppose we wanted to store the bits 101
in bits 4-6 of the variable i, we might do the following:
i = i & ~0x0070 | 0x0050; //stores 101 in bits 4-6
--> The & operation will clear the bit field ranging from bit position 4 to 6 in the variable i, then the | operation will set bits 4 and 6. Take notice of the fact that i |= 0x0050; wouldn't always work
if our goal is to store the bits 101 in bits 4-6. In fact, i |= 0x0050 will indeed set bits 4 and 6 but it won't clear bit 5.
--> More generally, if we assume that a variable j contains the value that we want to store in bits 4-6 of i, we'll need to shift j into position first then perform a bitwise or:
i = (i & ~0x0070) | (j << 4); //stores j in bits 4-6
--> The previous statement can be further simplified since | has lower precedence compared to & and <<
i = i & ~0x0070 | j << 4;
    *) Retrieve a bit field: When a bit field sits at the right end of a number (in the least significant bits), retrieving its value is fairly easy. Example: Suppose we wanted to retrieve bits 0-2 in the
variable i, we might do the following:
j = i & 0x0007; //retrieves bits 0-2 of i and stores them in j
--> If however, the bit field we want to retrieve does not sit at the right end of a number, we can first shift the bit field until it is then extract it using the & operator. Example: Suppose we wanted
to retrieve the bits 4-6 of the variable i, we might do the following:
j = (i >> 4) & 0x0007; //retrieves bits 4-6
*/