# The Problem

This is a classic problem that has been posed many times (including for the dreaded coding interview by employers). The problem is this:

#### Given a string of characters, which are encoded in ascii, determine if the string contains all unique characters.


There are many solutions in various languages, some of which are straightforward, but at the same time may be inefficient. Others may perform fairly well, but are rather incomplete (they don't cover all ascii characters that are easy to check). Perhaps the most vexing issue with many proposed solutions is that they do not handle cases when a string contains characters it does not expect. The web is filled with examples that are too simple and not exhaustive. Writing and using code like this has consequences. **Your goal** is to use what you learn about how ascii characters are encoded as bits, and therefor numbers. The problem can be solved using the numerical representation of all possible characters and some special unsigned long integers that you treat as 'bit vectors' (described further below).

The 128 fundamental ascii characters are found in the file provided called
`ascii_table.txt`. This is purely a reference and is not designed to be part of
your code solution.



## Starter code you are given

For this problem, you already have a `Makefile` that you can use to build your
code as you work. The executable, called **hasUniqueChars**, is created by the
gcc compiler from 3 C code files.

1. The `binary_convert.c`file and its binary_convert.h file are just as you had
used in the Data Activities. As you have seen, it has functions that you can use
to help you debug your code. You should not need to change this file. You should
study it, however (some code is like what you will need to do).

2. The file where you should create the necessary function that will determine
whether a given string has unique characters in it or not is called
`hasUniqueChars.c`. The name of the function you will complete is also called
*hasUniqueChars*. Note that you are also required to document this function by
replacing the comment immediately above it in the code file.

    - In the code given to you in `hasUniqueChars.c`, the function declared as
      `void checkInvalid(char * inputStr)` is designed to fail and exit if it
      finds a non-printing character, which are listed in the first, or left
      column of the four columns of characters listed in ascii_table.txt. See
      the Notes below for more information about how some of these characters
      can be added to C strings by 'escaping' them using an *escape sequence*.
      This will enable you to test whether *hasUniqueChars* will fail on a
      string containing non-printing characters.

3. The file that will contain all your exhaustive tests of your *hasUniqueChars*
function is `test.c`. A few very basic tests are provided, but you must be much
more careful and exhaustive, adding enough tests to be certain your function
works for *all cases of character that you can create in a string*. Document
this file at the top with a description and your name, and make sure that you
describe your tests.

    - Until you have a correct version of *hasUniqueChars*, the initial code
      that builds will fail on one of the asserts.

4. The Makefile is given for you.

## How it should run

The graders should be able to do the following:

    make clean
    make
    ./hasUniqueChars

## What you must complete

### The function hasUniqueChars in hasUniqueChars.c

You must complete the function defined like this:

```
bool hasUniqueChars(char * inputStr)
```

This function should do the following:

- Take any length of input string (variable inputStr), provided as an array of
  chars. The characters in the array could be 'non printing', which are aded to
  a string using an 'escape' character sequence (you will need to lookup and
  investigate this- there is one reference at the bottom of this page).
- Fail and exit the program if a non-printing character, including DEL (ascii
  value 127) is in the string, regardless of the other characters.
- Return a `bool` (find documentation on the C library stdbool.h) value of true
  if every character, ignoring spaces, only occurs once in the input string.
- The space character is the only ascii character that can be repeated in the
  input string and still result in hasUniqueChars returning true.

You should implement this function by using what you know about the integer
representation used for each ascii character. The code that you are given in
`hasUniqueChars.c` contains two variables that form the key for completing a
solution that needs only bitwaise operators inside of the main for loop that
checks every character in the string. These variables are:

```
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp =0;  // for checking ! though @ 
```

The idea behind a solution that can work with all non-printing characters and
uses only these two additional unsigned long variables is as follows:

Your compiler, gcc, compiles and stores variables declared as `unsigned long`
using 8 bytes, or 64 bits in the default 64-bit Intel instruction set. You can
use each of the 64 bits of an unsigned long as indicators of whether a certain
character has been seen yet in a string. We can think of `checkBitsA_z` as a bit
vector, where we set a 1 in a position if a character has been encountered in a
string. The mapping of ascii characters to poistions in this bit vector
`checkBitsA_z` can be like this:

|index of bit in checkBitsA_z | ascii char | char value|
|-----------------------------|------------|-----------|
|0 | A | 65 |
|1 | B | 66 |
|...|...|...|
|25| Z | 90 |
|...|...|...|
|61 | ~ | 126 |

Notice that bits 62 and 63 will not be needed. What this means is that if given
an input string "AB}", then after checking each of the three characters,
`checkBitsA_z` should look like this in binary (spaces have been added after
every 4 bits for readability):

    0001 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

Bit 0 of `checkBitsA_z` is on the right in the above depiction, and got set to 1
for the A in the input string. Bit 63 of `checkBitsA_z` is on the left (not
used, so will always stay 0).

#### Important
Any `char` variable, such as the one called `nextChar` in the code, can be
treated like an integral number and used in mathematical expressions in C
using + or -. Thus, you can easily determine the index into a bit vector for
each character you encounter by doing math on the character. You need to
determine what the expression is to compute the number of the bit in the
vector.

Next think about how you can place a one in that position of a temporary
variable, which can be used as a mask.

So for any of the ascii characters whose numeric value is between 65 and 126
inclusive, the bit vector `checkBitsA_z` can be used to mark whether a character
has been seen already. The function can loop through each character in the input
string (this loop is given to you in the code) and stop early and return false
whenever a bit for a particular character is already set. If it is not, then it
should be set. If the loop never stops early, then all the characters were
unique. However, this also must be done for the other possible ascii characters:

The other bit vector, `checkBitsexcl_amp`, can be used for the characters whose
decimal values range from 33 to 64. (More bits of this vector will remain
unused- 32 through 63).

|index of bit in checkBitsexcl_amp | ascii char | char value|
|-----------------------------|------------|-----------|
|0 | ! | 33 |
|1 | " | 34 |
|...|...|...|
|31| @ | 64 |

You can use this vector for checking and marking for any characters whose value
is between 33 and 64, inclusive.

#### Rules for the function hasUniqueChars

1. Use any of the following bitwise operators to make checks in the loop:

    << >> & | ~ ^

You will not need all of these.

2. You are also free to use any other operators that work on numerical
variables, such as +, -, \*, <, >.

3. You may also use relational operators in if statements (!, &&, ||).

4. You might be tempted to use any functions in the C library ctype.h, but this
strategy will likely make your code more complicated. You should just treat
nextChar as an integral value.

### Complete the test.c file

Complete enough tests to fully check your hasUniqueChars function. This means
**complete and exhaustive** testing, using examples that should return true,
those that should return false, and those that should fail and exit the program.
Use asserts for each test.

## How you will be graded

Your code should:

- use asserts for your tests
- follow the coding guidelines found on the previous page of this unit
- work correctly on exhaustive test cases you have created and described
- have all debug statements removed or commented
  This means the only output should be from the error conditions, like this:
  
	$ ./hasUniqueChars
	invalid character in string

## Some notes

### Declaring and creating strings

These examples are taken from [this C tutorial
site](http://www.crasseux.com/books/ctutorial/Initializing-strings.html), with
some additional comments and bug fixes- beware that not all examples online are
correct!

There are three examples of how to declare and initialize strings in C given in
the main() of text.c. They are:

```
  /* Example 1 */
  char string1[] = "A string declared as an array.\n";

  /* Example 2 */
  char *string2 = "A string declared as a pointer.\n";

  /* Example 3 */
  char string3[128];   // can copy in up to 127 characters
                       // chose 128 because it is a multiple of 8 bytes
  strcpy(string3, "A string constant copied in.\n");
  
  printf ("%s", string1);
  printf ("%s", string2);
  printf ("%s", string3);
  
```

What follows are an explanation of each one.

```
/* Example 1 */
  char string1[] = "A string declared as an array.\n";
```

This is often the best way to declare and initialize a string that should keep a
constant value and not change. The character array is declared explicitly. There
is no size declaration for the array; just enough memory is allocated for the
string, because the compiler knows how long the string constant is. The compiler
stores the string constant in the character array and adds a null character (\0)
to the end. This works well if you don't intend to change the string and wish to
treat it as a constant.

```
  /* Example 2 */
  char *string2 = "A string declared as a pointer.\n";
```

The second of these initializations is a pointer to an array of characters. Just
as in the first example, the compiler calculates the size of the array from the
string constant and adds a null character. The compiler then assigns a pointer
to the first character of the character array to the variable string2.

Note: Most string functions will accept strings declared in either of these two
ways. Consider the printf statements at the end of the example program above --
the statements to print the variables string1 and string2 are identical.

```
  /* Example 3 */
  char string3[128];
  strcpy(string3, "A string constant copied in.\n");
```
  
Declaring a string in this way is useful when you don't know what the string
variable will contain, but have a general idea of the length of its contents (in
this case, the string can be a maximum of 128 characters long). The drawback is
that you will either have to use some kind of string function to assign the
variable a value, as the next line of code does (strcpy(string3, "A string
constant copied in.\n");), or you will have to assign the elements of the array
the hard way, character by character. (See string.h library functions for more
information on the function strcpy.)

### Escape sequences

Some special ascii non-printing characters need to be represented in a character
string using what is called an *escape sequence*. Please read about this on the
[Wikipedia page](https://en.wikipedia.org/wiki/Escape_sequences_in_C) devoted to
describing them. 






