<h1 align="center">💡<strong> Low-Level Programming</strong></h1>
<p align="center">
  <a href="#gear-bitwise-operators">Bitwise Operators</a> •
  <a href="#clamp-bit-fields-in-structures">Bit-Fields In Structures</a> •
  <a href="#hammer_and_wrench-other-low-level-techniques">Other Low-Level Techniques</a> •
  <a href="#game_die-miscellaneous"> Miscellaneous</a>
</p>

## :gear: Bitwise Operators

* C provides six bitwise operators that can be used to operate on integers at the bit level.
   * The bitwise left shift operator ```<<```.
   * The bitwise right shift operator ```>>```.
   * The bitwise complement operator ```~```.
   * The bitwise and operator ```&```.
   * The bitwise exclusive or operator ```^```.
   * The bitwise inclusive or operator ```|```.

### :small_blue_diamond: Bitwise Shift Operators

* C provides two bitwise shift operators.
   * The bitwise left shift operator ```<<```.
   * The bitwise right shift operator ```>>```.
* C's bitwise shift operators are used to transform the binary representation of an integer operand by shifting its bits left or right.
* C's bitwise shift operators support operands of any integer type including ```char```.
   * Integer promotions are performed on both operands.
   * The result has the type of the left operand after promotion.
* Both of C's bitwise shift operators are binary.
   * These operators expect two integer operands.
   * Assuming ```i``` and ```j``` are two integers:
      * ```i << j``` causes all bits in ```i```'s binary representation to be shifted ```j``` places to the left.
         * For every bit (no matter the value) shifted off the left end of ```i```, a ```0``` is added to the right end.
      * ```i >> j``` causes all bits in ```i```'s binary representation to be shifted ```j``` places to the right.
         * If ```i``` has an unsigned type or a nonnegative value, for each bit shifted off the right end of ```i```, a ```0``` is introduced at the left end.
         * If ```i``` has a negative value, the result is implementation-defined.
            * Some implementations add a ```0``` for every bit shifted off the right end of ```i```.
            * Some implementations add a ```1``` for every bit shifted off the right end of ```i``` to preserve the sign.
* It's usually best to avoid performing bit shifting on signed numbers to ensure we always write portable programs.
* Since neither bitwise shift operator has side effects, C provides bitwise shift compound assignment operators ```<<=``` and ```>>=```.
* C's bitwise right and left shift operators have the same level of precedence.
* C's bitwise shift operators are left-associative.
* C's bitwise shift operators have lower precedence compared to C's arithmetic operators.

### :small_blue_diamond: Bitwise Complement, And, Exclusive Or and Inclusive Or Operators

* C's bitwise complement operator ```~``` is unary.
   * It requires a single integer operand.
   * Integer promotions are performed on its operand.
* C's bitwise and ```&```, bitwise exclusive ```^``` and inclusive or ```|``` operators are binary.
   * They require two integer operands.
   * The usual arithmetic conversions are performed on their operands.
* All four operators perform boolean operations on their operands at the bit level.
   * ```~``` produces the complement of its operand.
      * ```0```s are replaced by ```1```s and vice versa.
   * ```&``` performs a boolean and operation on every pair of corresponding bits in its operands.
      * ```0 & 0 = 0```.
      * ```0 & 1 = 0```.
      * ```1 & 1 = 1```.
      * ```&``` is commutative.
   * ```^``` performs a boolean exclusive or operation on every pair of corresponding bits in its operands. Two ```1```s produce a ```0```.
      * ```0 ^ 0 = 0```.
      * ```0 ^ 1 = 1```.
      * ```1 ^ 1 = 0```.
      * ```^``` is commutative.
   * ```|``` performs a boolean inclusive or operation on every pair of corresponding bits in its operands. Two ```1```s produce a ```1```.
      * ```0 | 0 = 0```.
      * ```0 | 1 = 1```.
      * ```1 | 1 = 1```.
      * ```|``` is commutative.
* It's important not to confuse the bitwise ```&``` and ```|``` operators with the logical ```&&``` and ```||``` operators respectively.
* To ensure program portability, C programmers usually use the bitwise complement operator ```~``` for several purposes.
   * ```~0``` produces an integer with all ```1```s irrespective of its size.
   * ```~0x7``` produces an integer with all ```1```s except for the three least significant bits, irrespective of its size.
* All four operators have the following relative level of precedence from highest to lowest:
   * The bitwise complement operator ```~```.
   * The bitwise and operator ```&```.
   * The bitwise exclusive or operator ```^```.
   * The bitwise inclusive or operator ```|```.
* C's bitwise shift operators have lower precedence compared to the bitwise complement operator ```~``` and higher precedence compared to the remaining three bitwise operators.
* All four operators have lower precedence compared to C's relational and equality operators.
   * This leads to common traps. Assuming ```a``` is an integer variable:
      * ```a & 5 == b``` is equivalent to ```a & (5 == b)``` which is perhaps not what first comes to mind when writing such an expression.
* All four operators do not have side effects. For this reason, C provides corresponding compound assignment operators:
   * ```~=```.
   * ```&=```.
   * ```^=```.
   * ```|=```.
* C's bitwise operators can be used to achieve some of the most common low-level operations. Assuming ```i``` is an integer variable and ```j``` is an integer:
   * Setting a bit: ```i |= 1 << j``` sets the ```j```th bit in ```i``` (assuming the least significant bit is bit ```0```).
   * Clearing a bit: ```i &= ~(1 << j)``` clears the ```j```th bit in ```i``` (assuming the least significant bit it bit ```0```).
   * Testing a bit: ```i & 1 << j``` produces a nonzero value if the ```j```th bit in ```i``` is set, and produces ```0``` otherwise.
* When working with bit fields instead of individual bits, single bitwise operations are usually not enough to achieve what we want. Assuming ```i``` is an integer variable and ```j``` is an integer:
   * Suppose we want to set the bits that make up ```j``` in a certain position in ```i```.
      * First thing to do is to determine the width of the bit field to be set. We'll call this width ```w```.
      * Next, we need to determine the position at which we want to insert ```j```'s bits. We'll call this position ```p```.
      * Let ```a``` be the integer formed by the bit field with width ```w``` shifted to position ```p``` containing all ```1```s with everything else being ```0```.
      * ```i & a | j << p``` inserts ```j``` into ```i``` at position ```p```.
         * Example: If we want to insert ```101``` in ```i``` at position 4-6:
            * ```j``` is ```101``` in this case.
            * ```j```'s width is ```3```.
            * The insert position into ```i``` is ```4```.
            * ```a``` is ```0x0070```.
            * ```i & 0x0070 | 0x0050``` inserts ```j``` into ```i``` at position ```4```.
            * A more general form would be ```i & 0x0070 | j << 4```.
   * Suppose we want to retrieve a bit field with a particular width at a particular position from an integer variable ```i```.
      * First thing to do is to determine the width of the bit field to be set. We'll call this width ```w```.
      * Let ```a``` be the integer formed by the bit field with width ```w``` containing all ```1```s at the right end.
      * If the bit field is at the right end of ```i```:
         * ```i & a``` retrieves the bit field of width ```w``` from ```i```.
      * If the bit field is not at the right end of ```i```:
         * Let ```p``` be the position at which the bit field in ```i``` starts.
         * ```(i >> p) & a``` retrieves the bit field of width ```w```, at position ```p``` from ```i```.

## :clamp: Bit-Fields In Structures

* C allows using bit fields in structure members of type ```int```, ```unsigned int``` and ```signed int```.
   * Assuming ```date_t``` is a structure type used to represent a date:
   ```c
   struct date_t {
      unsigned int day: 5;
      unsigned int month: 4;
      unsigned int year: 7;
   };
   ```
   * The number after each colon ```:``` represents the structure member's length in bits.
   * The declaration can be made shorter since all three bit fields have the same type:
   ```c
   struct date_t {
      unsigned int day: 5, month: 4, year: 7;
   };
   ```
* A bit field's type must be either ```int```, ```unsigned int``` or ```signed int```.
   * Using ```int``` may hurt program portability because some compilers will treat the most significant bit in the bit field as a sign bit, while others won't.
   * To ensure we write portable low-level programs, it's best to use ```unsigned int``` or ```signed int``` for bit fields.
* C99 allows bit fields to be of type ```_Bool```.
* Bit fields can be accessed and used just like any other structure member.
* Since bit fields in structures don't have ordinary addresses in memory, C prohibits applying the address operator ```&``` to a bit field.
   * For this reason, functions like ```scanf``` can't read data directly into a bit field.
   * C still allows assignment to a bit field.
* How a compiler processes the declaration of a structure that has bit field members depends on the concept of "storage unit".
   * A storage unit is the smallest unit of data storage in main memory.
   * The size of a storage unit is implementation-defined. Typical values are ```8```, ```16``` and ```32``` bits.
   * The compiler processes bit field structure members one by one, storing them contiguously in a storage unit with no holes in between.
   * When the remaining space in a storage unit is not enough to store the next bit field, the compiler's behavior is implementation-defined.
      * Some compilers skip to the start of the next storage unit.
      * Other compilers split the bit field between both storage units.
   * Whether bit fields are stored from right to left or left to right inside a storage unit is implementation-defined.
* C allows adding nameless bit fields as structure members.
   * These bit fields serve as paddings to ensure other bit fields are positioned correctly inside a storage unit.
   ```c
   struct date_t {
      unsigned int day: 5;
      unsigned int : 4;
      unsigned int year: 7;
   };
   ```
   * The second bit field member in the previous example is not named. The compiler will therefore leave it out.
   * The ```year``` bit field will still be positioned as if the second member existed.
   * Some C programmers set an unnamed bit field's length to ```0```. This effectively tells the compiler to skip to the start of the next storage unit before storing the next bit field.

## :hammer_and_wrench: Other Low-Level Techniques

## :game_die: Miscellaneous