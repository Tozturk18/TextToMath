/* textMath.h 
 * Created by Ozgur Tuna Ozturk and ChatGPT on July 14, 2023.
 * Last updated July 15, 2023.
 * 
 * This is the header file for the Text-To-Math program. This file contains all the 
 * definitions of the functions that are used. Almost all of the functions except one are static.
 * This is to stop the user from accesing the other functions that are parts of the recursion.
 * This program only works as a whole and cannot work as pieces, which would make the recursion break.
 * 
 * textCalc() function is the user callable function that triggers the recursion and returns the solution.
 */

/* --- getNumber() Function ---
 * This function parses the input string starting from a certain
 * index value to get the float value in the string.
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value, containing the parsed value from the string.
 */
static float getNumber(char *str, int *index);

/* --- phranthesisRepeater() Function ---
 * This function parses the input string that contains paranthesis to handle
 * embedded paranthesis and multiple expressions.
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value, containing the parsed value from the string.
 */
static float phranthesisRepeater(char *str, int *index);

/* --- evaluateFactor() function ---
 * This function is mainly to check for the paranthesis.
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
static float evaluateFactor(char *str, int *index);

/* --- evaluatePower() function ---
 * This function evaluates the exponent sign and the difference between
 * -1^2 and (-1)^2
 * 
 * Parameters:
 *  - char *str: This is the string containing the mathematical expression
 *  - int *index: This is an integer index variable passed by reference.
 *      index variable keeps track of the current index the program is on.
 * 
 * Return:
 * - number: a float value result of powering two expressions
 */
static float evaluatePower(char *str, int *index);

/* --- evaluateTerm() function ---
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
static float evaluateTerm(char *str, int *index);

/* --- evaluateExpression() function ---
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
static float evaluateExpression(char *str, int *index);

/* --- removeSpace() function ---
 * This function is created by Aaron on Nov 13, 2009 and last edited by Wolf on Aug 12, 2021
 * This function can be found on stackOverflow (https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c)
 * This function takes in a string and removes all the spaces
 * 
 * Parameters:
 *  - char *str: This is the string that might contain space character. the str string
 *      parameter is passed by reference
 * 
 * Return:
 * - void
 */
static void removeSpace(char* str);

/* --- textCalc() function ---
 * This is the only non static function which allows the user to call only this function.
 * This function triggers the removeSpace() and evaluateExpression functions to clean the string
 * containing the mathematical expression and trigger the recursion to solve it.
 * 
 * Parameters:
 *  - char *str: This is a string that contains mathematical expressions.
 * 
 * Return:
 * - float: this function returns a float value that is the complete solution of
 *      the mathematical expression inputed by the user.
 */
float textCalc(char *str);