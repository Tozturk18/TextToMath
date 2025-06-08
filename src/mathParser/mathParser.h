/**
 * @file mathParser.h
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2025
 * @version 1.0
 * 
 * @copyright MIT License
 * 
 * @brief Header file for the main parsing interface.
 *
 * This file declares the public interface for parsing and evaluating
 * mathematical expressions. It exposes the textCalc() function to
 * tokenize, parse, and later evaluate input expressions.
 */

#ifndef MATHPARSER_H
#define MATHPARSER_H

#include "mathStructs.h"
#include <stdio.h>

/**
 * @brief Parses and calculates a mathematical expression.
 *
 * This function serves as the main entry point for parsing and evaluating
 * a mathematical expression provided as a string.
 *
 * @param expr Null-terminated input string containing the expression.
 * @return The evaluated result of the expression as a double.
 */
double textCalc(const char *expr);

/**
 * @brief Evaluates the input expression and returns result as a clean scientific string.
 * 
 * @param input_expr  Input mathematical expression string.
 * @param output_buffer  Buffer to store the result string.
 * @param buffer_size  Size of the output buffer.
 * @return Pointer to the output_buffer containing the formatted result.
 */
char* textCalcString(const char *input_expr, char *output_buffer, size_t buffer_size);

#endif // MATHPARSER_H
