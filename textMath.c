/* textMath.c 
 * Created by Ozgur Tuna Ozturk and ChatGPT on July 14, 2023.
 * Last updated on July 15, 2023.
 * 
 * This file contains the code for parsing a string into float variables,
 * and then interpret the mathematical expressions to calculate the final desired result.
 * Thi program follows the mathematical principles of oder of operations according to
 * priority such as paranthesis are first, power (^) is second, etc...
 * 
 * This program currently also supports some pre-defined functionalities:
 *  - sqrt(): This takes the square root of values inside the paranthesis
 *  - round(): This rounds the values inside the paranthesis to the nearest integer
 *  - floor(): This floors the values inside the paranthesis to the nearest higher integer
 *  - ceil(): This floors the values inside the paranthesis to the nearest lower integer
 * (Support for more functionalities will come soon).
 * 
 * This program also supports some pre-defined mathematical constants:
 *  - pi: (~3.14) The ratio of a circle's circumference to its diameter
 *  - e: (~2.72) Euler's constant
 * (Support for more constants will come soon).
 */

/* --- Imports --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "textMath.h"
/* --- End of Imports --- */

//float evaluateExpression(char *str, int *index);

/* --- getNumber() Function ---
 * This function parses the input string starting from a certain
 * index value to get the float value in the string. This function
 * uses atof() function as a trick to only get the number until it makes sense.
 * Hence, if you do atof("2.45*2"); then you will get 2.45 as a float value, 
 * because atof takes in every digit until it reaches '*' and ignores everything else
 * since 2.45*2 is not a number so the nearest correct thing is 2.45. Moreover, a temp
 * string is used to chop off the already stored values so that atof() function can
 * now store that other 2.00 in "2.45*2".
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value, containing the parsed value from the string.
 */
static float getNumber(char *str, int *index) {

    
    char *temp = str + *index;  // Create a temp string containing only the unparsed part

    float number = atof(temp);  // Parse the number as float value

    int i = 0;                  // keep track of the number of digits on the number

    // Count the number of digits in the number to parse
    while (isdigit(temp[i]) || temp[i] == '.' || (temp[i] == '-' && number < 0) ) {
        i++;
    }
    
    (*index) += i;              // Update the index accordingly

    return number;              // Return the value found by atof()
} /* --- End of getNumber() --- */

/* --- evaluateFactor() function ---
 * Since this program use recursion to go through each character in
 * the string and parse it, this function is the final stop before checking
 * if the character is a number, in other words this means it has the highest
 * priority (order). This function is mainly to check for the paranthesis.
 * However, it is also a convinient spot to put other checks such as the ones
 * for mathematical constants and functionalities such as pi, and sqrt().
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value, containing the parsed value from the string
 *      according to the given mathematical function or constant.
 */
static float evaluateFactor(char *str, int *index) {

    // Check if there is an opening paranthesis
    if (str[*index] == '(') {
        (*index)++;                                     // Skip the opening paranthesis
        float result = evaluateExpression(str, index);  // Get the expressions in the paranthesis
        (*index)++;                                     // Skip the closing parenthesis
        return result;                                  
    }

    // Check for Pi
    if ( ( str[*index] == 'p' || str[*index] == 'P' ) && ( str[*index + 1] == 'i' || str[*index + 1] == 'I' )) {
        *index += 2;                                    // Skip the "pi"
        return M_PI;                                    // Return the pre-defined value for pi
    }

    // Check for Euler's number (e)
    if (str[*index] == 'e') {
        (*index)++;                                     // Skip the 'e'
        return M_E;                                     // Return the pre-defined value for Euler's Number
    }

    // Get the unparsed part of the expression entered by the user
    char *temp = str + *index;

    // Create a variable to hold the value
    float expression = 0.00;

    // Check for "sqrt("
    if (temp[0] == 's' && temp[1] == 'q' && temp[2] == 'r' && temp[3] == 't' && temp[4] == '(') {
        *index += 5;                                    // Move the index past "sqrt("
        expression = evaluateExpression(str, index);    // Resolve the expressions inside the square root
        (*index)++;                                     // Skip the closing parenthesis
        return sqrt(expression);
    }

    // Check for "round("
    if (temp[0] == 'r' && temp[1] == 'o' && temp[2] == 'u' && temp[3] == 'n' && temp[4] == 'd' && temp[5] == '(') {
        *index += 6;                                    // Move the index past "round("
        expression = evaluateExpression(str, index);    // Resolve the expressions inside the rounding
        (*index)++;                                     // Skip the closing parenthesis
        return round(expression);
    }

    // Check for "floor("
    if (temp[0] == 'f' && temp[1] == 'l' && temp[2] == 'o' && temp[3] == 'o' && temp[4] == 'r' && temp[5] == '(') {
        *index += 6;                                    // Move the index past "floor("
        expression = evaluateExpression(str, index);    // Resolve the expressions inside the flooring
        (*index)++;                                     // Skip the closing parenthesis
        return floor(expression);
    }

    // Check for "ceil("
    if (temp[0] == 'c' && temp[1] == 'e' && temp[2] == 'i' && temp[3] == 'l' && temp[4] == '(') {
        *index += 5;                                    // Move the index past "ceil("
        expression = evaluateExpression(str, index);    // Resolve the expressions inside the ceiling
        (*index)++;                                     // Skip the closing parenthesis
        return ceil(expression);
    }

    // If none of these, then it must be a number
    return getNumber(str, index);
} /* --- End of evaluateFactor() --- */

/* --- evaluatePower() function ---
 * This function has the second mathematical order for resolving power
 * and the third order in the recursion.
 * Since after the power sign, the only things that can come is the 
 * mathematical factors and constants, numbers, or a paranthesis,
 * then recursion can be directly be started with evaluateFactor() function.
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value result of powering two expressions
 */
static float evaluatePower(char *str, int *index) {
    float result = evaluateFactor(str, index);          // Get the initial expression

    // Correctly square a negative number
    if (str[*index-1] == ')' && str[*index] == '^') {
        (*index)++;                                     // Skip the exponent sign

        float nextFactor = evaluateFactor(str, index);  // Get the next expression
        result = pow(result, nextFactor);               // power the intial expression by the next expression
    } else if (str[*index] == '^') {
        (*index)++;                                     // Skip the exponent sign

        float nextFactor = evaluateFactor(str, index);  // Get the next expression

        // Check if the initial expression is a negative number
        if (result < 0) {
            result = -pow(result, nextFactor);          // -1^2 != (-1)^2
        } else {
            result = pow(result, nextFactor);           
        }
    }
    return result;
} /* --- End of evaluatePower() --- */

/* --- evaluateTerm() function ---
 * This function has the third mathematical order for resolving power
 * and the fourth order in recursion.
 * This function resolves multiplication, divison and modulus.
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value result of multiplication, division or modulus of two expressions
 */
static float evaluateTerm(char *str, int *index) {
    float result = evaluatePower(str, index);           // Get the initial expression

    // Check for multiplication, division, or modulus sign
    if (str[*index] == '*' || str[*index] == '/' || str[*index] == '%') {
        char operator = str[*index];                    // Load the operator
        (*index)++;                                     // Skip the operator

        float nextFactor = evaluatePower(str, index);   // Get the second expression

        // Resolve the opperation
        if (operator == '*') {
            result *= nextFactor;
        } else if (operator == '/') {
            result /= nextFactor;
        } else if (operator == '%') {
            result = fmod(result, nextFactor);
        }
    }

    return result;
} /* --- End of evaluateTerm() --- */

/* --- evaluateExpression() function ---
 * This function has the fourth and last mathematical order for resolving power
 * and the fifth order in recursion.
 * This function resolves addition, and substraction.
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value result of addition, or substraction of two expressions.
 */
static float evaluateExpression(char *str, int *index) {
    float result = evaluateTerm(str, index);        // Get the first expression

    // Check for addition or substraction
    if (str[*index] == '+' || str[*index] == '-') {
        char operator = str[*index];                // Load the operator
        (*index)++;                                 // Skip the operator

        float nextTerm = evaluateTerm(str, index);  // Get the second expression

        // Resulve the opperation
        if (operator == '+') {
            result += nextTerm;
        } else if (operator == '-') {
            result -= nextTerm;
        }
    }

    return result;
} /* --- End of evaluateExpression() --- */

/* --- removeSpace() function ---
 * This function is created by Aaron on Nov 13, 2009 and last edited by Wolf on Aug 12, 2021
 * This function can be found on stackOverflow (https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c)
 * This function takes in a string and removes all the spaces and stiches
 * the string back together. This is important because it makes the code much
 * easier to handle.
 * 
 * Parameters:
 *  - char *str: This is the string that might contain space character. the str string
 *      parameter is passed by reference
 * 
 * Return:
 * - void
 */
static void removeSpace(char* str) {
    char* i = str;
    do {
        while (*i == ' ') {
            ++i;
        }
    } while (*str++ = *i++);
}

/* --- textCalc() function ---
 * This function is a placer function that helps clean up the input string by calling
 * the removeSpace function, sets a starting index and triggers the recursion loop in
 * evaluateExpression() function and returns the float value which is the result of the
 * mathematical expression inputed into the evaluateExpression.
 * 
 * Parameters:
 *  - char *str: This is a string that contains mathematical expressions.
 * 
 * Return:
 * - float: this function returns a float value that is the complete solution of
 *      the mathematical expression inputed by the user.
 */
float textCalc(char *str) {
    int index = 0;
    
    removeSpace(str);
    
    return evaluateExpression(str, &index);
}

/*int main() {
    char expression[] = "2.45 * 2";
    int index = 0;
    float solution = textCalc(expression);
    printf("Solution: %.2f\n", solution);

    return 0;
}*/