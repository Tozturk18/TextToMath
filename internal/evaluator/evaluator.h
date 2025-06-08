/**
 * @file evaluator.h
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2024
 * @version 1.0
 * 
 * @brief Header file for postfix expression evaluation.
 *
 * This file declares the function for evaluating a postfix
 * (Reverse Polish Notation) expression composed of tokens.
 */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "mathStructs.h"
#include <stdint.h>

/**
 * @brief Structure for math function lookup table entries.
 */
typedef struct {
    const char *name;
    double (*func)(double);
} FunctionEntry;

/**
 * @brief Structure for temperature conversion function entries.
 */
typedef struct {
    const char *name;
    double (*convert)(double);
} ConversionEntry;

/**
 * @brief Structure for constant table entries.
 */
typedef struct {
    const char *name;
    double value;
} ConstantEntry;

/**
 * @brief Evaluates a postfix token array and computes the result.
 *
 * This function reads tokens in postfix order (RPN) and computes
 * the result using a stack-based evaluation method. It supports:
 * - Basic arithmetic operators: +, -, *, /, ^
 * - Scientific functions: sin, cos, tan, log, ln, etc.
 * - Temperature conversions: C=>K, F=>C, etc.
 * - Constants: pi, e
 *
 * @param postfixTokens Array of tokens in postfix order.
 * @return              The evaluated result as a double.
 */
double evaluatePostfix(const Token *postfixTokens);

#endif // EVALUATOR_H
