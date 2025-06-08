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

#define MAX_OUTPUT_LENGTH 64 // Enough for a double in scientific notation

/* --- textCalcString() --- */
char* textCalcString(const char *input_expr, char *output_buffer, size_t buffer_size) {

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
    tokenize(expr, infixTokens);
    /* -------------------- */

    /* --- Shunting-Yard: Infix → Postfix --- */
    shuntingYard(infixTokens, postfixTokens);
    /* ------------------------------------- */

    /* --- Evaluate Postfix Expression --- */
    double result = evaluatePostfix(postfixTokens);
    /* ------------------------------------ */

    /* --- Format Result to Scientific Notation --- */
    char temp_buffer[MAX_OUTPUT_LENGTH];
    snprintf(temp_buffer, sizeof(temp_buffer), "%.10e", result);
    /* --------------------------------------------- */

    /* --- Intelligent Trimming of Zeros --- */
    char *e_ptr = strchr(temp_buffer, 'e'); // Find where 'e' starts
    if (e_ptr) {
        char *dot_ptr = strchr(temp_buffer, '.');
        if (dot_ptr) {
            char *end_ptr = e_ptr - 1; // Move left before 'e'
            // Remove trailing zeros
            while (end_ptr > dot_ptr && *end_ptr == '0') {
                *end_ptr = '\0';
                end_ptr--;
            }
            // If dot is last, remove dot too
            if (end_ptr == dot_ptr) {
                *end_ptr = '\0';
            }
        }
    }

    // Now copy cleaned-up string to output_buffer
    snprintf(output_buffer, buffer_size, "%s", temp_buffer);
    /* --------------------------------------------- */

    return output_buffer;
}