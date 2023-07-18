#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../textMath.h"

int main() {
    printf("\nWelcome! Thank you for trying out Text-To-Math program.\nPlease enter a mathematical expression below!\nCurrently the character limit is 225 character...\n\n");
    char expression[225];
    fgets(expression, sizeof(expression), stdin);
    
    float solution = textCalc(expression);
    printf("Solution: %.2f\n", solution);

    return 0;
}