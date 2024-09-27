/*
 * hasUniqueChars.c
 * 
 * This program checks if a string has only unique printable characters,
 * meaning no characters are repeated. It uses bitwise operations to track 
 * which characters have been seen and exits if it encounters any invalid 
 * characters (non-printing ASCII values).
 * 
 * Author: Noel Raehl
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  // useful character operations
#include <stdbool.h> // to define a boolean type and true, false

#include "binary_convert.h"

/*
 * This function is for debugging by printing out the value
 * of an input unsigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
    char *bin_str = ulong_to_bin_str(value);
    printf("%s%s\n", debug_text, bin_str);
    free(bin_str);
}

/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char *inputStr) {
    char nextChar;
    int i;

    for (i = 0; i < strlen(inputStr); i++) {
        nextChar = inputStr[i];

        if ((nextChar <= 31) || (nextChar == 127)) {
            fprintf(stderr, "invalid character in string\n");
            exit(EXIT_FAILURE);
        }
    }
}

/*
 * This function checks if the input string contains only unique printable
 * characters, ignoring spaces. It uses two bit vectors to track which 
 * characters have been seen. It returns true if all characters are unique, 
 * and false if any duplicates (other than spaces) are found.
 */
bool hasUniqueChars(char *inputStr) {
    unsigned long checkBitsA_z = 0;       // For 'A' through '~' (ASCII 65-126)
    unsigned long checkBitsexcl_amp = 0;  // For '!' through '@' (ASCII 33-64)

    int i;
    char nextChar;

    for (i = 0; i < strlen(inputStr); i++) {
        nextChar = inputStr[i];

        if (nextChar == ' ') {
            continue;
        }

        // Characters from 'A' to '~' (ASCII 65 to 126)
        if (nextChar >= 'A' && nextChar <= '~') {
            int bitIndex = nextChar - 'A'; 

            // Check if the bit is already set in checkBitsA_z
            if ((checkBitsA_z >> bitIndex) & 1) {
                return false; 
            }
            checkBitsA_z |= (1UL << bitIndex);  
        }
        // Characters from '!' to '@' (ASCII 33 to 64)
        else if (nextChar >= '!' && nextChar <= '@') {
            int bitIndex = nextChar - '!'; 

            // Check if the bit is already set in checkBitsexcl_amp
            if ((checkBitsexcl_amp >> bitIndex) & 1) {
                return false; 
            }
            checkBitsexcl_amp |= (1UL << bitIndex);  
        }
    }

    return true;
}