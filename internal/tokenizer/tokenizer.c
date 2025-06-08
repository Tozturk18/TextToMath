/**
 * @file tokenizer.c
 * @author Ozgur Tuna Ozturk
 * @date 07-06-2025
 * @version 1.1
 * 
 * @copyright MIT License
 * 
 * @brief Implementation of the tokenizer module for mathematical expression parsing.
 *
 * This file provides functionality to convert a mathematical expression string
 * into a sequence of tokens representing numbers, operators, parentheses, and functions.
 */

/* --- Imports --- */
#include "tokenizer.h"
#include "mathStructs.h"
#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* --- End of Imports --- */

/* --- tokenize() --- */
uint32_t tokenize(const char *expr, Token *tokens) {

    /* --- Indexes --- */
    uint32_t i = 0;         // Index for input string
    uint32_t t = 0;         // Index for tokens array
    /* --------------- */

    /* --- Unary Sign Flag --- */
    int expectUnary = 1;    // Indicates if a unary minus is expected
    /* ----------------------- */

    /* --- Expression Iteration Loop --- */
    while (expr[i] != '\0') {

        // Check for number or unary minus
        if (isdigit((unsigned char)expr[i]) || expr[i] == '.' || (expectUnary && expr[i] == '-')) {
            
            /* --- Unary Minus Check --- */
            int isNegative = 0; // Flag to indicate if the number is negative
            if (expr[i] == '-') {
                isNegative = 1; // Set flag for negative number
                i++;            // Skip the minus sign
            }
            /* ------------------------- */

            /* --- Read Value to Buffer --- */
            char buffer[64];
            uint32_t j = 0;
            while (isdigit((unsigned char)expr[i]) || expr[i] == '.') {
                buffer[j++] = expr[i++];
            }
            buffer[j] = '\0';
            /* ---------------------------- */

            /* --- Suffix Check --- */
            // Check for unit suffixes or temperature conversions
            if (isalpha((unsigned char)expr[i])) {

                // Read the unit or conversion into buffer
                char unitBuffer[16];
                uint32_t k = 0;
                while ((isalpha((unsigned char)expr[i]) || isdigit((unsigned char)expr[i]) || expr[i] == '=' || expr[i] == '>') && k < sizeof(unitBuffer) - 1) {
                    unitBuffer[k++] = expr[i++];
                }
                unitBuffer[k] = '\0';

                /* --- Function Token Creation --- */
                // Create a new token for the unit or conversion
                tokens[t].type = TOKEN_FUNCTION;
                strcpy(tokens[t].function, unitBuffer);
                t++;    // Move to the next token
                /* ------------------------------- */

                /* --- Parentheses and Number Insertion --- */
                tokens[t].type = TOKEN_PARENTHESIS;
                tokens[t].parenthesis = '(';
                t++;

                tokens[t].type = TOKEN_NUMBER;
                tokens[t].number = atof(buffer);
                if (isNegative) {
                    tokens[t].number = -tokens[t].number;
                }
                t++;

                tokens[t].type = TOKEN_PARENTHESIS;
                tokens[t].parenthesis = ')';
                t++;
                /* ---------------------------------------- */

            } else {
                /* --- Create Number Token --- */
                tokens[t].type = TOKEN_NUMBER;
                tokens[t].number = atof(buffer);
                if (isNegative) {
                    tokens[t].number = -tokens[t].number;
                }
                t++;    // Move to the next token
                /* ----------------------------- */
            }
            /* -------------------- */

            /* --- Reset Unary Minus --- */
            expectUnary = 0;    // Reset unary expectation after a number
            /* ------------------------- */
        
        // Check for functions such as sin, cos, log21, etc.
        } else if (isFuncChar(expr[i])) {

            /* --- Read Function to Buffer --- */
            char buffer[16];
            uint32_t j = 0;

            // Special Case: Detect log<digits> pattern
            if (strncmp(&expr[i], "log", 3) == 0) {
                i += 3;

                // Collect digits as base number
                char numberBuffer[16];
                uint32_t k = 0;
                while (isdigit((unsigned char)expr[i]) && k < sizeof(numberBuffer) - 1) {
                    numberBuffer[k++] = expr[i++];
                }
                numberBuffer[k] = '\0';

                // Save the base number as a token
                tokens[t].type = TOKEN_NUMBER;
                tokens[t].number = atof(numberBuffer);
                t++;

                // Save the function token as logX
                strcpy(buffer, "logX");
            } else {
                while (isFuncChar(expr[i]) && j < sizeof(buffer) - 1) {
                    buffer[j++] = expr[i++];
                }
                buffer[j] = '\0';
            }
            /* ------------------------------- */

            /* --- Function Token Creation --- */
            tokens[t].type = TOKEN_FUNCTION;
            strcpy(tokens[t].function, buffer);
            t++;    // Move to the next token
            /* ------------------------------- */

            /* --- Reset Unary Minus --- */
            expectUnary = 1;    // Expect a unary minus or another number after a function
            /* ------------------------- */

        // Check for operators
        } else if (strchr("+-%*/^", expr[i])) {

            /* --- Operator Token Creation --- */
            // Create a token for the operator
            tokens[t].type = TOKEN_OPERATOR;
            tokens[t].operator = expr[i++];
            t++;    // Move to the next token
            /* ------------------------------- */

            /* --- Reset Unary Minus --- */
            expectUnary = 1;    // Expect a unary minus or another number after an operator
            /* ------------------------- */

        // Check for parentheses
        } else if (expr[i] == '(' || expr[i] == ')') {

            /* --- Parenthesis Token Creation --- */
            // Create a token for the parenthesis
            tokens[t].type = TOKEN_PARENTHESIS;
            tokens[t].parenthesis = expr[i++];
            t++;    // Move to the next token
            /* ------------------------------- */

            /* --- Reset Unary Minus --- */
            // If it's an opening parenthesis, expect a unary minus or a number next
            expectUnary = (tokens[t-1].parenthesis == '(');
            /* ------------------------- */

        // Handle invalid characters
        } else {
            printf("Unknown character: %c\n", expr[i]);
            return (uint32_t)(-1);
        }

        // Check for maximum token limit
        if (t >= MAX_TOKENS) {
            printf("Too many tokens!\n");
            return (uint32_t)(-1);
        }
    }
    /* --------------------------------- */

    /* --- Completion --- */
    // If we reach here, we have successfully tokenized the expression
    tokens[t].type = TOKEN_END;

    // Return the number of tokens parsed
    return t;
    /* ----------------- */
}
/* --- End of tokenize() --- */
