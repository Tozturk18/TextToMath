/**
 * @file tokenizer.h
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @version 0.1
 * @date 07-06-2025
 * 
 * @copyright MIT License
 * 
 * @brief Header file for the tokenizer module.
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

/* --- Imports --- */
#include "mathStructs.h"
#include <stdint.h>
/* --- End of Imports --- */

/** 
 * @brief Tokenizes a mathematical expression string into an array of tokens.
 *
 * This function parses the input expression character-by-character and generates
 * an array of Token structures. It recognizes:
 * - Numbers (supporting unary minus)
 * - Operators (+, -, *, /, ^)
 * - Parentheses ( )
 * - Functions (sin, cos, log21, C->K, etc.)
 * - Unit suffixes (deg, rad) and temperature conversions (C->K, F->C, etc.)
 *
 * @param expr    Pointer to the input null-terminated expression string.
 * @param tokens  Pointer to an array of Token structures to fill.
 * @return        Number of tokens parsed on success, or (uint32_t)-1 on error.
 */
uint32_t tokenize(const char *expr, Token *tokens);

#endif // TOKENIZER_H
