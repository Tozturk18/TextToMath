/**
 * @file mathStructs.h
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2025
 * @version 1.0
 * 
 * @copyright MIT License
 * 
 * @brief Header file for the token structure and token types.
 *
 * This file defines the TokenType enumeration and the Token structure,
 * used for representing parsed elements of mathematical expressions
 * such as numbers, operators, parentheses, and functions.
 */

#ifndef MATHSTRUCTS_H
#define MATHSTRUCTS_H

#include <stdint.h>

/* --- Max Number of Tokens --- */
#define MAX_TOKENS 256
/* ---------------------------- */

/* --- Token Types --- */
typedef enum {
    TOKEN_NUMBER,       // Numeric values
    TOKEN_OPERATOR,     // Operators: +, -, *, /, ^
    TOKEN_PARENTHESIS,  // Parentheses: ( )
    TOKEN_FUNCTION,     // Functions: sin, cos, log, C->K, etc.
    TOKEN_END           // End marker
} TokenType;
/* ------------------- */

/* --- Token Structure --- */
typedef struct {
    TokenType type;      // Type of token
    union {
        double number;   // Numeric value
        char operator;   // Operator character
        char parenthesis;// Parenthesis character
        char function[16]; // Function name
    };
} Token;
/* ----------------------- */

#endif // MATHSTRUCTS_H
