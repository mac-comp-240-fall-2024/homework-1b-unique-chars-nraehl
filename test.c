/*
 * Test program for hasUniqueChars.c
 * 
 * Description: This program tests the hasUniqueChars function to verify 
 * that it correctly identifies strings with unique characters, accounting 
 * for various cases including duplicates, spaces, special characters, 
 * and non-printing characters.
 * 
 * Author: Noel Raehl
 * 
 */

#include <stdio.h>    // printf
#include <stdbool.h>  // to define a boolean type and true, false
#include <string.h>   // strcpy to copy a string
#include <assert.h>

// Declaration of function from hasUniqueChars.c
bool hasUniqueChars(char * inputStr);

int main() {
    /* Example 1 */
    char string1[] = "A string declared as an array.\n";

    /* Example 2 */
    char *string2 = "A string declared as a pointer.\n";

    /* Example 3 */
    char string3[128];
    strcpy(string3, "A string constant copied in.\n");

    // printf ("%s", string1);
    // printf ("%s", string2);
    // printf ("%s", string3);

    // -------------------------------------------------------------
    // Tests of hasUniqueChars()  
    bool ok;
  
    // Test 1: A test case that should return false because characters are duplicated
    strcpy(string3, "This should fail (l and s and i and h)");
    ok = hasUniqueChars(string3);
    assert(!(ok));
  
    // Test 2: This should return true as all characters are unique
    strcpy(string3, "abcdefghij");
    ok = hasUniqueChars(string3);
    assert(ok);
  
    // Test 3: String with unique alphanumeric characters (should return true)
    strcpy(string3, "12345abcDEF");
    ok = hasUniqueChars(string3);
    assert(ok);

    // Test 4: String with multiple spaces (should return true since spaces are ignored)
    strcpy(string3, "a b c d e");
    ok = hasUniqueChars(string3);
    assert(ok);

    // Test 5: String with duplicate special characters (should return false)
    strcpy(string3, "!!@@##");
    ok = hasUniqueChars(string3);
    assert(!(ok));

    // Test 6: Non-printing character (should trigger an error)
    strcpy(string3, "Hello\x01World");
    ok = hasUniqueChars(string3);

    // Test 7: Edge case with maximum number of unique characters (should return true)
    strcpy(string3, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
    ok = hasUniqueChars(string3);
    assert(ok);

    // Additional test case for string with duplicates
    strcpy(string3, "a b cc\n");
    ok = hasUniqueChars(string3);
    assert(!(ok));

    return 0;
}
