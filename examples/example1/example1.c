/* example1.c
 * Created by Ozgur Tuna Ozturk on July 15, 2023.
 * Last updated August 1, 2023.
 * 
 * This is an example program allowing users to run it and play around with the
 * Text-To-Math library. When you run the program, it displays a welcome prompt
 * and asks the user for an input which is suppose to be a mathematical input.
 * When the user enters the mathematical input, this program runs it through the
 * Text-To-Math library using the textCalc() function and displays the solution.
 */

/* --- Imports --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../textMath.h"
/* --- End of Imports --- */

/* --- main() ---
 * This is the main function of the program.
 * This function prompts the user, inputs the mathematical expression,
 * solves it using textCalc() function and then displays the solution.
 * 
 * Parameters:
 *  - None
 * 
 * Return:
 *  - Integer: returns 0 when finish to signify normal completion.
 */
int main() {

    // Prompt the user
    printf("\nWelcome! Thank you for trying out Text-To-Math program.\nPlease enter a mathematical expression below!\nCurrently the character limit is 225 character...\n\n");

    // Create a variable to hold the user input
    char expression[225];

    // Input the user's mathematical expression
    fgets(expression, sizeof(expression), stdin);
    
    // Get the solution
    float solution = textCalc(expression);

    // Display the solution
    printf("Solution: %.2f\n", solution);

    return 0;   // End the program with normal completion
} /* --- End of main() --- */