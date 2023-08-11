/* textMath.c 
 * Created by Ozgur Tuna Ozturk and ChatGPT on July 14, 2023.
 * Last updated on August 11, 2023.
 * 
 * This file contains the code for parsing a string into float variables,
 * and then interpret the mathematical expressions to calculate the final desired result.
 * This program follows the mathematical principles of order of operations according to the
 * priority of expressions such as paranthesis are first, power (^) is second, etc...
 * 
 * This program currently also supports some pre-defined functionalities:
 *  - sqrt(): This takes the square root of values inside the paranthesis
 *  - round(): This rounds the values inside the paranthesis to the nearest integer
 *  - floor(): This rounds down the values inside the paranthesis to the nearest lower integer
 *  - ceil(): This rounds up the values inside the paranthesis to the nearest higher integer
 *  - sin(): This takes the sine of values inside the paranthesis
 *  - cos(): This takes the cosine of values inside the paranthesis
 *  - tan(): This takes the tangent of values inside the paranthesis
 *  - cot(): This takes the cotangent of values inside the paranthesis
 *  - asin(): This takes the inverse sine of values inside the paranthesis
 *  - acos(): This takes the inverse cosine of values inside the paranthesis
 *  - atan(): This takes the inverse tangent of values inside the paranthesis
 *  - acot(): This takes the inverse cotangent of values inside the paranthesis
 *  - ln(): This takes the natural log of values inside the paranthesis
 *  - log(): This takes the log base 10 of values inside the paranthesis
 *  - logX(): This tales the log base X of values inside the paranthesis
 * (Support for more functionalities will come soon...)
 * 
 * This program also supports some pre-defined mathematical constants:
 *  - pi: (~3.14) The ratio of a circle's circumference to its diameter
 *  - e: (~2.72) Euler's constant
 * (Support for more constants will come soon...)
 * 
 * This program also supports for Degrees to Radians and vice versa conversions
 *  - (number)deg: putting the word "deg" converts the number to degrees assuming it was in radians originally
 *  - (number)rad: putting the word "rad" converts the number to radians assuming it was in degrees originally
 *  - (number)!: putting the character '!' takes the factorial of the number.
 */

/* --- Imports --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "textMath.h"
/* --- End of Imports --- */

/* --- getNumber() Function ---
 * This function parses the input string starting from a certain
 * index value to get the float value in the string. This function
 * uses strtof() function as a trick to only get the number until it makes sense.
 * Hence, if you do strtof("2.45*2"); then you will get 2.45 as a float value, 
 * because atof takes in every digit until it reaches '*' and gives you a pointer at '*',
 * since 2.45*2 is not a number so the nearest correct thing is 2.45. Moreover, a temp
 * string is used to chop off the already stored values so that strtof() function can
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
    
    char *temp = str + *index;                              // Create a temp string containing only the unparsed part
                 
    float number = strtof(temp, &temp);                     // Parse the number as float value                            

    int i = temp - (str + *index);                          // keep track of the number of digits on the number

    // Radians to degrees (the user simply needs to enter "deg" next to a number)
    if (temp[0] == 'd' && temp[1] == 'e' && temp[2] == 'g') {

        number = number * M_PI / 180;                       // Convert radians to degrees
        i += 3;                                             // move index by 3 positions
    
    // Degrees to radians (the user simply needs to enter "rad" next to a number)
    } else if (temp[0] == 'r' && temp[1] == 'a' && temp[2] == 'd') {

        number = number * 180 / M_PI;                       // Convert degrees to radians
        i += 3;                                             // move index by 3 positions

    // Factorial
    } else if (temp[0] == '!') {

        number = tgamma(number+1);
        i++;

    // Fail Safe for wrong input
    } else if (!isdigit(temp[0]) && temp[0] != '^' && temp[0] != '*' && temp[0] != '_' && temp[0] != '/' && temp[0] != '%' && temp[0] != '+' && temp[0] != '-' && temp[0] != ')' && temp[0] != '}' && temp[0] != ']' && temp[0] != '(' && temp[0] != '{' && temp[0] != '[' && temp[0] != '\0' ) {
        int pos = 0;                                        // Current position in the new truncated temporary string

        // Skip the Unrecognized Characters 
        while (!isdigit(temp[pos]) && temp[pos] != '^' && temp[pos] != '*' && temp[pos] != '_' && temp[pos] != '/' && temp[pos] != '%' && temp[pos] != '+' && temp[pos] != '-' && temp[pos] != ')' && temp[pos] != '}' && temp[pos] != ']' && temp[pos] != '(' && temp[pos] != '{' && temp[pos] != '[' && temp[pos] != '\0' ) {
            pos++;                                          // Increment position each time an unrecognized character appears
        }

        // Reset number
        number = 0.0f;

        // Error message
        printf("\nUnkown expressions detected in the input. Please check your input and make sure it is correct\n");

        // Update the temporary position holder
        i += pos;
    }
    
    (*index) += i;                                          // Update the index accordingly

    //printf("\nnumber: %.2f\n", number);

    return number;                                          // Return the value found by atof()
} /* --- End of getNumber() --- */

/* --- phranthesisRepeater() Function ---
 * This function parses the input to get rid of the paranthesis and solve
 * the contents of the paranthesis using truncate, solve, and attach procedure.
 * To solve embedded paranthesis with multiple operations inside, the program needs
 * to go itterate through all expressions. To achieve a final accurate result, this
 * function allows for itteration through each expression.
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value, containing the parsed value from the string.
 */
static float phranthesisRepeater(char *str, int *index) {

    int openParan = 0;                                      // The number of unterminated open paranthesis

    // truncated string containing the initial string without the paranthesis
    char truncatedStr[(int)strlen(str)+1];
    strcpy(truncatedStr, str + *index);

    // Find the according close paranthesis to the open paranthesis
    for (int i = 0; i < (int)strlen(truncatedStr); i++)  {

        // Count the number of embedded open paranthesis
        if (truncatedStr[i] == '(' || truncatedStr[i] == '{' || truncatedStr[i] == '[') {
            openParan++;                                    // Increment the number of unterminated open paranthesis
        }

        // Check if the close paranthesis belongs to the truncated open paranthesis
        if ( (truncatedStr[i] == ')' || truncatedStr[i] == '}' || truncatedStr[i] == ']' ) && openParan > 0) {
            openParan--;                                    // Decrement the number of unterminated open paranthesis
        } else if ( ( truncatedStr[i] == ')' || truncatedStr[i] == '}' || truncatedStr[i] == ']' ) && openParan == 0) {
            truncatedStr[i] = '\0';                         // Truncate the string from pos i
        }
    }

    int pos;                                                // Output index position
    int i = 0;                                              // Current index relative to the original string

    float val = 0.00f;                                      // Output value
    char buf[100];                                          // Buffer variable

    char temp[strlen(truncatedStr)+1];                      // Temporary variable
    strcpy(temp,truncatedStr);                              // Copy input string into the temporary variable

    char tempBuf[100];                                      // Temporary buffer variable

    // Iterate through eaach repetation
    while ((int)strlen(truncatedStr) > i) {
        pos = 0;                                            // Reset the index

        val = evaluateExpression(temp, &pos);               // Get the output value and pass the index by reference

        gcvt(val,6,buf);                                    // Store the output value as a string in the buffer

        // Update the current index accordingly
        if (i>0) {
            i += pos - (int)strlen(tempBuf);
        } else {
            i += pos;
        }

        char *truncatedTemp = temp + pos;                   // Truncate the temp variable to get rid of the part that is already calculated

        strcat(buf, truncatedTemp);                         // Combine the buffer and the truncatedTemp and store it in the buffer
        strcpy(temp,buf);                                   // Copy the buffer into the temp variable.

        gcvt(val,6,tempBuf);                                // Update the temporary buffer

    }

    (*index) += i;                                          // Update the universal index

    return val;                                             // Return the final value
} /* --- End of phranthesisRepeater() --- */

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
    if (str[*index] == '(' || str[*index] == '[' || str[*index] == '{') {
        (*index)++;                                         // Skip the opening paranthesis

        float result = phranthesisRepeater(str, index);     // Resolve the expression inside the paranthesis

        (*index)++;                                         // Skip the closing parenthesis
        return result;                                  
    }

    // Check for Pi
    if ( ( str[*index] == 'p' || str[*index] == 'P' ) && ( str[*index + 1] == 'i' || str[*index + 1] == 'I' )) {
        (*index) += 2;                                        // Skip the "pi"
        return M_PI;                                        // Return the pre-defined value for pi
    }

    // Check for Euler's number (e)
    if (str[*index] == 'e') {
        (*index)++;                                         // Skip the 'e'
        return M_E;                                         // Return the pre-defined value for Euler's Number
    }

    // Get the unparsed part of the expression entered by the user
    char *temp = str + *index;

    // Create a variable to hold the value
    float expression = 0.00;

    // Check for "sqrt("
    if (temp[0] == 's' && temp[1] == 'q' && temp[2] == 'r' && temp[3] == 't') {
        if (temp[4] == '(' || temp[4] == '[' || temp[4] == '{') {
            *index += 5;                                    // Move the index past "sqrt("
            expression = phranthesisRepeater(str, index);   // Resolve the expression inside the square root
            (*index)++;                                     // Skip the closing parenthesis
            return sqrt(expression);
        }
    }

    // Check for "round("
    if (temp[0] == 'r' && temp[1] == 'o' && temp[2] == 'u' && temp[3] == 'n' && temp[4] == 'd') {
        if (temp[5] == '(' || temp[5] == '[' || temp[5] == '{') {
            *index += 6;                                    // Move the index past "round("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the rounding
            (*index)++;                                     // Skip the closing parenthesis
            return round(expression);
        }
    }

    // Check for "floor("
    if (temp[0] == 'f' && temp[1] == 'l' && temp[2] == 'o' && temp[3] == 'o' && temp[4] == 'r') {
        if (temp[5] == '(' || temp[5] == '[' || temp[5] == '{') {
            *index += 6;                                    // Move the index past "floor("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the flooring
            (*index)++;                                     // Skip the closing parenthesis
            return floor(expression);
        }
    }

    // Check for "ceil("
    if (temp[0] == 'c' && temp[1] == 'e' && temp[2] == 'i' && temp[3] == 'l') {
        if (temp[4] == '(' || temp[4] == '[' || temp[4] == '{') {
            *index += 5;                                    // Move the index past "ceil("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return ceil(expression);
        }
    }

    // Check for "sin("
    if (temp[0] == 's' && temp[1] == 'i' && temp[2] == 'n') {
        if (temp[3] == '(' || temp[3] == '[' || temp[3] == '{') {
            *index += 4;                                    // Move the index past "sin("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round(sinf(expression)*1000000)/1000000; // Round the uncertainty in float value
        }
    }

    // Check for "cos("
    if (temp[0] == 'c' && temp[1] == 'o' && temp[2] == 's') {
        if (temp[3] == '(' || temp[3] == '[' || temp[3] == '{') {
            *index += 4;                                    // Move the index past "cos("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round(cosf(expression)*1000000)/1000000; // Round the uncertainty in float value
        }
    }

    // Check for "tan("
    if (temp[0] == 't' && temp[1] == 'a' && temp[2] == 'n') {
        if (temp[3] == '(' || temp[3] == '[' || temp[3] == '{') {
            *index += 4;                                    // Move the index past "tan("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round(tanf(expression)*1000000)/1000000; // Round the uncertainty in float value
        }
    }

    // Check for "cot("
    if (temp[0] == 'c' && temp[1] == 'o' && temp[2] == 't') {
        if (temp[3] == '(' || temp[3] == '[' || temp[3] == '{') {
            *index += 4;                                    // Move the index past "cot("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round((float)1/tanf(expression)*1000000)/1000000; // Round the uncertainty in float value
        }
    }

    // Check for "asin("
    if (temp[0] == 'a' && temp[1] == 's' && temp[2] == 'i' && temp[3] == 'n') {
        if (temp[4] == '(' || temp[4] == '[' || temp[4] == '{') {
            *index += 5;                                    // Move the index past "asin("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round(asinf(expression)*1000000)/1000000;// Round the uncertainty in float value
        }
    }

    // Check for "acos("
    if (temp[0] == 'a' && temp[1] == 'c' && temp[2] == 'o' && temp[3] == 's') {
        if (temp[4] == '(' || temp[4] == '[' || temp[4] == '{') {
            *index += 5;                                    // Move the index past "acos("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round(acosf(expression)*1000000)/1000000;// Round the uncertainty in float value
        }
    }

    // Check for "atan("
    if (temp[0] == 'a' && temp[1] == 't' && temp[2] == 'a' && temp[3] == 'n') {
        if (temp[4] == '(' || temp[4] == '[' || temp[4] == '{') {
            *index += 5;                                    // Move the index past "atan("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round(atanf(expression)*1000000)/1000000;// Round the uncertainty in float value
        }
    }

    // Check for "acot("
    if (temp[0] == 'a' && temp[1] == 'c' && temp[2] == 'o' && temp[3] == 't') {
        if (temp[4] == '(' || temp[4] == '[' || temp[4] == '{') {
            *index += 5;                                    // Move the index past "acot("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return round((float)1/atanf(expression)*1000000)/1000000; // Round the uncertainty in float value
        }
    }

    // Check for "abs("
    if (temp[0] == 'a' && temp[1] == 'b' && temp[2] == 's') {
        if (temp[3] == '(' || temp[3] == '[' || temp[3] == '{') {
            *index += 4;                                    // Move the index past "abs("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return fabs(expression);
        }
    }

    // Check for "ln("
    if (temp[0] == 'l' && temp[1] == 'n') {
        if (temp[2] == '(' || temp[2] == '[' || temp[2] == '{') {
            *index += 3;                                    // Move the index past "ln("
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return log(expression);
        }
    }

    // Check for "logX("
    if (temp[0] == 'l' && temp[1] == 'o' && temp[2] == 'g') {
        *index += 3;                                        // Move the index past "log"
        if (temp[3] == '(' || temp[3] == '[' || temp[3] == '{') {
            (*index)++;                                     // Move the index past opening parenthesis
            expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
            (*index)++;                                     // Skip the closing parenthesis
            return log10(expression);
        } else {
            float base = evaluateExpression(str,index);
            if ((int)base != 0) {
                if (temp[*index] == '(' || temp[*index] == '[' || temp[*index] == '{') {
                    (*index)++;                                     // Move the index past opening parenthesis
                    expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
                    (*index)++;                                     // Skip the closing parenthesis
                    return (float)log(expression)/log(base);        // Take the log with a custom base
                }
            } else {
                if (temp[*index] == '(' || temp[*index] == '[' || temp[*index] == '{') {
                    (*index)++;                                     // Move the index past opening parenthesis
                    expression = phranthesisRepeater(str, index);   // Resolve the expressions inside the ceiling
                    (*index)++;                                     // Skip the closing parenthesis
                    return log10(expression);
                }
            }
        }
    }

    // If none of these, then it must be a number
    return getNumber(str, index);
} /* --- End of evaluateFactor() --- */

/* --- evaluatePower() function ---
 * This function has the second mathematical order for resolving power
 * and the third order in the recursion.
 * This function calls the evaluateFactor function and deals with exponents.
 * This function also allows for differentiation between -1^2 and (-1)^2
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
    if ((str[*index-1] == ')' || str[*index-1] == ']' || str[*index-1] == '}') && str[*index] == '^') {
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
    if (str[*index] == '*' || str[*index] == '/' || str[*index] == '%' || str[*index] == '_') {
        char operator = str[*index];                    // Load the operator
        (*index)++;                                     // Skip the operator

        float nextFactor = evaluatePower(str, index);   // Get the second expression

        // Resolve the opperation
        if (operator == '*' || operator == '_') {
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
    char* i = str;                                  // Get a pointer, pointing at the input string

    // Itterate through each character on the string
    do {
        while ( isspace(*i) ) {
            ++i;                                    // Skip the character whenever there is a space.
        }
    } while ((*str++ = *i++) != '\0');
}

/* --- textCalcStr() function ---
 * This function is a placer function that helps clean up the input string by calling
 * the removeSpace function, sets a starting index and triggers the recursion loop in
 * evaluateExpression() function and returns the float value which is the result of the
 * mathematical expression inputed into the evaluateExpression. This functions also
 * ensures that the all of the input string is parsed through the evaluateExpression()
 * function.
 * 
 * Parameters:
 *  - char *str: This is a string that contains mathematical expressions.
 * 
 * Return:
 * - char*: this function returns a char array that holds a string which is the complete
 *      solution of the mathematical expression inputed by the user. This function returns 
 *      the result in scientific notation if the number is larger than 10^10 or abs(val) < 0.1
 */
char *textCalcStr(char *str) {

    int index;                                              // Output index
    int i = 0;                                              // Current index
    
    removeSpace(str);                                       // Remove whitespace from the string

    float val = 0.00f;                                      // Output value
    char buf[100];                                          // Buffer variable
    
    char *temp = malloc(strlen(str)+1 * sizeof(char));      // Temporary varaible
    strcpy(temp,str);                                       // Copy input string into the temporary variable
    
    char tempBuf[100];                                      // Temporary Buffer Variable

    // Iterate through each repetation
    while ((int)strlen(str) > i) {
        index = 0;                                          // Reset the index
        
        val = evaluateExpression(temp, &index);             // get the output value and pass the index by reference
        
        gcvt(val,6,buf);                                    // Store the output value as a string in the buffer

        // Update the current index accordingly
        if (i>0) {
            i += index - (int)strlen(tempBuf);              // Decrease the output index by the number of digits of the previous itteration value
        } else {
            i += index;                             
        }

        char *truncatedTemp = temp + index;                 // Truncate the temp variable to get rid of the part that is already calculated
        
        strcat(buf, truncatedTemp);                         // Combine the buffer and the truncatedTemp and store it in the buffer
        strcpy(temp,buf);                                   // Copy the buffer into the temp variable.
        
        gcvt(val,6,tempBuf);                                // Update the temporary buffer
    }

    return temp;                                             // Return the final value
}

/* --- textCalc() function ---
 * This function is a placer function that helps clean up the input string by calling
 * the removeSpace function, sets a starting index and triggers the recursion loop in
 * evaluateExpression() function and returns the float value which is the result of the
 * mathematical expression inputed into the evaluateExpression. This functions also
 * ensures that the all of the input string is parsed through the evaluateExpression()
 * function.
 * 
 * Parameters:
 *  - char *str: This is a string that contains mathematical expressions.
 * 
 * Return:
 * - float: this function returns a float value that is the complete solution of
 *      the mathematical expression inputed by the user.
 */
float textCalc(char *str) {

    int index;                                              // Output index
    int i = 0;                                              // Current index
    
    removeSpace(str);                                       // Remove whitespace from the string

    float val = 0.00f;                                      // Output value
    char buf[100];                                          // Buffer variable
    
    char *temp = malloc(strlen(str)+1 * sizeof(char));      // Temporary varaible
    strcpy(temp,str);                                       // Copy input string into the temporary variable
    
    char tempBuf[100];                                      // Temporary Buffer Variable

    // Iterate through each repetation
    while ((int)strlen(str) > i) {
        index = 0;                                          // Reset the index
        
        val = evaluateExpression(temp, &index);             // get the output value and pass the index by reference
        
        gcvt(val,6,buf);                                    // Store the output value as a string in the buffer

        // Update the current index accordingly
        if (i>0) {
            i += index - (int)strlen(tempBuf);              // Decrease the output index by the number of digits of the previous itteration value
        } else {
            i += index;                             
        }

        char *truncatedTemp = temp + index;                 // Truncate the temp variable to get rid of the part that is already calculated
        
        strcat(buf, truncatedTemp);                         // Combine the buffer and the truncatedTemp and store it in the buffer
        strcpy(temp,buf);                                   // Copy the buffer into the temp variable.
        
        gcvt(val,6,tempBuf);                                // Update the temporary buffer
    }

    return val;                                             // Return the final value
}