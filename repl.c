#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdint.h>
#include<repl.h>
#include<parser.h>
#include<value.h>

void quit() /* write error message and quit */
{
    fprintf(stderr, "memory exhausted\n");
    exit(1);
}

uint8_t* getInput() {
    int max = 20;
    uint8_t* input = (uint8_t*)malloc(max); // allocate buffer
    if (input == 0) quit();

    int i = 0;
    while (1) {
        int c = getchar();
        if (c == '\n' || c == EOF) { // at end, add terminating zero
            input[i] = 0;
            break;
        }
        input[i] = c;
        if (i == max - 1) { /* buffer full */
            max = max + max;
            input = (uint8_t*)realloc(input, max); /* get a new and larger buffer */
            if (input == 0) quit();
        }
        i++;
    }

    return input;
}

int runRepl() {
    printf("Welcome to the Clocure REPL, enter your input below:\n");
    uint8_t* replInput;
    // check memory was successfully allocated
    Value* parsedValue = malloc(sizeof(Value));

    while(1) {
        printf("#> ");
        replInput = getInput();
        if (strcmp(replInput, "exit") == 0) {
            break;
        }
        else if(strcmp(replInput, "") == 0) {
            continue;
        }

        parseValue(replInput, parsedValue);
        printf("%s\n", toString(parsedValue));

        free(replInput);
    }

    return 0;
}
