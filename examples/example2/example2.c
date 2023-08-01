#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../textMath.h"

int main(int argc, char *argv[]) {

    // Fail Safe
    if (argc < 2) {
        printf("\nPlease input a mathematical expression to run this program.\n");
        return 0;
    } else if (argc > 2) {
        printf("\nPlease make sure that you do not have spaces between the terms of your mathematical expression.\nEven though the Text-To-Math library can handle spaces, the terminal cannot.\n");
        return 0;
    }

    // Get the result from the Text-To-Math library
    float result = textCalc(argv[1]);

    // Display the result
    printf("\nSolution: %.2f\n", result);

    // End the program
    return 0;
}