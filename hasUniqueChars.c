/*
 * hasUniqueChars.c
 * 
 * (replace this line with lines containing a description)
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

///// Note that the following function is used below and
///// is an example of how to loop through a string one
///// character at a time.
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
 * You write the description of what this function does and returns.
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

// see ascii_table.txt

  ///////////////////////////////////////////////
  // debug (remove or comment when satisfied of correctness)
  
  char debug_str_A_z[128];
//   strcpy(debug_str_A_z, "checkBitsA_z before: \n");
//   seeBits(checkBitsA_z, debug_str_A_z);
  
  char debug_str_excl_amp[128];
//   strcpy(debug_str_excl_amp, "checkBitsexcl_amp before: \n");
//   seeBits(checkBitsexcl_amp, debug_str_excl_amp);
  
  // initially, these strings should contain all zeros
  
  /////////////////////////// end debug

  // you will want to declare more variables here

  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    
    ///////////// debug 
    ///////////// move where useful
    //////////////(remove when your function works)
//     printf("nextchar int value: %d\n", nextChar);
//     char char_str[2] = "\0";
//     char_str[0] = nextChar;
//     strcpy(debug_str_A_z, "nextchar: ");
//     strcat(debug_str_A_z, char_str);
//     strcat(debug_str_A_z,", checkBitsA_z: \n");
//     seeBits(checkBitsA_z, debug_str_A_z);
    // you can do something very similar for checkBitsexcl_amp
    //////////////// end debug

    

  }

  // if through all the characters, then no duplicates found
  return true;
  
}

