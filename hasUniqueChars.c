/*
 * hasUniqueChars.c
 * 
 * TODO: replace this line with lines containing a description
 * 
 * Author: 
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"


/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}


// TODO: Read this carefully to see how to loop over characters of a string
// TODO: (Remove TODOs once you have completed the task they describe)
/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}


/*
 * TODO: Replace this code by a good description this function takes in, does and returns.
 * Include the error conditions that cause it to exit with failure.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp =0;  // for checking ! though @ 

  char nextChar;         // next character in string to check

  // -------------------------------------------------------------
  // This section contains code to display the initial values of checkBitsA_z
  // and checkBitsexcl_amp, for debugging purposes. 
  // It also illustrates how to use the seeBits function for debugging.
  // Printed values should initially be all zeros
  // TODO: remove or comment out this code when satisfied of function correctness
  
  char debug_str_A_z[128];
  strcpy(debug_str_A_z, "checkBitsA_z before: \n");
  seeBits(checkBitsA_z, debug_str_A_z);
  
  char debug_str_excl_amp[128];
  strcpy(debug_str_excl_amp, "checkBitsexcl_amp before: \n");
  seeBits(checkBitsexcl_amp, debug_str_excl_amp);
  // -------------------------------------------------------------

  // TODO: Declare additional variables you need here

  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    // TODO: Add your code here to check nextChar, see if it is a duplicate, and update the checkBits variables

    // -------------------------------------------------------------
    // Below this are examples of debugging print statements you could use
    // Move/use as makes sense for you!
    // Modify to work on checkBitsexcl_amp
    // TODO: Comment out or remove when your function works correctly
    printf("nextchar int value: %d\n", nextChar);
    char char_str[2] = "\0";
    char_str[0] = nextChar;
    strcpy(debug_str_A_z, "nextchar: ");
    strcat(debug_str_A_z, char_str);
    strcat(debug_str_A_z,", checkBitsA_z: \n");
    seeBits(checkBitsA_z, debug_str_A_z);
    // ------------------------------------------------------------- 
  }

  // if through all the characters, then no duplicates found
  return true;
  
}
