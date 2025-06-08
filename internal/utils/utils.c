/**
 * @file utils.c
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2025
 * @version 1.0
 * 
 * @copyright MIT License
 * 
 * @brief Implementation of utility functions for tokenizer and parser modules.
 *
 * This file provides basic helper functions for string manipulation and
 * character classification.
 */

/* --- Imports --- */
#include "utils.h"
#include <ctype.h>
/* --- End of Imports --- */

/* --- removeSpace() --- */
void removeSpace(char *str) {
    /* --- Pointer Initialization --- */
    char *i = str;    // Traversal pointer
    /* ------------------------------- */

    /* --- Whitespace Removal Loop --- */
    do {
        while (isspace((unsigned char)*i)) {
            ++i;      // Skip whitespace
        }
    } while ((*str++ = *i++) != '\0');
    /* -------------------------------- */
}
/* --- End of removeSpace() --- */

/* --- isFuncChar() --- */
int isFuncChar(char c) {
    /* --- Valid Function Character Check --- */
    // Check if character is alphabetic, digit, '-' or '>'
    return (isalpha((unsigned char)c) || isdigit((unsigned char)c) || c == '=' || c == '>');
    /* --------------------------------------- */
}
/* --- End of isFuncChar() --- */
