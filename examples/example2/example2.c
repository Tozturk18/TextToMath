/* example2.c
 * Created by Ozgur Tuna Ozturk on August 1, 2023.
 * Last updated August 1, 2023.
 * 
 * This is an example program allowing users to run it and play around with the
 * Text-To-Math library. This is the second version of the example program showcasing
 * the usage of the Text-To-Math library with terminal inline inputs. While running the
 * ./example2 program the user needs to write their mathematical expression right next to
 * the program name as an terminal inline input. An example to this is given in README.md file.
 * Due to restrictions of terminal inline inputs, the user cannot use space or th multiplication '*'
 * sign. Hence this program tries to make the user familiar with how to circumvent the issues caused
 * by the terminal. (Instead of '*' the user can use '_')
 */

/* --- Imports --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../textMath.h"
/* --- End of Imports --- */

/* --- main() ---
 * This is the main function of the program.
 * This function makes sure that the user entered the expression correctly,
 * and runs the user input through the Text-To-Math library to then display
 * the solution.
 * 
 * Parameters:
 *  - argc: this is an integer parameter that holds the amount of arguments entered in the terminal inline inputs
 *  - argv: this is an array of strings that contains all the arguments entered in the terminal inline inputs
 * 
 * Return:
 *  - Integer: returns an integer (either 0 or -1) to signify a normal completion or an error.
 */
int main(int argc, char *argv[]) {

    // Fail Safe
    if (argc < 2) {
        printf("\nPlease input a mathematical expression to run this program.\n");
        return -1;  // Return -1 to signify an error
    } else if (argc > 2) {
        printf("\nPlease make sure that you do not have spaces between the terms of your mathematical expression.\nEven though the Text-To-Math library can handle spaces, the terminal cannot.\n");
        return -1;  // Return -1 to signify an error
    }

    // Get the result from the Text-To-Math library
    float result = textCalc(argv[1]);

    // Display the result
    printf("\nSolution: %.2f\n", result);

    // End the program
    return 0;
}