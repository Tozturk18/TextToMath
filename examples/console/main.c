/**
 * @file main.c
 * @brief Main program for interactive console calculator.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mathParser.h"

#define MAX_INPUT_LENGTH 512
#define MAX_RESULT_LENGTH 64 // For formatted scientific output

int main() {
    char input[MAX_INPUT_LENGTH];
    char result_str[MAX_RESULT_LENGTH];

    printf("Welcome to C Calculator! 🧮\n");
    printf("Type your equation below or 'exit' to quit.\n");

    while (1) {
        printf("\n> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break; // EOF or error
        }

        // Remove trailing newline
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }

        // Check for exit
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // Call textCalcString from mathParser.h
        if (textCalcString(input, result_str, sizeof(result_str))) {
            printf("= %s\n", result_str);
        } else {
            printf("Error: Could not compute result.\n");
        }
    }

    return 0;
}
