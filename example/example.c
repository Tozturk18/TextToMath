#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../textMath.h"

char* anan(char* str) {

    
    char temp[225];
    strcpy(temp, str);

    char* first = strchr(temp, '(') + 1;
    char* last = strrchr(temp, ')');
    *last = '\0';

    printf("\nfirst: %s\n", first);

    return first;
}

int main() {
    printf("\nWelcome! Thank you for trying out Text-To-Math program.\nPlease enter a mathematical expression below!\nCurrently the character limit is 225 character...\n\n");
    char expression[225];
    fgets(expression, sizeof(expression), stdin);
    
    float solution = textCalc(expression);
    printf("Solution: %.2f\n", solution);

    /*char stupid[225] = "2-((2+2+2)*(2+2))*2";

    char* first = anan(stupid);

    printf("\nStupid: %s, first: %s\n", stupid, first);*/

    return 0;
}