/**
 * @file shuntingYard.h
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @version 0.1
 * @date 2025-06-07
 * 
 * @copyright Copyright (c) 2025
 * 
 * @brief Header file for the Shunting-Yard algorithm implementation.
 * 
 */

#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "mathStructs.h"
#include <stdint.h>

/**
 * @brief Converts an array of tokens from infix to postfix notation.
 *
 * This function implements the Shunting-Yard algorithm to reorder
 * the tokens based on operator precedence and associativity.
 *
 * @param infixTokens   Array of tokens in infix order.
 * @param postfixTokens Output array of tokens in postfix order.
 * @return              Number of tokens in the postfix array.
 */
uint32_t shuntingYard(const Token *infixTokens, Token *postfixTokens);

#endif // SHUNTING_YARD_H
