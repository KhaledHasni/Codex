/* Takeaways */

/*
1) C came about as a by-product of the UNIX operating system, which was a project undertaken by the engineering team at Bell Laboratories (D&R branch of Nokia today).
2) The first version of UNIX was written by Ken Thompson in 1969 in assembly and it ran on a minicomputer with 8K words of main memory called the DEC PDP-7.
3) Programs written in assembly are notorious for being hard to debug and tough to enhance and UNIX in its original version was no exception. Recognizing this fact,
Thompson decided to create a higher level language to further the development of UNIX. His efforts culminated in the creation of a small language that he called B.
4) The name B was most likely inspired from another language which B was inspired from called BCPL (Basic Combined Programming Language) created by Martin Richards
which also traces its ancestry back to another language known as ALGOL 60.
5) In 1970, Dennis Ritchie joined the UNIX project and began programming in B.
6) Soon after, Bell Labs acquired a new computing system called the PDP-11 and the team immediately got it to run B programs. But it soon became apparent that B
wasn't suited for this new platform.
7) Ritchie started developing an extended version of B that he initially called NB (short for "New B") to make suitable for the PDP-11, but as NB continued to drift
further away from B, he decided to drop the B junction and named it C.
8) By 1973, C had become stable enough that the team decided to completely rewrite UNIX in C, write C compilers for all machines they had and get UNIX running on all
those machines. This was C's first big win in terms of portability.
9) C's evolution continued past 1973 and peaked in the late 70s, especially between 1977 and 1979.
10) The first book about C was published in 1978 by Brian Kernighan and Dennis Ritchie of Bell Labs and it was called "The C programming language" a.k.a the white book.
11) At this time and throughout the 70s, there were few C programmers and most of them were involved with UNIX in some way. In the 1980s however, C had grown to an
extent that C was being run on different platforms, under various operating system and had basically broken away from the confines of being the language associated with
UNIX.
12) This didn't come without its problems though. Since many programmers running C on these different platforms had to write their own C compilers, and the fact that
there was no single reference or standard for the language at this time, differences in how to handle certain features of C started to emerge.
13) At this time, K&R's "The C programming language" was being used as the go-to reference for C to write all these different compilers, but this document has some
deficiencies:
    *) It was fuzzy about some C features --> Compiler developers interpreted them differently --> C behaved differently on different platforms.
    *) It didn't make the distinction between what was inherently part of the language and what was part of UNIX.
    *) C continued to evolve after its publication therefore it quickly became obsolete.
14) This state of affairs was threatening what C had set out to establish from the onset, which was to create portable systems.
15) The need for a clear, concise and unambiguous standard for the language became very clear.
16) The American National Standards Institute (ANSI for short) started working on creating a US C standard in 1983, finished it in 1988 and it was formally approved
in 1989. Largely the same standard with slight editorial amendments was approved by the International Standards Organization (ISO) in 1990. This version of language
was called C89 or sometimes C90 in contrast to the earlier not standardized version known colloquially as K&R C.
17) C continued to evolve past this point and in 1995, it underwent small changes in the form of an amendment called amendment 1.
18) In 1999, C underwent its most significant change to date in the form of a new standard produced by ISO. This new version of the language was called C99.
19) The line between what is ISO C, ANSI C and what is not became blurry ever since C99 came into the picture. But it's safe to say that when someone refers to ANSI C
they most likely mean C89. When they refer to ISO C, they most likely mean C99 or the latest C standard released by ISO.
20) C influenced a lot of modern programming languages. Some examples of such languages include:
    *) C++: Inherited all the features of C and added object-oriented features and better data structure handling.
    *) Java: Based on C++.
    *) C#: Based on C++ and Java.
    *) Perl: Started out as a scripting language but quickly evolved as it kept getting influenced by C.
21) It might be tempting to wonder whether it's even worth learning C if all these languages already include many of C's features, and some of them, by most metrics have
superseded C. To make the case for why one might still want to learn C, we can say:
    *) A lot of C-based languages try to abstract away some of C's most fundamental and core concepts which may be notoriously hard to understand. Learning such
C-based languages without learning C first might result in a lack of understanding of those core concepts. Even though a programmer might not need them when writing
programs in such languages, they still are being implemented under the hood.
    *) A lot of projects that are still being used today (important ones for that matter) are written in C. One might need to read that code and understand or might
be put in a position where they have to maintain C code.
    *) C is a great language for programming resource-constrained devices, devices with limited processing power or when the overhead of other languages is not welcome.
Programming embedded devices is a good example.
22) C was originally designed to develop an operating system, so it's meant for systems programming from the onset. This leads to several facts:
    *) C is a low-level language: It deals with low-level concepts that other languages simply try to hide like addresses and bytes. The idea here is that C was
designed to be as fast as possible so it had to strip away all layers of abstraction and be as raw and as close to the hardware as possible. We have to bear in mind
that it was originally meant to be used to develop an operating system; a software that other applications will have to rely on to perform many utilities like
storage management and input and output. This meant that C had no choice but to be fast and low-level.
    *) C is a permissive language: It assumes the programmer knows what they're doing and doesn't try to exert boundaries on them. It doesn't enforce a rigorous
error-checking policy like many other languages try to do.
    *) C is a small language: C offers very few features compared to other languages but it relies on its extended standard library for a lot of what it has to offer.
23) C has many strengths:
    *) Efficiency: C is often the go-to language when a program needs to run on a platform with limited memory or processing power.
    *) Portability: C is often the go-to language when a program needs to run on a wide range of different platforms.
    *) Flexibility: C allows many quirks that other languages prohibit like adding characters to integers. This might make programming easier.
    *) Power: C can accomplish a lot with just a few lines of code.
    *) Standard library: C's standard library and its wide range of functions offer the language a great deal of versatility.
    *) UNIX: C is particularly powerful when used with UNIX or one of its variants including Linux.
24) C has some weaknesses that usually stem from its closeness to the machine:
    *) C programs can be error-prone: The fact that C is both permissive and flexible can be a source of trouble. Some of C's most frustrating bugs and errors are
usually not detected by compilers, rather they show at runtime in the form of unexpected behavior. In this respect, C is much like assembly.
    *) C programs can be hard to read: It's common for a C program not to be understood by a reader, although it's perfectly obvious what it does to the person who
wrote it. Programmers trying to be cheeky and clever, of course, doesn't help either.
    *) C programs can be hard to change: C doesn't offer classes or packages or other containment concepts that break down programs into smaller, more manageable
pieces.
25) To write effective C code:
    *) Avoid C's pitfalls: A programmer will become familiar with many of these pitfalls the more C code they write.
    *) Use available C libraries: Much of what a programmer is trying to achieve, will have most likely been solved already by some other C programmer. It's a good
idea to use other people's C programs that come in the form of functions bundled together to form libraries, some of which are open source, and some of which are
locked behind a paywall.
    *) Avoid tricks: C tempts programmers to solve problems in the most concise way. It's best to steer away from this kind of thinking.
    *) Use debuggers to catch run-time errors and other tools like leak finders (Valgrind for example) and bound-checkers to unearth potential issues.
    *) Apply a coding convention and abide by it.
    *) Stick to the standard: Many C compilers offer features and library functions that are not compliant with either C89 or C99. It's best to avoid these to write
portable C programs.
*/