/**
 * @file evaluator.c
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @version 0.1
 * @date 2025-06-07
 * 
 * @copyright Copyright (c) 2025
 * 
 * @brief Implementation of postfix expression evaluation.
 * 
 * This file provides the function to evaluate a postfix (RPN) token array.
 */

/* --- Imports --- */
#include "evaluator.h"
#include "mathStructs.h"
#include "unitConversion.h"
#include <math.h>
#include <stdio.h>
#include <string.h> // for strcmp, strstr
/* --- End of Imports --- */

/* --- Constants Table --- */
static const ConstantEntry constants[] = {
    {"pi", M_PI},
    {"e",  M_E},
    {NULL, 0.0}
};
/* ------------------------ */

// Reciprocal Trig Functions
static double sec(double x) { return 1.0 / cos(x); }
static double csc(double x) { return 1.0 / sin(x); }
static double cot(double x) { return 1.0 / tan(x); }

// Reciprocal Hyperbolic Functions
static double sech(double x) { return 1.0 / cosh(x); }
static double csch(double x) { return 1.0 / sinh(x); }
static double coth(double x) { return 1.0 / tanh(x); }

/* --- Math Function Table --- */
static const FunctionEntry mathFunctions[] = {
    // Basic Trig
    {"sin", sin},
    {"cos", cos},
    {"tan", tan},
    {"asin", asin},
    {"acos", acos},
    {"atan", atan},

    // Hyperbolic Trig
    {"sinh", sinh},
    {"cosh", cosh},
    {"tanh", tanh},
    {"asinh", asinh},
    {"acosh", acosh},
    {"atanh", atanh},

    // Reciprocal Trig
    {"sec", sec},
    {"csc", csc},
    {"cot", cot},

    // Reciprocal Hyperbolic
    {"sech", sech},
    {"csch", csch},
    {"coth", coth},

    // Special
    {"deg", NULL},
    {NULL, NULL}
};

/* --------------------------- */

/* --- evaluatePostfix() --- */
double evaluatePostfix(const Token *postfixTokens) {

    /* --- Stack for Evaluation --- */
    double stack[MAX_TOKENS];
    uint32_t top = 0;  // Stack pointer
    /* ---------------------------- */

    /* --- Postfix Traversal Loop --- */
    uint32_t i = 0;
    while (postfixTokens[i].type != TOKEN_END) {
        const Token *token = &postfixTokens[i];

        if (token->type == TOKEN_NUMBER) {
            // Push number onto stack
            stack[top++] = token->number;

        } else if (token->type == TOKEN_OPERATOR) {
            // Operator: Pop two operands
            if (top < 2) {
                printf("Error: Not enough operands for operator '%c'\n", token->operator);
                return 0.0;
            }
            double right = stack[--top];
            double left = stack[--top];
            double result = 0.0;

            /* --- Operator Evaluation --- */
            switch (token->operator) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '%': result = fmod(left, right); break;
                case '*': result = left * right; break;
                case '/': 
                    if (right == 0) {
                        printf("Error: Division by zero\n");
                        return 0.0;
                    }
                    result = left / right; 
                    break;
                case '^': result = pow(left, right); break;
                default:
                    printf("Error: Unknown operator '%c'\n", token->operator);
                    return 0.0;
            }
            /* ---------------------------- */

            // Push result back onto stack
            stack[top++] = result;

        } else if (token->type == TOKEN_FUNCTION) {
            /* --- Special Case: Constants --- */
            int isConstant = 0;
            for (int j = 0; constants[j].name != NULL; j++) {
                if (strcmp(token->function, constants[j].name) == 0) {
                    stack[top++] = constants[j].value;
                    isConstant = 1;
                    break;
                }
            }
            if (isConstant) {
                i++; // Move to next token
                continue;
            }
            /* -------------------------------- */

            /* --- Special Case: logX (Custom Base Logarithm) --- */
            if (strcmp(token->function, "logX") == 0) {
                if (top < 2) {
                    printf("Error: Not enough operands for function 'logX'\n");
                    return 0.0;
                }
                double value = stack[--top]; // Right (value)
                double base = stack[--top];  // Left (base)
                if (base <= 0 || base == 1 || value <= 0) {
                    printf("Error: Invalid domain for log base or value\n");
                    return 0.0;
                }
                double result = log(value) / log(base); // ln(value) / ln(base)
                stack[top++] = result;
                i++;
                continue;
            }
            /* -------------------------------------------------- */

            /* --- Special Case: Unit Conversion A=>B --- */
            if (strstr(token->function, "=>") != NULL) {
                char from_unit[16], to_unit[16];
                if (sscanf(token->function, "%15[^=]=>%15s", from_unit, to_unit) != 2) {
                    printf("Error: Invalid unit conversion format '%s'\n", token->function);
                    return 0.0;
                }

                if (top < 1) {
                    printf("Error: Not enough operands for unit conversion\n");
                    return 0.0;
                }
                double value = stack[--top];
                double converted;
                if (convert_units(value, from_unit, to_unit, &converted) != 0) {
                    printf("Error: Failed to convert from '%s' to '%s'\n", from_unit, to_unit);
                    return 0.0;
                }
                stack[top++] = converted;
                i++;
                continue;
            }
            /* -------------------------------------------------- */

            // Function: Pop one operand
            if (top < 1) {
                printf("Error: Not enough operands for function '%s'\n", token->function);
                return 0.0;
            }
            double value = stack[--top];
            double result = 0.0;
            int found = 0;

            /* --- Search in Math Function Table --- */
            for (int j = 0; mathFunctions[j].name != NULL; j++) {
                if (strcmp(token->function, mathFunctions[j].name) == 0) {
                    if (mathFunctions[j].func != NULL) {
                        result = mathFunctions[j].func(value);
                        found = 1;
                    } else if (strcmp(token->function, "deg") == 0) {
                        // Special case: convert degrees to radians
                        result = value * (M_PI / 180.0);
                        found = 1;
                    }
                    break;
                }
            }
            /* -------------------------------------- */

            if (!found) {
                printf("Error: Unknown function or constant '%s'\n", token->function);
                return 0.0;
            }

            // Push result back onto stack
            stack[top++] = result;
        }

        i++;
    }
    /* ------------------------------ */

    /* --- Completion --- */
    if (top != 1) {
        printf("Error: Invalid expression, stack has %u elements\n", top);
        return 0.0;
    }
    return stack[0]; // Final result
    /* ----------------- */
}
/* --- End of evaluatePostfix() --- */
