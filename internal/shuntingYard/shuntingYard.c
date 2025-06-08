/**
 * @file shuntingYard.c
 * @author your name (you@domain.com)
 * @version 0.1
 * @date 2025-06-07
 * 
 * @copyright Copyright (c) 2025
 * 
 * @brief Implementation of Shunting-Yard algorithm for infix to postfix conversion.
 * 
 */

/* --- Imports --- */
#include "shuntingYard.h"
#include "mathStructs.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
/* --- End of Imports --- */

/* --- Helper Functions --- */

// Return precedence level
static int precedence(char op) {
    switch (op) {
        case '^': return 4;
        case '*':
        case '/':
        case '%': return 3;
        case '+':
        case '-': return 2;
        default:  return 0;
    }
}

// Return 1 if operator is right-associative
static int isRightAssociative(char op) {
    return (op == '^');
}

// Return 1 if token is operator
static int isOperator(const Token *token) {
    return token->type == TOKEN_OPERATOR;
}

// Return 1 if token is function
static int isFunction(const Token *token) {
    return token->type == TOKEN_FUNCTION;
}
/* --- End of Helper Functions --- */

/* --- shuntingYard() --- */
uint32_t shuntingYard(const Token *infixTokens, Token *postfixTokens) {
    
    /* --- Local Variables --- */
    Token opStack[MAX_TOKENS];  // Operator stack
    uint32_t opTop = 0;         // Stack pointer
    uint32_t outIdx = 0;        // Output queue index
    uint32_t i = 0;             // Infix token index
    /* ----------------------- */

    /* --- Infix Traversal Loop --- */
    // Iterate through each token in the infix expression
    while (infixTokens[i].type != TOKEN_END) {

        // Get the current token
        const Token *token = &infixTokens[i];

        /* --- Token Handling --- */
        // Check if the token is a number
        if (token->type == TOKEN_NUMBER) {
            // Push numbers directly to output
            postfixTokens[outIdx++] = *token;
        
        // Check if the token is a function
        } else if (isFunction(token)) {
            // Functions go to operator stack
            opStack[opTop++] = *token;

        // Check if the token is an operator
        } else if (isOperator(token)) {
            // Operator precedence handling
            while (opTop > 0 && (isOperator(&opStack[opTop-1]) || isFunction(&opStack[opTop-1]))) {
                Token *top = &opStack[opTop-1];
                if ((isOperator(top) && ( (precedence(top->operator) > precedence(token->operator)) || (precedence(top->operator) == precedence(token->operator) && !isRightAssociative(token->operator)) )) || isFunction(top) ) {
                    postfixTokens[outIdx++] = *top;
                    opTop--; // Pop
                } else {
                    break;
                }
            }
            opStack[opTop++] = *token;

        // Check if the token is a parenthesis
        } else if (token->type == TOKEN_PARENTHESIS) {
            if (token->parenthesis == '(') {
                opStack[opTop++] = *token;
            } else if (token->parenthesis == ')') {
                // Pop until '('
                while (opTop > 0 && opStack[opTop-1].type != TOKEN_PARENTHESIS) {
                    postfixTokens[outIdx++] = opStack[--opTop];
                }
                if (opTop == 0) {
                    printf("Error: Mismatched parentheses\n");
                    return (uint32_t)(-1);
                }
                opTop--; // Pop '('
                // If top of stack is a function, pop it to output
                if (opTop > 0 && isFunction(&opStack[opTop-1])) {
                    postfixTokens[outIdx++] = opStack[--opTop];
                }
            }
        }
        /* ---------------------- */

        i++;
    }
    /* --------------------------- */

    /* --- Pop Remaining Operators --- */
    while (opTop > 0) {
        if (opStack[opTop-1].type == TOKEN_PARENTHESIS) {
            printf("Error: Mismatched parentheses\n");
            return (uint32_t)(-1);
        }
        postfixTokens[outIdx++] = opStack[--opTop];
    }
    /* -------------------------------- */

    /* --- Completion --- */
    postfixTokens[outIdx].type = TOKEN_END;
    return outIdx;
    /* ------------------ */
}
/* --- End of shuntingYard() --- */
