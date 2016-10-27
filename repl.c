#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdint.h>
#include<repl.h>
#include<reader.h>
#include<value.h>

void quit() /* write error message and quit */
{
    fprintf(stderr, "memory exhausted\n");
    exit(1);
}

char* getInput() {
    int max = 20;
    char* input = malloc(max); // allocate buffer
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
            input = realloc(input, max); /* get a new and larger buffer */
            if (input == 0) quit();
        }
        i++;
    }

    return input;
}

int runRepl() {
    printf("Welcome to the Clocure REPL, enter your input below:\n");
    char* replInput;
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

        char* inputStart = replInput;

        while (strcmp(replInput, "") != 0) {
            replInput = readValue(replInput, parsedValue);
            printf("%s\n", toString(parsedValue));

            freeValueContents(parsedValue);

        }

        free(inputStart);
    }

    return 0;
}
