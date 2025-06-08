/**
 * @file utils.h
 * @author Ozgur Tuna Ozturk (tunaozturk2001@hotmail.com)
 * @date 07-06-2025
 * @version 1.0
 * 
 * @copyright MIT License
 * 
 * @brief Header file for the utility functions used in tokenizer and parser modules.
 *
 * This file contains the declaration of utility functions that provide common
 * functionality such as whitespace removal and character classification for function names.
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Removes all whitespace characters from a string in-place.
 *
 * This function modifies the given string by removing all whitespace characters,
 * shifting the remaining characters left.
 *
 * @param str Pointer to the input string to be modified.
 */
void removeSpace(char *str);

/**
 * @brief Checks if a character is valid inside a function name.
 *
 * A valid character is an alphabetic character, a digit, '-' or '>'.
 * Used to parse functions like sin, cos, log21, and temperature conversions like C->K.
 *
 * @param c Character to check.
 * @return  1 if the character is valid, 0 otherwise.
 */
int isFuncChar(char c);

#endif // UTILS_H
