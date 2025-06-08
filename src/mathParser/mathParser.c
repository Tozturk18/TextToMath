/**
 * @file mathParser.c
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2025
 * @version 1.0
 * 
 * @copyright MIT License
 * 
 * @brief Implementation of the main parsing interface.
 *
 * This file provides the textCalc() function which utilizes the tokenizer
 * and utility functions to parse a mathematical expression into tokens.
 */

/* --- Imports --- */
#include "mathParser.h"
#include "mathStructs.h"
#include "tokenizer.h"
#include "shuntingYard.h"
#include "evaluator.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
/* --- End of Imports --- */

/* --- textCalc() --- */
double textCalc(const char *input_expr) {

    /* --- Input Buffer --- */
    char expr[512];
    strncpy(expr, input_expr, sizeof(expr) - 1);
    expr[sizeof(expr) - 1] = '\0'; // Ensure null-termination
    /* -------------------- */

    /* --- Pre-processing: Remove Spaces --- */
    removeSpace(expr);
    /* ------------------------------------- */

    /* --- Token Arrays --- */
    Token infixTokens[MAX_TOKENS];
    Token postfixTokens[MAX_TOKENS];
    //uint32_t nInfix = tokenize(expr, infixTokens);
    tokenize(expr, infixTokens);
    /* -------------------- */

    /* --- Shunting-Yard: Infix → Postfix --- */
    //uint32_t nPostfix = shuntingYard(infixTokens, postfixTokens);
    shuntingYard(infixTokens, postfixTokens);
    /* ------------------------------------- */

    /* --- Evaluate Postfix Expression --- */
    double result = evaluatePostfix(postfixTokens);
    /* ------------------------------------ */

    return result;
}
/* --- End of textCalc() --- */


#define MAX_OUTPUT_LENGTH 128  // Updated for larger outputs

/**
 * @brief Evaluates the input expression and returns result as a clean scientific string.
 * 
 * @param input_expr  Input mathematical expression string.
 * @param output_buffer  Buffer to store the result string.
 * @param buffer_size  Size of the output buffer.
 * @return Pointer to the output_buffer containing the formatted result.
 */
char* textCalcString(const char *input_expr, char *output_buffer, size_t buffer_size) {
    char expr[512];
    strncpy(expr, input_expr, sizeof(expr) - 1);
    expr[sizeof(expr) - 1] = '\0';

    removeSpace(expr);

    Token infixTokens[MAX_TOKENS];
    Token postfixTokens[MAX_TOKENS];
    tokenize(expr, infixTokens);
    shuntingYard(infixTokens, postfixTokens);

    double result = evaluatePostfix(postfixTokens);

    // Format to scientific notation with high precision
    char temp_buffer[128];
    snprintf(temp_buffer, sizeof(temp_buffer), "%.15e", result); // 15 decimal digits

    // Find 'e'
    char *e_ptr = strchr(temp_buffer, 'e');
    if (e_ptr) {
        char *dot_ptr = strchr(temp_buffer, '.');
        if (dot_ptr) {
            char *last_nonzero = e_ptr - 1;
            while (last_nonzero > dot_ptr && *last_nonzero == '0') {
                last_nonzero--;
            }
            // Only modify before 'e'
            if (last_nonzero == dot_ptr) {
                // Only '.' left, remove it too
                memmove(dot_ptr, e_ptr, strlen(e_ptr) + 1);
            } else {
                // Move everything after last nonzero to 'e'
                memmove(last_nonzero + 1, e_ptr, strlen(e_ptr) + 1);
            }
        }
    }

    snprintf(output_buffer, buffer_size, "%s", temp_buffer);
    return output_buffer;
}
