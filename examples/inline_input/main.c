/**
 * @file main.c
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2025
 * @version 1.0
 * 
 * @copyright MIT License
 * 
 * @brief Main entry point for testing the math parser.
 *
 * This file provides a simple example of how to use the math parser
 * library to tokenize and (in the future) evaluate a mathematical expression.
 */

/* --- Imports --- */
#include "mathParser.h"
#include <stdio.h>
/* --- End of Imports --- */

/* --- main() --- */
// Get inputs from the user via the command line
int main(int argc, char *argv[] ) {

    /* --- Command Line Argument Check --- */
    if (argc != 2) {
        printf("Usage: %s \"<expression>\"\n", argv[0]);
        return 1;
    }
    /* ----------------------------------- */

    /* --- Input Expression --- */
    const char *expr = argv[1]; // Get the expression from command line arguments
    /* ------------------------ */

    /* --- Parse and Evaluate --- */
    double result = textCalc(expr);
    /* -------------------------- */

    /* --- Output Result --- */
    printf("Result: %f\n", result); // Placeholder output
    /* --------------------- */

    return 0;
}
/* --- End of main() --- */
